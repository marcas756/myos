/*! \copyright
    Copyright (c) 2014, marcas756@gmail.com.
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
/*!
    \file   project.h

    \brief

    \details
*/

#ifndef PROJECT_H_
#define PROJECT_H_

#include "debug.h"



#ifdef MAESTRA_INSTRUM

#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if (__STDC_VERSION__ >= 199901L)
    #define __FUNCTION__ __func__
#else
    #define __FUNCTION__ "unknown"
#endif

#define INSTRUM_HEADER "maestra_instrum.h"
#include "unittest/maestra/maestra.h"

#endif /* MAESTRA_INSTRUM */

#ifdef UNITTEST_EXPOSE
    #define STATIC
#else
    #define STATIC static
#endif


#define LIST_TYPE_SLIST    0
#define LIST_TYPE_DLIST    1
#define LIST_TYPE_XLIST    2

#define TASK_LIST_TYPE                      LIST_TYPE_SLIST
#define TASK_EVENT_QUEUE_SIZE               16




#endif /*PROJECT_H_ */
