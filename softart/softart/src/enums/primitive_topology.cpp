/**************************
NEVER CHANGE THIS FILE MANUALLY!

This File Was Generated By enums_gen.py Automatically.
************************/

#include "../../include/enums/primitive_topology.h"

#include "eflib/include/eflib.h"

#ifdef _DEBUG
std::set<int>& primitive_topology::get_primitive_topology_table()
{
	static std::set<int> ret;
	return ret;
}
#endif

primitive_topology::primitive_topology(int v):val(v)
{
#ifdef _DEBUG
	if(get_primitive_topology_table().find(v) != get_primitive_topology_table().end()) {
		custom_assert(false, "");
	} else {
		get_primitive_topology_table().insert(v);
	}
#endif
}

primitive_topology primitive_topology::cast(int val)
{
	#ifdef _DEBUG
	if(get_primitive_topology_table().find(val) == get_primitive_topology_table().end()){
		custom_assert(false, "");
		return primitive_topology(0);
	}
	#endif
	return primitive_topology(val);
}

const primitive_topology primitive_topology::invalid(-1);
const primitive_topology primitive_topology::line_list(0);
const primitive_topology primitive_topology::line_strip(1);
const primitive_topology primitive_topology::triangle_list(2);
const primitive_topology primitive_topology::triangle_fan(3);
const primitive_topology primitive_topology::triangle_strip(4);
const primitive_topology primitive_topology::max(5);
