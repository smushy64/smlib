/**
 * Description:  C++ Math Library
 * Author:       Alicia Amarilla (smushy) 
 * File Created: February 06, 2023
 * Includes:     <math.h> ONLY WITH MSVC COMPILER
*/
#include "smath.hpp"

#if defined(SMUSHY_SIMD_ENABLED)

    #if defined(SMUSHY_X86_64_PLATFORM)

    #include <immintrin.h>

    #endif // simd::x86

#endif // simd

#if defined(_MSC_VER)
    #include <math.h>
#endif

namespace smath {

namespace internal {

#if defined(_MSC_VER)

inline f32 _sinf_( f32 x ) {
    return sinf(x);
}
inline f64 _sin_( f64 x ) {
    return sin(x);
}
inline f32 _asinf_( f32 x ) {
    return asinf(x);
}
inline f64 _asin_( f64 x ) {
    return asin(x);
}
inline f32 _cosf_( f32 x ) {
    return cosf(x);
}
inline f64 _cos_( f64 x ) {
    return cos(x);
}
inline f32 _acosf_( f32 x ) {
    return acosf(x);
}
inline f64 _acos_( f64 x ) {
    return acos(x);
}
inline f32 _tanf_( f32 x ) {
    return tanf(x);
}
inline f64 _tan_( f64 x ) {
    return tan(x);
}
inline f32 _atanf_( f32 x ) {
    return atanf(x);
}
inline f64 _atan_( f64 x ) {
    return atan(x);
}
inline f32 _atan2f_( f32 y, f32 x ) {
    return atan2f(y, x);
}
inline f64 _atan2_( f64 y, f64 x ) {
    return atan2(y, x);
}

inline f32 _powf_( f32 base, f32 exponent ) {
    return powf(base, exponent);
}
inline f64 _pow_( f64 base, f64 exponent ) {
    return pow(base, exponent);
}

inline f32 _powif_( f32 base, i32 exponent ) {
    return powi(base, exponent);
}
inline f64 _powi_( f64 base, i32 exponent ) {
    return powi(base, exponent);
}

inline f32 _sqrtf_( f32 x ) {
    return sqrtf( x );
}
inline f64 _sqrt_( f64 x ) {
    return sqrt( x );
}

inline f32 _logf_( f32 x ) {
    return logf( x );
}
inline f64 _log_( f64 x ) {
    return log( x );
}

inline f32 _modf_( f32 numerator, f32 denominator ) {
    return fmodf( numerator, denominator );
}

inline f64 _mod_( f64 numerator, f64 denominator ) {
    return fmod( numerator, denominator );
}

#elif __GNUC__

inline f32 _sinf_( f32 x ) {
    return __builtin_sinf(x);
}
inline f64 _sin_( f64 x ) {
    return __builtin_sin(x);
}
inline f32 _asinf_( f32 x ) {
    return __builtin_asinf(x);
}
inline f64 _asin_( f64 x ) {
    return __builtin_asin(x);
}
inline f32 _cosf_( f32 x ) {
    return __builtin_cosf(x);
}
inline f64 _cos_( f64 x ) {
    return __builtin_cos(x);
}
inline f32 _acosf_( f32 x ) {
    return __builtin_acosf(x);
}
inline f64 _acos_( f64 x ) {
    return __builtin_acos(x);
}
inline f32 _tanf_( f32 x ) {
    return __builtin_tanf(x);
}
inline f64 _tan_( f64 x ) {
    return __builtin_tan(x);
}
inline f32 _atanf_( f32 x ) {
    return __builtin_atanf(x);
}
inline f64 _atan_( f64 x ) {
    return __builtin_atan(x);
}
inline f32 _atan2f_( f32 y, f32 x ) {
    return __builtin_atan2f(y, x);
}
inline f64 _atan2_( f64 y, f64 x ) {
    return __builtin_atan2(y, x);
}

inline f32 _powf_( f32 base, f32 exponent ) {
    return __builtin_powf(base, exponent);
}
inline f64 _pow_( f64 base, f64 exponent ) {
    return __builtin_pow(base, exponent);
}

inline f32 _powif_( f32 base, i32 exponent ) {
    return __builtin_powif(base, exponent);
}
inline f64 _powi_( f64 base, i32 exponent ) {
    return __builtin_powi(base, exponent);
}

inline f32 _sqrtf_( f32 x ) {
    return __builtin_sqrtf( x );
}
inline f64 _sqrt_( f64 x ) {
    return __builtin_sqrt( x );
}

inline f32 _logf_( f32 x ) {
    return __builtin_logf( x );
}
inline f64 _log_( f64 x ) {
    return __builtin_log( x );
}

inline f32 _modf_( f32 numerator, f32 denominator ) {
    return __builtin_fmodf( numerator, denominator );
}

inline f64 _mod_( f64 numerator, f64 denominator ) {
    return __builtin_fmod( numerator, denominator );
}

#else // unknown compiler
#endif

inline f32 degrees_overflow( f32 degrees ) {
    f32 result = degrees;
    if( result < 0.0f ) {
        result += 360.0f;
    }
    if( result > 360.0f ) {
        return _modf_( result, 360.0f );
    } else {
        return result;
    }
}

// TODO(alicia): make sure this is correct
inline f32 signed_angle_to_unsigned( f32 radians ) {
    f32 result = radians;
    while( result < 0.0f ) {
        result += F32::TAU;
    }
    return result;
}

} // namespace smath::internal

namespace simd {

#if defined(SMUSHY_SIMD_ENABLED)

#if defined(SMUSHY_X86_64_PLATFORM)

lane4f::lane4f() : simd( _mm_setzero_ps() ) {}
lane4f::lane4f( f32 a, f32 b, f32 c, f32 d ) : simd( _mm_setr_ps( a, b, c, d ) ) {}
lane4f::lane4f( f32 scalar ) : simd( _mm_set1_ps( scalar ) ) {}
lane4f::lane4f( const f32* four_wide_array ) : simd( _mm_load_ps( four_wide_array ) ) {}
f32& lane4f::operator[]( u32 index ) { return (&a)[index]; }
f32  lane4f::operator[]( u32 index ) const { return simd[index]; }
lane4f& lane4f::operator+=( const lane4f& rhs ) {
    this->simd = _mm_add_ps( this->simd, rhs.simd );
    return *this;
}
lane4f& lane4f::operator-=( const lane4f& rhs ) {
    this->simd = _mm_sub_ps( this->simd, rhs.simd );
    return *this;
}
lane4f& lane4f::operator*=( const lane4f& rhs ) {
    this->simd = _mm_mul_ps( this->simd, rhs.simd );
    return *this;
}
lane4f& lane4f::operator/=( const lane4f& rhs ) {
    this->simd = _mm_div_ps( this->simd, rhs.simd );
    return *this;
}
lane4f sqrt( lane4f x ) {
    x.simd = _mm_sqrt_ps( x.simd );
    return x;
}
void store( f32* four_wide_array, lane4f registers ) {
    _mm_store_ps( four_wide_array, registers.simd );
}

lane8f::lane8f() : simd( _mm256_setzero_ps() ) {}
lane8f::lane8f( f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h )
: simd( _mm256_setr_ps( a, b, c, d, e, f, g, h ) ){}
lane8f::lane8f( f32 scalar ) : simd( _mm256_set1_ps( scalar ) ) {}
lane8f::lane8f( const f32* eight_wide_array ) : simd( _mm256_load_ps( eight_wide_array ) ) {}
f32& lane8f::operator[]( u32 index ) { return (&a)[index]; }
f32  lane8f::operator[]( u32 index ) const { return simd[index]; }
lane8f& lane8f::operator+=( const lane8f& rhs ) {
    this->simd = _mm256_add_ps( this->simd, rhs.simd );
    return *this;
}
lane8f& lane8f::operator-=( const lane8f& rhs ) {
    this->simd = _mm256_sub_ps( this->simd, rhs.simd );
    return *this;
}
lane8f& lane8f::operator*=( const lane8f& rhs ) {
    this->simd = _mm256_mul_ps( this->simd, rhs.simd );
    return *this;
}
lane8f& lane8f::operator/=( const lane8f& rhs ) {
    this->simd = _mm256_div_ps( this->simd, rhs.simd );
    return *this;
}
lane8f sqrt( lane8f x ) {
    x.simd = _mm256_sqrt_ps( x.simd );
    return x;
}
void store( f32* eight_wide_array, lane8f registers ) {
    _mm256_store_ps( eight_wide_array, registers.simd );
}
lane4f extract_high( lane8f a ) {
    lane4f result;
    result.simd = _mm256_extractf128_ps( a.simd, 1 );
    return result;
}
lane4f extract_low( lane8f a ) {
    lane4f result;
    result.simd = _mm256_castps256_ps128( a.simd );
    return result;
}

#endif // x86

#else // simd

lane4f::lane4f() : a(0.0f), b(0.0f), c(0.0f), d(0.0f) {}
lane4f::lane4f( f32 a, f32 b, f32 c, f32 d ) : a(a), b(b), c(c), d(d) {}
lane4f::lane4f( f32 scalar ) : a(scalar), b(scalar), c(scalar), d(scalar) {}
lane4f::lane4f( const f32* four_wide_array )
: a(four_wide_array[0]), b(four_wide_array[1]), c(four_wide_array[2]), d(four_wide_array[3]) {}
f32& lane4f::operator[]( u32 index ) { return (&a)[index]; }
f32  lane4f::operator[]( u32 index ) const { return (&a)[index]; }
lane4f& lane4f::operator+=( const lane4f& rhs ) {
    this->a += rhs.a;
    this->b += rhs.b;
    this->c += rhs.c;
    this->d += rhs.d;
    return *this;
}
lane4f& lane4f::operator-=( const lane4f& rhs ) {
    this->a -= rhs.a;
    this->b -= rhs.b;
    this->c -= rhs.c;
    this->d -= rhs.d;
    return *this;
}
lane4f& lane4f::operator*=( const lane4f& rhs ) {
    this->a *= rhs.a;
    this->b *= rhs.b;
    this->c *= rhs.c;
    this->d *= rhs.d;
    return *this;
}
lane4f& lane4f::operator/=( const lane4f& rhs ) {
    this->a /= rhs.a;
    this->b /= rhs.b;
    this->c /= rhs.c;
    this->d /= rhs.d;
    return *this;
}
lane4f sqrt( lane4f x ) {
    return {
        internal::_sqrtf_( x.a ),
        internal::_sqrtf_( x.b ),
        internal::_sqrtf_( x.c ),
        internal::_sqrtf_( x.d )
    };
}
void store( f32* four_wide_array, lane4f registers ) {
    four_wide_array[0] = registers[0];
    four_wide_array[1] = registers[1];
    four_wide_array[2] = registers[2];
    four_wide_array[3] = registers[3];
}

lane8f::lane8f()
: a(0.0f), b(0.0f), c(0.0f), d(0.0f),
e(0.0f), f(0.0f), g(0.0f), h(0.0f) {}
lane8f::lane8f( f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h )
: a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h) {}
lane8f::lane8f( f32 scalar )
: a(scalar), b(scalar), c(scalar), d(scalar), e(scalar), f(scalar), g(scalar), h(scalar) {}
lane8f::lane8f( const f32* eight_wide_array )
: a(eight_wide_array[0]), b(eight_wide_array[1]), c(eight_wide_array[2]), d(eight_wide_array[3]),
e(eight_wide_array[4]), f(eight_wide_array[5]), g(eight_wide_array[6]), h(eight_wide_array[7]) {}
f32& lane8f::operator[]( u32 index ) { return (&a)[index]; }
f32  lane8f::operator[]( u32 index ) const { return (&a)[index]; }
lane8f& lane8f::operator+=( const lane8f& rhs ) {
    this->a += rhs.a;
    this->b += rhs.b;
    this->c += rhs.c;
    this->d += rhs.d;
    this->e += rhs.e;
    this->f += rhs.f;
    this->g += rhs.g;
    this->h += rhs.h;
    return *this;
}
lane8f& lane8f::operator-=( const lane8f& rhs ) {
    this->a -= rhs.a;
    this->b -= rhs.b;
    this->c -= rhs.c;
    this->d -= rhs.d;
    this->e -= rhs.e;
    this->f -= rhs.f;
    this->g -= rhs.g;
    this->h -= rhs.h;
    return *this;
}
lane8f& lane8f::operator*=( const lane8f& rhs ) {
    this->a *= rhs.a;
    this->b *= rhs.b;
    this->c *= rhs.c;
    this->d *= rhs.d;
    this->e *= rhs.e;
    this->f *= rhs.f;
    this->g *= rhs.g;
    this->h *= rhs.h;
    return *this;
}
lane8f& lane8f::operator/=( const lane8f& rhs ) {
    this->a /= rhs.a;
    this->b /= rhs.b;
    this->c /= rhs.c;
    this->d /= rhs.d;
    this->e /= rhs.e;
    this->f /= rhs.f;
    this->g /= rhs.g;
    this->h /= rhs.h;
    return *this;
}
lane8f sqrt( lane8f x ) {
    return {
        internal::_sqrtf_( x.a ),
        internal::_sqrtf_( x.b ),
        internal::_sqrtf_( x.c ),
        internal::_sqrtf_( x.d ),
        internal::_sqrtf_( x.e ),
        internal::_sqrtf_( x.f ),
        internal::_sqrtf_( x.g ),
        internal::_sqrtf_( x.h ),
    };
}
void store( f32* eight_wide_array, lane8f registers ) {
    eight_wide_array[0] = registers[0];
    eight_wide_array[1] = registers[1];
    eight_wide_array[2] = registers[2];
    eight_wide_array[3] = registers[3];
    eight_wide_array[4] = registers[4];
    eight_wide_array[5] = registers[5];
    eight_wide_array[6] = registers[6];
    eight_wide_array[7] = registers[7];
}
lane4f extract_high( lane8f a ) {
    return { a.e, a.f, a.g, a.h };
}
lane4f extract_low( lane8f a ) {
    return { a.a, a.b, a.c, a.d };
}

#endif // no simd

lane4f operator+( const lane4f& lhs, const lane4f& rhs ) {
    return lane4f( lhs ) += rhs;
}
lane4f operator-( const lane4f& lhs, const lane4f& rhs ) {
    return lane4f( lhs ) -= rhs;
}
lane4f operator*( const lane4f& lhs, const lane4f& rhs ) {
    return lane4f( lhs ) *= rhs;
}
lane4f operator/( const lane4f& lhs, const lane4f& rhs ) {
    return lane4f( lhs ) /= rhs;
}
lane8f operator+( const lane8f& lhs, const lane8f& rhs ) {
    return lane8f(lhs) += rhs;
}
lane8f operator-( const lane8f& lhs, const lane8f& rhs ) {
    return lane8f(lhs) -= rhs;
}
lane8f operator*( const lane8f& lhs, const lane8f& rhs ) {
    return lane8f(lhs) *= rhs;
}
lane8f operator/( const lane8f& lhs, const lane8f& rhs ) {
    return lane8f(lhs) /= rhs;
}

} // namespace smath::simd

i64 trunc64( f32 x ) {
    return (i64)x;
}
i64 trunc64( f64 x ) {
    return (i64)x;
}
i32 trunc32( f32 x ) {
    return (i32)x;
}
i32 trunc32( f64 x ) {
    return (i32)x;
}
i16 trunc16( f32 x ) {
    return (i16)x;
}
i16 trunc16( f64 x ) {
    return (i16)x;
}
i8 trunc8( f32 x ) {
    return (i8)x;
}
i8 trunc8( f64 x ) {
    return (i8)x;
}

i64 floor64( f64 x ) {
    return x > 0.0 ? trunc64(x) : trunc64(x - 0.99999999);
}
i64 floor64( f32 x ) {
    return x > 0.0f ? trunc64(x) : trunc64(x - 0.999999f);
}
i32 floor32( f64 x ) {
    return x > 0.0 ? trunc32(x) : trunc32(x - 0.99999999);
}
i32 floor32( f32 x ) {
    return x > 0.0f ? trunc32(x) : trunc32(x - 0.999999f);
}
i16 floor16( f64 x ) {
    return x > 0.0 ? trunc16(x) : trunc16(x - 0.99999999);
}
i16 floor16( f32 x ) {
    return x > 0.0f ? trunc16(x) : trunc16(x - 0.999999f);
}
i8 floor8( f64 x ) {
    return x > 0.0 ? trunc8(x) : trunc8(x - 0.99999999);
}
i8 floor8( f32 x ) {
    return x > 0.0f ? trunc8(x) : trunc8(x - 0.999999f);
}

i64 ceil64( f64 x ) {
    return x > 0.0 ? trunc64( x + 0.99999999 ) : trunc64(x);
}
i64 ceil64( f32 x ) {
    return x > 0.0f ? trunc64( x + 0.999999f ) : trunc64(x);
}
i32 ceil32( f64 x ) {
    return x > 0.0 ? trunc32( x + 0.99999999 ) : trunc32(x);
}
i32 ceil32( f32 x ) {
    return x > 0.0f ? trunc32( x + 0.999999f ) : trunc32(x);
}
i16 ceil16( f64 x ) {
    return x > 0.0 ? trunc16( x + 0.99999999 ) : trunc16(x);
}
i16 ceil16( f32 x ) {
    return x > 0.0f ? trunc16( x + 0.999999f ) : trunc16(x);
}
i8 ceil8( f64 x ) {
    return x > 0.0 ? trunc8( x + 0.99999999 ) : trunc8(x);
}
i8 ceil8( f32 x ) {
    return x > 0.0f ? trunc8( x + 0.999999f ) : trunc8(x);
}

i64 round64( f64 x ) {
    return x > 0.0 ? trunc64( x + 0.5 ) : trunc64( x - 0.5 );
}
i64 round64( f32 x ) {
    return x > 0.0f ? trunc64( x + 0.5f ) : trunc64( x - 0.5f );
}
i32 round32( f64 x ) {
    return x > 0.0 ? trunc32( x + 0.5 ) : trunc32( x - 0.5 );
}
i32 round32( f32 x ) {
    return x > 0.0f ? trunc32( x + 0.5f ) : trunc32( x - 0.5f );
}
i16 round16( f64 x ) {
    return x > 0.0 ? trunc16( x + 0.5 ) : trunc16( x - 0.5 );
}
i16 round16( f32 x ) {
    return x > 0.0f ? trunc16( x + 0.5f ) : trunc16( x - 0.5f );
}
i8 round8( f64 x ) {
    return x > 0.0 ? trunc8( x + 0.5 ) : trunc8( x - 0.5 );
}
i8 round8( f32 x ) {
    return x > 0.0f ? trunc8( x + 0.5f ) : trunc8( x - 0.5f );
}

i8 sign( i8 x ) {
    return ( x > 0 ) - ( x < 0 );
}
i16 sign( i16 x ) {
    return ( x > 0 ) - ( x < 0 );
}
i32 sign( i32 x ) {
    return ( x > 0 ) - ( x < 0 );
}
i64 sign( i64 x ) {
    return ( x > 0 ) - ( x < 0 );
}
f32 sign( f32 x ) {
    return ( x > 0.0f ) - ( x < 0.0f );
}
f64 sign( f64 x ) {
    return ( x > 0.0 ) - ( x < 0.0 );
}

i8 absolute( i8 x ) {
    return x * sign( x );
}
i16 absolute( i16 x ) {
    return x * sign( x );
}
i32 absolute( i32 x ) {
    return x * sign( x );
}
i64 absolute( i64 x ) {
    return x * sign( x );
}
f32 absolute( f32 x ) {
    return x * sign( x );
}
f64 absolute( f64 x ) {
    return x * sign( x );
}

i8 clamp( i8 value, i8 min, i8 max ) {
    const i8 t = value < min ? min : value;
    return t > max ? max : t;
}
i16 clamp( i16 value, i16 min, i16 max ) {
    const i16 t = value < min ? min : value;
    return t > max ? max : t;
}
i32 clamp( i32 value, i32 min, i32 max ) {
    const i32 t = value < min ? min : value;
    return t > max ? max : t;
}
i64 clamp( i64 value, i64 min, i64 max ) {
    const i64 t = value < min ? min : value;
    return t > max ? max : t;
}
u8 clamp( u8 value, u8 min, u8 max ) {
    const u8 t = value < min ? min : value;
    return t > max ? max : t;
}
u16 clamp( u16 value, u16 min, u16 max ) {
    const u16 t = value < min ? min : value;
    return t > max ? max : t;
}
u32 clamp( u32 value, u32 min, u32 max ) {
    const u32 t = value < min ? min : value;
    return t > max ? max : t;
}
u64 clamp( u64 value, u64 min, u64 max ) {
    const u64 t = value < min ? min : value;
    return t > max ? max : t;
}
f32 clamp( f32 value, f32 min, f32 max ) {
    const f32 t = value < min ? min : value;
    return t > max ? max : t;
}
f64 clamp( f64 value, f64 min, f64 max ) {
    const f64 t = value < min ? min : value;
    return t > max ? max : t;
}
f32 clamp01( f32 value ) {
    return clamp( value, 0.0f, 1.0f );
}
f64 clamp01( f64 value ) {
    return clamp( value, 0.0, 1.0 );
}

i8 min( i8 a, i8 b) {
    return a < b ? a : b;
}
i16 min( i16 a, i16 b) {
    return a < b ? a : b;
}
i32 min( i32 a, i32 b) {
    return a < b ? a : b;
}
i64 min( i64 a, i64 b) {
    return a < b ? a : b;
}
u8 min( u8 a, u8 b) {
    return a < b ? a : b;
}
u16 min( u16 a, u16 b) {
    return a < b ? a : b;
}
u32 min( u32 a, u32 b) {
    return a < b ? a : b;
}
u64 min( u64 a, u64 b) {
    return a < b ? a : b;
}
f32 min( f32 a, f32 b) {
    return a < b ? a : b;
}
f64 min( f64 a, f64 b) {
    return a < b ? a : b;
}

i8 max( i8 a, i8 b) {
    return a < b ? b : a;
}
i16 max( i16 a, i16 b) {
    return a < b ? b : a;
}
i32 max( i32 a, i32 b) {
    return a < b ? b : a;
}
i64 max( i64 a, i64 b) {
    return a < b ? b : a;
}
u8 max( u8 a, u8 b) {
    return a < b ? b : a;
}
u16 max( u16 a, u16 b) {
    return a < b ? b : a;
}
u32 max( u32 a, u32 b) {
    return a < b ? b : a;
}
u64 max( u64 a, u64 b) {
    return a < b ? b : a;
}
f32 max( f32 a, f32 b) {
    return a < b ? b : a;
}
f64 max( f64 a, f64 b) {
    return a < b ? b : a;
}

f32 normalize_range( i8 x ) {
    return (f32)x / (x > 0 ? (f32)I8::MAX : -((f32)I8::MIN));
}
f32 normalize_range( i16 x ) {
    return (f32)x / (x > 0 ? (f32)I16::MAX : -((f32)I16::MIN));
}
f32 normalize_range( i32 x ) {
    return (f32)x / (x > 0 ? (f32)I32::MAX : -((f32)I32::MIN));
}
f32 normalize_range( i64 x ) {
    return (f32)x / (x > 0 ? (f32)I64::MAX : -((f32)I64::MIN));
}
f32 normalize_range( u8 x ) {
    return (f32)x / (f32)U8::MAX;
}
f32 normalize_range( u16 x ) {
    return (f32)x / (f32)U16::MAX;
}
f32 normalize_range( u32 x ) {
    return (f32)x / (f32)U32::MAX;
}
f32 normalize_range( u64 x ) {
    return (f32)x / (f32)U64::MAX;
}
f64 normalize_range64( i8 x ) {
    return (f64)x / (x > 0 ? (f64)I8::MAX : -((f64)I8::MIN));
}
f64 normalize_range64( i16 x ) {
    return (f64)x / (x > 0 ? (f64)I16::MAX : -((f64)I16::MIN));
}
f64 normalize_range64( i32 x ) {
    return (f64)x / (x > 0 ? (f64)I32::MAX : -((f64)I32::MIN));
}
f64 normalize_range64( i64 x ) {
    return (f64)x / (x > 0 ? (f64)I64::MAX : -((f64)I64::MIN));
}
f64 normalize_range64( u8 x ) {
    return (f64)x / (f64)U8::MAX;
}
f64 normalize_range64( u16 x ) {
    return (f64)x / (f64)U16::MAX;
}
f64 normalize_range64( u32 x ) {
    return (f64)x / (f64)U32::MAX;
}
f64 normalize_range64( u64 x ) {
    return (f64)x / (f64)U64::MAX;
}

f64 sqrt( f64 x ) {
    return internal::_sqrt_(x);
}
f32 sqrt( f32 x ) {
    return internal::_sqrtf_(x);
}

f32 powi( f32 base, i32 exponent ) {
    return internal::_powif_( base, exponent );
}
f64 powi( f64 base, i32 exponent ) {
    return internal::_powi_( base, exponent );
}
f32 pow( f32 base, f32 exponent ) {
    return internal::_powf_( base, exponent );
}
f64 pow( f64 base, f64 exponent ) {
    return internal::_pow_( base, exponent );
}

f32 mod( f32 lhs, f32 rhs ) {
    return internal::_modf_( lhs, rhs );
}
f64 mod( f64 lhs, f64 rhs ) {
    return internal::_mod_( lhs, rhs );
}

f32 sin( f32 x ) {
    return internal::_sinf_( x );
}
f64 sin( f64 x ) {
    return internal::_sin_( x );
}
f32 asin( f32 x ) {
    return internal::_asinf_( x );
}
f64 asin( f64 x ) {
    return internal::_asin_( x );
}

f32 asin_real( f32 x ) {
    if( absolute( x ) >= 1.0f ) {
        const f32 PI_2 = ( F32::PI / 2.0f );
        return PI_2 * sign( x );
    } else {
        return asin( x );
    }
}
f64 asin_real( f64 x ) {
    if( absolute( x ) >= 1.0 ) {
        const f64 PI_2 = ( F64::PI / 2.0 );
        return PI_2 * sign( x );
    } else {
        return asin( x );
    }
}

f32 cos( f32 x ) {
    return internal::_cosf_( x );
}
f64 cos( f64 x ) {
    return internal::_cos_( x );
}
f32 acos( f32 x ) {
    return internal::_acosf_( x );
}
f64 acos( f64 x ) {
    return internal::_acos_( x );
}
f32 tan( f32 x ) {
    return internal::_tanf_( x );
}
f64 tan( f64 x ) {
    return internal::_tan_( x );
}
f32 atan( f32 x ) {
    return internal::_atanf_( x );
}
f64 atan( f64 x ) {
    return internal::_atan_( x );
}

f32 atan2( f32 y, f32 x ) {
    return internal::_atan2f_( y, x );
}
f64 atan2( f64 y, f64 x ) {
    return internal::_atan2_( y, x );
}

constexpr f32 to_rad( f32 theta ) {
    return theta * ( F32::PI / 180.0f );
}
constexpr f64 to_rad( f64 theta ) {
    return theta * ( F64::PI / 180.0 );
}
constexpr f32 to_deg( f32 theta ) {
    return theta * ( 180.0f / F32::PI );
}
constexpr f64 to_deg( f64 theta ) {
    return theta * ( 180.0 / F64::PI );
}

f32 log( f32 x ) {
    return internal::_logf_( x );
}
f64 log( f64 x ) {
    return internal::_log_( x );
}

f32 lerp( f32 a, f32 b, f32 t ) {
    return ( 1.0f - t ) * a + b * t;
}
f64 lerp( f64 a, f64 b, f64 t ) {
    return ( 1.0 - t ) * a + b * t;
}
f32 clamped_lerp( f32 a, f32 b, f32 t ) {
    return lerp( a, b, clamp01(t) );
}
f64 clamped_lerp( f64 a, f64 b, f64 t ) {
    return lerp( a, b, clamp01(t) );
}
f32 inverse_lerp( f32 a, f32 b, f32 v ) {
    return ( v - a ) / ( b - a );
}
f64 inverse_lerp( f64 a, f64 b, f64 v ) {
    return ( v - a ) / ( b - a );
}

f32 remap( f32 imin, f32 imax, f32 omin, f32 omax, f32 v ) {
    const f32 t = inverse_lerp( imin, imax, v );
    return lerp( omin, omax, t );
}
f64 remap( f64 imin, f64 imax, f64 omin, f64 omax, f64 v ) {
    const f64 t = inverse_lerp( imin, imax, v );
    return lerp( omin, omax, t );
}

f32 smooth_step( f32 a, f32 b, f32 t ) {
    return ( b - a ) * ( 3.0f - t * 2.0f ) * t * t + a;
}
f64 smooth_step( f64 a, f64 b, f64 t ) {
    return ( b - a ) * ( 3.0 - t * 2.0 ) * t * t + a;
}
f32 smooth_step_clamped( f32 a, f32 b, f32 t ) {
    return smooth_step( a, b, clamp01(t) );
}
f64 smooth_step_clamped( f64 a, f64 b, f64 t ) {
    return smooth_step( a, b, clamp01(t) );
}
f32 smoother_step( f32 a, f32 b, f32 t ) {
    return ( b - a ) * ( ( t * ( t * 6.0f - 15.0f ) + 10.0f ) * t * t * t ) + a;
}
f64 smoother_step( f64 a, f64 b, f64 t ) {
    return ( b - a ) * ( ( t * ( t * 6.0 - 15.0 ) + 10.0 ) * t * t * t ) + a;
}
f32 smoother_step_clamped( f32 a, f32 b, f32 t ) {
    return smoother_step( a, b, clamp01(t) );
}
f64 smoother_step_clamped( f64 a, f64 b, f64 t ) {
    return smoother_step( a, b, clamp01(t) );
}

#define VEC_CMP_THRESHOLD 0.0001f

// NOTE(alicia): vec2

vec2 vec2::create( f32 x, f32 y ) {
    return { x, y };
}
vec2 vec2::create( f32 scalar ) {
    return { scalar, scalar };
}
vec2 vec2::create( const vec3& v ) {
    return { v.x, v.y };
}
vec2 vec2::create( const vec4& v ) {
    return { v.x, v.y };
}
vec2 vec2::create( const ivec2& v ) {
    return { (f32)v.x, (f32)v.y };
}
vec2 vec2::create( const bvec2& v ) {
    return { (f32)((bool)v.x), (f32)((bool)v.y) };
}
vec2 operator+( const vec2& lhs, const vec2& rhs ) {
    return vec2(lhs) += rhs;
}
vec2 operator-( const vec2& lhs, const vec2& rhs ) {
    return vec2(lhs) -= rhs;
}
vec2 operator*( const vec2& lhs, f32 rhs ) {
    return vec2(lhs) *= rhs;
}
vec2 operator*( f32 lhs, const vec2& rhs ) {
    return vec2(rhs) *= lhs;
}
vec2 operator/( const vec2& lhs, f32 rhs ) {
    return vec2(lhs) /= rhs;
}
f32* vec2::ptr() { return &x; }
const f32* vec2::ptr() const { return &x; }
f32& vec2::operator[]( u32 index ) {
    return ptr()[index];
}
f32 vec2::operator[]( u32 index ) const {
    return ptr()[index];
}
vec2& vec2::operator-() { return *this *= -1.0f; }
bool32 vec2::operator==( const vec2& rhs ) const { return cmp( *this, rhs ); }
bool32 vec2::operator!=( const vec2& rhs ) const { return !(*this == rhs); }
vec2& vec2::operator+=( const vec2& rhs ) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}
vec2& vec2::operator-=( const vec2& rhs ) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}
vec2& vec2::operator*=( f32 rhs ) {
    this->x *= rhs;
    this->y *= rhs;
    return *this;
}
vec2& vec2::operator/=( f32 rhs ) {
    this->x /= rhs;
    this->y /= rhs;
    return *this;
}
void swap( vec2& v ) {
    f32 tmp = v.x;
    v.x = v.y;
    v.y = tmp;
}
f32 horizontal_add( const vec2& v ) {
    return v.x + v.y;
}
f32 horizontal_mul( const vec2& v ) {
    return v.x * v.y;
}
vec2 hadamard( const vec2& lhs, const vec2& rhs ) {
    return {
        lhs.x * rhs.x,
        lhs.y * rhs.y
    };
}
f32 sqr_mag( const vec2& v ) {
    vec2 result = hadamard( v, v );
    return horizontal_add( result );
}
f32 mag( const vec2& v ) {
    return sqrt( sqr_mag( v ) );
}
vec2 normalize( const vec2& v ) {
    f32 m = mag( v );
    return m < 0.0001f ? vec2::zero() : v / m;
}
f32 dot( const vec2& lhs, const vec2& rhs ) {
    vec2 result = hadamard( lhs, rhs );
    return horizontal_add(result);
}
f32 angle( const vec2& a, const vec2& b ) {
    return acos( dot( a, b ) );
}
f32 unsigned_angle( const vec2& a, const vec2& b ) {
    return internal::signed_angle_to_unsigned( angle( a, b ) );
}
vec2 lerp( const vec2& a, const vec2& b, f32 t ) {
    return ( 1.0f - t ) * a + b * t;
}
vec2 clamped_lerp( const vec2& a, const vec2& b, f32 t ) {
    return lerp( a, b, clamp01(t) );
}
vec2 smooth_step( const vec2& a, const vec2& b, f32 t ) {
    return ( b - a ) * ( 3.0f - t * 2.0f ) * t * t + a;
}
vec2 smooth_step_clamped( const vec2& a, const vec2& b, f32 t ) {
    return smooth_step( a, b, clamp01(t) );
}
vec2 smoother_step( const vec2& a, const vec2& b, f32 t ) {
    return ( b - a ) * ( ( t * ( t * 6.0f - 15.0f ) + 10.0f ) * t * t * t ) + a;
}
vec2 smoother_step_clamped( const vec2& a, const vec2& b, f32 t ) {
    return smoother_step( a, b, clamp01(t) );
}
vec2 rotate( const vec2& v, f32 theta ) {
    f32 theta_sin = sin( theta );
    f32 theta_cos = cos( theta );
    vec2 a = { theta_cos, theta_sin };
    vec2 b = { -theta_sin, theta_cos };
    return (v.x * a) + (v.y * b);
}
vec2 clamp( const vec2& v, f32 max ) {
    f32 maximum = absolute(max);
    f32 magnitude = mag(v);
    if( magnitude > maximum ) {
        vec2 result = v / magnitude;
        result *= maximum;
        return result;
    } else {
        return v;
    }
}
ivec2 trunc32( const vec2& v ) {
    return ivec2::create( v );
}
ivec2 floor32( const vec2& v ) {
    return { floor32(v.x), floor32(v.y) };
}
ivec2 ceil32( const vec2& v ) {
    return { ceil32(v.x), ceil32(v.y) };
}
ivec2 round32( const vec2& v ) {
    return { round32(v.x), round32(v.y) };
}
bool32 cmp( const vec2& a, const vec2& b ) {
    return sqr_mag(a - b) < VEC_CMP_THRESHOLD;
}

// NOTE(alicia): ivec2

ivec2 ivec2::create( i32 x, i32 y ) {
    return { x, y };
}
ivec2 ivec2::create( i32 scalar ) {
    return { scalar, scalar };
}
ivec2 ivec2::create( const vec2& v ) {
    return { (i32)v.x, (i32)v.y };
}
ivec2 ivec2::create( const ivec3& v ) {
    return { v.x, v.y };
}
ivec2 ivec2::create( const ivec4& v ) {
    return { v.x, v.y };
}
ivec2 ivec2::create( const bvec2& v ) {
    return { (i32)((bool)v.x), (i32)((bool)v.y) };
}
i32* ivec2::ptr() { return &x; }
const i32* ivec2::ptr() const { return &x; }
i32& ivec2::operator[]( u32 index ) { return ptr()[index]; }
i32 ivec2::operator[]( u32 index ) const { return ptr()[index]; }
ivec2& ivec2::operator-() { return *this *= -1.0f; }
bool32 ivec2::operator==( const ivec2& rhs ) const { return cmp( *this, rhs ); }
bool32 ivec2::operator!=( const ivec2& rhs ) const { return !(*this == rhs); }
ivec2& ivec2::operator+=( const ivec2& rhs ) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}
ivec2& ivec2::operator-=( const ivec2& rhs ) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}
ivec2& ivec2::operator*=( i32 rhs ) {
    this->x *= rhs;
    this->y *= rhs;
    return *this;
}
ivec2& ivec2::operator/=( i32 rhs ) {
    this->x /= rhs;
    this->y /= rhs;
    return *this;
}
ivec2 operator+( const ivec2& lhs, const ivec2& rhs ) {
    return ivec2(lhs) += rhs;
}
ivec2 operator-( const ivec2& lhs, const ivec2& rhs ) {
    return ivec2(lhs) -= rhs;
}
ivec2 operator*( const ivec2& lhs, i32 rhs ) {
    return ivec2(lhs) *= rhs;
}
ivec2 operator*( i32 lhs, const ivec2& rhs ) {
    return ivec2(rhs) *= lhs;
}
ivec2 operator/( const ivec2& lhs, i32 rhs ) {
    return ivec2(lhs) /= rhs;
}
void swap( ivec2& v ) {
    i32 tmp = v.x;
    v.x = v.y;
    v.y = tmp;
}
i32 horizontal_add( const ivec2& v ) {
    return v.x + v.y;
}
i32 horizontal_mul( const ivec2& v ) {
    return v.x * v.y;
}
ivec2 hadamard( const ivec2& lhs, const ivec2& rhs ) {
    return { lhs.x * rhs.x, lhs.y * rhs.y };
}
f32 dot( const ivec2& lhs, const ivec2& rhs ) {
    return dot( vec2::create(lhs), vec2::create(rhs) );
}
f32 sqr_mag( const ivec2& v ) {
    return sqr_mag( vec2::create(v) );
}
f32 mag( const ivec2& v ) {
    return sqrt( sqr_mag( v ) );
}
f32 angle( const ivec2& a, const ivec2& b ) {
    return angle( vec2::create(a), vec2::create(b) );
}
f32 unsigned_angle( const ivec2& a, const ivec2& b ) {
    return unsigned_angle( vec2::create(a), vec2::create(b) );
}
ivec2 min( const ivec2& a, const ivec2& b ) {
    return { min( a.x, b.x ), min( a.y, b.y ) };
}
ivec2 max( const ivec2& a, const ivec2& b ) {
    return { max( a.x, b.x ), max( a.y, b.y ) };
}
vec2 normalize_range( const ivec2& v ) {
    return { normalize_range(v.x), normalize_range(v.y) };
}
vec2 normalize_range01( const ivec2& v ) {
    return { normalize_range((u32)v.x), normalize_range((u32)v.y) };
}
bool32 cmp( const ivec2& a, const ivec2& b ) {
    return a.x == b.x && a.y == b.y;
}

// NOTE(alicia): bvec2

bvec2 bvec2::create( bool32 x, bool32 y ) {
    return { x, y };
}
bvec2 bvec2::create( bool32 boolean ) {
    return { boolean, boolean };
}
bvec2 bvec2::create( const vec2& v ) {
    return { (bool)v.x, (bool)v.y };
}
bvec2 bvec2::create( const ivec2& v ) {
    return { (bool)v.x, (bool)v.y };
}
bvec2 bvec2::create( const bvec3& v ) {
    return { v.x, v.y };
}
bvec2 bvec2::create( const bvec4& v ) {
    return { v.x, v.y };
}
bool32* bvec2::ptr() { return &x; }
const bool32* bvec2::ptr() const { return &x; }
bool32& bvec2::operator[]( u32 index ) { return ptr()[index]; }
bool32 bvec2::operator[]( u32 index ) const { return ptr()[index]; }
bvec2& bvec2::operator!() {
    *this = { !this->x, !this->y }; 
    return *this;
}
bool32 bvec2::operator==( const bvec2& rhs ) const {
    return this->x == rhs.x && this->y == rhs.y;
}
bool32 bvec2::operator!=( const bvec2& rhs ) const {
    return !(*this == rhs);
}
bvec2 bvec2::operator>( const bvec2& rhs ) {
    return { this->x > rhs.x, this->y > rhs.y };
}
bvec2 bvec2::operator>=( const bvec2& rhs ) {
    return { this->x >= rhs.x, this->y >= rhs.y };
}
bvec2 bvec2::operator<( const bvec2& rhs ) {
    return { this->x < rhs.x, this->y < rhs.y };
}
bvec2 bvec2::operator<=( const bvec2& rhs ) {
    return { this->x <= rhs.x, this->y <= rhs.y };
}
bool32 horizontal_and( const bvec2& v ) {
    return v.x && v.y;
}
bool32 horizontal_or( const bvec2& v ) {
    return v.x || v.y;
}

// NOTE(alicia): vec3

vec3 vec3::create( f32 x, f32 y, f32 z ) {
    return { x, y, z };
}
vec3 vec3::create( f32 scalar ) {
    return { scalar, scalar, scalar };
}
vec3 vec3::create( const vec2& v ) {
    return { v.x, v.y, 0.0f };
}
vec3 vec3::create( const ivec3& v ) {
    return { (f32)v.x, (f32)v.y, (f32)v.z };
}
vec3 vec3::create( const bvec3& v ) {
    return { (f32)((bool)v.x), (f32)((bool)v.y), (f32)((bool)v.z) };
}
vec3 vec3::create( const vec4& v ) {
    return { v.x, v.y, v.z };
}
f32* vec3::ptr() { return &x; }
const f32* vec3::ptr() const { return &x; }
f32& vec3::operator[]( u32 index ) { return ptr()[index]; }
f32 vec3::operator[]( u32 index ) const { return ptr()[index]; }
vec3& vec3::operator-() { return *this *= -1.0f; }
bool32 vec3::operator==( const vec3& rhs ) const { return cmp( *this, rhs ); }
bool32 vec3::operator!=( const vec3& rhs ) const { return !(*this == rhs); }
vec3& vec3::operator+=( const vec3& rhs ) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
}
vec3& vec3::operator-=( const vec3& rhs ) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
}
vec3& vec3::operator*=( f32 rhs ) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
}
vec3& vec3::operator/=( f32 rhs ) {
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    return *this;
}
vec3 operator+( const vec3& lhs, const vec3& rhs ) {
    return vec3(lhs) += rhs;
}
vec3 operator-( const vec3& lhs, const vec3& rhs ) {
    return vec3(lhs) -= rhs;
}
vec3 operator*( const vec3& lhs, f32 rhs ) {
    return vec3(lhs) *= rhs;
}
vec3 operator*( f32 lhs, const vec3& rhs ) {
    return vec3(rhs) *= lhs;
}
vec3 operator/( const vec3& lhs, f32 rhs ) {
    return vec3(lhs) /= rhs;
}
hsv vec3::create_hsv( f32 hue, f32 saturation, f32 value ) {
    return {
        internal::degrees_overflow( hue ),
        clamp01(saturation),
        clamp01(value)
    };
}
hsv rgb_to_hsv( const rgb& rgb ) {
    f32 x_max, x_min;
    x_max = rgb.r > rgb.g ?
        ( rgb.r > rgb.b ? rgb.r : rgb.b ) :
        ( rgb.g > rgb.b ? rgb.g : rgb.b );
    x_min = rgb.r < rgb.g ?
        ( rgb.r < rgb.b ? rgb.r : rgb.b ) :
        ( rgb.g < rgb.b ? rgb.g : rgb.b );

    f32 chroma = x_max - x_min;
    
    f32 hue;
    if( chroma == 0.0f ) {
        hue = 0.0f;
    } else if( x_max == rgb.r ) {
        hue = 60.0f * ( 0.0f + ( ( rgb.g - rgb.b ) / chroma ) );
    } else if( x_max == rgb.g ) {
        hue = 60.0f * ( 2.0f + ( ( rgb.b - rgb.r ) / chroma ) );
    } else {
        hue = 60.0f * ( 4.0f + ( ( rgb.r - rgb.g ) / chroma ) );
    }

    f32 saturation = x_max == 0.0f ? 0.0f : chroma / x_max;

    return hsv::create_hsv( hue, saturation, x_max );
}
rgb hsv_to_rgb( const hsv& hsv ) {
    
    f32 chroma    = hsv.value * hsv.saturation;
    f32 hue       = hsv.hue / 60.0f;
    i32 hue_index = floor32( hue );

    f32 x = chroma * ( 1.0f - absolute( mod( hue, 2.0f ) - 1.0f ) );

    rgb result;

    if( hue_index < 1 ) {
        result = { chroma, x, 0.0f };
    } else if( hue_index < 2 ) {
        result = { x, chroma, 0.0f };
    } else if( hue_index < 3 ) {
        result = { 0.0f, chroma, x };
    } else if( hue_index < 4 ) {
        result = { 0.0f, x, chroma };
    } else if( hue_index < 5 ) {
        result = { x, 0.0f, chroma };
    } else {
        result = { chroma, 0.0f, x };
    }
    
    f32 m = hsv.value - chroma;

    return {
        result.r + m,
        result.g + m,
        result.b + m
    };
}
void set_hue( hsv& hsv, f32 hue ) {
    hsv.hue = internal::degrees_overflow( hue );
}
void set_saturation( hsv& hsv, f32 saturation ) {
    hsv.saturation = clamp01( saturation );
}
void set_value( hsv& hsv, f32 value ) {
    hsv.value = clamp01( value );
}
rgb linear_to_srgb( const rgb& linear ) {
    return {
        pow( linear.r, 1.0f / 2.2f ),
        pow( linear.g, 1.0f / 2.2f ),
        pow( linear.b, 1.0f / 2.2f ),
    };
}
rgb srgb_to_linear( const rgb& srgb ) {
    return {
        pow( srgb.r, 2.2f ),
        pow( srgb.g, 2.2f ),
        pow( srgb.b, 2.2f ),
    };
}
void shift_left( vec3& v ) {
    f32 tmp = v.x;
    v.x = v.y;
    v.y = v.z;
    v.z = tmp;
}
void shift_right( vec3& v ) {
    f32 tmp = v.z;
    v.z = v.y;
    v.y = v.x;
    v.x = tmp;
}
f32 horizontal_add( const vec3& v ) {
    return v.x + v.y + v.z;
}
f32 horizontal_mul( const vec3& v ) {
    return v.x * v.y * v.z;
}
vec3 hadamard( const vec3& lhs, const vec3& rhs ) {
    return {
        lhs.x * rhs.x,
        lhs.y * rhs.y,
        lhs.z * rhs.z
    };
}
vec3 normalize( const vec3& v ) {
    f32 m = mag( v );
    return m < 0.0001f ? vec3::zero() : v / m;
}
f32 dot( const vec3& lhs, const vec3& rhs ) {
    vec3 result = hadamard( lhs, rhs );
    return horizontal_add(result);
}
vec3 cross( const vec3& lhs, const vec3& rhs ) {
    return {
        ( lhs.y * rhs.z ) - ( lhs.z * rhs.y ),
        ( lhs.z * rhs.x ) - ( lhs.x * rhs.z ),
        ( lhs.x * rhs.y ) - ( lhs.y * rhs.x )
    };
}
f32 sqr_mag( const vec3& v ) {
    vec3 result = hadamard( v, v );
    return horizontal_add( result );
}
f32 mag( const vec3& v ) {
    return sqrt( sqr_mag( v ) );
}
vec3 reflect( const vec3& direction, const vec3& normal ) {
    return ( normal - direction ) * ( 2.0f * dot( direction, normal ) );
}
f32 angle( const vec3& a, const vec3& b ) {
    return acos( dot( a, b ) );
}
f32 unsigned_angle( const vec3& a, const vec3& b ) {
    return internal::signed_angle_to_unsigned( angle( a, b ) );
}
vec3 lerp( const vec3& a, const vec3& b, f32 t ) {
    return ( 1.0f - t ) * a + b * t;
}
vec3 clamped_lerp( const vec3& a, const vec3& b, f32 t ) {
    return lerp( a, b, clamp01(t) );
}
vec3 smooth_step( const vec3& a, const vec3& b, f32 t ) {
    return ( b - a ) * ( 3.0f - t * 2.0f ) * t * t + a;
}
vec3 smooth_step_clamped( const vec3& a, const vec3& b, f32 t ) {
    return smooth_step( a, b, clamp01(t) );
}
vec3 smoother_step( const vec3& a, const vec3& b, f32 t ) {
    return ( b - a ) * ( ( t * ( t * 6.0f - 15.0f ) + 10.0f ) * t * t * t ) + a;
}
vec3 smoother_step_clamped( const vec3& a, const vec3& b, f32 t ) {
    return smoother_step( a, b, clamp01(t) );
}
vec3 clamp( const vec3& v, f32 max ) {
    f32 maximum = absolute(max);
    f32 magnitude = mag(v);
    if( magnitude > maximum ) {
        vec3 result = v / magnitude;
        result *= maximum;
        return result;
    } else {
        return v;
    }
}
ivec3 trunc32( const vec3& v ) {
    return { trunc32(v.x), trunc32(v.y), trunc32(v.z) };
}
ivec3 floor32( const vec3& v ) {
    return { floor32(v.x), floor32(v.y), floor32(v.z) };
}
ivec3 ceil32( const vec3& v ) {
    return { ceil32(v.x), ceil32(v.y), ceil32(v.z) };
}
ivec3 round32( const vec3& v ) {
    return { round32(v.x), round32(v.y), round32(v.z) };
}
bool32 cmp( const vec3& a, const vec3& b ) {
    return sqr_mag(a - b) < VEC_CMP_THRESHOLD;
}
euler_angles to_rad( const euler_angles& deg ) {
    const euler_angles _to_rad = euler_angles::create(F32::PI / 180.0f);
    return hadamard( _to_rad, deg );
}
euler_angles to_deg( const euler_angles& rad ) {
    const euler_angles _to_deg = euler_angles::create(180.0f / F32::PI);
    return hadamard( _to_deg, rad );
}

// NOTE(alicia): ivec3

ivec3 ivec3::create( i32 x, i32 y, i32 z ) {
    return { x, y, z };
}
ivec3 ivec3::create( i32 scalar ) {
    return { scalar, scalar, scalar };
}
ivec3 ivec3::create( const vec3& v ) {
    return { (i32)v.x, (i32)v.y, (i32)v.z };
}
ivec3 ivec3::create( const ivec2& v ) {
    return { v.x, v.y, 0 };
}
ivec3 ivec3::create( const ivec4& v ) {
    return { v.x, v.y, v.z };
}
ivec3 ivec3::create( const bvec3& v ) {
    return { (i32)((bool)v.x), (i32)((bool)v.y), (i32)((bool)v.z), };
}
i32* ivec3::ptr() { return &x; }
const i32* ivec3::ptr() const { return &x; }
i32& ivec3::operator[]( u32 index ) { return ptr()[index]; }
i32 ivec3::operator[]( u32 index ) const { return ptr()[index]; }
ivec3& ivec3::operator-() { return *this *= -1.0f; }
bool32 ivec3::operator==( const ivec3& rhs ) const { return cmp( *this, rhs ); }
bool32 ivec3::operator!=( const ivec3& rhs ) const { return !(*this == rhs); }
ivec3& ivec3::operator+=( const ivec3& rhs ) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
}
ivec3& ivec3::operator-=( const ivec3& rhs ) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
}
ivec3& ivec3::operator*=( i32 rhs ) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
}
ivec3& ivec3::operator/=( i32 rhs ) {
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    return *this;
}
ivec3 operator+( const ivec3& lhs, const ivec3& rhs ) {
    return ivec3(lhs) += rhs;
}
ivec3 operator-( const ivec3& lhs, const ivec3& rhs ) {
    return ivec3(lhs) -= rhs;
}
ivec3 operator*( const ivec3& lhs, i32 rhs ) {
    return ivec3(lhs) *= rhs;
}
ivec3 operator*( i32 lhs, const ivec3& rhs ) {
    return ivec3(rhs) *= lhs;
}
ivec3 operator/( const ivec3& lhs, i32 rhs ) {
    return ivec3(lhs) /= rhs;
}
void shift_left( ivec3& v ) {
    i32 tmp = v.x;
    v.x = v.y;
    v.y = v.z;
    v.z = tmp;
}
void shift_right( ivec3& v ) {
    i32 tmp = v.z;
    v.z = v.y;
    v.y = v.x;
    v.x = tmp;
}
i32 horizontal_add( const ivec3& v ) {
    return v.x + v.y + v.z;
}
i32 horizontal_mul( const ivec3& v ) {
    return v.x * v.y * v.z;
}
ivec3 hadamard( const ivec3& lhs, const ivec3& rhs ) {
    return { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
}
f32 dot( const ivec3& lhs, const ivec3& rhs ) {
    return dot( vec3::create(lhs), vec3::create(rhs) );
}
ivec3 cross( const ivec3& lhs, const ivec3& rhs ) {
    return ivec3::create( cross( vec3::create(lhs), vec3::create(rhs) ) );
}
f32 sqr_mag( const ivec3& v ) {
    return sqr_mag( vec3::create(v) );
}
f32 mag( const ivec3& v ) {
    return sqrt( sqr_mag( v ) );
}
f32 angle( const ivec3& a, const ivec3& b ) {
    return angle( vec3::create(a), vec3::create(b) );
}
f32 unsigned_angle( const ivec3& a, const ivec3& b ) {
    return unsigned_angle( vec3::create(a), vec3::create(b) );
}
ivec3 min( const ivec3& a, const ivec3& b ) {
    return { min( a.x, b.x ), min( a.y, b.y ), min( a.z, b.z ) };
}
ivec3 max( const ivec3& a, const ivec3& b ) {
    return { max( a.x, b.x ), max( a.y, b.y ), max( a.z, b.z ) };
}
vec3 normalize_range( const ivec3& v ) {
    return { normalize_range(v.x), normalize_range(v.y), normalize_range(v.z) };
}
vec3 normalize_range01( const ivec3& v ) {
    return { normalize_range((u32)v.x), normalize_range((u32)v.y), normalize_range((u32)v.z) };
}
bool32 cmp( const ivec3& a, const ivec3& b ) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

// NOTE(alicia): bvec3

bvec3 bvec3::create( bool32 x, bool32 y, bool32 z  ) {
    return { x, y, z };
}
bvec3 bvec3::create( bool32 boolean ) {
    return { boolean, boolean, boolean };
}
bvec3 bvec3::create( const vec3& v ) {
    return { (bool)v.x, (bool)v.y, (bool)v.z };
}
bvec3 bvec3::create( const ivec3& v ) {
    return { (bool)v.x, (bool)v.y, (bool)v.z };
}
bvec3 bvec3::create( const bvec2& v ) {
    return { v.x, v.y, false };
}
bvec3 bvec3::create( const bvec4& v ) {
    return { v.x, v.y, v.z };
}
bool32* bvec3::ptr() { return &x; }
const bool32* bvec3::ptr() const { return &x; }
bvec3& bvec3::operator!() {
    *this = { !this->x, !this->y, !this->z }; 
    return *this;
}
bool32& bvec3::operator[]( u32 index ) {
    return ptr()[index];
}
bool32 bvec3::operator[]( u32 index ) const {
    return ptr()[index];
}
bool32 bvec3::operator==( const bvec3& rhs ) const {
    return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
}
bool32 bvec3::operator!=( const bvec3& rhs ) const {
    return !(*this == rhs);
}
bvec3 bvec3::operator>( const bvec3& rhs ) {
    return { this->x > rhs.x, this->y > rhs.y, this->z > rhs.z };
}
bvec3 bvec3::operator>=( const bvec3& rhs ) {
    return { this->x >= rhs.x, this->y >= rhs.y, this->z >= rhs.z };
}
bvec3 bvec3::operator<( const bvec3& rhs ) {
    return { this->x < rhs.x, this->y < rhs.y, this->z < rhs.z };
}
bvec3 bvec3::operator<=( const bvec3& rhs ) {
    return { this->x <= rhs.x, this->y <= rhs.y, this->z <= rhs.z };
}
bool32 horizontal_and( const bvec3& v ) {
    return v.x && v.y && v.z;
}
bool32 horizontal_or( const bvec3& v ) {
    return v.x || v.y || v.z;
}

// NOTE(alicia): vec4

vec4 vec4::create( f32 x, f32 y, f32 z, f32 w ) {
    return { x, y, z, w };
}
vec4 vec4::create( f32 scalar ) {
    return { scalar, scalar, scalar, scalar };
}
vec4 vec4::create( const vec2& v ) {
    return { v.x, v.y, 0.0f, 0.0f };
}
vec4 vec4::create( const vec3& v ) {
    return { v.x, v.y, v.z, 0.0f };
}
vec4 vec4::create( const ivec4& v ) {
    return { (f32)v.x, (f32)v.y, (f32)v.z, (f32)v.w };
}
vec4 vec4::create( const bvec4& v ) {
    return { (f32)((bool)v.x), (f32)((bool)v.y), (f32)((bool)v.z), (f32)((bool)v.w) };
}
f32* vec4::ptr() { return &x; }
const f32* vec4::ptr() const { return &x; }
f32& vec4::operator[]( u32 index ) { return ptr()[index]; }
f32 vec4::operator[]( u32 index ) const { return ptr()[index]; }
vec4& vec4::operator-() { return *this *= -1.0f; }
bool32 vec4::operator==( const vec4& rhs ) const { return cmp( *this, rhs ); }
bool32 vec4::operator!=( const vec4& rhs ) const { return !(*this == rhs); }
vec4& vec4::operator+=( const vec4& rhs ) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    this->w += rhs.w;
    return *this;
}
vec4& vec4::operator-=( const vec4& rhs ) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    this->w -= rhs.w;
    return *this;
}
vec4& vec4::operator*=( f32 rhs ) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    this->w *= rhs;
    return *this;
}
vec4& vec4::operator/=( f32 rhs ) {
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    this->w /= rhs;
    return *this;
}
vec4 operator+( const vec4& lhs, const vec4& rhs ) {
    return vec4(lhs) += rhs;
}
vec4 operator-( const vec4& lhs, const vec4& rhs ) {
    return vec4(lhs) -= rhs;
}
vec4 operator*( const vec4& lhs, f32 rhs ) {
    return vec4(lhs) *= rhs;
}
vec4 operator*( f32 lhs, const vec4& rhs ) {
    return vec4(rhs) *= lhs;
}
vec4 operator/( const vec4& lhs, f32 rhs ) {
    return vec4(lhs) /= rhs;
}
bool32 cmp( const vec4& a, const vec4& b ) {
    return sqr_mag(a - b) < VEC_CMP_THRESHOLD;
}
rgba linear_to_srgb( const rgba& linear ) {
    return {
        pow( linear.r, 1.0f / 2.2f ),
        pow( linear.g, 1.0f / 2.2f ),
        pow( linear.b, 1.0f / 2.2f ),
        linear.a
    };
}
rgba srgb_to_linear( const rgba& srgb ) {
    return {
        pow( srgb.r, 2.2f ),
        pow( srgb.g, 2.2f ),
        pow( srgb.b, 2.2f ),
        srgb.a
    };
}
void shift_left( vec4& v ) {
    f32 tmp = v.x;
    v.x = v.y;
    v.y = v.z;
    v.z = v.w;
    v.w = tmp;
}
void shift_right( vec4& v ) {
    f32 tmp = v.w;
    v.w = v.z;
    v.z = v.y;
    v.y = v.x;
    v.x = tmp;
}
f32 horizontal_add( const vec4& v ) {
    return v.x + v.y + v.z + v.w;
}
f32 horizontal_mul( const vec4& v ) {
    return v.x * v.y * v.z * v.w;
}
vec4 hadamard( const vec4& lhs, const vec4& rhs ) {
    return {
        lhs.x * rhs.x,
        lhs.y * rhs.y,
        lhs.z * rhs.z,
        lhs.w * rhs.w
    };
}
f32 sqr_mag( const vec4& v ) {
    vec4 result = hadamard( v, v );
    return horizontal_add( result );
}
f32 mag( const vec4& v ) {
    return sqrt( sqr_mag( v ) );
}
vec4 normalize( const vec4& v ) {
    f32 m = mag( v );
    return m < 0.0001f ? vec4::zero() : v / m;
}
f32 dot( const vec4& lhs, const vec4& rhs ) {
    vec4 result = hadamard( lhs, rhs );
    return horizontal_add(result);
}
vec4 lerp( const vec4& a, const vec4& b, f32 t ) {
    return ( 1.0f - t ) * a + b * t;
}
vec4 clamped_lerp( const vec4& a, const vec4& b, f32 t ) {
    return lerp( a, b, clamp01(t) );
}
vec4 smooth_step( const vec4& a, const vec4& b, f32 t ) {
    return ( b - a ) * ( 3.0f - t * 2.0f ) * t * t + a;
}
vec4 smooth_step_clamped( const vec4& a, const vec4& b, f32 t ) {
    return smooth_step( a, b, clamp01(t) );
}
vec4 smoother_step( const vec4& a, const vec4& b, f32 t ) {
    return ( b - a ) * ( ( t * ( t * 6.0f - 15.0f ) + 10.0f ) * t * t * t ) + a;
}
vec4 smoother_step_clamped( const vec4& a, const vec4& b, f32 t ) {
    return smoother_step( a, b, clamp01(t) );
}
vec4 clamp( const vec4& v, f32 max ) {
    f32 maximum = absolute(max);
    f32 magnitude = mag(v);
    if( magnitude > maximum ) {
        vec4 result = v / magnitude;
        result *= maximum;
        return result;
    } else {
        return v;
    }
}
ivec4 trunc32( const vec4& v ) {
    return { trunc32(v.x), trunc32(v.y), trunc32(v.z), trunc32(v.w) };
}
ivec4 floor32( const vec4& v ) {
    return { floor32(v.x), floor32(v.y), floor32(v.z), floor32(v.w) };
}
ivec4 ceil32( const vec4& v ) {
    return { ceil32(v.x), ceil32(v.y), ceil32(v.z), ceil32(v.w) };
}
ivec4 round32( const vec4& v ) {
    return { round32(v.x), round32(v.y), round32(v.z), round32(v.w) };
}
rgba rgb_to_rgba( const rgb& v ) {
    rgba result = rgba::create(v);
    result.a = 1.0f;
    return result;
}

// NOTE(alicia): ivec4

ivec4 ivec4::create( i32 x, i32 y, i32 z, i32 w ) {
    return { x, y, z, w };
}
ivec4 ivec4::create( i32 scalar ) {
    return { scalar, scalar, scalar, scalar };
}
ivec4 ivec4::create( const vec4& v ) {
    return { (i32)v.x, (i32)v.y, (i32)v.z, (i32)v.w };
}
ivec4 ivec4::create( const ivec3& v ) {
    return { v.x, v.y, v.z, 0 };
}
ivec4 ivec4::create( const ivec2& v ) {
    return { v.x, v.y, 0, 0 };
}
ivec4 ivec4::create( const bvec4& v ) {
    return { (i32)((bool)v.x), (i32)((bool)v.y), (i32)((bool)v.z), (i32)((bool)v.w) };
}
i32* ivec4::ptr() { return &x; }
const i32* ivec4::ptr() const { return &x; }
i32& ivec4::operator[]( u32 index ) { return ptr()[index]; }
i32 ivec4::operator[]( u32 index ) const { return ptr()[index]; }
ivec4& ivec4::operator-() { return *this *= -1; }
bool32 ivec4::operator==( const ivec4& rhs ) const { return cmp( *this, rhs ); }
bool32 ivec4::operator!=( const ivec4& rhs ) const { return !(*this == rhs); }
ivec4& ivec4::operator+=( const ivec4& rhs ) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    this->w += rhs.w;
    return *this;
}
ivec4& ivec4::operator-=( const ivec4& rhs ) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    this->w -= rhs.w;
    return *this;
}
ivec4& ivec4::operator*=( i32 rhs ) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    this->w *= rhs;
    return *this;
}
ivec4& ivec4::operator/=( i32 rhs ) {
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    this->w /= rhs;
    return *this;
}
ivec4 operator+( const ivec4& lhs, const ivec4& rhs ) {
    return ivec4(lhs) += rhs;
}
ivec4 operator-( const ivec4& lhs, const ivec4& rhs ) {
    return ivec4(lhs) -= rhs;
}
ivec4 operator*( const ivec4& lhs, i32 rhs ) {
    return ivec4(lhs) *= rhs;
}
ivec4 operator*( i32 lhs, const ivec4& rhs ) {
    return ivec4(rhs) *= lhs;
}
ivec4 operator/( const ivec4& lhs, i32 rhs ) {
    return ivec4(lhs) /= rhs;
}
bool32 cmp( const ivec4& a, const ivec4& b ) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}
void shift_left( ivec4& v ) {
    i32 tmp = v.x;
    v.x = v.y;
    v.y = v.z;
    v.z = v.w;
    v.w = tmp;
}
void shift_right( ivec4& v ) {
    i32 tmp = v.w;
    v.w = v.z;
    v.z = v.y;
    v.y = v.x;
    v.x = tmp;
}
i32 horizontal_add( const ivec4& v ) {
    return v.x + v.y + v.z + v.w;
}
i32 horizontal_mul( const ivec4& v ) {
    return v.x * v.y * v.z * v.w;
}
ivec4 hadamard( const ivec4& lhs, const ivec4& rhs ) {
    return {
        lhs.x * rhs.x,
        lhs.y * rhs.y,
        lhs.z * rhs.z,
        lhs.w * rhs.w
    };
}
f32 dot( const ivec4& lhs, const ivec4& rhs ) {
    return dot( vec4::create(lhs), vec4::create(rhs) );
}
f32 sqr_mag( const ivec4& v ) {
    return sqr_mag( vec4::create(v) );
}
f32 mag( const ivec4& v ) {
    return sqrt( sqr_mag( v ) );
}
ivec4 min( const ivec4& a, const ivec4& b ) {
    return {
        min( a.x, b.x ),
        min( a.y, b.y ),
        min( a.z, b.z ),
        min( a.w, b.w )
    };
}
ivec4 max( const ivec4& a, const ivec4& b ) {
    return {
        max( a.x, b.x ),
        max( a.y, b.y ),
        max( a.z, b.z ),
        max( a.w, b.w )
    };
}
vec4 normalize_range( const ivec4& v ) {
    return {
        normalize_range(v.x),
        normalize_range(v.y),
        normalize_range(v.z),
        normalize_range(v.w)
    };
}
vec4 normalize_range01( const ivec4& v ) {
    return {
        normalize_range((u32)v.x),
        normalize_range((u32)v.y),
        normalize_range((u32)v.z),
        normalize_range((u32)v.w)
    };
}

// NOTE(alicia): bvec4

bvec4 bvec4::create( bool32 x, bool32 y, bool32 z, bool32 w ) {
    return { x, y, z, w };
}
bvec4 bvec4::create( bool32 boolean ) {
    return { boolean, boolean, boolean, boolean };
}
bvec4 bvec4::create( const vec4& v ) {
    return { (bool)v.x, (bool)v.y, (bool)v.z, (bool)v.w };
}
bvec4 bvec4::create( const ivec4& v ) {
    return { (bool)v.x, (bool)v.y, (bool)v.z, (bool)v.w };
}
bvec4 bvec4::create( const bvec2& v ) {
    return { v.x, v.y, false, false };
}
bvec4 bvec4::create( const bvec3& v ) {
    return { v.x, v.y, v.z, false };
}
bool32* bvec4::ptr() { return &x; }
const bool32* bvec4::ptr() const { return &x; }
bvec4& bvec4::operator!() {
    *this = { !this->x, !this->y, !this->z, !this->w }; 
    return *this;
}
bool32& bvec4::operator[]( u32 index ) {
    return ptr()[index];
}
bool32 bvec4::operator[]( u32 index ) const {
    return ptr()[index];
}
bool32 bvec4::operator==( const bvec4& rhs ) const {
    return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->w == rhs.w;
}
bool32 bvec4::operator!=( const bvec4& rhs ) const {
    return !(*this == rhs);
}
bvec4 bvec4::operator>( const bvec4& rhs ) {
    return {
        this->x > rhs.x,
        this->y > rhs.y,
        this->z > rhs.z,
        this->w > rhs.w
    };
}
bvec4 bvec4::operator>=( const bvec4& rhs ) {
    return {
        this->x >= rhs.x,
        this->y >= rhs.y,
        this->z >= rhs.z,
        this->w >= rhs.w
    };
}
bvec4 bvec4::operator<( const bvec4& rhs ) {
    return {
        this->x < rhs.x,
        this->y < rhs.y,
        this->z < rhs.z,
        this->w < rhs.w
    };
}
bvec4 bvec4::operator<=( const bvec4& rhs ) {
    return {
        this->x <= rhs.x,
        this->y <= rhs.y,
        this->z <= rhs.z,
        this->w <= rhs.w
    };
}
bool32 horizontal_and( const bvec4& v ) {
    return v.x && v.y && v.z && v.w;
}
bool32 horizontal_or( const bvec4& v ) {
    return v.x || v.y || v.z || v.w;
}

// NOTE(alicia): quat

quat quat::create( f32 w, f32 x, f32 y, f32 z ) {
    return { w, x, y, z };
}
quat quat::create( f32 theta, const vec3& axis ) {
    f32 half_theta = theta / 2.0f;
    f32 s = sin( half_theta );

    return {
        cos( half_theta ),
        axis.x * s,
        axis.y * s,
        axis.z * s
    };
}
quat quat::create( const angle_axis& aa ) {
    return create( aa.theta, aa.axis );
}
quat quat::create( f32 pitch, f32 yaw, f32 roll ) {
    f32 half_x = pitch / 2.0f;
    f32 half_y = yaw   / 2.0f;
    f32 half_z = roll  / 2.0f;

    f32 x_sin = sin( half_x );
    f32 y_sin = sin( half_y );
    f32 z_sin = sin( half_z );

    f32 x_cos = cos( half_x );
    f32 y_cos = cos( half_y );
    f32 z_cos = cos( half_z );

    f32 xyz_cos = x_cos * y_cos * z_cos;
    f32 xyz_sin = x_sin * y_sin * z_sin;

    return {
        ( xyz_cos ) + ( xyz_sin ),
        ( x_sin * y_cos * z_cos ) + ( x_cos * y_sin * z_sin ),
        ( x_cos * y_sin * z_cos ) + ( x_sin * y_cos * z_sin ),
        ( x_cos * y_cos * z_sin ) + ( x_sin * y_sin * z_cos )
    };
}
quat quat::create( const euler_angles& euler ) {
    return create( euler.pitch, euler.yaw, euler.roll );
}
f32* quat::ptr() { return &w; }
const f32* quat::ptr() const { return &w; }
f32& quat::operator[]( u32 index ) { return ptr()[index]; }
f32 quat::operator[]( u32 index ) const { return ptr()[index]; }
quat& quat::operator-() { return *this *= -1.0f; }
bool32 quat::operator==( const quat& rhs ) const { return cmp( *this, rhs ); }
bool32 quat::operator!=( const quat& rhs ) const { return !(*this == rhs); }
quat& quat::operator+=( const quat& rhs ) {
    this->w += rhs.w;
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
}
quat& quat::operator-=( const quat& rhs ) {
    this->w -= rhs.w;
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
}
quat& quat::operator*=( f32 rhs ) {
    this->w *= rhs;
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
}
quat& quat::operator/=( f32 rhs ) {
    this->w /= rhs;
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    return *this;
}
quat operator+( const quat& lhs, const quat& rhs ) {
    return quat(lhs) += rhs;
}
quat operator-( const quat& lhs, const quat& rhs ) {
    return quat(lhs) -= rhs;
}
quat operator*( const quat& lhs, const quat& rhs ) {
   using namespace simd;

    const lane4f _negate_first = lane4f( -1.0f, 1.0f, 1.0f, 1.0f );

    lane4f _a = lane4f( lhs.x, lhs.x, lhs.y, lhs.z );
    lane4f _b = lane4f( rhs.x, rhs.w, rhs.w, rhs.w );
    _a = _a * _b;

    _b = lane4f( lhs.y, lhs.y, lhs.z, lhs.x );
    lane4f _c = lane4f( rhs.y, rhs.z, rhs.x, rhs.y );
    _b = _b * _c;

    _c = lane4f( lhs.z, lhs.z, lhs.x, lhs.y );
    lane4f _d = lane4f( rhs.z, rhs.y, rhs.z, rhs.x );
    _c = _c * _d;

    _c = _c * _negate_first;

    _d = _b - _c;
    _a = _a + _d;

    _a = _a * _negate_first;

    lane4f _w = lane4f( lhs.w );
    _b = lane4f( rhs.w, rhs.x, rhs.y, rhs.z );
    _w = _w * _b;

    quat result;
    store( result.ptr(), _w + _a );
    return result;

}
vec3 operator*( const quat& lhs, const vec3& rhs ) {
    vec3 qxyz = { lhs.x, lhs.y, lhs.z };
    vec3 t    = 2.0f * cross( qxyz, rhs );
    return rhs + t * lhs.w + cross( qxyz, t );
}
quat operator*( const quat& lhs, f32 rhs ) {
    return quat(lhs) *= rhs;
}
quat operator*( f32 lhs, const quat& rhs ) {
    return quat(rhs) *= lhs;
}
quat operator/( const quat& lhs, f32 rhs ) {
    return quat(lhs) /= rhs;
}
f32 sqr_mag( const quat& q ) {
    vec4 result = {
        q.w * q.w,
        q.x * q.x,
        q.y * q.y,
        q.z * q.z
    };
    return horizontal_add( result );
}
f32 mag( const quat& q ) {
    return sqrt( sqr_mag( q ) );
}
quat normalize( const quat& q ) {
    f32 m = mag( q );
    return m < 0.0001f ? quat::identity() : q / m;
}
quat conjugate( const quat& q ) {
    quat r = q;
    r   = -r;
    r.w = -r.w;
    return r;
}
quat inverse( const quat& q ) {
    return conjugate( q ) / sqr_mag( q );
}
f32 angle( const quat& a, const quat& b ) {
    quat qd = inverse( a ) * b;
    return 2.0f * atan2( mag( vec3::create( qd.x, qd.y, qd.z ) ), qd.w );
}
f32 unsigned_angle( const quat& a, const quat& b ) {
    return internal::signed_angle_to_unsigned( angle( a, b ) );
}
f32 dot( const quat& lhs, const quat& rhs ) {
    vec4 result = {
        lhs.w * rhs.w,
        lhs.x * rhs.x,
        lhs.y * rhs.y,
        lhs.z * rhs.z
    };
    return horizontal_add(result);
}
quat lerp( const quat& a, const quat& b, f32 t ) {
    return normalize( ( 1.0f - t ) * a + b * t );
}
quat clamped_lerp( const quat& a, const quat& b, f32 t ) {
    return lerp( a, b, clamp01(t) );
}
quat slerp( const quat& a, const quat& b, f32 t ) {
    quat _b = b;
    f32 theta = dot(a, b);
    f32 cos_theta = cos( theta );
    if( cos_theta < 0.0f ) {
        _b = -_b;
        cos_theta = -cos_theta;
    }
    if( cos_theta > 1.0f - F32::EPSILON ) {
        return lerp( a, b, t );
    } else {
        return normalize(( sin( ( 1.0f - t ) * theta ) * a + sin( t * theta ) * _b ) / sin( theta ));
    }
}
bool32 cmp( const quat& a, const quat& b ) {
    return sqr_mag(a - b) < VEC_CMP_THRESHOLD;
}
euler_angles quat_to_euler( const quat& q ) {
    return {
        atan2( 2.0f * (( q.w * q.x ) + ( q.y * q.z )), 1.0f - 2.0f * ( ( q.x * q.x ) + ( q.y * q.y ) ) ),
        asin_real( 2.0f * (( q.w * q.y ) - ( q.z * q.x )) ),
        atan2( 2.0f * (( q.w * q.z ) + ( q.x * q.y )), 1.0f - 2.0f * ( ( q.y * q.y ) + ( q.z * q.z ) ) ),
    };
}
angle_axis quat_to_angle_axis( const quat& q ) {
    f32 inv_w2_sqrt = sqrt(1.0f - (q.w * q.w));
    return {
        {
            q.x / inv_w2_sqrt,
            q.y / inv_w2_sqrt,
            q.z / inv_w2_sqrt
        },
        2.0f * acos(q.w),
    };
}

// NOTE(alicia): mat2

mat2 mat2::create( f32 m00, f32 m01, f32 m10, f32 m11 ) {
    return {
        m00, m01,
        m10, m11
    };
}
mat2 mat2::create( const mat3& m ) {
    return {
        m[0], m[1],
        m[3], m[4]
    };
}
mat2 mat2::create( const mat4& m ) {
    return {
        m[0], m[1],
        m[4], m[5]
    };
}
f32* mat2::ptr() { return &_m00; }
const f32* mat2::ptr() const { return &_m00; }
f32& mat2::operator[]( u32 index ) {
    return ptr()[index];
}
f32 mat2::operator[]( u32 index ) const {
    return ptr()[index];
}
vec2& mat2::column( u32 index ) {
    f32* flt = (f32*)this;
    return *(vec2*)&flt[index * 2];
}
const vec2& mat2::column( u32 index ) const {
    const f32* flt = (const f32*)this;
    return *(vec2*)&flt[index * 2];
}
vec2 mat2::row( u32 index ) const {
    return {
        (*this)[index],
        (*this)[index + 2]
    };
}
mat2& mat2::operator+=( const mat2& rhs ) {
    this->_col0 += rhs._col0;
    this->_col1 += rhs._col1;
    return *this;
}
mat2& mat2::operator-=( const mat2& rhs ) {
    this->_col0 -= rhs._col0;
    this->_col1 -= rhs._col1;
    return *this;
}
mat2& mat2::operator*=( f32 rhs ) {
    this->_col0 *= rhs;
    this->_col1 *= rhs;
    return *this;
}
mat2& mat2::operator/=( f32 rhs ) {
    this->_col0 /= rhs;
    this->_col1 /= rhs;
    return *this;
}
mat2& mat2::operator*=( const mat2& rhs ) {
    *this = {
        ((*this)[0] * rhs[0]) + ((*this)[2] * rhs[1]),
        ((*this)[1] * rhs[0]) + ((*this)[3] * rhs[1]),

        ((*this)[0] * rhs[2]) + ((*this)[2] * rhs[3]),
        ((*this)[1] * rhs[2]) + ((*this)[3] * rhs[3]),
    };
    return *this;
}
f32& mat2::nm( u32 row, u32 column ) {
    return (*this)[row + (column * 2)];
}
f32 mat2::nm( u32 row, u32 column ) const {
    return (*this)[row + (column * 2)];
}
mat2 operator+( const mat2& lhs, const mat2& rhs ) {
    return mat2(lhs) += rhs;
}
mat2 operator-( const mat2& lhs, const mat2& rhs ) {
    return mat2(lhs) -= rhs;
}
mat2 operator*( const mat2& lhs, f32 rhs ) {
    return mat2(lhs) *= rhs;
}
mat2 operator*( f32 lhs, const mat2& rhs ) {
    return mat2(rhs) *= lhs;
}
mat2 operator/( const mat2& lhs, f32 rhs ) {
    return mat2(lhs) /= rhs;
}
mat2 operator*( const mat2& lhs, const mat2& rhs ) {
    return mat2(lhs) *= rhs;
}
mat2 transpose( const mat2& m ) {
    return {
        m[0], m[2],
        m[1], m[3]
    };
}
f32 determinant( const mat2& m ) {
    return ( m[0] * m[3] ) - ( m[2] * m[1] );
}

// NOTE(alicia): mat3

mat3 mat3::create(
    f32 m00, f32 m01, f32 m02,
    f32 m10, f32 m11, f32 m12,
    f32 m20, f32 m21, f32 m22
) {
    return {
        m00, m01, m02,
        m10, m11, m12,
        m20, m21, m22
    };
}
mat3 mat3::create( const mat2& m ) {
    return {
        m[0], m[1], 0.0f,
        m[2], m[3], 0.0f,
        0.0f, 0.0f, 0.0f
    };
}
mat3 mat3::create( const mat4& m ) {
    return {
        m[0], m[1], m[2],
        m[4], m[5], m[6],
        m[8], m[9], m[10]
    };
}
f32* mat3::ptr() { return &_m00; }
const f32* mat3::ptr() const { return &_m00; }
f32& mat3::operator[]( u32 index ) { return ptr()[index]; }
f32 mat3::operator[]( u32 index ) const { return ptr()[index]; }
f32& mat3::nm( u32 row, u32 column ) {
    return (*this)[row + (column * 3)];
}
f32 mat3::nm( u32 row, u32 column ) const {
    return (*this)[row + (column * 3)];
}
vec3& mat3::column( u32 index ) {
    f32* flt = (f32*)this;
    return *(vec3*)&flt[index * 3];
}
const vec3& mat3::column( u32 index ) const {
    const f32* flt = (const f32*)this;
    return *(vec3*)&flt[index * 3];
}
vec3 mat3::row( u32 index ) const {
    return {
        (*this)[index],
        (*this)[index + 3],
        (*this)[index + 6]
    };
}
mat3& mat3::operator+=( const mat3& rhs ) {
    this->_col0 += rhs._col0;
    this->_col1 += rhs._col1;
    this->_col2 += rhs._col2;
    return *this;
}
mat3& mat3::operator-=( const mat3& rhs ) {
    this->_col0 -= rhs._col0;
    this->_col1 -= rhs._col1;
    this->_col2 -= rhs._col2;
    return *this;
}
mat3& mat3::operator*=( f32 rhs ) {
    this->_col0 *= rhs;
    this->_col1 *= rhs;
    this->_col2 *= rhs;
    return *this;
}
mat3& mat3::operator/=( f32 rhs ) {
    this->_col0 /= rhs;
    this->_col1 /= rhs;
    this->_col2 /= rhs;
    return *this;
}
mat3& mat3::operator*=( const mat3& rhs ) {
    *this = {
        // column - 0
        ( (*this)[0] * rhs[0] ) + ( (*this)[3] * rhs[1] ) + ( (*this)[6] * rhs[2] ),
        ( (*this)[1] * rhs[0] ) + ( (*this)[4] * rhs[1] ) + ( (*this)[7] * rhs[2] ),
        ( (*this)[2] * rhs[0] ) + ( (*this)[5] * rhs[1] ) + ( (*this)[8] * rhs[2] ),
        // column - 1
        ( (*this)[0] * rhs[3] ) + ( (*this)[3] * rhs[4] ) + ( (*this)[6] * rhs[5] ),
        ( (*this)[1] * rhs[3] ) + ( (*this)[4] * rhs[4] ) + ( (*this)[7] * rhs[5] ),
        ( (*this)[2] * rhs[3] ) + ( (*this)[5] * rhs[4] ) + ( (*this)[8] * rhs[5] ),
        // column - 2
        ( (*this)[0] * rhs[6] ) + ( (*this)[3] * rhs[7] ) + ( (*this)[6] * rhs[8] ),
        ( (*this)[1] * rhs[6] ) + ( (*this)[4] * rhs[7] ) + ( (*this)[7] * rhs[8] ),
        ( (*this)[2] * rhs[6] ) + ( (*this)[5] * rhs[7] ) + ( (*this)[8] * rhs[8] ),
    };
    return *this;
}
mat3 operator+( const mat3& lhs, const mat3& rhs ) {
    return mat3(lhs) += rhs;
}
mat3 operator-( const mat3& lhs, const mat3& rhs ) {
    return mat3(lhs) -= rhs;
}
mat3 operator*( const mat3& lhs, f32 rhs ) {
    return mat3(lhs) *= rhs;
}
mat3 operator*( f32 lhs, const mat3& rhs ) {
    return mat3(rhs) *= lhs;
}
mat3 operator/( const mat3& lhs, f32 rhs ) {
    return mat3(lhs) /= rhs;
}
mat3 operator*( const mat3& lhs, const mat3& rhs ) {
    return mat3(lhs) *= rhs;
}
mat3 transpose( const mat3& m ) {
    return {
        m[0], m[3], m[6],
        m[1], m[4], m[7],
        m[2], m[5], m[8]
    };
}
f32 determinant( const mat3& m ) {
    return
     ( m[0] * ( ( m[4] * m[8] ) - ( m[7] * m[5] ) ) ) +
    -( m[3] * ( ( m[1] * m[8] ) - ( m[7] * m[2] ) ) ) +
     ( m[6] * ( ( m[1] * m[5] ) - ( m[4] * m[2] ) ) );
}

// NOTE(alicia): mat4

mat4 mat4::create(
    f32 m00, f32 m01, f32 m02, f32 m03,
    f32 m10, f32 m11, f32 m12, f32 m13,
    f32 m20, f32 m21, f32 m22, f32 m23,
    f32 m30, f32 m31, f32 m32, f32 m33
) {
    return {
        m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33
    };
}
mat4 mat4::create( const mat2& m ) {
    return {
        m[0], m[1], 0.0f, 0.0f,
        m[2], m[3], 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    };
}
mat4 mat4::create( const mat3& m ) {
    return {
        m[0], m[1], m[2], 0.0f,
        m[3], m[4], m[5], 0.0f,
        m[6], m[7], m[8], 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    };
}
mat4 mat4::look_at( const vec3& position, const vec3& target, const vec3& up ) {
    vec3 z = normalize( target - position );
    vec3 x = cross( z, up );
    vec3 y = cross( x, z );
    z = -z;
    
    return {
        x.x, y.x, z.x, 0.0f,
        x.y, y.y, z.y, 0.0f,
        x.z, y.z, z.z, 0.0f,

        -dot( x, position ),
        -dot( y, position ),
        -dot( z, position ),
        1.0f
    };
}
mat4 mat4::ortho(
    f32 left, f32 right,
    f32 bottom, f32 top,
    f32 _near, f32 _far
) {
    mat4 result = identity();
    result[ 0] =  2.0f / ( right - left );
    result[ 5] =  2.0f / ( top - bottom );
    result[10] = -2.0f / ( _far - _near );
    result[12] = -( right + left ) / ( right - left );
    result[13] = -( top + bottom ) / ( top - bottom );
    result[14] = -( _far + _near ) / ( _far - _near );
    return result;
}
mat4 mat4::ortho(
    f32 left, f32 right,
    f32 bottom, f32 top
) {
    return ortho( left, right, bottom, top, -1.0f, 1.0f );
}
mat4 mat4::view2d( const vec2& position ) {
    return mat4::look_at(
        vec3::create(position) + vec3::forward(),
        vec3::create(position),
        vec3::up()
    );
}
mat4 mat4::projection2d( f32 aspect_ratio, f32 scale ) {
    f32 scaled_aspect_ratio = aspect_ratio * scale;
    return mat4::ortho(
        -scaled_aspect_ratio, scaled_aspect_ratio,
        -scale, scale
    );
}
mat4 mat4::projection2d( f32 aspect_ratio, const vec2& scale ) {
    f32 scaled_aspect_ratio = aspect_ratio * scale.x;
    return mat4::ortho(
        -scaled_aspect_ratio, scaled_aspect_ratio,
        -scale.y, scale.y
    );
}
mat4 mat4::perspective( f32 fov, f32 aspect, f32 _near, f32 _far ) {
    mat4 result = {};

    f32 half_fov_tan   = tan( fov / 2.0f );
    f32 far_minus_near = _far - _near;
    result[ 0] = 1.0f / ( aspect * half_fov_tan );
    result[ 5] = 1.0f / half_fov_tan;
    result[10] = -( ( _far + _near ) / far_minus_near );
    result[11] = -1.0f;
    result[14] = -( ( 2.0f * _far * _near ) / far_minus_near );

    return result;
}
mat4 mat4::translate( const vec3& translation ) {
    mat4 result = identity();
    result[12] = translation.x;
    result[13] = translation.y;
    result[14] = translation.z;
    return result;
}
mat4 mat4::translate( f32 x, f32 y, f32 z ) {
    return translate( { x, y, z } );
}
mat4 mat4::translate2d( const vec2& translation ) {
    return mat4::translate( vec3::create( translation ) );
}
mat4 mat4::translate2d( f32 x, f32 y ) {
    return mat4::translate( x, y, 0.0f );
}
mat4 mat4::rotate_pitch( f32 pitch ) {
    mat4 result = identity();

    f32 _cos = cos(pitch);
    f32 _sin = sin(pitch);

    result[5]  =  _cos;
    result[6]  =  _sin;
    result[9]  = -_sin;
    result[10] =  _cos;

    return result;
}
mat4 mat4::rotate_yaw( f32 yaw ) {
    mat4 result = identity();

    f32 _cos = cos(yaw);
    f32 _sin = sin(yaw);

    result[0]  =  _cos;
    result[2]  = -_sin;
    result[8]  =  _sin;
    result[10] =  _cos;

    return result;
}
mat4 mat4::rotate_roll( f32 roll ) {
    mat4 result = identity();

    f32 _cos = cos(roll);
    f32 _sin = sin(roll);

    result[0] =  _cos;
    result[1] =  _sin;
    result[4] = -_sin;
    result[5] =  _cos;

    return result;
}
mat4 mat4::rotate( const euler_angles& rotation ) {
    return rotate_pitch( rotation.pitch ) *
        rotate_yaw( rotation.yaw ) *
        rotate_roll( rotation.roll );
}
mat4 mat4::rotate( const quat& rotation ) {
    mat4 result = identity();

    f32 _2x2 = 2.0f * (rotation.x * rotation.x);
    f32 _2y2 = 2.0f * (rotation.y * rotation.y);
    f32 _2z2 = 2.0f * (rotation.z * rotation.z);

    f32 _2xy = 2.0f * (rotation.x * rotation.y);
    f32 _2xz = 2.0f * (rotation.x * rotation.z);
    f32 _2yz = 2.0f * (rotation.y * rotation.z);
    f32 _2wx = 2.0f * (rotation.w * rotation.x);
    f32 _2wy = 2.0f * (rotation.w * rotation.y);
    f32 _2wz = 2.0f * (rotation.w * rotation.z);

    result[0] = 1.0f - _2y2 - _2z2;
    result[1] = _2xy + _2wz;
    result[2] = _2xz - _2wy;

    result[4] = _2xy - _2wz;
    result[5] = 1.0f - _2x2 - _2z2;
    result[6] = _2yz + _2wx;

    result[8]  = _2xz + _2wy;
    result[9]  = _2yz - _2wx;
    result[10] = 1.0f - _2x2 - _2y2;

    return result;
}
mat4 mat4::rotate2d( f32 theta ) {
    return mat4::rotate_roll( theta );
}
mat4 mat4::scale( const vec3& scale ) {
    mat4 result = identity();

    result[0]  = scale.x;
    result[5]  = scale.y;
    result[10] = scale.z;

    return result;
}
mat4 mat4::scale( f32 x, f32 y, f32 z ) {
    return mat4::scale( vec3::create( x, y, z ) );
}
mat4 mat4::scale2d( const vec2& scale ) {
    return mat4::scale( scale.x, scale.y, 1.0f );
}
mat4 mat4::scale2d( f32 x, f32 y ) {
    return mat4::scale( x, y, 1.0f );
}
mat4 mat4::transform(
    const vec3& translation,
    const quat& rotation,
    const vec3& scale
) {
    return mat4::translate( translation ) *
        mat4::rotate( rotation ) *
        mat4::scale( scale );
}
mat4 mat4::transform(
    const vec3& translation,
    const euler_angles& rotation,
    const vec3& scale
) {
    return mat4::translate( translation ) *
        mat4::rotate( rotation ) *
        mat4::scale( scale );
}
mat4 mat4::transform2d(
    const vec2& translation,
    f32 rotation,
    const vec2& scale
) {
    return mat4::translate2d( translation ) *
        mat4::rotate2d( rotation ) *
        mat4::scale2d( scale );
}
f32* mat4::ptr() { return &_m00; }
const f32* mat4::ptr() const { return &_m00; }
f32& mat4::operator[]( u32 index ) { return ptr()[index]; }
f32 mat4::operator[]( u32 index ) const { return ptr()[index]; }
vec4& mat4::column( u32 index ) {
    f32* flt = (f32*)this;
    return *(vec4*)&flt[index * 4];
}
const vec4& mat4::column( u32 index ) const {
    const f32* flt = (const f32*)this;
    return *(vec4*)&flt[index * 4];
}
vec4 mat4::row( u32 index ) const {
    return {
        (*this)[index],
        (*this)[index + 4],
        (*this)[index + 8],
        (*this)[index + 12]
    };
}
f32& mat4::nm( u32 row, u32 column ) {
    return (*this)[row + (column * 4)];
}
f32 mat4::nm( u32 row, u32 column ) const {
    return (*this)[row + (column * 4)];
}
mat4& mat4::operator+=( const mat4& rhs ) {
    using namespace simd;
    lane4f _lhs0, _lhs1, _lhs2, _lhs3;
    lane4f _rhs0, _rhs1, _rhs2, _rhs3;

    _lhs0 = lane4f( this->_col0.ptr() );
    _lhs1 = lane4f( this->_col1.ptr() );
    _lhs2 = lane4f( this->_col2.ptr() );
    _lhs3 = lane4f( this->_col3.ptr() );

    _rhs0 = lane4f( rhs._col0.ptr() );
    _rhs1 = lane4f( rhs._col1.ptr() );
    _rhs2 = lane4f( rhs._col2.ptr() );
    _rhs3 = lane4f( rhs._col3.ptr() );

    mat4 result;
    store( result._col0.ptr(), _lhs0 + _rhs0 );
    store( result._col1.ptr(), _lhs1 + _rhs1 );
    store( result._col2.ptr(), _lhs2 + _rhs2 );
    store( result._col3.ptr(), _lhs3 + _rhs3 );
    *this = result;
    return *this;
}
mat4& mat4::operator-=( const mat4& rhs ) {
    using namespace simd;
    lane4f _lhs0, _lhs1, _lhs2, _lhs3;
    lane4f _rhs0, _rhs1, _rhs2, _rhs3;

    _lhs0 = lane4f( this->_col0.ptr() );
    _lhs1 = lane4f( this->_col1.ptr() );
    _lhs2 = lane4f( this->_col2.ptr() );
    _lhs3 = lane4f( this->_col3.ptr() );

    _rhs0 = lane4f( rhs._col0.ptr() );
    _rhs1 = lane4f( rhs._col1.ptr() );
    _rhs2 = lane4f( rhs._col2.ptr() );
    _rhs3 = lane4f( rhs._col3.ptr() );

    mat4 result;
    store( result._col0.ptr(), _lhs0 - _rhs0 );
    store( result._col1.ptr(), _lhs1 - _rhs1 );
    store( result._col2.ptr(), _lhs2 - _rhs2 );
    store( result._col3.ptr(), _lhs3 - _rhs3 );
    *this = result;
    return *this;
}
mat4& mat4::operator*=( f32 rhs ) {
    using namespace simd;
    lane4f _lhs0, _lhs1, _lhs2, _lhs3;
    lane4f _rhs;

    _lhs0 = lane4f( this->_col0.ptr() );
    _lhs1 = lane4f( this->_col1.ptr() );
    _lhs2 = lane4f( this->_col2.ptr() );
    _lhs3 = lane4f( this->_col3.ptr() );

    _rhs = lane4f( rhs );

    mat4 result;
    store( result._col0.ptr(), _lhs0 * _rhs );
    store( result._col1.ptr(), _lhs1 * _rhs );
    store( result._col2.ptr(), _lhs2 * _rhs );
    store( result._col3.ptr(), _lhs3 * _rhs );
    *this = result;
    return *this;
}
mat4& mat4::operator/=( f32 rhs ) {
    using namespace simd;
    lane4f _lhs0, _lhs1, _lhs2, _lhs3;
    lane4f _rhs;

    _lhs0 = lane4f( this->_col0.ptr() );
    _lhs1 = lane4f( this->_col1.ptr() );
    _lhs2 = lane4f( this->_col2.ptr() );
    _lhs3 = lane4f( this->_col3.ptr() );

    _rhs = lane4f( rhs );

    mat4 result;
    store( result._col0.ptr(), _lhs0 / _rhs );
    store( result._col1.ptr(), _lhs1 / _rhs );
    store( result._col2.ptr(), _lhs2 / _rhs );
    store( result._col3.ptr(), _lhs3 / _rhs );
    *this = result;
    return *this;
}
mat4& mat4::operator*=( const mat4& rhs ) {
    using namespace simd;
    const u32 COLUMN_LENGTH = 4;

    // TODO(alicia): see if this can't be made even faster

    mat4 result = {};

    lane4f _a, _b, _c;

    u32 col = 0;
    u32 row = 0;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    row = 1;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    row = 2;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    row = 3;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    col = 1;
    row = 0;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    row = 1;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    row = 2;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    row = 3;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    col = 2;
    row = 0;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    row = 1;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    row = 2;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    row = 3;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    col = 3;
    row = 0;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    row = 1;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    row = 2;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );

    row = 3;
    _a = lane4f( &(*this)[ row * COLUMN_LENGTH ] );
    _b = _a * lane4f( rhs[ (col * COLUMN_LENGTH) + row ] );
    _c = lane4f( &result[  col * COLUMN_LENGTH ] );
    store( &result[ col * COLUMN_LENGTH ], _b + _c );


    *this = result;
    return *this;
}
mat4 operator+( const mat4& lhs, const mat4& rhs ) {
    return mat4(lhs) += rhs;
}
mat4 operator-( const mat4& lhs, const mat4& rhs ) {
    return mat4(lhs) -= rhs;
}
mat4 operator*( const mat4& lhs, f32 rhs ) {
    return mat4(lhs) *= rhs;
}
mat4 operator/( const mat4& lhs, f32 rhs ) {
    return mat4(lhs) /= rhs;
}
mat4 operator*( const mat4& lhs, const mat4& rhs ) {
    return mat4(lhs) *= rhs;
}
mat4 operator*( f32 lhs, const mat4& rhs ) {
    return rhs * lhs;
}
vec3 operator*( const mat4& lhs, const vec3& rhs ) {
    return {
        ( lhs[0] * rhs[0] ) + ( lhs[4] * rhs[1] ) + ( lhs[8]  * rhs[2] ) + lhs[12],
        ( lhs[1] * rhs[0] ) + ( lhs[5] * rhs[1] ) + ( lhs[9]  * rhs[2] ) + lhs[13],
        ( lhs[2] * rhs[0] ) + ( lhs[6] * rhs[1] ) + ( lhs[10] * rhs[2] ) + lhs[14],
    };
}
vec4 operator*( const mat4& lhs, const vec4& rhs  ) {
    return {
        ( lhs[0] * rhs[0] ) + ( lhs[4] * rhs[1] ) + ( lhs[8]  * rhs[2] ) + ( lhs[12] * rhs[3] ),
        ( lhs[1] * rhs[0] ) + ( lhs[5] * rhs[1] ) + ( lhs[9]  * rhs[2] ) + ( lhs[13] * rhs[3] ),
        ( lhs[2] * rhs[0] ) + ( lhs[6] * rhs[1] ) + ( lhs[10] * rhs[2] ) + ( lhs[14] * rhs[3] ),
        ( lhs[3] * rhs[0] ) + ( lhs[7] * rhs[1] ) + ( lhs[11] * rhs[2] ) + ( lhs[15] * rhs[3] ),
    };
}
mat4 transpose( const mat4& m ) {
    return {
        m[0], m[4], m[8],  m[12],
        m[1], m[5], m[9],  m[13],
        m[2], m[6], m[10], m[14],
        m[3], m[7], m[11], m[15]
    };
}
mat3 submatrix( const mat4& m, u32 row, u32 column ) {
    mat3 result;
    u32 i = 0;
    for( u32 _col = 0; _col < 4; ++_col ) {
        if( _col != column ) {
            for( u32 _row = 0; _row < 4; ++_row ) {
                if( _row != row ) {
                    result[i] = m.column( _col )[_row];
                    ++i;
                }
            }
        }
    }
    return result;
}
f32 minor( const mat4& m, u32 row, u32 column ) {
    return determinant( submatrix( m, row, column ) );
}
f32 cofactor( const mat4& m, u32 row, u32 column ) {
    f32 _minor = minor( m, row, column );
    return _minor * powi( -1.0f, ( row + 1 ) + ( column + 1 ) );
}
mat4 cofactor_matrix( const mat4& m ) {
    return {
        cofactor( m, 0, 0 ), cofactor( m, 0, 1 ), cofactor( m, 0, 2 ), cofactor( m, 0, 3 ),
        cofactor( m, 1, 0 ), cofactor( m, 1, 1 ), cofactor( m, 1, 2 ), cofactor( m, 1, 3 ),
        cofactor( m, 2, 0 ), cofactor( m, 2, 1 ), cofactor( m, 2, 2 ), cofactor( m, 2, 3 ),
        cofactor( m, 3, 0 ), cofactor( m, 3, 1 ), cofactor( m, 3, 2 ), cofactor( m, 3, 3 )
    };
}
mat4 adjoint( const mat4& m ) {
    return transpose( cofactor_matrix( m ) );
}
f32 determinant( const mat4& m ) {
    return ( m[0]  * determinant( submatrix( m, 0, 0 ) ) ) -
           ( m[4]  * determinant( submatrix( m, 0, 1 ) ) ) +
           ( m[8]  * determinant( submatrix( m, 0, 2 ) ) ) -
           ( m[12] * determinant( submatrix( m, 0, 3 ) ) );
}
bool32 inverse( const mat4& m, mat4& result ) {
    f32 det = determinant( m );
    if( det == 0.0f ) {
        return false;
    } else {
        result = adjoint( m ) / det;
        return true;
    }
}
mat4 inverse_unchecked( const mat4& m ) {
    return adjoint( m ) / determinant( m );
}
bool32 normal_matrix( const mat4& transform, mat3& result ) {
    mat4 _inverse;
    if( inverse( transform, _inverse ) ) {
        result = mat3::create(transpose( _inverse ));
        return true;
    } else {
        return false;
    }
}
mat3 normal_matrix_unchecked( const mat4& transform ) {
    return mat3::create(transpose( inverse_unchecked( transform ) ));
}

lcg new_lcg( i32 seed ) {
    lcg result  = {};
    result.seed = seed;
    result.a    = 166463;
    result.b    = 235;
    result.m    = 21446837;
    result.current = result.seed;
    return result;
}
lcg64 new_lcg64( i64 seed ) {
    lcg64 result  = {};
    result.seed = seed;
    result.a    = 1664654683;
    result.b    = 2384695;
    result.m    = 2144683865487;
    result.current = result.seed;
    return result;
}
void rand( lcg& state, i32& next ) {
    state.current = ( state.a * state.current + state.b ) % state.m;
    next = state.current;
}
void rand( lcg& state, f32& next ) {
    i32 result;
    rand( state, result );
    next = (f32)result / (f32)state.m;
}
void rand( lcg& state, vec2& result ) {
    rand( state, result.x );
    rand( state, result.y );
}
void rand( lcg& state, ivec2& result ) {
    rand(state, result.x);
    rand(state, result.y);
}
void rand( lcg& state, vec3& result ) {
    rand( state, result.x );
    rand( state, result.y );
    rand( state, result.z );
}
void rand( lcg& state, ivec3& result ) {
    rand(state, result.x);
    rand(state, result.y);
    rand(state, result.z);
}
void rand( lcg& state, vec4& result ) {
    rand( state, result.x );
    rand( state, result.y );
    rand( state, result.z );
    rand( state, result.w );
}
void rand( lcg& state, ivec4& result ) {
    rand(state, result.x);
    rand(state, result.y);
    rand(state, result.z);
    rand(state, result.w);
}
void rand( lcg64& state, i64& next ) {
    state.current = ( state.a * state.current + state.b ) % state.m;
    next = state.current;
}
void rand( lcg64& state, f64& next ) {
    i64 result;
    rand( state, result );
    next = (f64)result / (f64)state.m;
}

xor_shift new_xor_shift( u32 seed ) {
    xor_shift result = {};
    result.seed = max( seed, (u32)1 );
    result.current = result.seed;
    return result;
}
xor_shift64 new_xor_shift64( u64 seed ) {
    xor_shift64 result = {};
    result.seed = max( seed, (u64)1 );
    result.current = result.seed;
    return result;
}
void rand( xor_shift& state, u32& next ) {
    u32 result = state.current;
    result ^= result << 13;
    result ^= result >> 17;
    result ^= result << 5;

    state.current = result;
    next = result;
}
void rand( xor_shift& state, i32& next ) {
    u32 result;
    rand( state, result );
    next = *(i32*)&result;
}
void rand( xor_shift& state, f32& next ) {
    i32 result;
    rand( state, result );
    next = normalize_range(result);
}
void rand( xor_shift& state, vec2& result ) {
    rand( state, result.x );
    rand( state, result.y );
}
void rand( xor_shift& state, ivec2& result ) {
    rand( state, result.x );
    rand( state, result.y );
}
void rand( xor_shift& state, vec3& result ) {
    rand( state, result.x );
    rand( state, result.y );
    rand( state, result.z );
}
void rand( xor_shift& state, ivec3& result ) {
    rand( state, result.x );
    rand( state, result.y );
    rand( state, result.z );
}
void rand( xor_shift& state, vec4& result ) {
    rand( state, result.x );
    rand( state, result.y );
    rand( state, result.z );
    rand( state, result.w );
}
void rand( xor_shift& state, ivec4& result ) {
    rand( state, result.x );
    rand( state, result.y );
    rand( state, result.z );
    rand( state, result.w );
}
void rand( xor_shift64& state, u64& next ) {
    u64 result = state.current;
    result ^= result << 13;
    result ^= result >> 7;
    result ^= result << 17;

    state.current = result;
    next = result;
}
void rand( xor_shift64& state, i64& next ) {
    u64 result;
    rand( state, result );
    next = *(i64*)&result;
}
void rand( xor_shift64& state, f64& next ) {
    i64 result;
    rand( state, result );
    next = normalize_range64(result);
}

} // namespace smath
