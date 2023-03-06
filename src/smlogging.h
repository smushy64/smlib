/**
 * Description:  Logging library
 *               call smlog_initialize before anything else
 *               define SMUSHY_LOGGING_ENABLED at compiler level 
 *               tested with gcc, clang and msvc compilers
 * Author:       Alicia Amarilla (smushyaa@gmail.com)
 * File Created: March 06, 2023
 * Includes:     "smdef.h"
*/

#if !defined(SM_LOGGING)
#define SM_LOGGING

#include "smdef.h"

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum : u32 {
    LOGGING_COLOR_BLACK,
    LOGGING_COLOR_RED,
    LOGGING_COLOR_GREEN,
    LOGGING_COLOR_YELLOW,
    LOGGING_COLOR_MAGENTA,
    LOGGING_COLOR_CYAN,
    LOGGING_COLOR_WHITE,
    LOGGING_COLOR_BLUE,
    LOGGING_COLOR_RESET,
    LOGGING_COLOR_DEFAULT,

    LOGGING_COLOR_COUNT
} logging_color_t;

typedef enum : u32 {
    LOGGING_LEVEL_NONE    = 0,
    LOGGING_LEVEL_ERROR   = (1 << 0),
    LOGGING_LEVEL_WARN    = (1 << 1),
    LOGGING_LEVEL_DEBUG   = (1 << 2),
    LOGGING_LEVEL_INFO    = (1 << 3),
    LOGGING_LEVEL_TRACE   = (1 << 4),
    LOGGING_LEVEL_VERBOSE = (1 << 5),
} logging_level_t;

typedef bitflags32 logging_level_mask32;

#define LOGGING_LEVEL_ALL LOGGING_LEVEL_ERROR |\
    LOGGING_LEVEL_WARN  | \
    LOGGING_LEVEL_DEBUG | \
    LOGGING_LEVEL_INFO

#define LOGGING_LEVEL_ALL_TRACE LOGGING_LEVEL_ERROR |\
    LOGGING_LEVEL_WARN  | \
    LOGGING_LEVEL_DEBUG | \
    LOGGING_LEVEL_INFO  | \
    LOGGING_LEVEL_TRACE

#define LOGGING_LEVEL_ALL_VERBOSE LOGGING_LEVEL_ERROR |\
    LOGGING_LEVEL_WARN  | \
    LOGGING_LEVEL_DEBUG | \
    LOGGING_LEVEL_INFO  | \
    LOGGING_LEVEL_TRACE | \
    LOGGING_LEVEL_VERBOSE

/// initialize logging library
void smlogging_initialize( logging_level_mask32 level );
/// printf function :)
void smlogging_printf(
    logging_color_t color,
    logging_level_t level,
    bool32 always_print,
    bool32 new_line,
    const char* format,
    ...
);

#if defined(SMUSHY_LOGGING_ENABLED)
    #define LOG_DEBUG( ... ) \
        smlogging_printf( LOGGING_COLOR_BLUE,  LOGGING_LEVEL_DEBUG, false, false, "[DEBUG] " );\
        smlogging_printf( LOGGING_COLOR_RESET, LOGGING_LEVEL_DEBUG, false, true, __VA_ARGS__ )
    #define LOG_INFO( ... ) \
        smlogging_printf( LOGGING_COLOR_WHITE, LOGGING_LEVEL_INFO, false, false, "[INFO] " );\
        smlogging_printf( LOGGING_COLOR_RESET, LOGGING_LEVEL_INFO, false, true, __VA_ARGS__ )
    #define LOG_WARN( ... ) \
        smlogging_printf( LOGGING_COLOR_YELLOW, LOGGING_LEVEL_WARN, false, false, "[WARN] " );\
        smlogging_printf( LOGGING_COLOR_RESET,  LOGGING_LEVEL_WARN, false, true, __VA_ARGS__ )
    #define LOG_ERROR( ... ) \
        smlogging_printf( LOGGING_COLOR_RED,   LOGGING_LEVEL_ERROR, false, false, "[ERROR] " );\
        smlogging_printf( LOGGING_COLOR_RESET, LOGGING_LEVEL_ERROR, false, true, __VA_ARGS__ )
    #define LOG_DEBUG_TRACE( ... ) \
        smlogging_printf( LOGGING_COLOR_BLUE,  logging_level_t( LOGGING_LEVEL_DEBUG | LOGGING_LEVEL_TRACE ),\
        false, false, "[DEBUG | %s | %i] ", __FILE__, __LINE__ );\
        smlogging_printf( LOGGING_COLOR_RESET, logging_level_t( LOGGING_LEVEL_DEBUG | LOGGING_LEVEL_TRACE ),\
        false, true, __VA_ARGS__ )
    #define LOG_INFO_TRACE( ... ) \
        smlogging_printf( LOGGING_COLOR_WHITE,  logging_level_t( LOGGING_LEVEL_INFO | LOGGING_LEVEL_TRACE ),\
        false, false, "[INFO  | %s | %i] ", __FILE__, __LINE__ );\
        smlogging_printf( LOGGING_COLOR_RESET, logging_level_t( LOGGING_LEVEL_INFO | LOGGING_LEVEL_TRACE ),\
        false, true, __VA_ARGS__ )
    #define LOG_WARN_TRACE( ... ) \
        smlogging_printf( LOGGING_COLOR_YELLOW,  logging_level_t( LOGGING_LEVEL_WARN | LOGGING_LEVEL_TRACE ),\
        false, false, "[WARN  | %s | %i] ", __FILE__, __LINE__ );\
        smlogging_printf( LOGGING_COLOR_RESET, logging_level_t( LOGGING_LEVEL_WARN | LOGGING_LEVEL_TRACE ),\
        false, true, __VA_ARGS__ )
    #define LOG_ERROR_TRACE( ... ) \
        smlogging_printf( LOGGING_COLOR_RED,  logging_level_t( LOGGING_LEVEL_ERROR | LOGGING_LEVEL_TRACE ),\
        false, false, "[ERROR | %s | %i] ", __FILE__, __LINE__ );\
        smlogging_printf( LOGGING_COLOR_RESET, logging_level_t( LOGGING_LEVEL_ERROR | LOGGING_LEVEL_TRACE ),\
        false, true, __VA_ARGS__ )
    #define DEBUG_ASSERT(condition) do {\
        if(condition) {}\
        else {\
            smlogging_printf( LOGGING_COLOR_RED, LOGGING_LEVEL_NONE,\
            true, true, "[ASSERTION FAILED] %s %i", __FILE__, __LINE__ );\
            PANIC();\
        }\
    } while(0)
    #define DEBUG_ASSERT_LOG(condition, ...) do {\
        if(condition) {}\
        else {\
            smlogging_printf( LOGGING_COLOR_RED, LOGGING_LEVEL_NONE,\
            true, false, "[ASSERTION FAILED] %s %i | ", __FILE__, __LINE__ );\
            smlogging_printf( LOGGING_COLOR_RED, LOGGING_LEVEL_NONE,\
            true, true, __VA_ARGS__);\
            PANIC();\
        }\
    } while(0)
    #define DEBUG_UNIMPLEMENTED() smlogging_printf( LOGGING_COLOR_RED, LOGGING_LEVEL_NONE, true, true,\
        "[UNIMPLEMENTED] %s %i", __FILE__, __LINE__ );\
        PANIC()
#else
    #define LOG_DEBUG( ... )
    #define LOG_INFO( ... )
    #define LOG_WARN( ... )
    #define LOG_ERROR( ... )
    #define LOG_DEBUG_TRACE( ... )
    #define LOG_INFO_TRACE( ... )
    #define LOG_WARN_TRACE( ... )
    #define LOG_ERROR_TRACE( ... )
    #define DEBUG_ASSERT(condition)
    #define DEBUG_ASSERT_LOG(condition, ...)
    #define DEBUG_UNIMPLEMENTED()
#endif
#if defined(__cplusplus)
}
#endif

#endif // header guard
