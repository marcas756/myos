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
    \file   unittest_itempool.c

    \brief

    \details
*/

#define UNITTEST_CONF_VERBOSE

#include "unittest.h"
#include "itempool.h"

UNITTEST_TESTSUITE_INIT

#define SIZE 5
#define RANDOM_SEED     12345
#define GARBAGE 0xAA
#define EMPTY 0x00

ITEMPOOL_TYPEDEF(intpool,int,SIZE);
ITEMPOOL_T(intpool) MyPool;
int *intptrs [SIZE];


UNITTEST_TESTCASE(itempool_init)
{
    int tmp;
    int garbage_int;

    memset(&MyPool,GARBAGE,sizeof(MyPool));
    memset(&garbage_int,GARBAGE,sizeof(garbage_int));

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
        UNITTEST_ASSERT("Status Bytes have to be garbage",ITEMPOOL_STATUS(MyPool)[tmp] == GARBAGE);

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
        UNITTEST_ASSERT("Items have to be garbage",ITEMPOOL_ITEMS(MyPool)[tmp] == garbage_int);


    ITEMPOOL_INIT(MyPool);

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
        UNITTEST_ASSERT("Status Bytes have to be 0",ITEMPOOL_STATUS(MyPool)[tmp] == ITEMPOOL_ITEM_FREE);

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
        UNITTEST_ASSERT("Items have to be garbage",ITEMPOOL_ITEMS(MyPool)[tmp] == garbage_int);

}

UNITTEST_TESTCASE(itempool_alloc)
{
    int tmp;
    int garbage_int;
    memset(&garbage_int,GARBAGE,sizeof(garbage_int));

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
        UNITTEST_ASSERT("Items have to be garbage",ITEMPOOL_ITEMS(MyPool)[tmp] == garbage_int);

    srand(RANDOM_SEED);

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
    {
        intptrs[tmp] = (int*)ITEMPOOL_ALLOC(MyPool);
        *intptrs[tmp] = rand();
    }

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
    {
        UNITTEST_ASSERT("Status Bytes have to be 1",ITEMPOOL_STATUS(MyPool)[tmp] == ITEMPOOL_ITEM_USED);
        UNITTEST_ASSERT("Expected another item value",ITEMPOOL_ITEMS(MyPool)[tmp] == *intptrs[tmp]);
        UNITTEST_ASSERT("Expected another item",&ITEMPOOL_ITEMS(MyPool)[tmp] == intptrs[tmp]);
    }


    UNITTEST_ASSERT("No further allocation allowed",!ITEMPOOL_ALLOC(MyPool));



}



UNITTEST_TESTCASE(itempool_free)
{
    int tmp;

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
        ITEMPOOL_FREE(MyPool,intptrs[tmp]);

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
    {
        intptrs[tmp] =(int*)ITEMPOOL_ALLOC(MyPool);
        UNITTEST_ASSERT("Allocation may not return NULL",intptrs[tmp]);
    }

    UNITTEST_ASSERT("No further allocation allowed",!ITEMPOOL_ALLOC(MyPool));

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
        ITEMPOOL_FREE(MyPool,intptrs[tmp]);

}


UNITTEST_TESTCASE(itempool_calloc)
{
    /* MyPool should be initialized after unittest itempool_init */

    int tmp;
    int garbage_int;
    memset(&garbage_int,GARBAGE,sizeof(garbage_int));

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
    {
        intptrs[tmp] = (int*)ITEMPOOL_ALLOC(MyPool);
        UNITTEST_ASSERT("Allocation may not return NULL",intptrs[tmp]);
        *intptrs[tmp] = garbage_int;
    }

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
        ITEMPOOL_FREE(MyPool,intptrs[tmp]);

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
    {
        intptrs[tmp] = (int*)ITEMPOOL_ALLOC(MyPool);
        UNITTEST_ASSERT("Allocation may not return NULL",intptrs[tmp]);
        UNITTEST_ASSERT("Expected another item value",*intptrs[tmp] == garbage_int);
    }

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
        ITEMPOOL_FREE(MyPool,intptrs[tmp]);

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
    {
        intptrs[tmp] = (int*)ITEMPOOL_CALLOC(MyPool);
        UNITTEST_ASSERT("Allocation may not return NULL",intptrs[tmp]);
        UNITTEST_ASSERT("Expected another item value",*intptrs[tmp] == 0);
    }

    for(tmp=0; tmp < ITEMPOOL_SIZE(MyPool); tmp++)
        ITEMPOOL_FREE(MyPool,intptrs[tmp]);

}



UNITTEST_TESTSUITE(itempool)
{
    UNITTEST_TESTSUITE_BEGIN();

    UNITTEST_EXEC_TESTCASE(itempool_init);
    UNITTEST_EXEC_TESTCASE(itempool_alloc);
    UNITTEST_EXEC_TESTCASE(itempool_free);
    UNITTEST_EXEC_TESTCASE(itempool_calloc);

    UNITTEST_TESTSUITE_END();
}
