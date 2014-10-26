/*! \copyright
    Copyright (c) 2013, marcas756@gmail.com.
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
    \file   unittest.h

    \brief

    \details
*/

#ifndef UNITTEST_H_
#define UNITTEST_H_
#include <stdlib.h>

#ifdef UNITTEST_CONF_VERBOSE

    /* Define your output function here */
    #include <stdio.h>
    #include <time.h>


    #define UNITTEST_PRINTF(...) printf(__VA_ARGS__)

    /* strings required due to old or not string optimizing compilers */
    #define UNITTEST_TESTSUITE_INIT() const char* file_text = __FILE__;\
        const char* assert_text = ": Unittest failed in line ";\
        const char* testcase_begin_text = "Performing testcase ";

#ifdef UNITTEST_CONF_TIMESTAMPS
    #define UNITTEST_PRINTF_TIMESTAMP() UNITTEST_PRINTF("%6.2f: ",(float)clock()/CLOCKS_PER_SEC);
#else
    #define UNITTEST_PRINTF_TIMESTAMP()
#endif

#else /* UNITTEST_CONF_VERBOSE */

    #define UNITTEST_TESTSUITE_INIT()
    #define UNITTEST_PRINTF(...)
    #define UNITTEST_PRINTF_TIMESTAMP()

#endif /* UNITTEST_CONF_VERBOSE */

#define UNITTEST_TESTCASE_BEGIN(name) \
    static void unittest_##name(){ \
    UNITTEST_PRINTF_TIMESTAMP(); \
    UNITTEST_PRINTF("%s%s\n",testcase_begin_text,#name);{

#define UNITTEST_TESTCASE_END() }}

/* message is not compiled into code, thus it can be used as "in code" information (like remarks) */
#define UNITTEST_ASSERT(message,test) \
        do{if(!(test)){UNITTEST_PRINTF("%s%s%d\n",file_text,assert_text,__LINE__); exit(__LINE__);}}while(0)

#define UNITTEST_ADD_TESTCASE(name) unittest_##name()

#ifdef UNITTEST_CONF_VERBOSE

    #define UNITTEST_TESTSUITE_BEGIN(name) \
        int main(){ \
            const char* testsuite_name = #name; \
            UNITTEST_PRINTF_TIMESTAMP(); \
            UNITTEST_PRINTF("Entering testsuite %s ...\n", #name);

    #define UNITTEST_TESTSUITE_END() \
        UNITTEST_PRINTF_TIMESTAMP(); \
        UNITTEST_PRINTF("%s seems to be error free\n",testsuite_name);\
        return EXIT_SUCCESS;}

#else /* UNITTEST_CONF_VERBOSE */

    #define UNITTEST_TESTSUITE_BEGIN(name) int main(){
    #define UNITTEST_TESTSUITE_END() return EXIT_SUCCESS;}

#endif /* UNITTEST_CONF_VERBOSE */

#endif /* UNITTEST_H_ */
