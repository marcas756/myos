/*! \copyright
    Copyright (c) 2013 marcas756@gmail.com.
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
    \file       unittest.h

    \brief      Provides preprocessor macros to write unit tests

    \details
*/

#ifndef UNITTEST_H_
#define UNITTEST_H_
#include <stdlib.h>

#define UNITTEST_VERBOSE 1

#if UNITTEST_VERBOSE

    extern void unittest_printf_function ( const char * format, ... );
    #define UNITTEST_PRINTF(args) (unittest_printf_function args)

    #define uttcf  "<UTTCF>"
    #define uttcb  "<UTTCB>"
    #define uttsb  "<UTTSB>"
    #define uttce  "<UTTCE>"
    #define uttse  "<UTTSE>"

    #define UNITTEST_TESTSUITE_INIT                                                                 \
                                                                                                    \
        static void unittest_printf_sss(const char *s1, const char *s2, const char *s3)             \
        {                                                                                           \
            UNITTEST_PRINTF(("%s %s %s\n",s1,s2,s3));                                               \
        }                                                                                           \
                                                                                                    \
        static void unittest_printf_sssd(const char *s1, const char *s2, const char *s3, int d)     \
        {                                                                                           \
            UNITTEST_PRINTF(("%s %s %s %d\n",s1,s2,s3,d));                                          \
        }                                                                                           \

#else /* UNITTEST_VERBOSE */

    #define UNITTEST_TESTSUITE_INIT
    #define UNITTEST_PRINTF(args)

#endif /* UNITTEST_VERBOSE */

#if UNITTEST_VERBOSE

    #define UNITTEST_TESTCASE(name) \
        static void unittest_##name(const char *tsname, const char *tcname, int *uttcerrcnt)

    #define UNITTEST_EXEC_TESTCASE(name)                                \
        do{                                                             \
            int uttcerrcnt  = 0;                                        \
            const char* uttcname = #name;                               \
            unittest_printf_sss(uttcb,uttsname,uttcname);               \
            unittest_##name(uttsname,#name,&uttcerrcnt);                \
            unittest_printf_sssd(uttce,uttsname,uttcname,uttcerrcnt);   \
            uttserrcnt+=uttcerrcnt;                                     \
        }while(0)

/* message is not compiled into code, thus it can be used as "in code" information (like remarks) */
#define UNITTEST_ASSERT(message,test) \
        do{if(!(test)){unittest_printf_sssd(uttcf,tsname,tcname,__LINE__);(*uttcerrcnt)++;}}while(0)

#else /* !UNITTEST_VERBOSE */
    #define UNITTEST_TESTCASE(name) \
        static void unittest_##name(int *uttcerrcnt)

    #define UNITTEST_EXEC_TESTCASE(name)    \
        do{                                 \
            int uttcerrcnt = 0;             \
            unittest_##name(&uttcerrcnt);   \
            uttserrcnt+=uttcerrcnt;    \
        }while(0)

#define UNITTEST_ASSERT(message,test) \
        do{if(!(test)){(*uttcerrcnt)++;}}while(0)
#endif /* UNITTEST_VERBOSE */


#if UNITTEST_VERBOSE

    #define UNITTEST_TESTSUITE(name)        \
        const char*  uttsname = #name;      \
        int uttserrcnt = 0;                 \
        int main()

    #define UNITTEST_TESTSUITE_BEGIN()                           \
        {                                                        \
            UNITTEST_PRINTF(("%s %s \"%s\" \"%s\" \"%s\"\n",     \
            uttsb,uttsname,__FILE__,__DATE__,__TIME__));


    #define UNITTEST_TESTSUITE_END()                                      \
            UNITTEST_PRINTF(("%s %s %d\n",uttse,uttsname,uttserrcnt));    \
        }                                                                 \
        return uttserrcnt

#else /* UNITTEST_VERBOSE */

    #define UNITTEST_TESTSUITE(name)    \
            int uttserrcnt = 0;         \
            int main()

    #define UNITTEST_TESTSUITE_BEGIN()
    #define UNITTEST_TESTSUITE_END() return uttserrcnt

#endif /* UNITTEST_VERBOSE */

#endif /* UNITTEST_H_ */
