/**
 * Description:  Platform independent SIMD abstractions
 * Author:       Alicia Amarilla (smushyaa@gmail.com)
 * File Created: March 06, 2023
 * Notes:        set SMUSHY_SIMD_WIDTH to 1, 4, 8
 *               1 == scalar, 4 == SSE4/NEON, 8 == AVX
 *               Default: 1
 *               otherwise uses scalar operations
*/
#if !defined(SMUSHY_SIMD_ABS)
#define SMUSHY_SIMD_ABS

#include "smdef.h"

#if !defined(SMUSHY_SIMD_WIDTH) 
    #define SMUSHY_SIMD_WIDTH 1
#endif

#if defined(SM_ARCH_X86)
    #if SMUSHY_SIMD_WIDTH >= 4
        typedef __attribute((vector_size(16))) float __m128;
    #endif
    #if SMUSHY_SIMD_WIDTH >= 8
        typedef __attribute((vector_size(32))) float __m256;
    #endif
#endif // simd::x86

#if defined(__cplusplus)
namespace smath {

namespace simd {
#endif // c++

/// four-wide floating-point vector
typedef struct lane4f_t {
    union {
        f32 value[4];
        struct { f32 a, b, c, d; };

    #if defined(SM_CURRENT_PLATFORM_X86) && SMUSHY_SIMD_WIDTH >= 4
        __m128 simd;
    #endif // x86 SSE
    };

#if defined(__cplusplus)

    f32& operator[](u32 index);
    f32  operator[](u32 index) const;

    lane4f_t& operator+=( const lane4f_t& rhs );
    lane4f_t& operator-=( const lane4f_t& rhs );
    lane4f_t& operator*=( const lane4f_t& rhs );
    lane4f_t& operator/=( const lane4f_t& rhs );

#endif // c++
} lane4f_t;

#if defined(__cplusplus)
    lane4f_t operator+( const lane4f_t& lhs, const lane4f_t& rhs );
    lane4f_t operator-( const lane4f_t& lhs, const lane4f_t& rhs );
    lane4f_t operator*( const lane4f_t& lhs, const lane4f_t& rhs );
    lane4f_t operator/( const lane4f_t& lhs, const lane4f_t& rhs );
#endif

/// set four-wide vector components
inline lane4f_t lane4f_set( f32 a, f32 b, f32 c, f32 d );
/// set four-wide vector components to the same value
inline lane4f_t lane4f_set_scalar( f32 scalar );
/// set four-wide vector components to zero
inline lane4f_t lane4f_set_zero();
/// load components for four-wide vector from array
inline lane4f_t lane4f_load( const f32* load_array );
/// add four-wide vectors
inline lane4f_t lane4f_add( lane4f_t lhs, lane4f_t rhs );
/// subtract four-wide vectors
inline lane4f_t lane4f_sub( lane4f_t lhs, lane4f_t rhs );
/// multiply four-wide vectors
inline lane4f_t lane4f_mul( lane4f_t lhs, lane4f_t rhs );
/// divide four-wide vectors
inline lane4f_t lane4f_div( lane4f_t lhs, lane4f_t rhs );
/// sqrt four-wide vector components
inline lane4f_t lane4f_sqrt( lane4f_t x );
/// store four-wide vector components in array
inline void lane4f_store( lane4f_t registers, f32* store_array );

// struct lane8f {
//     union {
//         struct { f32 a, b, c, d, e, f, g, h; };
// #if defined(SMUSHY_SIMD_ENABLED)
//
// #if defined(SMUSHY_X86_64_PLATFORM)
//         __m256 simd;
// #endif // simd::x86
//
// #endif // simd
//     };
//
//     lane8f();
//     lane8f( f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h );
//     lane8f( f32 scalar );
//     lane8f( const f32* eight_wide_array );
//
//     f32& operator[]( u32 index );
//     f32  operator[]( u32 index ) const;
//     lane8f& operator+=( const lane8f& rhs );
//     lane8f& operator-=( const lane8f& rhs );
//     lane8f& operator*=( const lane8f& rhs );
//     lane8f& operator/=( const lane8f& rhs );
// };
// lane8f operator+( const lane8f& lhs, const lane8f& rhs );
// lane8f operator-( const lane8f& lhs, const lane8f& rhs );
// lane8f operator*( const lane8f& lhs, const lane8f& rhs );
// lane8f operator/( const lane8f& lhs, const lane8f& rhs );
// lane8f sqrt( lane8f x );
// void store( f32* eight_wide_array, lane8f registers );
// lane4f extract_high( lane8f a );
// lane4f extract_low( lane8f a );
//

#if defined(__cplusplus)
} // namespace smath::simd

} // namespace smath
#endif // c++

#endif
