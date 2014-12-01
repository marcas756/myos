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
    \file   unittest_xlist_dev.c

    \brief  Contains unittests created during development of xlist

    \details
            The generic list unit test suite was created before development of xlist.
            This test suite has been created during development of xlist with the purpose
            to get xlist on a level to pass the generic list unit tests.

            I decided to keep it.
*/

#define UNITTEST_CONF_VERBOSE

#include "unittest.h"
#include "xlist.h"

UNITTEST_TESTSUITE_INIT();

#define SIZE 20
#define RANDOM_SEED     12345
#define GARBAGE 0xAA
#define EMPTY 0x00

xlist_node_typedef(int);

void xlist_print (xlist_t *xlist)
{
    xlist_node_t *iterator = xlist->head;
    xlist_node_t *prev = NULL;
    xlist_node_t *next;

    UNITTEST_PRINTF("List [%d] : ",(int)xlist_size(xlist));

    if (!iterator)
    {
        UNITTEST_PRINTF("List is empty\n");
        return;
    }

    while(iterator)
    {
        UNITTEST_PRINTF("[%d]",*(int*) xlist_item(iterator));

        next = xlist_xor(prev,iterator->nextprev);
        prev = iterator;
        iterator = next;
    }

    UNITTEST_PRINTF("\n");
}


UNITTEST_TESTCASE_BEGIN(push_front_pop_front)

    int tmp;
    xlist_t mylist;
    xlist_node_t(int) intnodes [SIZE];

    xlist_init(&mylist);

    for (tmp = 0; tmp < SIZE; tmp++)
    {
        intnodes[tmp].item = tmp;
        xlist_push_front(&mylist,&intnodes[tmp]);
    }

    xlist_print(&mylist);


UNITTEST_TESTCASE_END()


UNITTEST_TESTCASE_BEGIN(push_back_pop_back)

    int tmp;
    xlist_t mylist;
    xlist_node_t(int) intnodes [SIZE];

    xlist_init(&mylist);

    for (tmp = 0; tmp < SIZE; tmp++)
    {
        intnodes[tmp].item = tmp;
        xlist_push_back(&mylist,&intnodes[tmp]);
    }

    xlist_print(&mylist);


UNITTEST_TESTCASE_END()



UNITTEST_TESTCASE_BEGIN(insert)

    int tmp;
    xlist_t mylist;
    xlist_node_t(int) intnodes [5];

    xlist_node_t(int) ia;
    xlist_node_t(int) ib;

    ia.item = 8;
    ib.item = 9;

    xlist_init(&mylist);

    for (tmp = 0; tmp < 5; tmp++)
    {
        intnodes[tmp].item = tmp;
        xlist_push_back(&mylist,&intnodes[tmp]);
    }

    xlist_print(&mylist);

    xlist_insert_after(&mylist,&intnodes[2],&ia);
    xlist_insert_before(&mylist,&intnodes[2],&ib);

    xlist_print(&mylist);

    xlist_erase(&mylist,&ia);
    xlist_erase(&mylist,&ib);

    xlist_print(&mylist);




UNITTEST_TESTCASE_END()

UNITTEST_TESTSUITE_BEGIN(xlist_dev)

UNITTEST_ADD_TESTCASE(push_front_pop_front);
UNITTEST_ADD_TESTCASE(push_back_pop_back);
UNITTEST_ADD_TESTCASE(insert);

UNITTEST_TESTSUITE_END()
