/**
 * Description:  
 * Author:       Alicia Amarilla (smushyaa@gmail.com)
 * File Created: March 06, 2023
*/
#include "smsimd.h"

// TODO(alicia): ARM NEON
// TODO(alicia): x86 AVX

#if SMUSHY_SIMD_WIDTH != 1
    #if defined(SM_ARCH_X86)
        #include <immintrin.h>
    #elif defined(SM_ARCH_ARM)
        #include <arm_neon.h>
    #endif
#endif

#if defined(SM_COMPILER_MSVC)
    #include <math.h>
    #define __builtin_sqrtf sqrtf
#endif

#if defined(__cplusplus)
    namespace smath {
    namespace simd  {
#endif // c++

// scalar
#if SMUSHY_SIMD_WIDTH == 1

lane4f_t lane4f_set( f32 a, f32 b, f32 c, f32 d ) {
    lane4f_t result;
    result.a = a;
    result.b = b;
    result.c = c;
    result.d = d;
    return result;
}
lane4f_t lane4f_set_scalar( f32 scalar ) {
    lane4f_t result;
    result.a = scalar;
    result.b = scalar;
    result.c = scalar;
    result.d = scalar;
    return result;
}
lane4f_t lane4f_set_zero() {
    lane4f_t result;
    result.a = 0;
    result.b = 0;
    result.c = 0;
    result.d = 0;
    return result;
}
lane4f_t lane4f_load( const f32* load_array ) {
    lane4f_t result;
    result.a = load_array[0];
    result.b = load_array[1];
    result.c = load_array[2];
    result.d = load_array[3];
    return result;
}
lane4f_t lane4f_add( lane4f_t lhs, lane4f_t rhs ) {
    lane4f_t result;
    result.a = lhs.a + rhs.a;
    result.b = lhs.b + rhs.b;
    result.c = lhs.c + rhs.c;
    result.d = lhs.d + rhs.d;
    return result;
}
lane4f_t lane4f_sub( lane4f_t lhs, lane4f_t rhs ) {
    lane4f_t result;
    result.a = lhs.a - rhs.a;
    result.b = lhs.b - rhs.b;
    result.c = lhs.c - rhs.c;
    result.d = lhs.d - rhs.d;
    return result;
}
lane4f_t lane4f_mul( lane4f_t lhs, lane4f_t rhs ) {
    lane4f_t result;
    result.a = lhs.a * rhs.a;
    result.b = lhs.b * rhs.b;
    result.c = lhs.c * rhs.c;
    result.d = lhs.d * rhs.d;
    return result;
}
lane4f_t lane4f_div( lane4f_t lhs, lane4f_t rhs ) {
    lane4f_t result;
    result.a = lhs.a / rhs.a;
    result.b = lhs.b / rhs.b;
    result.c = lhs.c / rhs.c;
    result.d = lhs.d / rhs.d;
    return result;
}
lane4f_t lane4f_sqrt( lane4f_t x ) {
    lane4f_t result;
    result.a = __builtin_sqrtf(x.a);
    result.b = __builtin_sqrtf(x.b);
    result.c = __builtin_sqrtf(x.c);
    result.d = __builtin_sqrtf(x.d);
    return result;
}
void lane4f_store( lane4f_t registers, f32* store_array ) {
    store_array[0] = registers.a;
    store_array[1] = registers.b;
    store_array[2] = registers.c;
    store_array[3] = registers.d;
}

#endif // scalar

// SSE
#if defined(SM_ARCH_X86) && SMUSHY_SIMD_WIDTH == 4

    lane4f_t lane4f_set( f32 a, f32 b, f32 c, f32 d ) {
        lane4f_t result;
        result.simd = _mm_setr_ps( a, b, c, d );
        return result;
    }
    lane4f_t lane4f_set_scalar( f32 scalar ) {
        lane4f_t result;
        result.simd = _mm_set1_ps( scalar );
        return result;
    }
    lane4f_t lane4f_set_zero() {
        lane4f_t result;
        result.simd = _mm_setzero_ps();
        return result;
    }
    lane4f_t lane4f_load( const f32* load_array ) {
        lane4f_t result;
        result.simd = _mm_load_ps( load_array );
        return result;
    }
    lane4f_t lane4f_add( lane4f_t lhs, lane4f_t rhs ) {
        lane4f_t result;
        result.simd = _mm_add_ps( lhs.simd, rhs.simd );
        return result;
    }
    lane4f_t lane4f_sub( lane4f_t lhs, lane4f_t rhs ) {
        lane4f_t result;
        result.simd = _mm_sub_ps( lhs.simd, rhs.simd );
        return result;
    }
    lane4f_t lane4f_mul( lane4f_t lhs, lane4f_t rhs ) {
        lane4f_t result;
        result.simd = _mm_mul_ps( lhs.simd, rhs.simd );
        return result;
    }
    lane4f_t lane4f_div( lane4f_t lhs, lane4f_t rhs ) {
        lane4f_t result;
        result.simd = _mm_div_ps( lhs.simd, rhs.simd );
        return result;
    }
    lane4f_t lane4f_sqrt( lane4f_t x ) {
        lane4f_t result;
        result.simd = _mm_sqrt_ps( x.simd );
        return result;
    }
    void lane4f_store( lane4f_t registers, f32* store_array ) {
        _mm_store_ps( store_array, registers.simd );
    }

#endif // SSE

// AVX
#if defined(SM_ARCH_X86) && SMUSHY_SIMD_WIDTH == 8



#endif // AVX

// C++ operator overloads
#if defined(__cplusplus)

    f32& lane4f_t::operator[](u32 index) { return this->value[index]; }
    f32  lane4f_t::operator[](u32 index) const { return this->value[index]; }

    lane4f_t& lane4f_t::operator+=( const lane4f_t& rhs ) {
        *this = lane4f_add( *this, rhs );
        return *this;
    }

    lane4f_t& lane4f_t::operator-=( const lane4f_t& rhs ) {
        *this = lane4f_sub( *this, rhs );
        return *this;
    }

    lane4f_t& lane4f_t::operator*=( const lane4f_t& rhs ) {
        *this = lane4f_mul( *this, rhs );
        return *this;
    }

    lane4f_t& lane4f_t::operator/=( const lane4f_t& rhs ) {
        *this = lane4f_div( *this, rhs );
        return *this;
    }

    lane4f_t operator+( const lane4f_t& lhs, const lane4f_t& rhs ) {
        return lane4f_add( lhs, rhs );
    }
    lane4f_t operator-( const lane4f_t& lhs, const lane4f_t& rhs ) {
        return lane4f_sub( lhs, rhs );
    }
    lane4f_t operator*( const lane4f_t& lhs, const lane4f_t& rhs ) {
        return lane4f_mul( lhs, rhs );
    }
    lane4f_t operator/( const lane4f_t& lhs, const lane4f_t& rhs ) {
        return lane4f_div( lhs, rhs );
    }

#endif

#if defined(__cplusplus)
    } // namespace smath::simd
    } // namespace smath
#endif // c++

