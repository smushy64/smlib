/**
 * Description:  
 * Author:       Alicia Amarilla (smushyaa@gmail.com)
 * File Created: March 06, 2023
*/
#include "smlogging.h"
#include <stdio.h>

#if defined(SM_PLATFORM_WINDOWS)
    #include <windows.h>
    HANDLE WIN_CONSOLE_HANDLE;
#endif

static logging_level_t GLOBAL_LEVEL = LOGGING_LEVEL_NONE;

void smlogging_initialize( uint32_t level ) {
    #if defined(SMUSHY_LOGGING_ENABLED)
        // check if it's a valid debug level?
        GLOBAL_LEVEL = (logging_level_t)level;
        #if defined(SM_PLATFORM_WINDOWS)

            WIN_CONSOLE_HANDLE = GetStdHandle( STD_OUTPUT_HANDLE );
            DWORD dwMode = 0;
            GetConsoleMode( WIN_CONSOLE_HANDLE, &dwMode );
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode( WIN_CONSOLE_HANDLE, dwMode );

        #endif

    #endif
}

const char* const LOGGING_COLOR_CODES[LOGGING_COLOR_COUNT] = {
    "\033[1;30m",
    "\033[1;31m",
    "\033[1;32m",
    "\033[1;33m",
    "\033[1;35m",
    "\033[1;36m",
    "\033[1;37m",
    "\033[1;34m",
    "\033[1;0m" ,
    "\033[1;39m"
};

void smlogging_set_color( logging_color_t color ) {
    #if defined(SMUSHY_LOGGING_ENABLED)
        printf("%s", LOGGING_COLOR_CODES[color]);
    #endif
}

SM_INLINE uint32_t smlogging_level_valid( logging_level_mask32 level ) {
    #if defined(SMUSHY_LOGGING_ENABLED)
        return (level & GLOBAL_LEVEL) == level;
    #endif
    return FALSE;
}

void smlogging_printf(
    logging_color_t color,
    logging_level_t level,
    bool32 always_print,
    bool32 new_line,
    const char* format,
    ...
) {
#if defined(SMUSHY_LOGGING_ENABLED)

    if( !(always_print || smlogging_level_valid( level )) ) {
        return;
    }

    smlogging_set_color( color );

    va_list args;
    va_start( args, format );
    vprintf( format, args );
    va_end( args );

    smlogging_set_color( LOGGING_COLOR_RESET );

    if( new_line ) {
        printf("\n");
    }

#endif
}


