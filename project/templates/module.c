/*! \copyright
    Copyright (c) 2018, marcas756@gmail.com.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. The name of the author may not be used to endorse or promote
       products derived from this software without specific prior
       written permission.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
    GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*! \addtogroup srcsyshdrs Inclusion of system headers */
/*!@{*/
/*!@}*//*srcsyshdrs*/

/*! \addtogroup srcusrhdrs Inclusion of user-defined headers */
/*!@{*/
#include "module.h"

#if DEBUG
#include "debug.h"
#endif

/*!@}*//*srcusrhdrs*/

/*! \addtogroup srcmacros #define macros used only in this file */
/*!@{*/
/*!@}*//*srcmacros*/

/*! \addtogroup srcfuncmacros #define function macros used only in this file */
/*!@{*/
#if DEBUG_MODULE
#define DBG(...) DBG_FUNC(__VA_ARGS__)
#else
#define DBG(...)
#endif
/*!@}*//*srcfucnmacros*/

/*! \addtogroup srctypedefs typedef definitions used only in this file */
/*!@{*/
/*!@}*//*srctypedefs*/

/*! \addtogroup srcenums enum tag definitions used only in this file */
/*!@{*/
/*!@}*//*srcenums*/

/*! \addtogroup srcstructs struct/union tag definitions used only in this file */
/*!@{*/
/*!@}*//*srcstructs*/

/*! \addtogroup srcstatvars static variable declarations shared in this file */
/*!@{*/
/*!@}*//*srcstatvars*/

/*! \addtogroup srcstatfuncs static function declarations*/
/*!@{*/
/*!@}*//*srcstatfuncs*/

/*! \addtogroup srcvardefs variable definitions*/
/*!@{*/
/*!@}*//*srcvardefs*/

/*! \addtogroup srcfuncdefs function definitions*/
/*!@{*/
/*!@}*//*srcfuncdefs*/
