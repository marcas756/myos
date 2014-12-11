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
	\file	unittest_pt.c

    \brief

    \details
*/

#define UNITTEST_CONF_VERBOSE

#include "unittest.h"
#include "pt.h"
#include <stdbool.h>

UNITTEST_TESTSUITE_INIT();

#define TRIALS  10

PT_THREAD(pt_wait_while(pt_t* pt, bool cond))
{
    PT_BEGIN(pt);
    PT_WAIT_WHILE(pt,cond);
    PT_END(pt);
}

PT_THREAD(pt_wait_until(pt_t* pt, bool cond))
{
    PT_BEGIN(pt);
    PT_WAIT_UNTIL(pt,cond);
    PT_END(pt);
}


PT_THREAD(pt_yield(pt_t* pt))
{
    PT_BEGIN(pt);
    PT_YIELD(pt);
    PT_YIELD(pt);
    PT_YIELD(pt);
    PT_END(pt);
}

PT_THREAD(pt_yield_until(pt_t* pt, bool cond))
{
    PT_BEGIN(pt);
    PT_YIELD_UNTIL(pt,cond);
    PT_END(pt);
}

UNITTEST_TESTCASE_BEGIN(pt_conditionals)

    pt_t pt1;
    int tmp;
    char retval;

    PT_INIT(&pt1);

    UNITTEST_PRINTF("lc value for zombie : 0x%X\n",LC_DEFAULT);

    /* WAIT WHILE -------------------------------------------------------------------------------------------------------- */

    for (tmp = 0; tmp < TRIALS; tmp++)
        UNITTEST_ASSERT("protothread has to block",PT_SCHEDULE(pt_wait_while(&pt1,true)) == PT_BLOCKED);

    UNITTEST_ASSERT("protothread has to be dead",PT_SCHEDULE(pt_wait_while(&pt1,false)) == PT_DEAD);

    for (tmp = 0; tmp < TRIALS; tmp++)
    {
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_wait_while(&pt1,false)) == PT_ZOMBIE);
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_wait_while(&pt1,true)) == PT_ZOMBIE);
    }

    PT_INIT(&pt1);

    UNITTEST_ASSERT("protothread has to be dead",PT_SCHEDULE(pt_wait_while(&pt1,false)) == PT_DEAD);

    for (tmp = 0; tmp < TRIALS; tmp++)
    {
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_wait_while(&pt1,false)) == PT_ZOMBIE);
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_wait_while(&pt1,true)) == PT_ZOMBIE);
    }

    /* WAIT UNTIL -------------------------------------------------------------------------------------------------------- */

    PT_INIT(&pt1);

    for (tmp = 0; tmp < TRIALS; tmp++)
        UNITTEST_ASSERT("protothread has to block",PT_SCHEDULE(pt_wait_until(&pt1,false)) == PT_BLOCKED);

    UNITTEST_ASSERT("protothread has to be dead",PT_SCHEDULE(pt_wait_until(&pt1,true)) == PT_DEAD);

    for (tmp = 0; tmp < TRIALS; tmp++)
    {
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_wait_until(&pt1,false)) == PT_ZOMBIE);
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_wait_until(&pt1,true)) == PT_ZOMBIE);
    }

    PT_INIT(&pt1);

    UNITTEST_ASSERT("protothread has to be dead",PT_SCHEDULE(pt_wait_until(&pt1,true)) == PT_DEAD);

    for (tmp = 0; tmp < TRIALS; tmp++)
    {
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_wait_until(&pt1,false)) == PT_ZOMBIE);
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_wait_until(&pt1,true)) == PT_ZOMBIE);
    }


    /* YIELD -------------------------------------------------------------------------------------------------------- */

    PT_INIT(&pt1);

    UNITTEST_ASSERT("protothread has to block",PT_SCHEDULE(pt_yield(&pt1)) == PT_BLOCKED); /* 1st yield */
    UNITTEST_ASSERT("protothread has to block",PT_SCHEDULE(pt_yield(&pt1)) == PT_BLOCKED); /* 2nd yield */
    UNITTEST_ASSERT("protothread has to block",PT_SCHEDULE(pt_yield(&pt1)) == PT_BLOCKED); /* 3rd yield */
    UNITTEST_ASSERT("protothread has to be dead",PT_SCHEDULE(pt_yield(&pt1)) == PT_DEAD);

    for (tmp = 0; tmp < TRIALS; tmp++)
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_yield(&pt1)) == PT_ZOMBIE);

    /* YIELD UNTIL -------------------------------------------------------------------------------------------------------- */

    PT_INIT(&pt1);

    for (tmp = 0; tmp < TRIALS; tmp++)
        UNITTEST_ASSERT("protothread has to block",PT_SCHEDULE(pt_yield_until(&pt1,false)) == PT_BLOCKED);

    UNITTEST_ASSERT("protothread has to be dead",PT_SCHEDULE(pt_yield_until(&pt1,true)) == PT_DEAD);

    for (tmp = 0; tmp < TRIALS; tmp++)
    {
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_wait_until(&pt1,false)) == PT_ZOMBIE);
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_wait_until(&pt1,true)) == PT_ZOMBIE);
    }

    PT_INIT(&pt1);

    /* also has to block first time if condition is met */
    UNITTEST_ASSERT("protothread has to block ",PT_SCHEDULE(pt_yield_until(&pt1,true)) == PT_BLOCKED);

    for (tmp = 0; tmp < TRIALS; tmp++)
        UNITTEST_ASSERT("protothread has to block ",PT_SCHEDULE(pt_yield_until(&pt1,false)) == PT_BLOCKED);

    UNITTEST_ASSERT("protothread has to be dead ",PT_SCHEDULE(pt_yield_until(&pt1,true)) == PT_DEAD);

    for (tmp = 0; tmp < TRIALS; tmp++)
    {
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_yield_until(&pt1,false)) == PT_ZOMBIE);
        UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_yield_until(&pt1,true)) == PT_ZOMBIE);
    }


UNITTEST_TESTCASE_END()


UNITTEST_TESTSUITE_BEGIN(pt)

UNITTEST_ADD_TESTCASE(pt_conditionals);

UNITTEST_TESTSUITE_END()
