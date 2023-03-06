# smlib - library for use in game development

Includes
- smdef: defines
    - platform defines
    - typedefs for integral types
    - integral type constants
    - compiler defines
    - compiler independent export/import macro
    - compiler independent panic
- smlogging: logging functions
    - colored printf function that's easy to extend with macros
    - macros for info/debug/warn/error
    - macros for assertions
- smath: C++ math functions and types
    - trig functions
    - rounding
    - random number generators
    - lerp/invlerp/slerp
    - types: int/float/bool vec2/3/4, mat2/3/4, quaternion
- smsimd: platform independent simd abstraction (WIP)
    - lane4/lane8 vector types
    - support for SSE/AVX on x86 and NEON on arm
    - unified API for C and C++
- smcol: collections
    - list: heap allocated dynamically sized array
    - string: heap allocated dynamically sized string
    - optional: define optional types with a macro
- smio: platform independent input/output (WIP)

