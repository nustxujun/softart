# Development Planning #



# 0.6 #

Release Data: June 2014

  * API
    * Try to support Direct3D API via an UMD wrapper.

  * Platform:
    * ~~GCC support on Linux~~
    * LLVM upgrade to ~~3.4 or~~ 3.5

  * Shader:
    * ~~Pixel shader will works on 2x2 quad~~
    * support keyword 'register'
    * Full operators/intrinsic support for pixel shader
    * Improve name of intermediate variable.
    * Maybe we have a new compiler front-end.

  * Pipeline:
    * Shader, shims, input assembler could be cached.
    * Support more interpolation method.
    * Alpha to Coverage

  * Shims and interpolator:
    * Interpolation method full support
    * Data matching & copy: vs\_output -> pixel shader
    * Data matching & copy: vertex shader -> vs\_output

# Future #

Following features need to be discussed:
  * Blend shader integrating
  * Shader Model 4.0
  * Geometry Shader
  * Better MSAA
  * JITed input assembler
  * JITed VS->PS shim (includes interpolator)