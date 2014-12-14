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
#define RANDOM_SEED 1234

PT_THREAD(pt_void(pt_t* pt))
{
    PT_BEGIN(pt);
    PT_END(pt);
}

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

    /* VOID -------------------------------------------------------------------------------------------------------- */

    PT_INIT(&pt1);
    UNITTEST_ASSERT("protothread has to be dead",PT_SCHEDULE(pt_void(&pt1)) == PT_DEAD);
    UNITTEST_ASSERT("protothread has to be zombie",PT_SCHEDULE(pt_void(&pt1)) == PT_ZOMBIE);

    /* WAIT WHILE -------------------------------------------------------------------------------------------------- */

    PT_INIT(&pt1);

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

typedef struct {
    uint8_t number;
    bool isPrime;
    uint8_t tmp;
    pt_t pt;
}pt_prime_data_t;


PT_THREAD(pt_prime(pt_t* pt, pt_prime_data_t* pt_prime_data))
{
    PT_BEGIN(pt);

    if (pt_prime_data->number <= 1)
    {
        pt_prime_data->isPrime = false; // zero and one are not prime
        PT_EXIT(pt);
    }

    for (pt_prime_data->tmp = 2; pt_prime_data->tmp*pt_prime_data->tmp <= pt_prime_data->number; pt_prime_data->tmp++)
    {
        if (pt_prime_data->number % pt_prime_data->tmp == 0)
        {
            pt_prime_data->isPrime = false;
            PT_EXIT(pt);
        }

        PT_YIELD(pt);
    }

    pt_prime_data->isPrime = true;

    PT_END(pt);
}

UNITTEST_TESTCASE_BEGIN(pt_computation)

    int tmp;
    pt_prime_data_t prime_data [5];
    bool someone_blocked;

    const uint8_t primes [] = {211, 83, 193, 23, 251};
    const uint8_t nonprimes [] = {213, 82, 189, 22, 253};

    for(tmp = 0; tmp < 5; tmp++)
    {
        PT_INIT(&prime_data[tmp].pt);
        prime_data[tmp].number = primes[tmp];
    }

    do
    {
        someone_blocked = false;

        for(tmp = 0; tmp < 5; tmp++)
        {
            if (PT_SCHEDULE(pt_prime(&prime_data[tmp].pt,&prime_data[tmp])) == PT_BLOCKED)
                someone_blocked = true;
        }

    } while (someone_blocked);


    for(tmp = 0; tmp < 5; tmp++)
        UNITTEST_ASSERT("Wrong result",prime_data[tmp].isPrime == true);


    for(tmp = 0; tmp < 5; tmp++)
    {
       PT_INIT(&prime_data[tmp].pt);
       prime_data[tmp].number = nonprimes[tmp];
    }

    do
    {
       someone_blocked = false;

       for(tmp = 0; tmp < 5; tmp++)
       {
           if (PT_SCHEDULE(pt_prime(&prime_data[tmp].pt,&prime_data[tmp])) == PT_BLOCKED)
               someone_blocked = true;
       }

    } while (someone_blocked);

    for(tmp = 0; tmp < 5; tmp++)
       UNITTEST_ASSERT("Wrong result",prime_data[tmp].isPrime == false);

UNITTEST_TESTCASE_END()



UNITTEST_BENCHMARK_BEGIN(primes_with_pt)

    pt_prime_data_t pt_prime_data;

    pt_prime_data.number = 0;


    while(pt_prime_data.number != 0xFF)
    {
        pt_prime_data.number++;
        PT_INIT(&pt_prime_data.pt);
        while (PT_SCHEDULE(pt_prime(&pt_prime_data.pt,&pt_prime_data)) == PT_BLOCKED){};
    }


UNITTEST_BENCHMARK_END()


bool isPrime(uint8_t number) {

    uint8_t i;

    if (number <= 1) return false;

    for (i=2; i*i<=number; i++) {
        if (number % i == 0) return false;
    }
    return true;
}

UNITTEST_BENCHMARK_BEGIN(primes_without_pt)

    uint8_t number = 0;

    while(number != 0xFF)
    {
        number++;
        isPrime(number);
    }

UNITTEST_BENCHMARK_END()


#define BENCHMARK_REPETITONS 10000


UNITTEST_TESTSUITE_BEGIN(pt)

UNITTEST_PRINTF("lc value for zombie : 0x%X\n",LC_DEFAULT);
UNITTEST_ADD_TESTCASE(pt_conditionals);
UNITTEST_ADD_TESTCASE(pt_computation);

UNITTEST_ADD_BENCHMARK(primes_with_pt, BENCHMARK_REPETITONS);
UNITTEST_ADD_BENCHMARK(primes_without_pt, BENCHMARK_REPETITONS);

UNITTEST_TESTSUITE_END()
