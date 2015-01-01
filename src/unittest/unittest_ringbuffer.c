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
	\file	unittest_ringbuffer.c

    \brief

    \details
*/
#define UNITTEST_CONF_VERBOSE

#include "unittest.h"
#include "ringbuffer.h"

UNITTEST_TESTSUITE_INIT();

#define SIZE 5
#define RANDOM_SEED     12345
#define RAND8() (rand()&0xFF)
#define GARBAGE 0xAA
#define EMPTY 0x00

RINGBUFFER_TYPEDEF(ringbuffer,int,SIZE);
RINGBUFFER_T(ringbuffer) test;



UNITTEST_TESTCASE_BEGIN(ringbuffer_init)

    int tmp;
    size_t garbage_size;
    memset(&test,GARBAGE,sizeof(test));
    memset(&garbage_size,GARBAGE,sizeof(garbage_size));


    UNITTEST_ASSERT("Did not expect empty ringbuffer", !RINGBUFFER_EMPTY(test));
    UNITTEST_ASSERT("Expected garbage in item counter", RINGBUFFER_COUNT(test) == garbage_size);
    UNITTEST_ASSERT("Expected garbage in head counter", RINGBUFFER_HEAD(test) == garbage_size);
    UNITTEST_ASSERT("Expected garbage in tail counter", RINGBUFFER_TAIL(test) == garbage_size);

    for(tmp=0; tmp < RINGBUFFER_SIZEOF(test); tmp++)
        UNITTEST_ASSERT("Expected garbage ringbuffer", RINGBUFFER_RAW(test)[tmp] == GARBAGE);


    RINGBUFFER_INIT(test);

    UNITTEST_ASSERT("Expected empty ringbuffer", RINGBUFFER_EMPTY(test));
    UNITTEST_ASSERT("Expected 0 in item counter", RINGBUFFER_COUNT(test) == 0);
    UNITTEST_ASSERT("Expected 0 in head counter", RINGBUFFER_HEAD(test) == 0);
    UNITTEST_ASSERT("Expected 0 in tail counter", RINGBUFFER_TAIL(test) == 0);

    for(tmp=0; tmp < RINGBUFFER_SIZEOF(test); tmp++)
        UNITTEST_ASSERT("Expected garbage ringbuffer", RINGBUFFER_RAW(test)[tmp] == GARBAGE);


UNITTEST_TESTCASE_END()


UNITTEST_TESTCASE_BEGIN(ringbuffer_fill_value)

    /* Ringbuffer initialized in ringbuffer_init  */

    srand(RANDOM_SEED+1);

    while (!RINGBUFFER_FULL(test))
    {
        RINGBUFFER_TAIL_VAL(test)=rand();
        RINGBUFFER_PUSH(test);
        UNITTEST_ASSERT("Did not expect empty ringbuffer", !RINGBUFFER_EMPTY(test));
    }

    UNITTEST_ASSERT("Ringbuffer seems not to be full", RINGBUFFER_COUNT(test) == RINGBUFFER_SIZE(test));
    UNITTEST_ASSERT("Head has to be tail", RINGBUFFER_HEAD(test) == RINGBUFFER_TAIL(test));
    UNITTEST_ASSERT("Head value has to be tail value", RINGBUFFER_HEAD_VAL(test) == RINGBUFFER_TAIL_VAL(test));
    UNITTEST_ASSERT("Head pointer has to be tail pointer", RINGBUFFER_HEAD_PTR(test) == RINGBUFFER_TAIL_PTR(test));

UNITTEST_TESTCASE_END()

BUFFER_TYPEDEF(reverse,int,SIZE);

UNITTEST_TESTCASE_BEGIN(ringbuffer_deflate_value)

    int tmp = 0;

    BUFFER_T(reverse) reverse;

    srand(RANDOM_SEED+1);
    BUFFER_INIT(reverse);

    while(!BUFFER_FULL(reverse))
        BUFFER_APPEND(reverse,rand());

    while (!RINGBUFFER_EMPTY(test))
    {
        UNITTEST_ASSERT("Expected another value", RINGBUFFER_HEAD_VAL(test) == BUFFER_ITEMS(reverse)[tmp]);
        RINGBUFFER_POP(test);
        tmp++;
        UNITTEST_ASSERT("Did not expect full ringbuffer", !RINGBUFFER_FULL(test));
    }

    UNITTEST_ASSERT("Ringbuffer seems not to be empty", RINGBUFFER_COUNT(test) == 0);
    UNITTEST_ASSERT("Head has to be tail", RINGBUFFER_HEAD(test) == RINGBUFFER_TAIL(test));
    UNITTEST_ASSERT("Head value has to be tail value", RINGBUFFER_HEAD_VAL(test) == RINGBUFFER_TAIL_VAL(test));
    UNITTEST_ASSERT("Head pointer has to be tail pointer", RINGBUFFER_HEAD_PTR(test) == RINGBUFFER_TAIL_PTR(test));

UNITTEST_TESTCASE_END()



UNITTEST_TESTCASE_BEGIN(ringbuffer_fill_ptr)

    /* Ringbuffer initialized in ringbuffer_init  */

    srand(RANDOM_SEED+2);

    while (!RINGBUFFER_FULL(test))
    {
        *RINGBUFFER_TAIL_PTR(test)=rand();
        RINGBUFFER_PUSH(test);
        UNITTEST_ASSERT("Did not expect empty ringbuffer", !RINGBUFFER_EMPTY(test));
    }

    UNITTEST_ASSERT("Ringbuffer seems not to be full", RINGBUFFER_COUNT(test) == RINGBUFFER_SIZE(test));
    UNITTEST_ASSERT("Head has to be tail", RINGBUFFER_HEAD(test) == RINGBUFFER_TAIL(test));
    UNITTEST_ASSERT("Head value has to be tail value", RINGBUFFER_HEAD_VAL(test) == RINGBUFFER_TAIL_VAL(test));
    UNITTEST_ASSERT("Head pointer has to be tail pointer", RINGBUFFER_HEAD_PTR(test) == RINGBUFFER_TAIL_PTR(test));

UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(ringbuffer_deflate_ptr)

    int tmp = 0;

    BUFFER_T(reverse) reverse;

    srand(RANDOM_SEED+2);
    BUFFER_INIT(reverse);

    while(!BUFFER_FULL(reverse))
        BUFFER_APPEND(reverse,rand());

    while (!RINGBUFFER_EMPTY(test))
    {
        UNITTEST_ASSERT("Expected another value", *RINGBUFFER_HEAD_PTR(test) == BUFFER_ITEMS(reverse)[tmp]);
        RINGBUFFER_POP(test);
        tmp++;
        UNITTEST_ASSERT("Did not expect full ringbuffer", !RINGBUFFER_FULL(test));
    }

    UNITTEST_ASSERT("Ringbuffer seems not to be empty", RINGBUFFER_COUNT(test) == 0);
    UNITTEST_ASSERT("Head has to be tail", RINGBUFFER_HEAD(test) == RINGBUFFER_TAIL(test));
    UNITTEST_ASSERT("Head value has to be tail value", RINGBUFFER_HEAD_VAL(test) == RINGBUFFER_TAIL_VAL(test));
    UNITTEST_ASSERT("Head pointer has to be tail pointer", RINGBUFFER_HEAD_PTR(test) == RINGBUFFER_TAIL_PTR(test));

UNITTEST_TESTCASE_END()



UNITTEST_TESTCASE_BEGIN(ringbuffer_fill_write)

    /* Ringbuffer initialized in ringbuffer_init  */

    srand(RANDOM_SEED+2);

    while (!RINGBUFFER_FULL(test))
    {
        RINGBUFFER_WRITE(test,rand());
        UNITTEST_ASSERT("Did not expect empty ringbuffer", !RINGBUFFER_EMPTY(test));
    }

    UNITTEST_ASSERT("Ringbuffer seems not to be full", RINGBUFFER_COUNT(test) == RINGBUFFER_SIZE(test));
    UNITTEST_ASSERT("Head has to be tail", RINGBUFFER_HEAD(test) == RINGBUFFER_TAIL(test));
    UNITTEST_ASSERT("Head value has to be tail value", RINGBUFFER_HEAD_VAL(test) == RINGBUFFER_TAIL_VAL(test));
    UNITTEST_ASSERT("Head pointer has to be tail pointer", RINGBUFFER_HEAD_PTR(test) == RINGBUFFER_TAIL_PTR(test));

UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(ringbuffer_deflate_read)

    int tmp = 0;

    BUFFER_T(reverse) reverse;

    srand(RANDOM_SEED+2);
    BUFFER_INIT(reverse);

    while(!BUFFER_FULL(reverse))
        BUFFER_APPEND(reverse,rand());

    while (!RINGBUFFER_EMPTY(test))
    {
        int read;
        RINGBUFFER_READ(test,read);
        UNITTEST_ASSERT("Expected another value", read == BUFFER_ITEMS(reverse)[tmp]);
        tmp++;
        UNITTEST_ASSERT("Did not expect full ringbuffer", !RINGBUFFER_FULL(test));
    }

    UNITTEST_ASSERT("Ringbuffer seems not to be empty", RINGBUFFER_COUNT(test) == 0);
    UNITTEST_ASSERT("Head has to be tail", RINGBUFFER_HEAD(test) == RINGBUFFER_TAIL(test));
    UNITTEST_ASSERT("Head value has to be tail value", RINGBUFFER_HEAD_VAL(test) == RINGBUFFER_TAIL_VAL(test));
    UNITTEST_ASSERT("Head pointer has to be tail pointer", RINGBUFFER_HEAD_PTR(test) == RINGBUFFER_TAIL_PTR(test));

UNITTEST_TESTCASE_END()

BUFFER_TYPEDEF(packet,uint8_t,SIZE);
RINGBUFFER_TYPEDEF(packetqueue,BUFFER_T(packet),SIZE);

UNITTEST_TESTCASE_BEGIN(packet_test)



    RINGBUFFER_T(packetqueue) input;

    RINGBUFFER_INIT(input);

    srand(RANDOM_SEED);

    /* Fill the buffer ringbuffer */

    while (!RINGBUFFER_FULL(input))
    {
        BUFFER_T(packet)* tmppacket;
        tmppacket = RINGBUFFER_TAIL_PTR(input);
        BUFFER_INIT(*tmppacket);

        while(!BUFFER_FULL(*tmppacket))
        {
            BUFFER_VAL(*tmppacket) = RAND8();
            BUFFER_NEXT(*tmppacket);
        }

        RINGBUFFER_PUSH(input);
    }

    srand(RANDOM_SEED);

    /* Empty the buffer ringbuffer */

    while (!RINGBUFFER_EMPTY(input))
    {
        size_t tmp;

        BUFFER_T(packet)* tmppacket;
        tmppacket = RINGBUFFER_HEAD_PTR(input);

        for (tmp = 0; tmp < BUFFER_COUNT(*tmppacket); tmp++)
        {
            UNITTEST_ASSERT("Expected another value", BUFFER_ITEMS(*tmppacket)[tmp] == RAND8());
        }

        RINGBUFFER_POP(input);
    }

UNITTEST_TESTCASE_END()

UNITTEST_TESTSUITE_BEGIN(ringbuffer)
    UNITTEST_ADD_TESTCASE(ringbuffer_init);
    UNITTEST_ADD_TESTCASE(ringbuffer_fill_value);
    UNITTEST_ADD_TESTCASE(ringbuffer_deflate_value);
    UNITTEST_ADD_TESTCASE(ringbuffer_fill_ptr);
    UNITTEST_ADD_TESTCASE(ringbuffer_deflate_ptr);
    UNITTEST_ADD_TESTCASE(ringbuffer_fill_write);
    UNITTEST_ADD_TESTCASE(ringbuffer_deflate_read);
    UNITTEST_ADD_TESTCASE(packet_test);
UNITTEST_TESTSUITE_END()
