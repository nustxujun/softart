# Change Logs #



# 0.5.7 (Dec 22, 2014) #
  * Feature and improvements
    * **New sample framework is available.** Playback, interactive, benchmark and testing support are integrated to one framework
    * Improved UMD device
    * Developing register-file based shader compiler and runtime
    * Introduced C++ 11 features (lambda and for-each) to replace boost features
    * Simplified unit tests files for shader testing
    * Renamed robust\_test to death\_test
    * Refactor fixed\_string to make it simpler
    * Ported sasl enums to C++ 11 enums
    * Remove unused WTL code
    * Added constants for indicating compilation configuration.

  * Bug fixing
    * Remove unused code for old vertex\_shader\_unit.
    * Fixed align\_free crash while pointer is null.
    * Fixed an crash error in d3d11\_swap\_chain deconstructor while present has not been called before release.
    * Fixed Font crash while msyh.ttc is not existed on system
    * Fixed performance issue while converting rgba8 to bgra8
    * Now render\_core returns immediately if color targets and DS target are all none

# 0.5.6 (Jun 05, 2014) #
  * Feature and improvements
    * **Rasterizer/Pixel shader/Sample rendering are working on quad(2x2)**
    * **Add two new vertex cache algorithm, and common vertex cache code was extracted to vertex\_cache\_impl**
    * Remove old vertex\_shader\_unit. Now vertex shader always use host.
    * Add time stamp profiling into pipeline
    * **New benchmark framework**
    * Benchmark could generate detailed performance report as JSON format

  * Optimization: **27% for Sponza and 6.6% for complex mesh**
    * geom\_setup\_engine are shared between draw calls
    * Add fetch3 to reduce fetch function called.
    * **New vertex cache algorithm to reduce time of vertex gathering.**
    * Eliminated unused malloc/free in geom\_setup\_engine.
    * For early-z test, depth-test-write are executed together.

  * Bug fix
    * Fixed interpolation error in lerp\_n.
    * Fixed backend\_input\_pixel counter.
    * LoD could be shared in quad pixels in cpp shader.
    * Host will return null pointer when vertex shader is not set.
    * Fixed bug of early-z condition computation.

# 0.5.5 (May 06, 2014) #
  * Building and deployment
    * **Supported platforms changed:**
      * vs2012 or higher;
      * gcc 4.7 or higher;
    * **Support MinGW on Windows;**
    * **Support GCC on Linux;**
    * Boost building parameters changed for cross platform support.
    * SCL macros are moved to CMake files.

  * Third-parties
    * **LLVM upgraded to 3.4.**
    * LLVM-boost workaround code is removed.

  * Optimization
    * **Performance improved 60% - 70%**
    * Removed duplicated triangle info computation.
    * Add quick test for clipper.
    * interpolation function works on quad to reduce multiply ops.
    * c++ pixel shader
      * has quad info to instead triangle info.
      * ddx/ddy is computed by subtraction directly.
      * since step-subtraction method for ddx/ddy is removed, related functions are removed also.
    * removed unused vso operators.
    * optimized derivative computation by edge.
    * Reused transformed verts pool in default\_vertex\_cache.
    * move front\_face from vso to triangle\_ctx.
    * vso viewport transform are executed parallel.

  * Refactor
    * Refactor file organization of shader/shader\_regs/shader\_regs\_op
    * cube map implementation was changed.
    * interfaces of texture/sampler/surface have been changed.

# 0.5.4 (Dec 30, 2013) #
  * Feature
    * **ESM-based Shadow Map demo and stencil based mirror/reflect demo;**
    * **MinGW and MinGW64 were supported;**
    * **Depth and stencil can be cleaned separately;**
    * Pipeline could works with DS target only;
    * Now pixel shader could overwrite depth(PS depth output);

  * Refactor
    * **Texture is not an available resource for shader, but sampler holds texture and could be used in shader.**
    * **All third-party libraries is intergated as source code and CMake was added to them.**
    * **Map/Unmap is belongs to renderer but not resource for synchronization.**
    * Due to C++11/boost.locale, implementation of multibyte-unicode conversation was improved.
    * Mask of swizzle/write mask is not uint32 any longer. elem\_indexes is introduced thus mask is strong-typed.
    * Improve build scripts and CMake files for:
      * Executable of build/make/compiler toolchains detection is supported or improved.
      * Clean variable names of CMake.
      * DirectX SDK will not be used in VS2012 or later.
      * Report and interrupt immediately once error occurs.
      * Code of project configuring and building were refractored.
    * Cleanup code of texture input/output.

  * Bug fixes
    * **Fixed a layout computation bug for "float4 main(): SV\_Position"**
    * **Fixed count\_bits functions.**
    * **Buffer allocation is 16-bytes aligned.**
    * **Fixed error that culled pixel rendered to frame buffer.**
    * Fixed default Z-range in pipeline.
    * Fixed a bugs of GL swap chain.
    * Fixed a potential issues in member of m128 settings.
    * Fixed bugs caused by incorrect cache in shims.
    * Fixes batch of bugs in shader compiler.
    * Fixed windows kit and d3d detection.

# 0.5.3 (Sep 10, 2013) #
  * **Refactor pipeline!**
    * All commands (draw, clear, asynchoronous begin/end) were treated as _commands_. Every command has a immutable _state object_.
    * Old _renderer\_impl_ was removed.
    * _render\_core_ was added to execute _command_ .
    * New _renderer\_impl_ is designed to set or get status from state object.
    * Renderers were refactored to _async\_renderer_ and _sync\_renderer_. They are all based on _renderer\_impl_ and _render\_core_
    * _async\_renderer_ holds an asynchronized queue for executing _commands_ asynchronized.
    * _Clipper_ is stateless between primitives.
    * Add new stage _geom\_setup\_engine_ to process IA and clipping. Its output is primitives for rasterizer.
    * Add _thread\_context_ to pipeline. It will make code more readable when function is parallel called.
    * Interpolation method was changed to base of total derivative but not integral any more.
    * Replace "presenters" with swap chain.
  * Third-party and tool-chain changes
    * Upgraded LLVM to 3.3.
    * Only support VS2010 and later.
    * Remove dependencies of GDI+ and D3DX.
  * New features
    * Support performance counter.
    * Support early-z (per sample).
  * Bug fixes and misc
    * Compact Sponza scene file by collapse vertexes. It will make Sponza demo ~30% faster.
    * Fixed bugs of default\_vso2reg.
    * Replace macro guard with pragma.
    * Now set\_variable of cpp shader is async-safey.

# 0.5.2 (Feb 10, 2013) #
  * **蛇年新春快乐！**
  * **Optimized performance of interpolator ~25% - 50%.**
  * **New architecture of shader is applied to Vertex Shader.**
  * **Visual Studio 2012 have been supported offically.**
  * **The minimum requirement of boost is 1.53.0 for now.**
  * Remove some implementations from eflib when it is supported by boost.
  * Build problems caused by DX SDK environment are fixed.
  * dynamic\_lib: Shared library will be free when reference count is 0.
  * Some bugs fixed.

# 0.5.1 (Dec 28, 2012) #
  * **The last update of SALVIA in 2012. Happy new year!**
  * **Optimized performance of parser and semantic analyzer. The performance is increased 70% in debug mode and about 150% in release mode.**
  * **New architecture of code generation which support pixel shader much better than old.**
  * **ABI of data transferred between pipeline and pixel shader was changed.**
  * Code clean.
  * Explicit cast operator has been supported.
  * Bug fixes:
    * _fast\_roundi_ always returns 0 when /fp:fast is enabled on MSVC.
    * Add SEH guard to preventing JIT error stops the whole test.
    * Add cast\_f2i.
    * All comments are in English for now.

# 0.3.6 (Sep 12, 2012) #
  * **Now API are called asynchronized.**
  * Add inference for l-value and r-value.
  * Fixed a bug that input data will be modified if semantic variable have been assigned in vertex shader.
  * Fixed threadpool compilation error when Boost 1.51 is used.
  * Refactor code generation.
  * Now LLVM code generator is the only valid code generator.
  * Fixed some compilation error and run-time bugs.
  * Add "--clean" option to build\_all.py to support clean build.

# 0.3.5 (Aug 21, 2012) #
  * **Add 28 intrinsic support to vertex shader.**
  * **Support anisotropic texture filter and added an demo.**
  * Integrated FreeType2, added font drawing code and demo for it.
  * Re-organize documentations.

# 0.3.4 (Jul 17, 2012) #
  * **Sorry I am late!**
  * **Add 3 IMPORTANT samples!**
    * Skinning Mesh
    * Multiple stream based vertex blending
    * Terrain Rendering based on Vertex Texture Fetching
  * **Shader compiling was at least 11% faster than old one.**
  * Support simple COLLADA model.
  * Context of semantic analysis was changed.
  * Refactor code about code generation.

# 0.3.3 (May 08, 2012) #
  * **All operators enabled for scalar, vector and matrix in Vertex Shader.**
  * **Intrinsics now support matrix parameters.**
  * **Add new intrinsics support to Vertex Shader: _sin/cos/tan/asin/acos/atan/ceil/floor/log/log2/log10/rsqrt/exp2/ldexp_.**
  * Support vector and matrix per-element implicit cast.
  * Add _system include_ and _include_ search path.
  * Add missing LLVM files to fix compiling bugs.
  * Port eflib matrix and vector to generic version.
  * Refactor code generators and external intrinsics machanism.

# 0.3.2 (Apr 20, 2012) #
  * **Add intrinsics _abs_, _any_, _all_, _asint_, _asuint_, _asfloat_,  _distance_, _dst_, _exp_, _fmod_, _lerp_, _radians_, _degrees_ support to vertex shader and general for scalar and vector.**
  * **Add operators _div_, _mod_, _bitwise and_, _bitwise or_, _logic and_, _logic or_, _comparison operators_, _shift operators_ support to vertex shader and general for scalar and vector.**
  * **Add include and virtual include to SASL. Didn't support system include search path yet.**
  * Handling more errors in semantic.
  * Bool operators are no longer short-evaluation. Only logic bool operator for scalar in general is shortly.
  * Project _host_ now depend on _driver_.
  * Multiple swizzle/write-mask now works.
  * Now defining variable in loop is no longer cause a stack overflow.
  * Implicit cast is executabe when it is needed in before call.

# 0.3.1 (Mar 30, 2012) #
  * **Add error handling for tokenizer and parser**
  * **Partially support error report for semantic analysis**
  * Split sasl\_compiler to sasl\_driver and sasl\_command.
    * sasl\_driver is facade of compiler classes.
    * sasl\_command is compiler as command line executable file .
  * Now jit test is based on driver.
  * Add document <SASL Developer Toturial> in Chinese.
  * Add CMake Project Group support.
  * Add emit\_abs for SISD.
  * Fixed a false error report of 'no overloads of operator '=''
  * Fixed presenter name bug in ObjLoader when DX is enabled.
  * Fixed cmake generator error when vs2005/2008 used.

# 0.3 (Mar 06, 2012) #
  * **Add tex2D support to pixel shader.**
  * Fixed a crash bug on ntx64 release without debugger.
  * Add constructors to builtin type.

# 0.2.6 (Mar 01, 2012) #
  * **Integrated Pixel Shader to Pipeline!**
  * Fixed jittering on Sponza when grand band is enabled.
  * Default clip planes is reduced to 2 faces.
  * Scanline based rasterizer was removed, now Larrabee rasterizer is as default.

# 0.2.5 (Feb 24, 2012) #
  * Pixel Shader now support **for**, **while** and **do-while** loop.
  * Add **ddx** and **ddy** support.
  * Add texture sampler prototype to pixel shader.
  * Optimized rasterizer.

# 0.2.4 (Feb 11, 2012) #
  * **Now pixel shader of SASL support if-statement via execution mask.**
  * Fix a bug that cmake cannot be customized.
  * Fix ambiguous overloads bug caused by vector1.
  * Fix a bug of memory alignment error in jit test.
  * Add a prototype of SSA analyser, in future it is used for optimization.

# 0.2.3 (Jan 06, 2012) #

  * **Now DirectX depenencies is not necessary of SALVIA any more.**
  * **Visual C++ Express now could be used to compile SALVIA. (x86 32-bit only)**
  * Added intrinsics 'dot', 'cross' and 'sqrt' support to pixel shader.
  * Fixed unaligned memory bug because asm generated by MSVC x86 is not keep the stack pointer 16 bytes aligned.

# 0.2.2 (Dec 25, 2011) #

  * **Added ALL-IN-ONE build script.**
  * **Finished prototype of pixel shader compiler.**
    * Implemented memory layout of parameters and variables of pixel shader.
    * Added operators '+', '-', '`*`' support to scalar and vector on SIMD mode.
    * Added swizzle and write mask support to vector on SIMD mode.
  * Removed pre-built llvm libraries located in 3rd\_party/llvm
  * Moved llvm source code from 3rd\_party/src/llvm to 3rd\_party/llvm
  * Renamed platform name and re-organized build directories.
  * Arranged documents.
  * Added project depenedency to fix test installation.
  * Now vertex output data is 16 bytes aligned.
  * Members of vertex output data now confirms C member alignment.

# 0.2.1 (Nov 30, 2011) #

  * Added switch-case support to vertex shader
  * Integer and floating point now could be casted to boolean implicit.

# 0.2 (Nov 25, 2011) #

  * Fixed unaligment memory access exception by SSE instruction while platform is x64 or SSE is enabled on x86-32.
  * New features have been added to vertex shader:
    * if-then-else, while, for statements.
    * break and continue statements
    * intrinsics support: mul, cross, sqrt and dot
    * SSE acceleration on x86 and x64
  * Refactored code generation in SASL.
  * Regression test framework and tests for Just-In-Time.

# 0.1.1 (Jul 11, 2011) #

  * Add new demo _Sponza_.
  * Add 32-bit index support for wavefront obj.
  * Fixed a mipmap computation bug.
  * Fixed a culling bug.

# 0.1.0 (Jun 01, 2011) #

  * **Project configuration and management:**
    * **Code repository now changed to Mercurial.**
    * **Rename _SoftArt_ to _SALVIA_.**
    * **Logo of SALVIA is published.**
    * Format of check in log now obey google issue tracker's demands.
    * **Added unit test and auto test system.**
    * Merge LLVM 2.9 source code to repo.
    * Fixed some compatibility bugs between LLVM and Boost.
    * Boost now requires 1.44 or later.
    * Add a tool for statistic code lines.
    * Documents were updated.
  * **Graphis:**
    * **Add an OpenGL based presenter.**
    * Optimize subdivision based rasterizer.
    * Changed namespace and organization of EFLIB.
    * **Add centroid sampling support.**
    * **Add 2x and 4x MSAA support.**
  * **SASL:**
    * Add a new combinator based parser to replace Boost.Spirit for reduce compiling time and object file size.
    * Add preprocessor based on Boost.Wave.
    * Add name mangling and overloading.
    * Finished shader ABI design.
    * Add JIT support.
    * Cross compilers is supported better.
    * Add CL styled compiler.
    * Add a reusable multi-targets compiler framework.
    * Add regression test to compiler.
    * Support following language features:
      * Scalar types, vector types, structures
      * Sequential statements.
      * Function declaration and definition.
      * Arithmentic operators and member operators(.)
      * Swizzle and mask.

# 0.0.1 (Aug 23, 2010) #

  * Full render pipeline.
  * New Larrabee like rasterizer is enabled and optimized.
  * Optimized texture sampling code by SSE.
  * Added shader ABI specification.
  * Protype of parser, semantic analyzer and code generator of shader compiler works now.