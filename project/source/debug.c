#if DEBUG

#include "debug.h"

#include <stdarg.h>
#include <stdio.h>

void debug_printf_function ( const char * format, ... )
{
    va_list arglist;
    va_start( arglist, format );
    vprintf( format, arglist );
    va_end( arglist );
}

#else /* !DEBUG */

void debug_printf_function ( const char * format, ... )
{

}

#endif /* DEBUG */
