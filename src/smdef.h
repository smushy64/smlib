/**
 * Description:  Typedefs for integral types and relevant constants
 *               Compiler independent asserts
 * Author:       Alicia Amarilla (smushyaa@gmail.com)
 * File Created: February 24, 2023
 * Notes:        define SMUSHY_CONSTANTS
 *               before including to get constants as macros
 * Includes:     <stdint.h>
 *               <intrin.h> MSVC ONLY
*/
#if !defined(SMUSHY_DEFINES)
#define SMUSHY_DEFINES

#include <stdint.h>

/// pointer-sized unsigned integer
typedef uintptr_t usize;
/// pointer-sized integer
typedef intptr_t  isize;

/// 8-bit unsigned integer
typedef uint8_t  u8;
/// 16-bit unsigned integer
typedef uint16_t u16;
/// 32-bit unsigned integer
typedef uint32_t u32;
/// 64-bit unsigned integer
typedef uint64_t u64;

/// 8-bit integer
typedef int8_t  i8;
/// 16-bit integer
typedef int16_t i16;
/// 32-bit integer
typedef int32_t i32;
/// 64-bit integer
typedef int64_t i64;

/// 8-bit boolean
typedef uint8_t  bool8;
/// 32-bit boolean
typedef uint32_t bool32;

#if !defined(__cplusplus)
    /// 8-bit boolean
    typedef uint8_t bool;
#endif

#define TRUE  1
#define FALSE 0

/// 16-bit bitflags
typedef uint16_t bitflags16;
/// 32-bit bitflags
typedef uint32_t bitflags32;
/// 64-bit bitflags
typedef uint64_t bitflags64;

/// 32-bit IEEE-754 floating-point number
typedef float  f32;
/// 64-bit IEEE-754 floating-point number
typedef double f64;

// panic and export/import definitions 
#if defined(_MSC_VER)
    #include <intrin.h>
    #define PANIC() __debugbreak()

    #if defined(SMEXPORT)
        #define SMAPI __declspec(dllexport)
    #else // import
        #define SMAPI __declspec(dllimport)
    #endif

#else // not MSVC
    #define PANIC() __builtin_trap()

    #if defined(SMEXPORT)
        #define SMAPI __attribute__((visibility("default")))
    #else // import
        // unknown?
        #define SMAPI 
    #endif
#endif

// platform defines
typedef enum {
    SM_PLATFORM_UNKNOWN,

    SM_PLATFORM_WINDOWS,
    SM_PLATFORM_LINUX  ,
    SM_PLATFORM_ANDROID,
    SM_PLATFORM_MACOS  ,
    SM_PLATFORM_IOS    ,

    SM_PLATFORM_COUNT,
} sm_platform_t;

#if defined(_WIN32) || defined(__WIN32__) || defined(__WIN64) || defined(__WIN64__)
    #define SM_CURRENT_PLATFORM SM_PLATFORM_WINDOWS
#elif defined(__linux__) || defined(__gnu_linux__)
    #define SM_CURRENT_PLATFORM SM_PLATFORM_LINUX
#elif defined(__ANDROID__)
    #define SM_CURRENT_PLATFORM SM_PLATFORM_ANDROID
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if defined(TARGET_IPHONE_SIMULATION) || defined(TARGET_OS_IPHONE)
        #define SM_CURRENT_PLATFORM SM_PLATFORM_IOS
    #elif defined(TARGET_OS_MAC)
        #define SM_CURRENT_PLATFORM SM_PLATFORM_MACOS
    #endif
#else
    #define SM_CURRENT_PLATFORM SM_PLATFORM_UNKNOWN
#endif

// platform cpu defines
typedef enum {
    SM_PLATFORM_CPU_UNKNOWN,

    SM_PLATFORM_CPU_X86_32,
    SM_PLATFORM_CPU_X86_64,

    SM_PLATFORM_CPU_ARM_32,
    SM_PLATFORM_CPU_ARM_64,

    SM_PLATFORM_CPU_COUNT
} sm_platform_cpu_t;

#if defined(_M_IX86) || defined(__i386__)
    #define SM_CURRENT_PLATFORM_CPU SM_PLATFORM_CPU_X86_32
#elif defined(__x86_64__) || defined(_M_X64_)
    #define SM_CURRENT_PLATFORM_CPU SM_PLATFORM_CPU_X86_64
#elif defined(__arm__) || defined(_M_ARM_)
    #define SM_CURRENT_PLATFORM_CPU SM_PLATFORM_CPU_ARM_32
#elif defined(__aarch64__)
    #define SM_CURRENT_PLATFORM_CPU SM_PLATFORM_CPU_ARM_64
#else
    #define SM_CURRENT_PLATFORM_CPU SM_PLATFORM_CPU_UNKNOWN
#endif

#if SM_CURRENT_PLATFORM_CPU == SM_PLATFORM_CPU_X86_32 || SM_CURRENT_PLATFORM_CPU == SM_PLATFORM_CPU_X86_64
    #define SM_CURRENT_PLATFORM_X86
#elif SM_CURRENT_PLATFORM_CPU == SM_PLATFORM_CPU_ARM_32 || SM_CURRENT_PLATFORM_CPU == SM_PLATFORM_CPU_ARM_64
    #define SM_CURRENT_PLATFORM_ARM
#endif

#if defined(__cplusplus)
    /// 32-bit floating point constants
    namespace F32 {
        /// Largest finite f32 value
        inline const constexpr f32 MAX = 3.40282347E+38f;
        /// Smallest finite f32 value
        inline const constexpr f32 MIN = -3.40282347E+38f;
        /// Not a number
        inline const f32 NAN = ( 0.0f / 0.0f );
        /// Smallest positive f32 value
        inline const constexpr f32 MIN_POS = 1.17549435E-38f;
        /// Positive infinity
        inline const f32 POS_INFINITY = (1.0f / 0.0f);
        /// Positive infinity
        inline const f32 NEG_INFINITY = (-(1.0f / 0.0f));
        /// Pi constant
        inline const constexpr f32 PI = 3.141592741f;
        /// Tau constant
        inline const constexpr f32 TAU = PI * 2.0f;
        /// Epsilon constant
        inline const constexpr f32 EPSILON = 1.1920929E-7f;
        /// Approximate number of significant digits in base-10
        inline const constexpr u32 SIGNIFICANT_DIGITS = 6;
        /// Number of significant digits in base-2
        inline const constexpr u32 MANTISSA_DIGITS = 24;
    };

    /// 64-bit floating point constants
    namespace F64 {
        /// Largest finite f64 value
        inline const constexpr f64 MAX = 1.7976931348623157E+308;
        /// Smallest finite f64 value
        inline const constexpr f64 MIN = -1.7976931348623157E+308;
        /// Not a number
        inline const f64 NAN = 0.0 / 0.0;
        /// Smallest positive f32 value
        inline const constexpr f64 MIN_POS = 2.2250738585072014E-308;
        /// Positive infinity
        inline const f64 POS_INFINITY = (1.0 / 0.0);
        /// Positive infinity
        inline const f64 NEG_INFINITY = (-(1.0 / 0.0));
        /// Pi constant
        inline const constexpr f64 PI = 3.14159265358979323846;
        /// Tau constant
        inline const constexpr f64 TAU = PI * 2.0;
        /// Epsilon constant
        inline const constexpr f64 EPSILON = 2.2204460492503131E-16;
        /// Approximate number of significant digits in base-10
        inline const constexpr u32 SIGNIFICANT_DIGITS = 15;
        /// Number of significant digits in base-2
        inline const constexpr u32 MANTISSA_DIGITS = 54;
    };

    /// 8-bit unsigned integer constants
    namespace U8 {
        /// Largest u8 value
        inline const constexpr u8 MAX = 255;
        /// Smallest u8 value
        inline const constexpr u8 MIN = 0;
    };

    /// 16-bit unsigned integer constants
    namespace U16 {
        /// Largest u16 value
        inline const constexpr u16 MAX = 65535;
        /// Smallest u16 value
        inline const constexpr u16 MIN = 0;
    };

    /// 32-bit unsigned integer constants
    namespace U32 {
        /// Largest u32 value
        inline const constexpr u32 MAX = 4294967295;
        /// Smallest u32 value
        inline const constexpr u32 MIN = 0;
    };

    /// 64-bit unsigned integer constants
    namespace U64 {
        /// Largest u64 value
        inline const constexpr u64 MAX = 18446744073709551615ULL;
        /// Smallest u64 value
        inline const constexpr u64 MIN = 0;
    };

    /// 8-bit integer constants
    namespace I8 {
        /// Largest i8 value
        inline const constexpr i8 MAX = 127;
        /// Smallest i8 value
        inline const constexpr i8 MIN = -128;
    };

    /// 16-bit integer constants
    namespace I16 {
        /// Largest i16 value
        inline const constexpr i16 MAX = 32767;
        /// Smallest i16 value
        inline const constexpr i16 MIN = -32768;
    };

    /// 32-bit integer constants
    namespace I32 {
        /// Largest i32 value
        inline const constexpr i32 MAX = 2147483647;
        /// Smallest i32 value
        inline const constexpr i32 MIN = -2147483648;
    };

    /// 64-bit integer constants
    namespace I64 {
        /// Largest i64 value
        inline const constexpr i64 MAX = 9223372036854775807;
        /// Smallest i64 value
        inline const constexpr i64 MIN = -9223372036854775807 - 1;
    };
#endif // if cpp

#if defined(SMUSHY_CONSTANTS)

    /// Largest finite f32 value
    #define F32_MAX 3.40282347E+38f
    /// Smallest finite f32 value
    #define F32_MIN -3.40282347E+38f
    /// Not a number
    #define F32_NAN ( 0.0f / 0.0f )
    /// Smallest positive f32 value
    #define F32_MIN_POS 1.17549435E-38f
    /// Positive infinity
    #define F32_POS_INFINITY (1.0f / 0.0f)
    /// Positive infinity
    #define F32_NEG_INFINITY (-(1.0f / 0.0f))
    /// Pi constant
    #define F32_PI 3.141592741f
    /// Tau constant
    #define F32_TAU 6.283185482f
    /// Epsilon constant
    #define F32_EPSILON 1.1920929E-7f
    /// Approximate number of significant digits in base-10
    #define F32_SIGNIFICANT_DIGITS 6
    /// Number of significant digits in base-2
    #define F32_MANTISSA_DIGITS 24
    
    /// Largest finite f64 value
    #define F64_MAX 1.7976931348623157E+308
    /// Smallest finite f64 value
    #define F64_MIN -1.7976931348623157E+308
    /// Not a number
    #define F64_NAN (0.0 / 0.0)
    /// Smallest positive f32 value
    #define F64_MIN_POS 2.2250738585072014E-308
    /// Positive infinity
    #define F64_POS_INFINITY (1.0 / 0.0)
    /// Positive infinity
    #define F64_NEG_INFINITY (-(1.0 / 0.0))
    /// Pi constant
    #define F64_PI 3.14159265358979323846
    /// Tau constant
    #define F64_TAU 6.28318530717959
    /// Epsilon constant
    #define F64_EPSILON 2.2204460492503131E-16
    /// Approximate number of significant digits in base-10
    #define F64_SIGNIFICANT_DIGITS 15
    /// Number of significant digits in base-2
    #define F64_MANTISSA_DIGITS 54
    
    /// Largest u8 value
    #define U8_MAX 255
    /// Smallest u8 value
    #define U8_MIN 0
    
    /// Largest u16 value
    #define U16_MAX 65535
    /// Smallest u16 value
    #define U16_MIN 0
    
    /// Largest u32 value
    #define U32_MAX 4294967295
    /// Smallest u32 value
    #define U32_MIN 0
    
    /// Largest u64 value
    #define U64_MAX 18446744073709551615ULL
    /// Smallest u64 value
    #define U64_MIN 0
    
    /// Largest i8 value
    #define I8_MAX 127
    /// Smallest i8 value
    #define I8_MIN -128
    
    /// Largest i16 value
    #define I16_MAX 32767
    /// Smallest i16 value
    #define I16_MIN -32768
    
    /// Largest i32 value
    #define I32_MAX 2147483647
    /// Smallest i32 value
    #define I32_MIN -2147483648
    
    /// Largest i64 value
    #define I64_MAX 9223372036854775807
    /// Smallest i64 value
    #define I64_MIN (-9223372036854775807 - 1)
    
#endif // if SMUSHY_CONSTANTS

#endif
