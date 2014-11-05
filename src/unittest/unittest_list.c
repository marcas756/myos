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
    \file   unittest_dlist.c

    \brief

    \details
*/

/* TODO: WRITE BASE TEST FOR ALL LIST TYPES! */

#define UNITTEST_CONF_VERBOSE

#include "unittest.h"
#include <stdlib.h>
#include <string.h>

UNITTEST_TESTSUITE_INIT();

#ifdef UNITTEST_SLIST
    #include"unittest_slist.h"
#elif UNITTEST_DLIST
    #include"unittest_dlist.h"
#else
   #error "Error: No list type defined"
#endif

#define UNITTEST_TESTSUITE_BEGIN_EXP(x) \
    UNITTEST_TESTSUITE_BEGIN(x)

#define SIZE 5
#define RANDOM_SEED 12345
#define GARBAGE 0xAA

list_t mylist;
list_node_typedef(int);
list_node_t(int) intnodes [SIZE];


UNITTEST_TESTCASE_BEGIN(init)

    list_init(&mylist);
    UNITTEST_ASSERT("Begin of list must be NULL", list_begin(&mylist) == NULL);
    UNITTEST_ASSERT("Tail of list must be NULL", list_tail(&mylist) == NULL);
    UNITTEST_ASSERT("Size of list must be 0", list_size(&mylist) == 0);
    UNITTEST_ASSERT("List must be empty", list_empty(&mylist));

UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(push_front_pop_back)

    int tmp;
    list_init(&mylist);

    for(tmp=1; tmp <= SIZE; tmp++)
    {
        intnodes[tmp].item = tmp;
        list_push_front(&mylist,&intnodes[tmp]);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == tmp);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
    }

    UNITTEST_ASSERT("Size of list must be SIZE", list_size(&mylist) == SIZE);

    for(tmp=1; tmp <= SIZE; tmp++)
    {

        UNITTEST_ASSERT("Expected another item content", *(int*)list_item(list_tail(&mylist)) == tmp);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
        list_pop_back(&mylist);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == SIZE-tmp);
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&mylist));


UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(push_back_pop_front)

    int tmp;
    list_init(&mylist);

    for(tmp=1; tmp <= SIZE; tmp++)
    {
        intnodes[tmp].item = tmp;
        list_push_back(&mylist,&intnodes[tmp]);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == tmp);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
    }

    UNITTEST_ASSERT("Size of list must be SIZE", list_size(&mylist) == SIZE);

    for(tmp=1; tmp <= SIZE; tmp++)
    {

        UNITTEST_ASSERT("Expected another item content", *(int*)list_item(list_begin(&mylist)) == tmp);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
        list_pop_front(&mylist);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == SIZE-tmp);
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&mylist));


UNITTEST_TESTCASE_END()


UNITTEST_TESTSUITE_BEGIN_EXP(unittest_list_type)

	UNITTEST_ADD_TESTCASE(init);
    UNITTEST_ADD_TESTCASE(push_front_pop_back);
    UNITTEST_ADD_TESTCASE(push_back_pop_front)

UNITTEST_TESTSUITE_END()
