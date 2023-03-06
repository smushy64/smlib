/**
 * Description:  C++ Math library
 * Author:       Alicia Amarilla (smushy) 
 * File Created: February 06, 2023
 * Includes:     "smalias.h"   required
 *               <immintrin.h> if SMUSHY_SIMD_ENABLED is defined (BEFORE INCLUDING smath.hpp!)
*/

#if !defined(SMUSHY_SMATH)
#define SMUSHY_SMATH

#include "smdef.h"

#if defined(__x86_64__) || defined(_M_X64)
    #define SMUSHY_X86_64_PLATFORM
#endif

#if defined(SMUSHY_SIMD_ENABLED)

#if defined(SMUSHY_X86_64_PLATFORM)

typedef __attribute((vector_size(16))) float __m128;
typedef __attribute((vector_size(32))) float __m256;

#endif // simd::x86

#endif // simd

namespace smath {

namespace simd {

struct lane4f {
    union {
        struct { f32 a, b, c, d; };
#if defined(SMUSHY_SIMD_ENABLED)

#if defined(SMUSHY_X86_64_PLATFORM)
        __m128 simd;
#endif // simd::x86

#endif // simd
    };

    lane4f();
    lane4f( f32 a, f32 b, f32 c, f32 d );
    lane4f( f32 scalar );
    lane4f( const f32* four_wide_array );

    f32& operator[]( u32 index );
    f32  operator[]( u32 index ) const;

    lane4f& operator+=( const lane4f& rhs );
    lane4f& operator-=( const lane4f& rhs );
    lane4f& operator*=( const lane4f& rhs );
    lane4f& operator/=( const lane4f& rhs );
};
lane4f operator+( const lane4f& lhs, const lane4f& rhs );
lane4f operator-( const lane4f& lhs, const lane4f& rhs );
lane4f operator*( const lane4f& lhs, const lane4f& rhs );
lane4f operator/( const lane4f& lhs, const lane4f& rhs );
lane4f sqrt( lane4f x );
void store( f32* four_wide_array, lane4f registers );

struct lane8f {
    union {
        struct { f32 a, b, c, d, e, f, g, h; };
#if defined(SMUSHY_SIMD_ENABLED)

#if defined(SMUSHY_X86_64_PLATFORM)
        __m256 simd;
#endif // simd::x86

#endif // simd
    };

    lane8f();
    lane8f( f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h );
    lane8f( f32 scalar );
    lane8f( const f32* eight_wide_array );

    f32& operator[]( u32 index );
    f32  operator[]( u32 index ) const;
    lane8f& operator+=( const lane8f& rhs );
    lane8f& operator-=( const lane8f& rhs );
    lane8f& operator*=( const lane8f& rhs );
    lane8f& operator/=( const lane8f& rhs );
};
lane8f operator+( const lane8f& lhs, const lane8f& rhs );
lane8f operator-( const lane8f& lhs, const lane8f& rhs );
lane8f operator*( const lane8f& lhs, const lane8f& rhs );
lane8f operator/( const lane8f& lhs, const lane8f& rhs );
lane8f sqrt( lane8f x );
void store( f32* eight_wide_array, lane8f registers );
lane4f extract_high( lane8f a );
lane4f extract_low( lane8f a );

} // namespace smath::simd

// NOTE(alicia): FUNCTIONS -------------------------------------------------------------------------------------------------

/// @brief  truncate x
/// @param x floating-point number
/// @return input number without the fractional part as i64
i64 trunc64( f32 x );
/// @brief  truncate x
/// @param x floating-point number
/// @return input number without the fractional part as i64
i64 trunc64( f64 x );
/// @brief  truncate x
/// @param x floating-point number
/// @return input number without the fractional part as i32
i32 trunc32( f32 x );
/// @brief  truncate x
/// @param x floating-point number
/// @return input number without the fractional part as i32
i32 trunc32( f64 x );
/// @brief  truncate x
/// @param x floating-point number
/// @return input number without the fractional part as i16
i16 trunc16( f32 x );
/// @brief  truncate x
/// @param x floating-point number
/// @return input number without the fractional part as i16
i16 trunc16( f64 x );
/// @brief  truncate x
/// @param x floating-point number
/// @return input number without the fractional part as i8
i8 trunc8( f32 x );
/// @brief  truncate x
/// @param x floating-point number
/// @return input number without the fractional part as i8
i8 trunc8( f64 x );

/// @brief  floor x
/// @param x floating-point number
/// @return round down as i64
i64 floor64( f64 x );
/// @brief  floor x
/// @param x floating-point number
/// @return round down as i64
i64 floor64( f32 x );
/// @brief  floor x
/// @param x floating-point number
/// @return round down as i32
i32 floor32( f64 x );
/// @brief  floor x
/// @param x floating-point number
/// @return round down as i32
i32 floor32( f32 x );
/// @brief  floor x
/// @param x floating-point number
/// @return round down as i16
i16 floor16( f64 x );
/// @brief  floor x
/// @param x floating-point number
/// @return round down as i16
i16 floor16( f32 x );
/// @brief  floor x
/// @param x floating-point number
/// @return round down as i8
i8 floor8( f64 x );
/// @brief  floor x
/// @param x floating-point number
/// @return round down as i8
i8 floor8( f32 x );

/// @brief  ceil x
/// @param x floating-point number
/// @return round up as i64
i64 ceil64( f64 x );
/// @brief  ceil x
/// @param x floating-point number
/// @return round up as i64
i64 ceil64( f32 x );
/// @brief  ceil x
/// @param x floating-point number
/// @return round up as i32
i32 ceil32( f64 x );
/// @brief  ceil x
/// @param x floating-point number
/// @return round up as i32
i32 ceil32( f32 x );
/// @brief  ceil x
/// @param x floating-point number
/// @return round up as i16
i16 ceil16( f64 x );
/// @brief  ceil x
/// @param x floating-point number
/// @return round up as i16
i16 ceil16( f32 x );
/// @brief  ceil x
/// @param x floating-point number
/// @return round up as i8
i8 ceil8( f64 x );
/// @brief  ceil x
/// @param x floating-point number
/// @return round up as i8
i8 ceil8( f32 x );

/// @brief  round x
/// @param x floating-point number
/// @return round as i64
i64 round64( f64 x );
/// @brief  round x
/// @param x floating-point number
/// @return round as i64
i64 round64( f32 x );
/// @brief  round x
/// @param x floating-point number
/// @return round as i32
i32 round32( f64 x );
/// @brief  round x
/// @param x floating-point number
/// @return round as i32
i32 round32( f32 x );
/// @brief  round x
/// @param x floating-point number
/// @return round as i16
i16 round16( f64 x );
/// @brief  round x
/// @param x floating-point number
/// @return round as i16
i16 round16( f32 x );
/// @brief  round x
/// @param x floating-point number
/// @return round as i8
i8 round8( f64 x );
/// @brief  round x
/// @param x floating-point number
/// @return round as i8
i8 round8( f32 x );

/// @brief sign of x
/// @param x integer
/// @return -1 if negative, otherwise 1 as i8
i8 sign( i8 x );
/// @brief sign of x
/// @param x integer
/// @return -1 if negative, otherwise 1 as i16
i16 sign( i16 x );
/// @brief sign of x
/// @param x integer
/// @return -1 if negative, otherwise 1 as i32
i32 sign( i32 x );
/// @brief sign of x
/// @param x integer
/// @return -1 if negative, otherwise 1 as i64
i64 sign( i64 x );
/// @brief sign of x
/// @param x floating-point number
/// @return -1.0 if negative, otherwise 1.0 as f32
f32 sign( f32 x );
/// @brief sign of x
/// @param x floating-point number
/// @return -1.0 if negative, otherwise 1.0 as f64
f64 sign( f64 x );

/// @brief absolute value of x
/// @param x integer
/// @return magnitude of real number x as i8
i8 absolute( i8 x );
/// @brief absolute value of x
/// @param x integer
/// @return magnitude of real number x as i16
i16 absolute( i16 x );
/// @brief absolute value of x
/// @param x integer
/// @return magnitude of real number x as i32
i32 absolute( i32 x );
/// @brief absolute value of x
/// @param x integer
/// @return magnitude of real number x as i64
i64 absolute( i64 x );
/// @brief absolute value of x
/// @param x integer
/// @return magnitude of real number x as f32
f32 absolute( f32 x );
/// @brief absolute value of x
/// @param x integer
/// @return magnitude of real number x as f64
f64 absolute( f64 x );

/// @brief clamp value between min and max range
/// @param value value to clamp
/// @param min minimum range, inclusive
/// @param max maximum range, inclusive
/// @return clamped value as i8
i8 clamp( i8 value, i8 min, i8 max );
/// @brief clamp value between min and max range
/// @param value value to clamp
/// @param min minimum range, inclusive
/// @param max maximum range, inclusive
/// @return clamped value as i16
i16 clamp( i16 value, i16 min, i16 max );
/// @brief clamp value between min and max range
/// @param value value to clamp
/// @param min minimum range, inclusive
/// @param max maximum range, inclusive
/// @return clamped value as i32
i32 clamp( i32 value, i32 min, i32 max );
/// @brief clamp value between min and max range
/// @param value value to clamp
/// @param min minimum range, inclusive
/// @param max maximum range, inclusive
/// @return clamped value as i64
i64 clamp( i64 value, i64 min, i64 max );
/// @brief clamp value between min and max range
/// @param value value to clamp
/// @param min minimum range, inclusive
/// @param max maximum range, inclusive
/// @return clamped value as u8
u8 clamp( u8 value, u8 min, u8 max );
/// @brief clamp value between min and max range
/// @param value value to clamp
/// @param min minimum range, inclusive
/// @param max maximum range, inclusive
/// @return clamped value as u16
u16 clamp( u16 value, u16 min, u16 max );
/// @brief clamp value between min and max range
/// @param value value to clamp
/// @param min minimum range, inclusive
/// @param max maximum range, inclusive
/// @return clamped value as u32
u32 clamp( u32 value, u32 min, u32 max );
/// @brief clamp value between min and max range
/// @param value value to clamp
/// @param min minimum range, inclusive
/// @param max maximum range, inclusive
/// @return clamped value as u64
u64 clamp( u64 value, u64 min, u64 max );
/// @brief clamp value between min and max range
/// @param value value to clamp
/// @param min minimum range, inclusive
/// @param max maximum range, inclusive
/// @return clamped value as f32
f32 clamp( f32 value, f32 min, f32 max );
/// @brief clamp value between min and max range
/// @param value value to clamp
/// @param min minimum range, inclusive
/// @param max maximum range, inclusive
/// @return clamped value as f64
f64 clamp( f64 value, f64 min, f64 max );
/// @brief clamp value between 0-1 range
/// @param value value to clamp
/// @return clamped value as f32
f32 clamp01( f32 value );
/// @brief clamp value between 0-1 range
/// @param value value to clamp
/// @return clamped value as f64
f64 clamp01( f64 value );

/// @brief smallest of two values
/// @param a,b values to test
/// @return smallest value as i8
i8 min( i8 a, i8 b);
/// @brief smallest of two values
/// @param a,b values to test
/// @return smallest value as i16
i16 min( i16 a, i16 b);
/// @brief smallest of two values
/// @param a,b values to test
/// @return smallest value as i32
i32 min( i32 a, i32 b);
/// @brief smallest of two values
/// @param a,b values to test
/// @return smallest value as i64
i64 min( i64 a, i64 b);
/// @brief smallest of two values
/// @param a,b values to test
/// @return smallest value as u8
u8 min( u8 a, u8 b);
/// @brief smallest of two values
/// @param a,b values to test
/// @return smallest value as u16
u16 min( u16 a, u16 b);
/// @brief smallest of two values
/// @param a,b values to test
/// @return smallest value as u32
u32 min( u32 a, u32 b);
/// @brief smallest of two values
/// @param a,b values to test
/// @return smallest value as u64
u64 min( u64 a, u64 b);
/// @brief smallest of two values
/// @param a,b values to test
/// @return smallest value as f32
f32 min( f32 a, f32 b);
/// @brief smallest of two values
/// @param a,b values to test
/// @return smallest value as f64
f64 min( f64 a, f64 b);

/// @brief largest of two values
/// @param a,b values to test
/// @return largest value as i8
i8 max( i8 a, i8 b);
/// @brief largest of two values
/// @param a,b values to test
/// @return largest value as i16
i16 max( i16 a, i16 b);
/// @brief largest of two values
/// @param a,b values to test
/// @return largest value as i32
i32 max( i32 a, i32 b);
/// @brief largest of two values
/// @param a,b values to test
/// @return largest value as i64
i64 max( i64 a, i64 b);
/// @brief largest of two values
/// @param a,b values to test
/// @return largest value as u8
u8 max( u8 a, u8 b);
/// @brief largest of two values
/// @param a,b values to test
/// @return largest value as u16
u16 max( u16 a, u16 b);
/// @brief largest of two values
/// @param a,b values to test
/// @return largest value as u32
u32 max( u32 a, u32 b);
/// @brief largest of two values
/// @param a,b values to test
/// @return largest value as u64
u64 max( u64 a, u64 b);
/// @brief largest of two values
/// @param a,b values to test
/// @return largest value as f32
f32 max( f32 a, f32 b);
/// @brief largest of two values
/// @param a,b values to test
/// @return largest value as f64
f64 max( f64 a, f64 b);

/// @brief normalize integer to -1 to 1 range.
/// @param x integer
/// @return result as f32
f32 normalize_range( i8 x );
/// @brief normalize integer to -1 to 1 range.
/// @param x integer
/// @return result as f32
f32 normalize_range( i16 x );
/// @brief normalize integer to -1 to 1 range.
/// @param x integer
/// @return result as f32
f32 normalize_range( i32 x );
/// @brief normalize integer to -1 to 1 range.
/// @param x integer
/// @return result as f32
f32 normalize_range( i64 x );
/// @brief normalize integer to 0-1 range.
/// @param x integer
/// @return result as f32
f32 normalize_range( u8 x );
/// @brief normalize integer to 0-1 range.
/// @param x integer
/// @return result as f32
f32 normalize_range( u16 x );
/// @brief normalize integer to 0-1 range.
/// @param x integer
/// @return result as f32
f32 normalize_range( u32 x );
/// @brief normalize integer to 0-1 range.
/// @param x integer
/// @return result as f32
f32 normalize_range( u64 x );
/// @brief normalize integer to -1 to 1 range.
/// @param x integer
/// @return result as f64
f64 normalize_range64( i8 x );
/// @brief normalize integer to -1 to 1 range.
/// @param x integer
/// @return result as f64
f64 normalize_range64( i16 x );
/// @brief normalize integer to -1 to 1 range.
/// @param x integer
/// @return result as f64
f64 normalize_range64( i32 x );
/// @brief normalize integer to -1 to 1 range.
/// @param x integer
/// @return result as f64
f64 normalize_range64( i64 x );
/// @brief normalize integer to 0-1 range.
/// @param x integer
/// @return result as f64
f64 normalize_range64( u8 x );
/// @brief normalize integer to 0-1 range.
/// @param x integer
/// @return result as f64
f64 normalize_range64( u16 x );
/// @brief normalize integer to 0-1 range.
/// @param x integer
/// @return result as f64
f64 normalize_range64( u32 x );
/// @brief normalize integer to 0-1 range.
/// @param x integer
/// @return result as f64
f64 normalize_range64( u64 x );

/// @brief square root of x
/// @param x floating-point number
/// @return square root as f64
f64 sqrt( f64 x );
/// @brief square root of x
/// @param x floating-point number
/// @return square root as f32
f32 sqrt( f32 x );

/// @brief raise x to the power of exponent
/// @param base floating-point number
/// @param exponent integer
/// @return power
f32 powi( f32 base, i32 exponent );
/// @brief raise x to the power of exponent
/// @param base floating-point number
/// @param exponent integer
/// @return power
f64 powi( f64 base, i32 exponent );
/// @brief raise x to the power of exponent
/// @param base floating-point number
/// @param exponent floating-point number
/// @return power
f32 pow( f32 base, f32 exponent );
/// @brief raise x to the power of exponent
/// @param base floating-point number
/// @param exponent floating-point number
/// @return power
f64 pow( f64 base, f64 exponent );

/// @brief floating point modulo operation
/// @param lhs numerator
/// @param rhs denominator
/// @return remainder of division as f32
f32 mod( f32 lhs, f32 rhs );
/// @brief floating point modulo operation
/// @param lhs numerator
/// @param rhs denominator
/// @return remainder of division as f64
f64 mod( f64 lhs, f64 rhs );

/// @brief sine of x
/// @param x floating-point number, radians
/// @return sine as f32
f32 sin( f32 x );
/// @brief sine of x
/// @param x floating-point number, radians
/// @return sine as f64
f64 sin( f64 x );
/// @brief arcsine of x
/// @param x floating-point number, radians
/// @return arcsine as f32
f32 asin( f32 x );
/// @brief arcsine of x
/// @param x floating-point number, radians
/// @return arcsine as f64
f64 asin( f64 x );
/// @brief arcsine of x
/// @param x floating-point number, radians
/// @return arcsine as f32.
/// if result is NaN, returns sign * PI/2
f32 asin_real( f32 x );
/// @brief arcsine of x, no NaN
/// @param x floating-point number, radians
/// @return arcsine as f64.
/// if result is NaN, returns sign * PI/2
f64 asin_real( f64 x );
/// @brief cosine of x
/// @param x floating-point number, radians
/// @return cosine as f32
f32 cos( f32 x );
/// @brief cosine of x
/// @param x floating-point number, radians
/// @return cosine as f64
f64 cos( f64 x );
/// @brief arccosine of x
/// @param x floating-point number, radians
/// @return arccosine as f32
f32 acos( f32 x );
/// @brief arccosine of x
/// @param x floating-point number, radians
/// @return arccosine as f64
f64 acos( f64 x );
/// @brief tangent of x
/// @param x floating-point number, radians
/// @return tangent as f32
f32 tan( f32 x );
/// @brief tangent of x
/// @param x floating-point number, radians
/// @return tangent as f64
f64 tan( f64 x );
/// @brief arctangent of x
/// @param x floating-point number, radians
/// @return arctangent as f32
f32 atan( f32 x );
/// @brief arctangent of x
/// @param x floating-point number, radians
/// @return arctangent as f64
f64 atan( f64 x );
/// @brief 2-argument arctangent.
/// angle theta between the ray to the point (x, y) and positive x-axis confined to (-pi, pi).
/// @param y,x point
/// @return theta as f32 (radians)
f32 atan2( f32 y, f32 x );
/// @brief 2-argument arctangent.
/// angle theta between the ray to the point (x, y) and positive x-axis confined to (-pi, pi).
/// @param y,x point
/// @return theta as f64 (radians)
f64 atan2( f64 y, f64 x );

/// @brief convert degrees to radians
/// @param theta floating-point number, degrees
/// @return radians as f32
constexpr f32 to_rad( f32 theta );
/// @brief convert degrees to radians
/// @param theta floating-point number, degrees
/// @return radians as f64
constexpr f64 to_rad( f64 theta );
/// @brief convert radians to degrees
/// @param theta floating-point number, radians
/// @return degrees as f32
constexpr f32 to_deg( f32 theta );
/// @brief convert radians to degrees
/// @param theta floating-point number, radians
/// @return degrees as f64
constexpr f64 to_deg( f64 theta );

/// @brief the natural logarithm of x
/// @param x floating-point number
/// @return result as f32
f32 log( f32 x );
/// @brief the natural logarithm of x
/// @param x floating-point number
/// @return result as f64
f64 log( f64 x );

/// @brief linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result as f32
f32 lerp( f32 a, f32 b, f32 t );
/// @brief linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result as f64
f64 lerp( f64 a, f64 b, f64 t );
/// @brief linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result as f32
f32 clamped_lerp( f32 a, f32 b, f32 t );
/// @brief linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result as f64
f64 clamped_lerp( f64 a, f64 b, f64 t );
/// @brief inverse linear interpolation. fraction that value occupies between a and b.
/// @param a minimum value
/// @param b maximum value
/// @param v value between a and b
/// @return result as f32
f32 inverse_lerp( f32 a, f32 b, f32 v );
/// @brief inverse linear interpolation. fraction that value occupies between a and b.
/// @param a minimum value
/// @param b maximum value
/// @param v value between a and b
/// @return result as f64
f64 inverse_lerp( f64 a, f64 b, f64 v );
/// @brief remap value from input range to output range
/// @param imin input range minimum
/// @param imax input range maximum
/// @param omin output range minimum
/// @param omax output range maximum
/// @param v value to remap
/// @return remapped value as f32
f32 remap( f32 imin, f32 imax, f32 omin, f32 omax, f32 v );
/// @brief remap value from input range to output range
/// @param imin input range minimum
/// @param imax input range maximum
/// @param omin output range minimum
/// @param omax output range maximum
/// @param v value to remap
/// @return remapped value as f64
f64 remap( f64 imin, f64 imax, f64 omin, f64 omax, f64 v );
/// @brief smooth-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result as f32
f32 smooth_step( f32 a, f32 b, f32 t );
/// @brief smooth-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result as f64
f64 smooth_step( f64 a, f64 b, f64 t );
/// @brief smooth-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result as f32
f32 smooth_step_clamped( f32 a, f32 b, f32 t );
/// @brief smooth-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result as f64
f64 smooth_step_clamped( f64 a, f64 b, f64 t );
/// @brief smoother-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result as f32
f32 smoother_step( f32 a, f32 b, f32 t );
/// @brief smoother-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result as f64
f64 smoother_step( f64 a, f64 b, f64 t );
/// @brief smoother-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result as f32
f32 smoother_step_clamped( f32 a, f32 b, f32 t );
/// @brief smoother-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result as f64
f64 smoother_step_clamped( f64 a, f64 b, f64 t );

// NOTE(alicia): TYPES -----------------------------------------------------------------------------------------------------

struct vec2;
struct ivec2;
struct bvec2;

struct vec3;
struct ivec3;
struct bvec3;

/// @brief rgb color
typedef vec3 rgb;
/// @brief 3D rotation euler angles
typedef vec3 euler_angles;
/// @brief hue, saturation, value
typedef vec3 hsv;

struct vec4;
struct ivec4;
struct bvec4;

/// @brief rgba color
typedef vec4 rgba;

struct angle_axis;
struct quat;

struct mat2;
struct mat3;
struct mat4;

/// @brief 2-component 32-bit float vector
struct vec2 {
    union {
        struct { f32 x, y; };
        struct { f32 u, v; };
        struct { f32 width, height; };
    };

    /// @brief create vec2 from components
    /// @param x,y components
    /// @return vec2
    static vec2 create( f32 x, f32 y );
    /// @brief create vec2 with all components set to the same value
    /// @param scalar component value
    /// @return vec2
    static vec2 create( f32 scalar );
    /// @brief create vec2 from vec3
    /// @param v vec3
    /// @return vec2
    static vec2 create( const vec3& v );
    /// @brief create vec2 from vec4
    /// @param v vec4
    /// @return vec2
    static vec2 create( const vec4& v );
    /// @brief create vec2 from ivec2
    /// @param v ivec2
    /// @return vec2
    static vec2 create( const ivec2& v );
    /// @brief create vec2 from bvec2
    /// @param v bvec2
    /// @return vec2
    static vec2 create( const bvec2& v );
    /// @return ( 1.0f, 1.0f ) 
    static vec2 one()   { return {  1.0f,  1.0f }; }
    /// @return ( 0.0f, 0.0f ) 
    static vec2 zero()  { return {  0.0f,  0.0f }; }
    /// @return ( -1.0f, 0.0f ) 
    static vec2 left()  { return { -1.0f,  0.0f }; }
    /// @return ( 1.0f, 0.0f ) 
    static vec2 right() { return {  1.0f,  0.0f }; }
    /// @return ( 0.0f, 1.0f ) 
    static vec2 up()    { return {  0.0f,  1.0f }; }
    /// @return ( 0.0f, -1.0f ) 
    static vec2 down()  { return {  0.0f, -1.0f }; }

    /// @return pointer to vector as f32
    f32* ptr();
    /// @return pointer to vector as f32
    const f32* ptr() const;

    /// @brief index into vector
    f32& operator[]( u32 index );
    /// @brief index into vector
    f32 operator[]( u32 index ) const;

    /// @brief negate vector 
    vec2& operator-();
    /// @brief compare vectors for equality
    bool32 operator==( const vec2& rhs ) const;
    /// @brief compare vectors for inequality
    bool32 operator!=( const vec2& rhs ) const;
    /// @brief add vectors
    vec2& operator+=( const vec2& rhs );
    /// @brief subtract vectors
    vec2& operator-=( const vec2& rhs );
    /// @brief scale vector
    vec2& operator*=( f32 rhs );
    /// @brief divide vector
    vec2& operator/=( f32 rhs );
};
/// @brief add vectors
/// @param lhs,rhs operands
/// @return result
vec2 operator+( const vec2& lhs, const vec2& rhs );
/// @brief subtract vectors
/// @param lhs,rhs operands
/// @return result
vec2 operator-( const vec2& lhs, const vec2& rhs );
/// @brief scale vector
/// @param lhs vector to scale
/// @param rhs scalar
/// @return result
vec2 operator*( const vec2& lhs, f32 rhs );
/// @brief scale vector
/// @param lhs scalar
/// @param rhs vector to scale
/// @return result
vec2 operator*( f32 lhs, const vec2& rhs );
/// @brief divide vector
/// @param lhs vector to divide
/// @param rhs scalar
/// @return result
vec2 operator/( const vec2& lhs, f32 rhs );
/// @brief compare two vectors
/// @param a,b vectors to compare
/// @return true if they are approximately equal
bool32 cmp( const vec2& a, const vec2& b );
/// @brief swap x and y
/// @param v vector
void swap( vec2& v );
/// @brief horizontal addition
/// @param v vector to sum
/// @return sum of all components of given vector
f32 horizontal_add( const vec2& v );
/// @brief horizontal multiplication
/// @param v vector to multiply
/// @return product of all components of given vector
f32 horizontal_mul( const vec2& v );
/// @brief component-wise multiply two vectors
/// @param lhs,rhs vectors to multiply
/// @return result of multiplication
vec2 hadamard( const vec2& lhs, const vec2& rhs );
/// @brief calculate square magnitude of given vector
/// @param v vector
/// @return square magnitude
f32 sqr_mag( const vec2& v );
/// @brief calculate magnitude of given vector
/// @param v vector
/// @return magnitude
f32 mag( const vec2& v );
/// @brief normalize given vector
/// @param v vector to normalize
/// @return normalized vector
vec2 normalize( const vec2& v );
/// @brief calculate dot product between two vectors
/// @param lhs,rhs vectors
/// @return dot product
f32 dot( const vec2& lhs, const vec2& rhs );
/// @brief calculate signed angle between two vectors
/// @param a,b vectors
/// @return signed angle in radians
f32 angle( const vec2& a, const vec2& b );
/// @brief calculate angle between two vectors
/// @param a,b vectors
/// @return angle in radians
f32 unsigned_angle( const vec2& a, const vec2& b );
/// @brief linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result
vec2 lerp( const vec2& a, const vec2& b, f32 t );
/// @brief linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result
vec2 clamped_lerp( const vec2& a, const vec2& b, f32 t );
/// @brief smooth-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result
vec2 smooth_step( const vec2& a, const vec2& b, f32 t );
/// @brief smooth-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result
vec2 smooth_step_clamped( const vec2& a, const vec2& b, f32 t );
/// @brief smoother-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result
vec2 smoother_step( const vec2& a, const vec2& b, f32 t );
/// @brief smoother-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result
vec2 smoother_step_clamped( const vec2& a, const vec2& b, f32 t );
/// @brief rotate vector by theta
/// @param v vector to rotate
/// @param theta angle to rotate in radians
/// @return rotated vector
vec2 rotate( const vec2& v, f32 theta );
/// @brief clamp magnitude of vector
/// @param v vector
/// @param max maximum magnitude
/// @return vector with the same direction, clamped magnitude
vec2 clamp( const vec2& v, f32 max );
/// @brief truncate vector to ivector
/// @param v vector
/// @return truncated vector
ivec2 trunc32( const vec2& v );
/// @brief floor vector to ivector
/// @param v vector
/// @return floored vector
ivec2 floor32( const vec2& v );
/// @brief ceil vector to ivector
/// @param v vector
/// @return ceiled vector
ivec2 ceil32( const vec2& v );
/// @brief round vector to ivector
/// @param v vector
/// @return rounded vector
ivec2 round32( const vec2& v );

/// @brief 2-component 32-bit integer vector
struct ivec2 {
    union {
        struct { i32 x, y; };
        struct { i32 width, height; };
    };

    /// @brief create ivec2 from components
    /// @param x,y components
    /// @return ivec2
    static ivec2 create( i32 x, i32 y );
    /// @brief create ivec2 with all components set to the same value
    /// @param scalar component value
    /// @return ivec2
    static ivec2 create( i32 scalar );
    /// @brief create ivec2 from vec2
    /// @param v vec2
    /// @return ivec2
    static ivec2 create( const vec2& v );
    /// @brief create ivec2 from vec3
    /// @param v vec3
    /// @return ivec2
    static ivec2 create( const ivec3& v );
    /// @brief create ivec2 from vec4
    /// @param v vec4
    /// @return ivec2
    static ivec2 create( const ivec4& v );
    /// @brief create ivec2 from bvec2
    /// @param v bvec2
    /// @return ivec2
    static ivec2 create( const bvec2& v );
    /// @return (  1,  1 ) 
    static ivec2 one()   { return {  1,  1 }; }
    /// @return (  0,  0 ) 
    static ivec2 zero()  { return {  0,  0 }; }
    /// @return ( -1,  0 ) 
    static ivec2 left()  { return { -1,  0 }; }
    /// @return (  1,  0 ) 
    static ivec2 right() { return {  1,  0 }; }
    /// @return (  0,  1 ) 
    static ivec2 up()    { return {  0,  1 }; }
    /// @return (  0, -1 ) 
    static ivec2 down()  { return {  0, -1 }; }

    /// @return pointer to vector as i32
    i32* ptr();
    /// @return pointer to vector as i32
    const i32* ptr() const;

    /// @brief index into vector
    i32& operator[]( u32 index );
    /// @brief index into vector
    i32 operator[]( u32 index ) const;

    /// @brief compare vectors for equality
    bool32 operator==( const ivec2& rhs ) const;
    /// @brief compare vectors for inequality
    bool32 operator!=( const ivec2& rhs ) const;
    /// @brief negate vector
    ivec2& operator-();
    /// @brief add vectors
    ivec2& operator+=( const ivec2& rhs );
    /// @brief subtract vectors
    ivec2& operator-=( const ivec2& rhs );
    /// @brief scale vector
    ivec2& operator*=( i32 rhs );
    /// @brief divide vector
    ivec2& operator/=( i32 rhs );
};
/// @brief add vectors
/// @param lhs,rhs operands
/// @return result
ivec2 operator+( const ivec2& lhs, const ivec2& rhs );
/// @brief subtract vectors
/// @param lhs,rhs operands
/// @return result
ivec2 operator-( const ivec2& lhs, const ivec2& rhs );
/// @brief scale vector
/// @param lhs vector to scale
/// @param rhs scalar
/// @return result
ivec2 operator*( const ivec2& lhs, i32 rhs );
/// @brief scale vector
/// @param lhs scalar
/// @param rhs vector to scale
/// @return result
ivec2 operator*( i32 lhs, const ivec2& rhs );
/// @brief divide vector
/// @param lhs vector to divide
/// @param rhs scalar
/// @return result
ivec2 operator/( const ivec2& lhs, i32 rhs );
/// @brief compare two vectors
/// @param a,b vectors to compare
/// @return true if they are equal
bool32 cmp( const ivec2& a, const ivec2& b );
/// @brief swap x and y
/// @param v vector
void swap( ivec2& v );
/// @brief horizontal addition
/// @param v vector to sum
/// @return sum of all components of given vector
i32 horizontal_add( const ivec2& v );
/// @brief horizontal multiplication
/// @param v vector to multiply
/// @return product of all components of given vector
i32 horizontal_mul( const ivec2& v );
/// @brief component-wise multiply two vectors
/// @param lhs,rhs vectors to multiply
/// @return result of multiplication
ivec2 hadamard( const ivec2& lhs, const ivec2& rhs );
/// @brief calculate dot product between two vectors
/// @param lhs,rhs vectors
/// @return dot product
f32 dot( const ivec2& lhs, const ivec2& rhs );
/// @brief calculate square magnitude of given vector
/// @param v vector
/// @return square magnitude
f32 sqr_mag( const ivec2& v );
/// @brief calculate magnitude of given vector
/// @param v vector
/// @return magnitude
f32 mag( const ivec2& v );
/// @brief calculate signed angle between two vectors
/// @param a,b vectors
/// @return signed angle in radians
f32 angle( const ivec2& a, const ivec2& b );
/// @brief calculate angle between two vectors
/// @param a,b vectors
/// @return angle in radians
f32 unsigned_angle( const ivec2& a, const ivec2& b );
/// @brief compose vector made of min of each component from two vectors
/// @param a,b vectors
/// @return min vector
ivec2 min( const ivec2& a, const ivec2& b );
/// @brief compose vector made of max of each component from two vectors
/// @param a,b vectors
/// @return max vector
ivec2 max( const ivec2& a, const ivec2& b );
/// @brief normalize vector components to -1 to 1 range.
/// @param v ivector
/// @return result as vec2
vec2 normalize_range( const ivec2& v );
/// @brief normalize vector components to 0 to 1 range.
/// @param v ivector
/// @return result as vec2
vec2 normalize_range01( const ivec2& v );

/// @brief 2-component 32-bit boolean vector
struct bvec2 {
    bool32 x, y;

    /// @brief create bvec2 from components
    /// @param x,y,z bool32 components
    /// @return bvec2
    static bvec2 create( bool32 x, bool32 y );
    /// @brief create bvec2 with all components set to the same value
    /// @param boolean bool32 value
    /// @return bvec2
    static bvec2 create( bool32 boolean );
    /// @brief create bvec2 from vec2
    /// @param v vec2
    /// @return bvec2
    static bvec2 create( const vec2& v );
    /// @brief create bvec2 from ivec2
    /// @param v ivec2
    /// @return bvec2
    static bvec2 create( const ivec2& v );
    /// @brief create bvec2 from bvec3
    /// @param v bvec3
    /// @return bvec2
    static bvec2 create( const bvec3& v );
    /// @brief create bvec2 from bvec4
    /// @param v bvec4
    /// @return bvec2
    static bvec2 create( const bvec4& v );
    /// @return ( true, true )
    static bvec2 all_true()  { return { true,  true  }; }
    /// @return ( false, false )
    static bvec2 all_false() { return { false, false }; }

    /// @return pointer to vector as bool32
    bool32* ptr();
    /// @return pointer to vector as bool32
    const bool32* ptr() const;

    /// @brief index into vector
    bool32& operator[]( u32 index );
    /// @brief index into vector
    bool32 operator[]( u32 index ) const;

    /// @brief not vector components
    bvec2& operator!();
    /// @brief compare vectors for equality 
    bool32 operator==( const bvec2& rhs ) const;
    /// @brief compare vectors for inequality
    bool32 operator!=( const bvec2& rhs ) const;
    /// @brief greater than compare vector components and store result in vector 
    bvec2 operator>( const bvec2& rhs );
    /// @brief greater than equals compare vector components and store result in vector 
    bvec2 operator>=( const bvec2& rhs );
    /// @brief less than compare vector components and store result in vector 
    bvec2 operator<( const bvec2& rhs );
    /// @brief less than equals compare vector components and store result in vector 
    bvec2 operator<=( const bvec2& rhs );
};
/// @brief horizontal and.
/// @param v vector to and
/// @return result as bool32
bool32 horizontal_and( const bvec2& v );
/// @brief horizontal or.
/// @param v vector to or
/// @return result as bool32
bool32 horizontal_or( const bvec2& v );

/// @brief 3-component 32-bit float vector
struct vec3 {
    union {
        struct { f32 x, y; };
        struct { f32 r, g; };
        struct { f32 pitch, yaw; };
        struct { f32 hue, saturation; };
        vec2 xy;
        vec2 rg;
    };
    union {
        f32 z;
        f32 b;
        f32 roll;
        f32 value;
    };

    /// @brief create vec3 from components
    /// @param x,y,z components
    /// @return vec3
    static vec3 create( f32 x, f32 y, f32 z );
    /// @brief create vec3 with all components set to the same value
    /// @param scalar component value
    /// @return vec3
    static vec3 create( f32 scalar );
    /// @brief create vec3 from vec2
    /// @param v vec2
    /// @return vec3
    static vec3 create( const vec2& v );
    /// @brief create vec3 from ivec3
    /// @param v ivec3
    /// @return vec3
    static vec3 create( const ivec3& v );
    /// @brief create vec3 from bvec3
    /// @param v bvec3
    /// @return vec3
    static vec3 create( const bvec3& v );
    /// @brief create vec3 from vec4
    /// @param v vec4
    /// @return vec3
    static vec3 create( const vec4& v );
    /// @brief create new hsv
    /// @param hue value between 0-360
    /// @param saturation value between 0-1
    /// @param value value between 0-1
    /// @return hsv
    static hsv create_hsv( f32 hue, f32 saturation, f32 value );
    /// @return ( 1.0f, 1.0f, 1.0f ) 
    static vec3 one()     { return {  1.0f,  1.0f,  1.0f }; }
    /// @return ( 0.0f, 0.0f, 0.0f ) 
    static vec3 zero()    { return {  0.0f,  0.0f,  0.0f }; }
    /// @return ( -1.0f, 0.0f, 0.0f ) 
    static vec3 left()    { return { -1.0f,  0.0f,  0.0f }; }
    /// @return ( 1.0f, 0.0f, 0.0f ) 
    static vec3 right()   { return {  1.0f,  0.0f,  0.0f }; }
    /// @return ( 0.0f, 1.0f, 0.0f )
    static vec3 up()      { return {  0.0f,  1.0f,  0.0f }; }
    /// @return ( 0.0f, -1.0f, 0.0f )
    static vec3 down()    { return {  0.0f, -1.0f,  0.0f }; }
    /// @return ( 0.0f, 0.0f, 1.0f )
    static vec3 forward() { return {  0.0f,  0.0f,  1.0f }; }
    /// @return ( 0.0f, 0.0f, -1.0f )
    static vec3 back()    { return {  0.0f,  0.0f, -1.0f }; }
    /// @return rgb color ( 1.0f, 0.0f, 0.0f ) 
    static rgb red()     { return {  1.0f,  0.0f,  0.0f }; }
    /// @return rgb color ( 0.0f, 1.0f, 0.0f ) 
    static rgb green()   { return {  0.0f,  1.0f,  0.0f }; }
    /// @return rgb color ( 0.0f, 0.0f, 1.0f ) 
    static rgb blue()    { return {  0.0f,  0.0f,  1.0f }; }
    /// @return rgb color ( 1.0f, 1.0f, 0.0f ) 
    static rgb yellow()  { return {  1.0f,  1.0f,  0.0f }; }
    /// @return rgb color ( 0.0f, 1.0f, 1.0f ) 
    static rgb cyan()    { return {  0.0f,  1.0f,  1.0f }; }
    /// @return rgb color ( 1.0f, 0.0f, 1.0f ) 
    static rgb magenta() { return {  1.0f,  0.0f,  1.0f }; }
    /// @return rgb color ( 1.0f, 1.0f, 1.0f ) 
    static rgb white()   { return {  1.0f,  1.0f,  1.0f }; }
    /// @return rgb color ( 0.5f, 0.5f, 0.5f ) 
    static rgb gray()    { return {  0.5f,  0.5f,  0.5f }; }
    /// @return rgb color ( 0.5f, 0.5f, 0.5f ) 
    static rgb grey()    { return {  0.5f,  0.5f,  0.5f }; }
    /// @return rgb color ( 0.0f, 0.0f, 0.0f ) 
    static rgb black()   { return {  0.0f,  0.0f,  0.0f }; }
    // TODO(alicia): add hsv versions

    /// @return pointer to vector as f32
    f32* ptr();
    /// @return pointer to vector as f32
    const f32* ptr() const;

    /// @brief index into vector
    f32& operator[]( u32 index );
    /// @brief index into vector
    f32 operator[]( u32 index ) const;

    /// @brief negate vector 
    vec3& operator-();
    /// @brief compare vectors for equality
    bool32 operator==( const vec3& rhs ) const;
    /// @brief compare vectors for inequality
    bool32 operator!=( const vec3& rhs ) const;
    /// @brief add vectors
    vec3& operator+=( const vec3& rhs );
    /// @brief subtract vectors
    vec3& operator-=( const vec3& rhs );
    /// @brief scale vector
    vec3& operator*=( f32 rhs );
    /// @brief divide vector
    vec3& operator/=( f32 rhs );
};
/// @brief add vectors
/// @param lhs,rhs operands
/// @return result
vec3 operator+( const vec3& lhs, const vec3& rhs );
/// @brief subtract vectors
/// @param lhs,rhs operands
/// @return result
vec3 operator-( const vec3& lhs, const vec3& rhs );
/// @brief scale vector
/// @param lhs vector to scale
/// @param rhs scalar
/// @return result
vec3 operator*( const vec3& lhs, f32 rhs );
/// @brief scale vector
/// @param lhs scalar
/// @param rhs vector to scale
/// @return result
vec3 operator*( f32 lhs, const vec3& rhs );
/// @brief divide vector
/// @param lhs vector to divide
/// @param rhs scalar
/// @return result
vec3 operator/( const vec3& lhs, f32 rhs );
/// @brief compare two vectors
/// @param a,b vectors to compare
/// @return true if they are approximately equal
bool32 cmp( const vec3& a, const vec3& b );
/// @brief calculate cross product of two vectors
/// @param lhs,rhs vectors
/// @return cross product
vec3 cross( const vec3& lhs, const vec3& rhs );
/// @brief normalize given vector
/// @param v vector to normalize
/// @return normalized vector
vec3 normalize( const vec3& v );
/// @brief calculate dot product of two vectors
/// @param lhs,rhs vectors
/// @return dot product
f32 dot( const vec3& lhs, const vec3& rhs );
/// @brief shift components of vector to the left
/// @param v vector to shift
void shift_left( vec3& v );
/// @brief shift components of vector to the right
/// @param v vector to shift
void shift_right( vec3& v );
/// @brief horizontal addition
/// @param v vector to sum
/// @return sum of all components of given vector
f32 horizontal_add( const vec3& v );
/// @brief horizontal multiplication
/// @param v vector to multiply
/// @return product of all components of given vector
f32 horizontal_mul( const vec3& v );
/// @brief component-wise multiply two vectors
/// @param lhs,rhs vectors to multiply
/// @return result of multiplication
vec3 hadamard( const vec3& lhs, const vec3& rhs );
/// @brief calculate square magnitude of given vector
/// @param v vector
/// @return square magnitude
f32 sqr_mag( const vec3& v );
/// @brief calculate magnitude of given vector
/// @param v vector
/// @return magnitude
f32 mag( const vec3& v );
/// @brief reflect direction off given surface normal
/// @param direction direction to reflect
/// @param normal normal of surface to reflect off of
/// @return reflected direction
vec3 reflect( const vec3& direction, const vec3& normal );
/// @brief calculate signed angle between two vectors
/// @param a,b vectors
/// @return signed angle in radians
f32 angle( const vec3& a, const vec3& b );
/// @brief calculate angle between two vectors
/// @param a,b vectors
/// @return angle in radians
f32 unsigned_angle( const vec3& a, const vec3& b );
/// @brief linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result
vec3 lerp( const vec3& a, const vec3& b, f32 t );
/// @brief linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result
vec3 clamped_lerp( const vec3& a, const vec3& b, f32 t );
/// @brief smooth-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result
vec3 smooth_step( const vec3& a, const vec3& b, f32 t );
/// @brief smooth-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result
vec3 smooth_step_clamped( const vec3& a, const vec3& b, f32 t );
/// @brief smoother-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result
vec3 smoother_step( const vec3& a, const vec3& b, f32 t );
/// @brief smoother-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result
vec3 smoother_step_clamped( const vec3& a, const vec3& b, f32 t );
/// @brief clamp magnitude of vector
/// @param v vector
/// @param max maximum magnitude
/// @return vector with the same direction, clamped magnitude
vec3 clamp( const vec3& v, f32 max );
/// @brief truncate vector to ivector
/// @param v vector
/// @return truncated vector
ivec3 trunc32( const vec3& v );
/// @brief floor vector to ivector
/// @param v vector
/// @return floored vector
ivec3 floor32( const vec3& v );
/// @brief ceil vector to ivector
/// @param v vector
/// @return ceiled vector
ivec3 ceil32( const vec3& v );
/// @brief round vector to ivector
/// @param v vector
/// @return rounded vector
ivec3 round32( const vec3& v );
/// @brief convert degrees to radians
/// @param deg floating-point number, degrees
/// @return radians as euler angles
euler_angles to_rad( const euler_angles& deg );
/// @brief convert radians to degrees
/// @param rad floating-point number, radians
/// @return degrees as euler angles
euler_angles to_deg( const euler_angles& rad );
/// @brief convert rgb color to hsv color
/// @param rgb rgb color
/// @return hsv color
hsv rgb_to_hsv( const rgb& rgb );
/// @brief convert hsv color to rgb color
/// @param hsv hsv color
/// @return rgb color
rgb hsv_to_rgb( const hsv& hsv );
/// @brief set the hue of an hsv color struct
/// @param hsv struct to modify
/// @param hue new hue
void set_hue( hsv& hsv, f32 hue );
/// @brief set the saturation of an hsv color struct
/// @param hsv struct to modify
/// @param saturation new saturation
void set_saturation( hsv& hsv, f32 saturation );
/// @brief set the value of an hsv color struct
/// @param hsv struct to modify
/// @param value new value
void set_value( hsv& hsv, f32 value );
/// @brief convert linear RGB to sRGB
/// @param linear linear RGB
/// @return sRGB
rgb linear_to_srgb( const rgb& linear );
/// @brief convert sRGB to linear RGB
/// @param linear sRGB
/// @return linear RGB
rgb srgb_to_linear( const rgb& srgb );

/// @brief 3-component 32-bit integer vector
struct ivec3 {
    union {
        struct{ i32 x, y; };
        ivec2 xy;
    };
    i32 z;

    /// @brief create ivec3 from components
    /// @param x,y components
    /// @return ivec3
    static ivec3 create( i32 x, i32 y, i32 z );
    /// @brief create ivec3 with all components set to the same value
    /// @param scalar component value
    /// @return ivec3
    static ivec3 create( i32 scalar );
    /// @brief create ivec3 from vec3
    /// @param v vec3
    /// @return ivec3
    static ivec3 create( const vec3& v );
    /// @brief create ivec3 from ivec2
    /// @param v ivec2
    /// @return ivec3
    static ivec3 create( const ivec2& v );
    /// @brief create ivec3 from bvec3
    /// @param v bvec3
    /// @return ivec3
    static ivec3 create( const bvec3& v );
    /// @brief create ivec3 from ivec4
    /// @param v ivec4
    /// @return ivec3
    static ivec3 create( const ivec4& v );
    /// @return (  1,  1,  1 ) 
    static ivec3 one()     { return {  1,  1,  1 }; }
    /// @return (  0,  0,  0 ) 
    static ivec3 zero()    { return {  0,  0,  0 }; }
    /// @return ( -1,  0,  0 ) 
    static ivec3 left()    { return { -1,  0,  0 }; }
    /// @return (  1,  0,  0 ) 
    static ivec3 right()   { return {  1,  0,  0 }; }
    /// @return (  0,  1,  0 ) 
    static ivec3 up()      { return {  0,  1,  0 }; }
    /// @return (  0, -1,  0 ) 
    static ivec3 down()    { return {  0, -1,  0 }; }
    /// @return (  0,  0,  1 ) 
    static ivec3 forward() { return {  0,  0,  1 }; }
    /// @return (  0,  0, -1 ) 
    static ivec3 back()    { return {  0,  0, -1 }; }

    /// @return pointer to vector as i32
    i32* ptr();
    /// @return pointer to vector as i32
    const i32* ptr() const;

    /// @brief index into vector
    i32& operator[]( u32 index );
    /// @brief index into vector
    i32 operator[]( u32 index ) const;

    /// @brief negate vector 
    ivec3& operator-();
    /// @brief compare vectors for equality
    bool32 operator==( const ivec3& rhs ) const;
    /// @brief compare vectors for inequality
    bool32 operator!=( const ivec3& rhs ) const;
    /// @brief add vectors
    ivec3& operator+=( const ivec3& rhs );
    /// @brief subtract vectors
    ivec3& operator-=( const ivec3& rhs );
    /// @brief scale vector
    ivec3& operator*=( i32 rhs );
    /// @brief divide vector
    ivec3& operator/=( i32 rhs );
};
/// @brief add vectors
/// @param lhs,rhs operands
/// @return result
ivec3 operator+( const ivec3& lhs, const ivec3& rhs );
/// @brief subtract vectors
/// @param lhs,rhs operands
/// @return result
ivec3 operator-( const ivec3& lhs, const ivec3& rhs );
/// @brief scale vector
/// @param lhs vector to scale
/// @param rhs scalar
/// @return result
ivec3 operator*( const ivec3& lhs, i32 rhs );
/// @brief scale vector
/// @param lhs scalar
/// @param rhs vector to scale
/// @return result
ivec3 operator*( i32 lhs, const ivec3& rhs );
/// @brief divide vector
/// @param lhs vector to divide
/// @param rhs scalar
/// @return result
ivec3 operator/( const ivec3& lhs, i32 rhs );
/// @brief compare two vectors
/// @param a,b vectors to compare
/// @return true if they are equal
bool32 cmp( const ivec3& a, const ivec3& b );
/// @brief shift components of vector to the left
/// @param v vector to shift
void shift_left( ivec3& v );
/// @brief shift components of vector to the right
/// @param v vector to shift
void shift_right( ivec3& v );
/// @brief horizontal addition
/// @param v vector to sum
/// @return sum of all components of given vector
i32 horizontal_add( const ivec3& v );
/// @brief horizontal multiplication
/// @param v vector to multiply
/// @return product of all components of given vector
i32 horizontal_mul( const ivec3& v );
/// @brief component-wise multiply two vectors
/// @param lhs,rhs vectors to multiply
/// @return result of multiplication
ivec3 hadamard( const ivec3& lhs, const ivec3& rhs );
/// @brief calculate dot product between two vectors
/// @param lhs,rhs vectors
/// @return dot product
f32 dot( const ivec3& lhs, const ivec3& rhs );
/// @brief calculate cross product of two vectors
/// @param lhs,rhs vectors
/// @return cross product
ivec3 cross( const ivec3& lhs, const ivec3& rhs );
/// @brief calculate square magnitude of given vector
/// @param v vector
/// @return square magnitude
f32 sqr_mag( const ivec3& v );
/// @brief calculate magnitude of given vector
/// @param v vector
/// @return magnitude
f32 mag( const ivec3& v );
/// @brief calculate signed angle between two vectors
/// @param a,b vectors
/// @return signed angle in radians
f32 angle( const ivec3& a, const ivec3& b );
/// @brief calculate angle between two vectors
/// @param a,b vectors
/// @return angle in radians
f32 unsigned_angle( const ivec3& a, const ivec3& b );
/// @brief compose vector made of min of each component from two vectors
/// @param a,b vectors
/// @return min vector
ivec3 min( const ivec3& a, const ivec3& b );
/// @brief compose vector made of max of each component from two vectors
/// @param a,b vectors
/// @return max vector
ivec3 max( const ivec3& a, const ivec3& b );
/// @brief normalize vector components to -1 to 1 range.
/// @param v ivector
/// @return result as vec3
vec3 normalize_range( const ivec3& v );
/// @brief normalize vector components to 0 to 1 range.
/// @param v ivector
/// @return result as vec3
vec3 normalize_range01( const ivec3& v );

/// @brief 3-component 32-bit boolean vector
struct bvec3 {
    union {
        struct{ bool32 x, y; };
        bvec2 xy;
    };
    bool32 z;

    /// @brief create bvec3 from components
    /// @param x,y,z bool32 components
    /// @return bvec3
    static bvec3 create( bool32 x, bool32 y, bool32 z  );
    /// @brief create bvec3 with all components set to the same value
    /// @param boolean bool32 value
    /// @return bvec3
    static bvec3 create( bool32 boolean );
    /// @brief create bvec3 from vec3
    /// @param v vec3
    /// @return bvec3
    static bvec3 create( const vec3& v );
    /// @brief create bvec3 from ivec3
    /// @param v ivec3
    /// @return bvec3
    static bvec3 create( const ivec3& v );
    /// @brief create bvec3 from bvec2
    /// @param v bvec2
    /// @return bvec3
    static bvec3 create( const bvec2& v );
    /// @brief create bvec3 from bvec4
    /// @param v bvec4
    /// @return bvec3
    static bvec3 create( const bvec4& v );
    /// @return ( true, true, true )
    static bvec3 all_true()  { return { true,  true,  true  }; }
    /// @return ( false, false, false )
    static bvec3 all_false() { return { false, false, false }; }

    /// @return pointer to vector as bool32
    bool32* ptr();
    /// @return pointer to vector as bool32
    const bool32* ptr() const;

    /// @brief index into vector
    bool32& operator[]( u32 index );
    /// @brief index into vector
    bool32 operator[]( u32 index ) const;

    /// @brief not vector components
    bvec3& operator!();
    /// @brief compare vectors for equality 
    bool32 operator==( const bvec3& rhs ) const;
    /// @brief compare vectors for inequality
    bool32 operator!=( const bvec3& rhs ) const;
    /// @brief greater than compare vector components and store result in vector 
    bvec3 operator>( const bvec3& rhs );
    /// @brief greater than equals compare vector components and store result in vector 
    bvec3 operator>=( const bvec3& rhs );
    /// @brief less than compare vector components and store result in vector 
    bvec3 operator<( const bvec3& rhs );
    /// @brief less than equals compare vector components and store result in vector 
    bvec3 operator<=( const bvec3& rhs );
};
/// @brief horizontal and.
/// @param v vector to and
/// @return result as bool32
bool32 horizontal_and( const bvec3& v );
/// @brief horizontal or.
/// @param v vector to or
/// @return result as bool32
bool32 horizontal_or( const bvec3& v );

/// @brief 4-component 32-bit float vector
struct vec4 {
    union {
        struct {
            union {
                struct { f32 x, y; };
                struct { f32 r, g; };
                vec2 xy;
                vec2 rg;
            };
            union { f32 z; f32 b; };
        };
        vec3 xyz;
        vec3 rgb;
    };
    union { f32 w; f32 a; };

    /// @brief create vec4 from components
    /// @param x,y,z,w components
    /// @return vec4
    static vec4 create( f32 x, f32 y, f32 z, f32 w );
    /// @brief create vec4 with all components set to the same value
    /// @param scalar component value
    /// @return vec4
    static vec4 create( f32 scalar );
    /// @brief create vec4 from vec2
    /// @param v vec2
    /// @return vec4
    static vec4 create( const vec2& v );
    /// @brief create vec4 from vec3
    /// @param v vec3
    /// @return vec4
    static vec4 create( const vec3& v );
    /// @brief create vec4 from ivec4
    /// @param v ivec4
    /// @return vec4
    static vec4 create( const ivec4& v );
    /// @brief create vec4 from bvec4
    /// @param v bvec4
    /// @return vec4
    static vec4 create( const bvec4& v );
    /// @return ( 1.0f, 1.0f, 1.0f, 1.0f ) 
    static vec4 one()     { return {  1.0f,  1.0f,  1.0f,  1.0f }; }
    /// @return ( 0.0f, 0.0f, 0.0f, 0.0f ) 
    static vec4 zero()    { return {  0.0f,  0.0f,  0.0f,  0.0f }; }
    /// @return ( 1.0f, 0.0f, 0.0f, 1.0f ) 
    static rgba red()     { return {  1.0f,  0.0f,  0.0f, 1.0f }; }
    /// @return ( 0.0f, 1.0f, 0.0f, 1.0f ) 
    static rgba green()   { return {  0.0f,  1.0f,  0.0f, 1.0f }; }
    /// @return ( 0.0f, 0.0f, 1.0f, 1.0f ) 
    static rgba blue()    { return {  0.0f,  0.0f,  1.0f, 1.0f }; }
    /// @return ( 1.0f, 1.0f, 0.0f, 1.0f ) 
    static rgba yellow()  { return {  1.0f,  1.0f,  0.0f, 1.0f }; }
    /// @return ( 0.0f, 1.0f, 1.0f, 1.0f ) 
    static rgba cyan()    { return {  0.0f,  1.0f,  1.0f, 1.0f }; }
    /// @return ( 1.0f, 0.0f, 1.0f, 1.0f ) 
    static rgba magenta() { return {  1.0f,  0.0f,  1.0f, 1.0f }; }
    /// @return ( 1.0f, 1.0f, 1.0f, 1.0f ) 
    static rgba white()   { return {  1.0f,  1.0f,  1.0f, 1.0f }; }
    /// @return ( 0.5f, 0.5f, 0.5f, 1.0f ) 
    static rgba gray()    { return {  0.5f,  0.5f,  0.5f, 1.0f }; }
    /// @return ( 0.5f, 0.5f, 0.5f, 1.0f ) 
    static rgba grey()    { return {  0.5f,  0.5f,  0.5f, 1.0f }; }
    /// @return ( 0.0f, 0.0f, 0.0f, 1.0f ) 
    static rgba black()   { return {  0.0f,  0.0f,  0.0f, 1.0f }; }
    /// @return ( 0.0f, 0.0f, 0.0f, 0.0f ) 
    static rgba clear()   { return {  0.0f,  0.0f,  0.0f, 0.0f }; }

    /// @return pointer to vector as f32
    f32* ptr();
    /// @return pointer to vector as f32
    const f32* ptr() const;

    /// @brief index into vector
    f32& operator[]( u32 index );
    /// @brief index into vector
    f32 operator[]( u32 index ) const;

    /// @brief negate vector 
    vec4& operator-();
    /// @brief compare vectors for equality
    bool32 operator==( const vec4& rhs ) const;
    /// @brief compare vectors for inequality
    bool32 operator!=( const vec4& rhs ) const;
    /// @brief add vectors
    vec4& operator+=( const vec4& rhs );
    /// @brief subtract vectors
    vec4& operator-=( const vec4& rhs );
    /// @brief scale vector
    vec4& operator*=( f32 rhs );
    /// @brief divide vector
    vec4& operator/=( f32 rhs );
};
/// @brief add vectors
/// @param lhs,rhs operands
/// @return result
vec4 operator+( const vec4& lhs, const vec4& rhs );
/// @brief subtract vectors
/// @param lhs,rhs operands
/// @return result
vec4 operator-( const vec4& lhs, const vec4& rhs );
/// @brief scale vector
/// @param lhs vector to scale
/// @param rhs scalar
/// @return result
vec4 operator*( const vec4& lhs, f32 rhs );
/// @brief scale vector
/// @param lhs scalar
/// @param rhs vector to scale
/// @return result
vec4 operator*( f32 lhs, const vec4& rhs );
/// @brief divide vector
/// @param lhs vector to divide
/// @param rhs scalar
/// @return result
vec4 operator/( const vec4& lhs, f32 rhs );
/// @brief convert linear RGBA to sRGBA. Alpha is unaffected.
/// @param linear linear RGBA
/// @return sRGBA
rgba linear_to_srgb( const rgba& linear );
/// @brief convert sRGBA to linear RGBA. Alpha is unaffected.
/// @param linear sRGBA
/// @return linear RGBA
rgba srgb_to_linear( const rgba& srgb );
/// @brief shift components of vector to the left
/// @param v vector to shift
void shift_left( vec4& v );
/// @brief shift components of vector to the right
/// @param v vector to shift
void shift_right( vec4& v );
/// @brief horizontal addition
/// @param v vector to sum
/// @return sum of all components of given vector
f32 horizontal_add( const vec4& v );
/// @brief horizontal multiplication
/// @param v vector to multiply
/// @return product of all components of given vector
f32 horizontal_mul( const vec4& v );
/// @brief component-wise multiply two vectors
/// @param lhs,rhs vectors to multiply
/// @return result of multiplication
vec4 hadamard( const vec4& lhs, const vec4& rhs );
/// @brief calculate square magnitude of given vector
/// @param v vector
/// @return square magnitude
f32 sqr_mag( const vec4& v );
/// @brief calculate magnitude of given vector
/// @param v vector
/// @return magnitude
f32 mag( const vec4& v );
/// @brief normalize given vector
/// @param v vector to normalize
/// @return normalized vector
vec4 normalize( const vec4& v );
/// @brief calculate dot product of two vectors
/// @param lhs,rhs vectors
/// @return dot product
f32 dot( const vec4& lhs, const vec4& rhs );
/// @brief linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result
vec4 lerp( const vec4& a, const vec4& b, f32 t );
/// @brief linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result
vec4 clamped_lerp( const vec4& a, const vec4& b, f32 t );
/// @brief smooth-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result
vec4 smooth_step( const vec4& a, const vec4& b, f32 t );
/// @brief smooth-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result
vec4 smooth_step_clamped( const vec4& a, const vec4& b, f32 t );
/// @brief smoother-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result
vec4 smoother_step( const vec4& a, const vec4& b, f32 t );
/// @brief smoother-step interpolation. smooth blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result
vec4 smoother_step_clamped( const vec4& a, const vec4& b, f32 t );
/// @brief clamp magnitude of vector
/// @param v vector
/// @param max maximum magnitude
/// @return vector with the same direction, clamped magnitude
vec4 clamp( const vec4& v, f32 max );
/// @brief truncate vector to ivector
/// @param v vector
/// @return truncated vector
ivec4 trunc32( const vec4& v );
/// @brief floor vector to ivector
/// @param v vector
/// @return floored vector
ivec4 floor32( const vec4& v );
/// @brief ceil vector to ivector
/// @param v vector
/// @return ceiled vector
ivec4 ceil32( const vec4& v );
/// @brief round vector to ivector
/// @param v vector
/// @return rounded vector
ivec4 round32( const vec4& v );
/// @brief convert rgb color to rgba color. sets alpha component to 1.0
/// @param v rgb color
/// @return rgba color
rgba rgb_to_rgba( const rgb& v );
/// @brief compare two vectors
/// @param a,b vectors to compare
/// @return true if they are approximately equal
bool32 cmp( const vec4& a, const vec4& b );

/// @brief 4-component 32-bit integer vector
struct ivec4 {
    union {
        struct {
            union {
                struct { i32 x, y; };
                ivec2 xy;
            };
            i32 z;
        };
        ivec3 xyz;
    };
    i32 w;

    /// @brief create ivec4 from components
    /// @param x,y,z,w components
    /// @return ivec4
    static ivec4 create( i32 x, i32 y, i32 z, i32 w );
    /// @brief create ivec4 with all components set to the same value
    /// @param scalar component value
    /// @return ivec4
    static ivec4 create( i32 scalar );
    /// @brief create ivec4 from vec4
    /// @param v vec4
    /// @return ivec4
    static ivec4 create( const vec4& v );
    /// @brief create ivec4 from ivec3
    /// @param v ivec3
    /// @return ivec4
    static ivec4 create( const ivec3& v );
    /// @brief create ivec4 from ivec2
    /// @param v ivec2
    /// @return ivec4
    static ivec4 create( const ivec2& v );
    /// @brief create ivec4 from bvec4
    /// @param v bvec4
    /// @return ivec4
    static ivec4 create( const bvec4& v );
    /// @return ( 1, 1, 1, 1 )
    static ivec4 one() { return { 1, 1, 1, 1 }; }
    /// @return ( 0, 0, 0, 0 )
    static ivec4 zero() { return { 0, 0, 0, 0 }; }

    /// @return pointer to vector as i32
    i32* ptr();
    /// @return pointer to vector as i32
    const i32* ptr() const;

    /// @brief index into vector
    i32& operator[]( u32 index );
    /// @brief index into vector
    i32 operator[]( u32 index ) const;

    /// @brief negate vector 
    ivec4& operator-();
    /// @brief compare vectors for equality
    bool32 operator==( const ivec4& rhs ) const;
    /// @brief compare vectors for inequality
    bool32 operator!=( const ivec4& rhs ) const;
    /// @brief add vectors
    ivec4& operator+=( const ivec4& rhs );
    /// @brief subtract vectors
    ivec4& operator-=( const ivec4& rhs );
    /// @brief scale vector
    ivec4& operator*=( i32 rhs );
    /// @brief divide vector
    ivec4& operator/=( i32 rhs );
};
/// @brief add vectors
/// @param lhs,rhs operands
/// @return result
ivec4 operator+( const ivec4& lhs, const ivec4& rhs );
/// @brief subtract vectors
/// @param lhs,rhs operands
/// @return result
ivec4 operator-( const ivec4& lhs, const ivec4& rhs );
/// @brief scale vector
/// @param lhs vector to scale
/// @param rhs scalar
/// @return result
ivec4 operator*( const ivec4& lhs, i32 rhs );
/// @brief scale vector
/// @param lhs scalar
/// @param rhs vector to scale
/// @return result
ivec4 operator*( i32 lhs, const ivec4& rhs );
/// @brief divide vector
/// @param lhs vector to divide
/// @param rhs scalar
/// @return result
ivec4 operator/( const ivec4& lhs, i32 rhs );
/// @brief shift components of vector to the left
/// @param v vector to shift
void shift_left( ivec4& v );
/// @brief shift components of vector to the right
/// @param v vector to shift
void shift_right( ivec4& v );
/// @brief horizontal addition
/// @param v vector to sum
/// @return sum of all components of given vector
i32 horizontal_add( const ivec4& v );
/// @brief horizontal multiplication
/// @param v vector to multiply
/// @return product of all components of given vector
i32 horizontal_mul( const ivec4& v );
/// @brief component-wise multiply two vectors
/// @param lhs,rhs vectors to multiply
/// @return result of multiplication
ivec4 hadamard( const ivec4& lhs, const ivec4& rhs );
/// @brief calculate dot product between two vectors
/// @param lhs,rhs vectors
/// @return dot product
f32 dot( const ivec4& lhs, const ivec4& rhs );
/// @brief calculate square magnitude of given vector
/// @param v vector
/// @return square magnitude
f32 sqr_mag( const ivec4& v );
/// @brief calculate magnitude of given vector
/// @param v vector
/// @return magnitude
f32 mag( const ivec4& v );
/// @brief compose vector made of min of each component from two vectors
/// @param a,b vectors
/// @return min vector
ivec4 min( const ivec4& a, const ivec4& b );
/// @brief compose vector made of max of each component from two vectors
/// @param a,b vectors
/// @return max vector
ivec4 max( const ivec4& a, const ivec4& b );
/// @brief normalize vector components to -1 to 1 range.
/// @param v ivector
/// @return result as vec4
vec4 normalize_range( const ivec4& v );
/// @brief normalize vector components to 0 to 1 range.
/// @param v ivector
/// @return result as vec4
vec4 normalize_range01( const ivec4& v );
/// @brief compare two vectors
/// @param a,b vectors to compare
/// @return true if they are equal
bool32 cmp( const ivec4& a, const ivec4& b );

/// @brief 4-component 32-bit boolean vector
struct bvec4 {
    union {
        struct {
            union {
                struct { bool32 x; bool32 y; };
                bvec2 xy;
            };
            bool32 z;
        };
        bvec3 xyz;
    };
    bool32 w;

    /// @brief create bvec4 from components
    /// @param x,y,z,w bool32 components
    /// @return bvec4
    static bvec4 create( bool32 x, bool32 y, bool32 z, bool32 w );
    /// @brief create bvec4 with all components set to the same value
    /// @param boolean bool32 value
    /// @return bvec4
    static bvec4 create( bool32 boolean );
    /// @brief create bvec4 from vec4
    /// @param v vec4
    /// @return bvec4
    static bvec4 create( const vec4& v );
    /// @brief create bvec4 from ivec4
    /// @param v ivec4
    /// @return bvec4
    static bvec4 create( const ivec4& v );
    /// @brief create bvec4 from bvec2
    /// @param v bvec2
    /// @return bvec4
    static bvec4 create( const bvec2& v );
    /// @brief create bvec4 from bvec3
    /// @param v bvec3
    /// @return bvec4
    static bvec4 create( const bvec3& v );
    /// @return ( true, true, true, true )
    static bvec4 all_true()  { return { true,  true,  true,  true  }; }
    /// @return ( false, false, false, false )
    static bvec4 all_false() { return { false, false, false, false }; }

    /// @return pointer to vector as bool32
    bool32* ptr();
    /// @return pointer to vector as bool32
    const bool32* ptr() const;

    /// @brief index into vector
    bool32& operator[]( u32 index );
    /// @brief index into vector
    bool32 operator[]( u32 index ) const;

    /// @brief not vector components
    bvec4& operator!();
    /// @brief compare vectors for equality 
    bool32 operator==( const bvec4& rhs ) const;
    /// @brief compare vectors for inequality
    bool32 operator!=( const bvec4& rhs ) const;
    /// @brief greater than compare vector components and store result in vector 
    bvec4 operator>( const bvec4& rhs );
    /// @brief greater than equals compare vector components and store result in vector 
    bvec4 operator>=( const bvec4& rhs );
    /// @brief less than compare vector components and store result in vector 
    bvec4 operator<( const bvec4& rhs );
    /// @brief less than equals compare vector components and store result in vector 
    bvec4 operator<=( const bvec4& rhs );
};
/// @brief horizontal and.
/// @param v vector to and
/// @return result as bool32
bool32 horizontal_and( const bvec4& v );
/// @brief horizontal or.
/// @param v vector to or
/// @return result as bool32
bool32 horizontal_or( const bvec4& v );

/// @brief rotation represented as angle-axis pair. angle is in radians
struct angle_axis {
    vec3 axis;
    f32  theta;
};

/// @brief 32-bit floating point quaternion
struct quat {
    union {
        f32 w;
        f32 a;
    };
    union {
        struct { f32 x, y, z; };
        struct { f32 b, c, d; };

        vec3 xyz;
    };

    /// @brief construct quaternion from components
    /// @param w,x,y,z components
    /// @return quaternion
    static quat create( f32 w, f32 x, f32 y, f32 z );
    /// @brief construct quaternion from angle and axis
    /// @param theta angle in radians
    /// @param axis axis to apply rotation around
    /// @return quaternion
    static quat create( f32 theta, const vec3& axis );
    /// @brief construct quaternion from angle axis
    /// @param aa angle axis
    /// @return quaternion
    static quat create( const angle_axis& aa );
    /// @brief construct quaternion from euler angles
    /// @param pitch,yaw,roll euler angle rotations in radians
    /// @return quaternion
    static quat create( f32 pitch, f32 yaw, f32 roll );
    /// @brief construct quaternion from euler anlges
    /// @param euler euler angles
    /// @return quaternion
    static quat create( const euler_angles& euler );
    /// @return identity quaternion ( 1.0, 0.0, 0.0, 0.0 )
    static quat identity() { return { 1.0f, 0.0f, 0.0f, 0.0f }; }

    /// @return pointer to quaternion as f32
    f32* ptr();
    /// @return pointer to quaternion as f32
    const f32* ptr() const;

    /// @brief index into quaternion
    f32& operator[]( u32 index );
    /// @brief index into quaternion
    f32 operator[]( u32 index ) const;

    /// @brief negate quaternion 
    quat& operator-();
    /// @brief compare quaternions for equality
    bool32 operator==( const quat& rhs ) const;
    /// @brief compare quaternions for inequality
    bool32 operator!=( const quat& rhs ) const;
    /// @brief add quaternions
    quat& operator+=( const quat& rhs );
    /// @brief subtract quaternions
    quat& operator-=( const quat& rhs );
    /// @brief scale quaternion
    quat& operator*=( f32 rhs );
    /// @brief divide quaternion
    quat& operator/=( f32 rhs );
};
/// @brief add quaternions
/// @param lhs,rhs operands
/// @return result
quat operator+( const quat& lhs, const quat& rhs );
/// @brief subtract quaternions
/// @param lhs,rhs operands
/// @return result
quat operator-( const quat& lhs, const quat& rhs );
/// @brief multiply quaternions, not commutative
/// @param lhs,rhs operands
/// @return result
quat operator*( const quat& lhs, const quat& rhs );
/// @brief multiply vec3 by quaternion
/// @param lhs quaternion
/// @param rhs vec3
/// @return result
vec3 operator*( const quat& lhs, const vec3& rhs );
/// @brief scale quaternion
/// @param lhs,rhs operands
/// @return result
quat operator*( const quat& lhs, f32 rhs );
/// @brief scale quaternion
/// @param lhs,rhs operands
/// @return result
quat operator*( f32 lhs, const quat& rhs );
/// @brief divide quaternion
/// @param lhs,rhs operands
/// @return result
quat operator/( const quat& lhs, f32 rhs );
/// @brief compare two quaternions
/// @param a,b quaternions to compare
/// @return true if they are approximately equal
bool32 cmp( const quat& a, const quat& b );
/// @brief calculate square magnitude of given quaternion
/// @param q quaternion
/// @return square magnitude
f32 sqr_mag( const quat& q );
/// @brief calculate magnitude of given quaternion
/// @param q quaternion
/// @return magnitude
f32 mag( const quat& q );
/// @brief normalize given quaternion
/// @param q quaternion to normalize
/// @return normalized quaternion
quat normalize( const quat& q );
/// @brief calculate the conjugate of given quaternion
/// @param q quaternion
/// @return conjugate
quat conjugate( const quat& q );
/// @brief calculate the inverse of given quaternion
/// @param q quaternion
/// @return inverse of quaternion
quat inverse( const quat& q );
/// @brief calculate signed angle between two quaternions
/// @param a,b quaternions
/// @return signed angle in radians
f32 angle( const quat& a, const quat& b );
/// @brief calculate angle between two quaternions
/// @param a,b quaternions
/// @return angle in radians
f32 unsigned_angle( const quat& a, const quat& b );
/// @brief calculate dot product of two quaternions
/// @param lhs,rhs quaternions
/// @return dot product
f32 dot( const quat& lhs, const quat& rhs );
/// @brief linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result
quat lerp( const quat& a, const quat& b, f32 t );
/// @brief linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result
quat clamped_lerp( const quat& a, const quat& b, f32 t );
/// @brief spherical linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction
/// @return result
quat slerp( const quat& a, const quat& b, f32 t );
/// @brief spherical linear interpolation. blend between a and b, based on fraction t.
/// @param a minimum value
/// @param b maximum value
/// @param t fraction clamped to 0-1 range
/// @return result
quat clamped_slerp( const quat& a, const quat& b, f32 t );
/// @brief convert quaternion rotation to euler angles
/// @param q quaternion
/// @return euler angles
euler_angles quat_to_euler( const quat& q );
/// @brief convert quaternion rotation to angle axis
/// @param q quaternion
/// @return angle axis
angle_axis quat_to_angle_axis( const quat& q );

/// @brief column-major 2x2 32-bit floating point matrix
struct mat2 {
    union {
        struct { f32 _m00, _m01; };
        vec2 _col0;
    };
    union {
        struct { f32 _m10, _m11; };
        vec2 _col1;
    };

    /// @brief create matrix from cells
    /// @param m00,m01 column 0
    /// @param m10,m11 column 1
    /// @return matrix
    static mat2 create( f32 m00, f32 m01, f32 m10, f32 m11 );
    /// @brief create 2x2 matrix from 3x3 matrix
    /// @param m 3x3 matrix
    /// @return 2x2 matrix
    static mat2 create( const mat3& m );
    /// @brief create 2x2 matrix from 4x4 matrix
    /// @param m 4x4 matrix
    /// @return 2x2 matrix
    static mat2 create( const mat4& m );
    /// @return identity matrix
    static mat2 identity() { return { 1.0f, 0.0f, 1.0f, 0.0f }; }

    // get pointer to matrix as f32
    f32* ptr();
    // get pointer to matrix as f32
    const f32* ptr() const;
    /// @brief index into vector
    f32& operator[]( u32 index );
    /// @brief index into vector
    f32 operator[]( u32 index ) const;
    /// @brief index into matrix with [row, column]
    /// @param row,column index
    /// @return cell at [row, column]
    f32& nm( u32 row, u32 column );
    /// @brief index into matrix with [row, column]
    /// @param row,column index
    /// @return cell at [row, column]
    f32 nm( u32 row, u32 column ) const;

    /// @brief get reference to column at given index
    /// @param index 0-1
    /// @return column as vec2
    vec2& column( u32 index );
    /// @brief get const reference to column at given index
    /// @param index 0-1
    /// @return column as vec2
    const vec2& column( u32 index ) const;
    /// @brief create vec2 from row at given index
    /// @param index 0-1
    /// @return row as vec2
    vec2 row( u32 index ) const;

    /// @brief add matrices 
    mat2& operator+=( const mat2& rhs );
    /// @brief subtract matrices
    mat2& operator-=( const mat2& rhs );
    /// @brief scale matrix
    mat2& operator*=( f32 rhs );
    /// @brief divide matrix
    mat2& operator/=( f32 rhs );
    /// @brief multiply matrices, not commutative
    mat2& operator*=( const mat2& rhs );
};
/// @brief add matrices
/// @param lhs,rhs operands
/// @return result
mat2 operator+( const mat2& lhs, const mat2& rhs );
/// @brief subtract matrices
/// @param lhs,rhs operands
/// @return result
mat2 operator-( const mat2& lhs, const mat2& rhs );
/// @brief scale matrix
/// @param lhs,rhs operands
/// @return result
mat2 operator*( const mat2& lhs, f32 rhs );
/// @brief scale matrix
/// @param lhs,rhs operands
/// @return result
mat2 operator*( f32 lhs, const mat2& rhs );
/// @brief divide matrix
/// @param lhs,rhs operands
/// @return result
mat2 operator/( const mat2& lhs, f32 rhs );
/// @brief multiply matrices
/// @param lhs,rhs operands
/// @return result
mat2 operator*( const mat2& lhs, const mat2& rhs );
/// @brief transpose matrix
/// @param m matrix to transpose
/// @return transposed matrix
mat2 transpose( const mat2& m );
/// @brief calculate the determinant of given matrix
/// @param m matrix to calculate determinant of
/// @return determinant
f32 determinant( const mat2& m );

/// @brief column-major 3x3 32-bit floating point matrix
struct mat3 {
    union {
        struct { f32 _m00, _m01, _m02; };
        vec3 _col0;
    };
    union {
        struct { f32 _m10, _m11, _m12; };
        vec3 _col1;
    };
    union {
        struct { f32 _m20, _m21, _m22; };
        vec3 _col2;
    };

    /// @brief create matrix from cells
    /// @param m00,m01,m02 column 0
    /// @param m10,m11,m12 column 1
    /// @param m20,m21,m22 column 2
    /// @return matrix
    static mat3 create(
        f32 m00, f32 m01, f32 m02,
        f32 m10, f32 m11, f32 m12,
        f32 m20, f32 m21, f32 m22
    );
    /// @brief create 3x3 matrix from 2x2 matrix
    /// @param m 2x2 matrix
    /// @return 3x3 matrix
    static mat3 create( const mat2& m );
    /// @brief create 3x3 matrix from 4x4 matrix
    /// @param m 4x4 matrix
    /// @return 3x3 matrix
    static mat3 create( const mat4& m );
    /// @return identity matrix
    static mat3 identity() {
        return {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };
    }

    // get pointer to matrix as f32
    f32* ptr();
    // get pointer to matrix as f32
    const f32* ptr() const;
    /// @brief index into vector
    f32& operator[]( u32 index );
    /// @brief index into vector
    f32 operator[]( u32 index ) const;
    /// @brief index into matrix with [row, column]
    /// @param row,column index
    /// @return cell at [row, column]
    f32& nm( u32 row, u32 column );
    /// @brief index into matrix with [row, column]
    /// @param row,column index
    /// @return cell at [row, column]
    f32 nm( u32 row, u32 column ) const;
    /// @brief get reference to column at given index
    /// @param index 0-2
    /// @return column as vec3
    vec3& column( u32 index );
    /// @brief get const reference to column at given index
    /// @param index 0-2
    /// @return column as vec3
    const vec3& column( u32 index ) const;
    /// @brief create vec3 from row at given index
    /// @param index 0-2
    /// @return row as vec3
    vec3 row( u32 index ) const;

    /// @brief add matrices 
    mat3& operator+=( const mat3& rhs );
    /// @brief subtract matrices
    mat3& operator-=( const mat3& rhs );
    /// @brief scale matrix
    mat3& operator*=( f32 rhs );
    /// @brief divide matrix
    mat3& operator/=( f32 rhs );
    /// @brief multiply matrices
    mat3& operator*=( const mat3& rhs );

};
/// @brief add matrices
/// @param lhs,rhs operands
/// @return result
mat3 operator+( const mat3& lhs, const mat3& rhs );
/// @brief subtract matrices
/// @param lhs,rhs operands
/// @return result
mat3 operator-( const mat3& lhs, const mat3& rhs );
/// @brief scale matrix
/// @param lhs,rhs operands
/// @return result
mat3 operator*( const mat3& lhs, f32 rhs );
/// @brief scale matrix
/// @param lhs,rhs operands
/// @return result
mat3 operator*( f32 lhs, const mat3& rhs );
/// @brief divide matrix
/// @param lhs,rhs operands
/// @return result
mat3 operator/( const mat3& lhs, f32 rhs );
/// @brief multiply matrices
/// @param lhs,rhs operands
/// @return result
mat3 operator*( const mat3& lhs, const mat3& rhs );
/// @brief transpose matrix
/// @param m matrix to transpose
/// @return transposed matrix
mat3 transpose( const mat3& m );
/// @brief calculate the determinant of given matrix
/// @param m matrix to calculate determinant of
/// @return determinant
f32 determinant( const mat3& m );

/// @brief column-major 4x4 32-bit floating point matrix
struct mat4 {
    union {
        struct { f32 _m00, _m01, _m02, _m03; };
        vec4 _col0;
    };
    union {
        struct { f32 _m10, _m11, _m12, _m13; };
        vec4 _col1;
    };
    union {
        struct { f32 _m20, _m21, _m22, _m23; };
        vec4 _col2;
    };
    union {
        struct { f32 _m30, _m31, _m32, _m33; };
        vec4 _col3;
    };

    /// @brief create matrix from cells
    /// @param m00,m01,m02,m03 column 0
    /// @param m10,m11,m12,m13 column 1
    /// @param m20,m21,m22,m23 column 2
    /// @param m30,m31,m32,m33 column 3
    /// @return matrix
    static mat4 create(
        f32 m00, f32 m01, f32 m02, f32 m03,
        f32 m10, f32 m11, f32 m12, f32 m13,
        f32 m20, f32 m21, f32 m22, f32 m23,
        f32 m30, f32 m31, f32 m32, f32 m33
    );
    /// @brief create 4x4 matrix from 2x2 matrix
    /// @param m 2x2 matrix
    /// @return 4x4 matrix
    static mat4 create( const mat2& m );
    /// @brief create 4x4 matrix from 3x3 matrix
    /// @param m 3x3 matrix
    /// @return 4x4 matrix
    static mat4 create( const mat3& m );
    /// @brief create new look at matrix
    /// @param position position of camera
    /// @param target camera target
    /// @param up up direction, normalized
    /// @return look at matrix
    static mat4 look_at( const vec3& position, const vec3& target, const vec3& up );
    /// @brief create look at matrix suitable for 2d rendering
    /// @param position position of camera
    /// @return look at matrix for 2d rendering
    static mat4 view2d( const vec2& position );
    /// @brief create projection matrix suitable for 2d rendering
    /// @param aspect_ratio aspect ratio of framebuffer
    /// @param scale scale of camera, must be positive and >0.0
    /// @return projection matrix for 2d rendering
    static mat4 projection2d( f32 aspect_ratio, f32 scale );
    /// @brief create projection matrix suitable for 2d rendering
    /// @param aspect_ratio aspect ratio of framebuffer
    /// @param scale axis are seperate camera scale, must be positive and >0.0
    /// @return projection matrix for 2d rendering
    static mat4 projection2d( f32 aspect_ratio, const vec2& scale );
    /// @brief create new orthographic projection matrix
    /// @param left,right left and right clipping planes
    /// @param bottom,top bottom and top clipping planes
    /// @param near,far near and far clipping planes
    /// @return orthographic projection matrix
    static mat4 ortho(
        f32 left, f32 right,
        f32 bottom, f32 top,
        f32 _near, f32 _far
    );
    /// @brief create new orthographic projection matrix. near and far clipping planes are set to -1.0f and 1.0f.
    /// @param left,right left and right clipping planes
    /// @param bottom,top bottom and top clipping planes
    /// @return orthographic projection matrix
    static mat4 ortho(
        f32 left, f32 right,
        f32 bottom, f32 top
    );
    /// @brief create new perspective projection matrix.
    /// @param fov field of view in radians
    /// @param aspect aspect ratio of camera
    /// @param near,far near and far clipping planes
    /// @return perspective projection matrix
    static mat4 perspective( f32 fov, f32 aspect, f32 _near, f32 _far );
    /// @brief create new translation matrix
    /// @param translation translation
    /// @return translation matrix
    static mat4 translate( const vec3& translation );
    /// @brief create new translation matrix
    /// @param x,y,z translation coordinates
    /// @return translation matrix
    static mat4 translate( f32 x, f32 y, f32 z );
    /// @brief create new 2d translation matrix
    /// @param translation translation
    /// @return translation matrix
    static mat4 translate2d( const vec2& translation );
    /// @brief create new 2d translation matrix
    /// @param x,y translation coordinates
    /// @return translation matrix
    static mat4 translate2d( f32 x, f32 y );
    /// @brief create new rotation matrix around x axis
    /// @param pitch euler rotation in radians
    /// @return rotation matrix
    static mat4 rotate_pitch( f32 pitch );
    /// @brief create new rotation matrix around y axis
    /// @param yaw euler rotation in radians
    /// @return rotation matrix
    static mat4 rotate_yaw( f32 yaw );
    /// @brief create new rotation matrix around z axis
    /// @param roll euler rotation in radians
    /// @return rotation matrix
    static mat4 rotate_roll( f32 roll );
    /// @brief create new rotation matrix
    /// @param rotation euler rotation
    /// @return rotation matrix
    static mat4 rotate( const euler_angles& rotation );
    /// @brief create new rotation matrix
    /// @param rotation quaternion rotation
    /// @return rotation matrix
    static mat4 rotate( const quat& rotation );
    /// @brief create new 2d rotation matrix
    /// @param theta 2d rotation in radians
    /// @return 2d rotation matrix
    static mat4 rotate2d( f32 theta );
    /// @brief create new scale matrix
    /// @param scale scale
    /// @return scale matrix
    static mat4 scale( const vec3& scale );
    /// @brief create new scale matrix
    /// @param x,y,z scale in each axis
    /// @return scale matrix
    static mat4 scale( f32 x, f32 y, f32 z );
    /// @brief create new 2d scale matrix
    /// @param scale scale
    /// @return 2d scale matrix
    static mat4 scale2d( const vec2& scale );
    /// @brief create new 2d scale matrix
    /// @param x,y scale in each axis
    /// @return 2d scale matrix
    static mat4 scale2d( f32 x, f32 y );
    /// @brief create new transform matrix
    /// @param translation coordinates
    /// @param rotation quaternion rotation
    /// @param scale scale
    /// @return transform matrix
    static mat4 transform(
        const vec3& translation,
        const quat& rotation,
        const vec3& scale
    );
    /// @brief create new transform matrix
    /// @param translation coordinates
    /// @param rotation euler rotation
    /// @param scale scale
    /// @return transform matrix
    static mat4 transform(
        const vec3& translation,
        const euler_angles& rotation,
        const vec3& scale
    );
    /// @brief create new 2d transform matrix
    /// @param translation coordinates
    /// @param rotation rotation around Z in radians
    /// @param scale scale
    /// @return 2d transform matrix
    static mat4 transform2d(
        const vec2& translation,
        f32 rotation,
        const vec2& scale
    );
    /// @return identity matrix
    static mat4 identity() {
        return {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    // get pointer to matrix as f32
    f32* ptr();
    // get pointer to matrix as f32
    const f32* ptr() const;
    /// @brief index into vector
    f32& operator[]( u32 index );
    /// @brief index into vector
    f32 operator[]( u32 index ) const;
    /// @brief index into matrix with [row, column]
    /// @param row,column index
    /// @return cell at [row, column]
    f32& nm( u32 row, u32 column );
    /// @brief index into matrix with [row, column]
    /// @param row,column index
    /// @return cell at [row, column]
    f32 nm( u32 row, u32 column ) const;
    /// @brief get reference to column at given index
    /// @param index 0-3
    /// @return column as vec4
    vec4& column( u32 index );
    /// @brief get reference to column at given index
    /// @param index 0-3
    /// @return column as vec4
    const vec4& column( u32 index ) const;
    /// @brief create vec4 from row at given index
    /// @param index 0-3
    /// @return row as vec4
    vec4 row( u32 index ) const;

    /// @brief add matrices 
    mat4& operator+=( const mat4& rhs );
    /// @brief subtract matrices
    mat4& operator-=( const mat4& rhs );
    /// @brief scale matrix
    mat4& operator*=( f32 rhs );
    /// @brief divide matrix
    mat4& operator/=( f32 rhs );
    /// @brief multiply matrices 
    mat4& operator*=( const mat4& rhs );

};
/// @brief add matrices
/// @param lhs,rhs operands
/// @return result
mat4 operator+( const mat4& lhs, const mat4& rhs );
/// @brief subtract matrices
/// @param lhs,rhs operands
/// @return result
mat4 operator-( const mat4& lhs, const mat4& rhs );
/// @brief scale matrix
/// @param lhs,rhs operands
/// @return result
mat4 operator*( const mat4& lhs, f32 rhs );
/// @brief scale matrix
/// @param lhs,rhs operands
/// @return result
mat4 operator*( f32 lhs, const mat4& rhs );
/// @brief divide matrix
/// @param lhs,rhs operands
/// @return result
mat4 operator/( const mat4& lhs, f32 rhs );
/// @brief multiply matrices
/// @param lhs,rhs operands
/// @return result
mat4 operator*( const mat4& lhs, const mat4& rhs );
/// @brief multiply vec3 by matrix
/// @param lhs matrix
/// @param rhs vec3
/// @return result
vec3 operator*( const mat4& lhs, const vec3& rhs );
/// @brief multiply vec4 by matrix
/// @param lhs matrix
/// @param rhs vec4
/// @return result
vec4 operator*( const mat4& lhs, const vec4& rhs  );
/// @brief transpose matrix
/// @param m matrix to transpose
/// @return transposed matrix
mat4 transpose( const mat4& m );
/// @brief get sub-matrix at given coordinates
/// @param m 4x4 matrix
/// @param row,column coordinates
/// @return 3x3 sub-matrix
mat3 submatrix( const mat4& m, u32 row, u32 column );
/// @brief calculate determinant of sub-matrix at given coordinates
/// @param m 4x4 matrix
/// @param row,column coordinates
/// @return minor ( determinant of sub-matrix )
f32 minor( const mat4& m, u32 row, u32 column );
/// @brief calculate the cofactor of minor at given coordinates
/// @param m 4x4 matrix
/// @param row,column coordinates
/// @return cofactor
f32 cofactor( const mat4& m, u32 row, u32 column );
/// @brief calculate the cofactor matrix of given matrix
/// @param m 4x4 matrix
/// @return cofactor matrix
mat4 cofactor_matrix( const mat4& m );
/// @brief calculate the adjoint matrix of given matrix
/// @param m 4x4 matrix
/// @return adjoint matrix
mat4 adjoint( const mat4& m );
/// @brief calculate the determinant of given matrix
/// @param m matrix to calculate determinant of
/// @return determinant
f32 determinant( const mat4& m );
/// @brief invert given matrix, if possible
/// @param m matrix to invert
/// @param result inverted matrix
/// @return true if successful
bool32 inverse( const mat4& m, mat4& result );
/// @brief invert matrix, even if determinant is 0
/// @param m matrix to invert
/// @return inverted matrix
mat4 inverse_unchecked( const mat4& m );
/// @brief calculate the normal matrix of transform, if possible
/// @param transform matrix
/// @param result result
/// @return true if successful
bool32 normal_matrix( const mat4& transform, mat3& result );
/// @brief calculate the normal matrix of transform, even if determinant is 0
/// @param transform matrix
/// @return normal matrix
mat3 normal_matrix_unchecked( const mat4& transform );

/// @brief linear congruential random number generator state
struct lcg {
    /// @brief value to start with
    i32 seed;
    /// @brief current value in sequence
    i32 current;
    /// @brief multiplier
    i32 a;
    /// @brief increment
    i32 b;
    /// @brief modulus
    i32 m;
};
/// @brief 64-bit linear congruential random number generator state
struct lcg64 {
    /// @brief value to start with
    i64 seed;
    /// @brief current value in sequence
    i64 current;
    /// @brief multiplier
    i64 a;
    /// @brief increment
    i64 b;
    /// @brief modulus
    i64 m;
};

/// @brief xor shift random number generator state
struct xor_shift {
    /// @brief value to start with
    u32 seed;
    /// @brief current value in sequence
    u32 current;
};
/// @brief xor shift random number generator state
struct xor_shift64 {
    /// @brief value to start with
    u64 seed;
    /// @brief current value in sequence
    u64 current;
};

// NOTE(alicia): FUNCTIONS (ext) -------------------------------------------------------------------------------------------

const f32 VEC_CMP_THRESHOLD = 0.0001f;

// NOTE(alicia): rand

/// @brief define new linear congruential generator state with default multiplier, increment and modulus.
/// @param seed value to start with
/// @return lcg state
lcg new_lcg( i32 seed );
/// @brief define new linear congruential generator state with default multiplier, increment and modulus.
/// @param seed value to start with
/// @return lcg state
lcg64 new_lcg64( i64 seed );
/// @brief generate new random 32-bit integer using linear congruential generator
/// @param state reference to state to use
/// @param next [out] next random number in sequence
void rand( lcg& state, i32& next );
/// @brief generate new random 32-bit floating point number using linear congruential generator
/// @param state reference to state to use
/// @param next [out] random value in -1-1 range
void rand( lcg& state, f32& next );
/// @brief generate random vector using linear congruential generator
/// @param state reference to state to use
/// @param result vector with random values in -1-1 range
void rand( lcg& state, vec2& result );
/// @brief generate random vector using linear congruential generator
/// @param state reference to state to use
/// @param result vector with random values
void rand( lcg& state, ivec2& result );
/// @brief generate random vector using linear congruential generator
/// @param state reference to state to use
/// @param result vector with random values in -1-1 range
void rand( lcg& state, vec3& result );
/// @brief generate random vector using linear congruential generator
/// @param state reference to state to use
/// @param result vector with random values
void rand( lcg& state, ivec3& result );
/// @brief generate random vector using linear congruential generator
/// @param state reference to state to use
/// @param result vector with random values in 0-1 range
void rand( lcg& state, vec4& result );
/// @brief generate random vector using linear congruential generator
/// @param state reference to state to use
/// @param result vector with random values
void rand( lcg& state, ivec4& result );
/// @brief generate new random 64-bit integer using linear congruential generator
/// @param state reference to state to use
/// @param next [out] next random number in sequence
void rand( lcg64& state, i64& next );
/// @brief generate new random 64-bit floating point number using linear congruential generator
/// @param state reference to state to use
/// @param next [out] random value in -1-1 range
void rand( lcg64& state, f64& next );

/// @brief define new xor shift generator state
/// @param seed value to start with, must be a non-zero value
/// @return xor shift state
xor_shift new_xor_shift( u32 seed );
/// @brief define new xor shift generator state
/// @param seed value to start with, must be a non-zero value
/// @return xor shift state
xor_shift64 new_xor_shift64( u64 seed );
/// @brief generate new random 32-bit unsigned integer using xor shift generator
/// @param state reference to state to use
/// @param next [out] next random number in sequence
void rand( xor_shift& state, u32& next );
/// @brief generate new random 32-bit integer using xor shift generator
/// @param state reference to state to use
/// @param next [out] next random number in sequence
void rand( xor_shift& state, i32& next );
/// @brief generate new random 32-bit floating-point number using xor shift generator
/// @param state reference to state to use
/// @param next [out] random value in -1-1 range
void rand( xor_shift& state, f32& next );
/// @brief generate random vector using xor shift generator
/// @param state reference to state to use
/// @param result vector with random values in -1-1 range
void rand( xor_shift& state, vec2& result );
/// @brief generate random vector using xor shift generator
/// @param state reference to state to use
/// @param result vector with random values
void rand( xor_shift& state, ivec2& result );
/// @brief generate random vector using xor shift generator
/// @param state reference to state to use
/// @param result vector with random values in -1-1 range
void rand( xor_shift& state, vec3& result );
/// @brief generate random vector using xor shift generator
/// @param state reference to state to use
/// @param result vector with random values
void rand( xor_shift& state, ivec3& result );
/// @brief generate random vector using xor shift generator
/// @param state reference to state to use
/// @param result vector with random values in -1-1 range
void rand( xor_shift& state, vec4& result );
/// @brief generate random vector using xor shift generator
/// @param state reference to state to use
/// @param result vector with random values
void rand( xor_shift& state, ivec4& result );
/// @brief generate new random 64-bit unsigned integer using xor shift generator
/// @param state reference to state to use
/// @param next [out] next random number in sequence
void rand( xor_shift64& state, u64& next );
/// @brief generate new random 64-bit integer using xor shift generator
/// @param state reference to state to use
/// @param next [out] next random number in sequence
void rand( xor_shift64& state, i64& next );
/// @brief generate new random 64-bit floating-point number using xor shift generator
/// @param state reference to state to use
/// @param next [out] random value in -1-1 range
void rand( xor_shift64& state, f64& next );

// NOTE(alicia): perlin noise

} // namespace smath

#endif
