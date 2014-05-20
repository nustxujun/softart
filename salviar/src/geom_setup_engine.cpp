#include <salviar/include/geom_setup_engine.h>

#include <salviar/include/clipper.h>
#include <salviar/include/thread_context.h>
#include <salviar/include/thread_pool.h>
#include <salviar/include/vertex_cache.h>
#include <salviar/include/shader_regs.h>

#include <eflib/include/math/math.h>
#include <eflib/include/platform/cpuinfo.h>

using boost::shared_array;
using boost::atomic;
using eflib::clampss;

int const GEOMETRY_SETUP_PACKAGE_SIZE = 8;
int const COMPACT_CLIPPED_VERTS_PACKAGE_SIZE = 8;

BEGIN_NS_SALVIAR();

geom_setup_engine::geom_setup_engine():
	ctxt_(NULL),
	clipping_package_count_(0),
	clipped_verts_size_(0),
	thread_count_( eflib::num_available_threads() )
{
}

void geom_setup_engine::execute(geom_setup_context const* ctxt)
{
	ctxt_ = ctxt;

	clip_geometries();
	compact_geometries();
}

void geom_setup_engine::clip_geometries()
{
	clipping_package_count_ = thread_context::compute_package_count(
		ctxt_->prim_count, GEOMETRY_SETUP_PACKAGE_SIZE
		);

	// Initialize resource used by clipper.
	if( clipped_verts_size_ < ctxt_->prim_count * 3 * 3)
	{
		clipped_verts_.reset(new vs_output* [ctxt_->prim_count * 3 * 3]);	// Every triangle can clipped out 3 triangles at most.
		clipped_verts_size_ = ctxt_->prim_count * 3 * 3;
	}
	clipped_package_verts_count_.reset(new uint32_t[clipping_package_count_]);
	
	vso_pools_.reset(new vs_output_pool[thread_count_]);
	for(size_t i = 0; i < thread_count_; ++ i)
	{
		vso_pools_[i].reserve(ctxt_->prim_count * 4, 16);	// Two clipping plane. In extreme case, there are 4 verts generated by clipper.
	}

	// Execute threads
	execute_threads(
		[this] (thread_context const* thread_ctx) -> void { this->threaded_clip_geometries(thread_ctx); },
		ctxt_->prim_count, GEOMETRY_SETUP_PACKAGE_SIZE
		);
}

void geom_setup_engine::threaded_clip_geometries(thread_context const* thread_ctx)
{
	clip_context clip_ctxt;
	clip_ctxt.vert_pool	= &(vso_pools_[thread_ctx->thread_id]);
	clip_ctxt.vso_ops	= ctxt_->vso_ops;
	clip_ctxt.cull		= ctxt_->cull;
	clip_ctxt.prim		= ctxt_->prim;

	clipper clp;
	clp.set_context(&clip_ctxt);

	clip_results clip_rslt;

    uint32_t clip_invocations = 0;

	thread_context::package_cursor cur = thread_ctx->next_package();
	while( cur.valid() )
	{
		std::pair<int32_t, int32_t> prim_range = cur.item_range();

		clip_rslt.clipped_verts		  = clipped_verts_.get() + prim_range.first * 9;
		uint32_t& clipped_verts_count = clipped_package_verts_count_[ cur.package_index() ];

		clipped_verts_count = 0;
		for (int32_t i = prim_range.first; i < prim_range.second; ++ i)
		{
			if (3 == ctxt_->prim_size)
			{
				vs_output* pv[3] =
				{
					&ctxt_->dvc->fetch(i*3+0),
					&ctxt_->dvc->fetch(i*3+1),
					&ctxt_->dvc->fetch(i*3+2)
				};

				// grand band culling
				float const GRAND_BAND_SCALE = 1.2f;
				eflib::vec4 t0 = clampss(eflib::vec4(-pv[0]->position().x(), -pv[0]->position().y(), pv[0]->position().x(), pv[0]->position().y()) - pv[0]->position().w() * GRAND_BAND_SCALE, 0, 1);
				eflib::vec4 t1 = clampss(eflib::vec4(-pv[1]->position().x(), -pv[1]->position().y(), pv[1]->position().x(), pv[1]->position().y()) - pv[1]->position().w() * GRAND_BAND_SCALE, 0, 1);
				eflib::vec4 t2 = clampss(eflib::vec4(-pv[2]->position().x(), -pv[2]->position().y(), pv[2]->position().x(), pv[2]->position().y()) - pv[2]->position().w() * GRAND_BAND_SCALE, 0, 1);
				eflib::vec4 t = t0 * t1 * t2;

				if ((0 == t.x()) && (0 == t.y()) && (0 == t.z()) && (0 == t.w()))
				{
                    ++clip_invocations;
					clp.clip(pv, &clip_rslt);

					// Step output to next range, sum total clipped verts count
					clip_rslt.clipped_verts += clip_rslt.num_clipped_verts;
					clipped_verts_count += clip_rslt.num_clipped_verts;
				}
			}
			else if (2 == ctxt_->prim_size)
			{
				assert(false);
			}
		}

		cur = thread_ctx->next_package();
	}

    ctxt_->acc_cinvocations(ctxt_->pipeline_stat, clip_invocations);
}

void geom_setup_engine::compact_geometries()
{
	// Compute compacted address of packages.
	uint32_t* addresses = new uint32_t[clipping_package_count_+1];
	clipped_package_compacted_addresses_.reset(addresses);

	addresses[0] = 0;
	for (int i = 1; i <= clipping_package_count_; ++ i)
	{
		addresses[i] = addresses[i-1] + clipped_package_verts_count_[i-1];
	}
	compacted_verts_.reset(new vs_output*[ addresses[clipping_package_count_] ]);

	// Execute threads for compacting
	execute_threads(
		[this] (thread_context const* thread_ctx) -> void { this->threaded_compact_geometries(thread_ctx); },
		clipping_package_count_, COMPACT_CLIPPED_VERTS_PACKAGE_SIZE
		);
}

void geom_setup_engine::threaded_compact_geometries(thread_context const* thread_ctx)
{
	thread_context::package_cursor current_package = thread_ctx->next_package();

	while ( current_package.valid() )
	{
		std::pair<int32_t, int32_t> compact_range = current_package.item_range();

		for (int32_t i = compact_range.first; i < compact_range.second; ++ i)
		{
			vs_output** compacted_addr	= compacted_verts_.get() + clipped_package_compacted_addresses_[i];
			vs_output** sparse_addr		= clipped_verts_.get() + GEOMETRY_SETUP_PACKAGE_SIZE * i * 9;
			size_t		copy_size		= clipped_package_verts_count_[i] * sizeof(vs_output*);

			memcpy(compacted_addr, sparse_addr, copy_size);
		}

		current_package = thread_ctx->next_package();
	}
}

END_NS_SALVIAR();
