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
	\file	unittest_buffer.c

    \brief

    \details
*/

#define UNITTEST_CONF_VERBOSE

#include "unittest.h"
#include "buffer.h"

UNITTEST_TESTSUITE_INIT();

#define SIZE 5
#define RANDOM_SEED     12345
#define GARBAGE 0xAA
#define EMPTY 0x00

BUFFER_TYPEDEF(buffer,int,SIZE);

BUFFER_T(buffer) input;

UNITTEST_TESTCASE_BEGIN(buffer_init)

    size_t tmp;

    memset(&input,0xAA,sizeof(input)); /* Fill with some garbage */

    UNITTEST_ASSERT("Did not expect empty buffer", BUFFER_COUNT(input) != 0);

    BUFFER_INIT(input);
    UNITTEST_ASSERT("Wrong buffer size", BUFFER_SIZE(input) == SIZE);
    UNITTEST_ASSERT("Initialized buffer has to be empty", BUFFER_COUNT(input) == 0);

    for (tmp=0; tmp < BUFFER_SIZEOF(input); ++tmp)
        UNITTEST_ASSERT("Expected garbage", BUFFER_RAW(input)[tmp] == GARBAGE);

    memset(&input,0xAA,sizeof(input)); /* Fill with some garbage */

    BUFFER_CLEAR(input);

    UNITTEST_ASSERT("Initialized buffer has to be empty", BUFFER_COUNT(input) == 0);

    for (tmp=0; tmp < BUFFER_SIZEOF(input); ++tmp)
            UNITTEST_ASSERT("Expected zero", BUFFER_RAW(input)[tmp] == EMPTY);

UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(buffer_fill_append)

    size_t tmp;

    BUFFER_INIT(input);
    srand(RANDOM_SEED);

    while(!BUFFER_FULL(input))
        BUFFER_APPEND(input,rand());

    UNITTEST_ASSERT("Item count differs from buffer size", BUFFER_COUNT(input) == BUFFER_SIZE(input));

    srand(RANDOM_SEED);

    for (tmp = 0; tmp < BUFFER_SIZE(input); ++tmp)
        UNITTEST_ASSERT("Expected another item value", BUFFER_ITEMS(input)[tmp] == rand());


UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(buffer_fill_value)

    size_t tmp;

    BUFFER_INIT(input);
    srand(RANDOM_SEED);

    while(!BUFFER_FULL(input))
    {
        BUFFER_VAL(input)=rand();
        BUFFER_NEXT(input);
    }

    UNITTEST_ASSERT("Item count differs from buffer size", BUFFER_COUNT(input) == BUFFER_SIZE(input));

    srand(RANDOM_SEED);

    for (tmp = 0; tmp < BUFFER_SIZE(input); ++tmp)
        UNITTEST_ASSERT("Expected another item value", BUFFER_ITEMS(input)[tmp] == rand());

UNITTEST_TESTCASE_END()


UNITTEST_TESTCASE_BEGIN(buffer_fill_pointer)

    size_t tmp;

    srand(RANDOM_SEED);
    BUFFER_INIT(input);

    while(!BUFFER_FULL(input))
    {
        *BUFFER_PTR(input)=rand();
        BUFFER_NEXT(input);
    }

    UNITTEST_ASSERT("Item count differs from buffer size", BUFFER_COUNT(input) == BUFFER_SIZE(input));

    srand(RANDOM_SEED);

    for (tmp = 0; tmp < BUFFER_SIZE(input); ++tmp)
        UNITTEST_ASSERT("Expected another item value", BUFFER_ITEMS(input)[tmp] == rand());

UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(buffer_compare)

    BUFFER_T(buffer) value,pointer,append,copy;

    BUFFER_INIT(value);
    BUFFER_INIT(pointer);
    BUFFER_INIT(append);

    srand(RANDOM_SEED);

    while(!BUFFER_FULL(value))
    {
        BUFFER_VAL(value)=rand();
        BUFFER_NEXT(value);
    }

    srand(RANDOM_SEED);

    while(!BUFFER_FULL(pointer))
    {
        *BUFFER_PTR(pointer)=rand();
        BUFFER_NEXT(pointer);
    }

    srand(RANDOM_SEED);

    while(!BUFFER_FULL(append))
        BUFFER_APPEND(append,rand());

    BUFFER_COPY(copy,value);

    UNITTEST_ASSERT("Buffers are different", BUFFER_COMPARE(value,pointer) == 0);
    UNITTEST_ASSERT("Buffers are different", BUFFER_COMPARE(pointer,append) == 0);
    UNITTEST_ASSERT("Buffers are different", BUFFER_COMPARE(append,copy) == 0);

    /*
         Will not work on x64 if struct is defined the following way:

            #define BUFFER_TYPEDEF(name,type,size) \
            typedef struct { \
                    type items [size]; \
                    size_t count; \
            } name##_buffer_t;

         Currently no idea why ... alignment for memset???

         But works the following way (implemented it now this way):

            #define BUFFER_TYPEDEF(name,type,size) \
            typedef struct { \
                    size_t count; \
                    type items [size]; \
            } name##_buffer_t;
     */

UNITTEST_TESTCASE_END()


UNITTEST_TESTSUITE_BEGIN(buffer)

UNITTEST_ADD_TESTCASE(buffer_init);
UNITTEST_ADD_TESTCASE(buffer_fill_append);
UNITTEST_ADD_TESTCASE(buffer_fill_value);
UNITTEST_ADD_TESTCASE(buffer_fill_pointer);
UNITTEST_ADD_TESTCASE(buffer_compare);

UNITTEST_TESTSUITE_END()
