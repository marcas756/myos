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
#include "dlist.h"
#include <stdlib.h>
#include <string.h>

UNITTEST_TESTSUITE_INIT();

#define SIZE 5
#define RANDOM_SEED 12345
#define GARBAGE 0xAA

dlist_node_typedef(int);

dlist_t mylist;

UNITTEST_TESTCASE_BEGIN(init)

    memset(&mylist,GARBAGE,sizeof(mylist));

    UNITTEST_ASSERT("Expected uninitialized head pointer", mylist.head != NULL);
    UNITTEST_ASSERT("Expected uninitialized tail pointer", mylist.tail != NULL);

    dlist_init(&mylist);

    UNITTEST_ASSERT("Expected initialized head pointer", mylist.head == NULL);
    UNITTEST_ASSERT("Expected initialized tail pointer", mylist.tail == NULL);

UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(push_front)

    dlist_node_t(int) nodes [SIZE];
    dlist_node_t(int) *iterator;

    int tmp;

    dlist_init(&mylist);

    for (tmp = 0; tmp < SIZE; tmp++)
        nodes[tmp].item = tmp;

    for (tmp = 0; tmp < SIZE; tmp++)
        dlist_push_front(&mylist,&nodes[tmp]);

    iterator = (dlist_node_t(int)*)mylist.head;
    UNITTEST_ASSERT("Did not expect predecessor node", iterator->link.prev == NULL);
    UNITTEST_ASSERT("Expected successor node", iterator->link.next != NULL);

    tmp = SIZE-1;

    while(iterator)
    {
        UNITTEST_ASSERT("Expected another node item value", iterator->item == tmp--);
        iterator = (dlist_node_t(int)*)iterator->link.next;
    }

    iterator = (dlist_node_t(int)*)mylist.tail;
    UNITTEST_ASSERT("Did not expect successor node", iterator->link.next == NULL);
    UNITTEST_ASSERT("Expected predecessor node", iterator->link.prev != NULL);

    tmp = 0;

    while(iterator)
    {
        UNITTEST_ASSERT("Expected another node item value", iterator->item == tmp++);
        iterator = (dlist_node_t(int)*)iterator->link.prev;
    }



UNITTEST_TESTCASE_END()


UNITTEST_TESTSUITE_BEGIN(dlist)

	UNITTEST_ADD_TESTCASE(init);
    UNITTEST_ADD_TESTCASE(push_front);

UNITTEST_TESTSUITE_END()
