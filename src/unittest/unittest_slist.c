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
    \file   unittest_slist.c

    \brief

    \details
*/

#define UNITTEST_CONF_VERBOSE

#include "unittest.h"
#include "slist.h"
#include <stdlib.h>

UNITTEST_TESTSUITE_INIT();

#define SIZE 5
#define RANDOM_SEED 12345

slist_node_typedef(int);
slist_node_t(int) intnodes [SIZE];
slist_t MyList;

static void unittest_slist_init_items()
{
	size_t tmp;
	for (tmp=0;tmp<SIZE;tmp++)
		intnodes[tmp].item = tmp;
}

static void unittest_print_list (slist_t *list)
{
	slist_node_t* iterator;

	UNITTEST_PRINTF("List [%ld] = ",slist_size(list));

	for (iterator = slist_begin(list); iterator != slist_end(list); iterator=slist_next(iterator))
	{
		UNITTEST_PRINTF("[%d]",*(int*)slist_item(iterator));
	}

	UNITTEST_PRINTF("\n");
}

UNITTEST_TESTCASE_BEGIN(iterator)

	size_t tmp;

	slist_init(&MyList);
	UNITTEST_ASSERT("List has to be empty",!slist_size(&MyList));

	for(tmp=0;tmp<SIZE;tmp++)
		slist_push_front(&MyList,&intnodes[tmp]);

	UNITTEST_ASSERT("List size has to be SIZE",slist_size(&MyList)==SIZE);

	slist_node_t* tmpNode = slist_begin(&MyList);

	for(tmp=1;tmp<=SIZE;tmp++)
	{
		UNITTEST_ASSERT("Expected another value",*(int*)slist_item(tmpNode)==SIZE-tmp);
		tmpNode = slist_next(tmpNode);
	}


	tmpNode = slist_tail(&MyList);

	for(tmp=0;tmp<SIZE;tmp++)
	{
		UNITTEST_ASSERT("Expected another value",*(int*)slist_item(tmpNode)==tmp);
		tmpNode = slist_prev(&MyList,tmpNode);
	}



	for (tmpNode=slist_begin(&MyList); tmpNode!=slist_end(&MyList); tmpNode=slist_next(tmpNode))
	{
		printf("%d\n",*(int*)slist_item(tmpNode));
	}




UNITTEST_TESTCASE_END()


UNITTEST_TESTCASE_BEGIN(push_pop_front)

	slist_init(&MyList);
	UNITTEST_ASSERT("List has to be empty",!slist_size(&MyList));


UNITTEST_TESTCASE_END()

item_result_t intcompare (item_t *item1, item_t *item2)
{
	if (*(int*)item1 > *(int*)item2) return ITEM_LARGER_THAN;
	if (*(int*)item1 < *(int*)item2) return ITEM_LESS_THAN;
	return ITEM_EQUALS_TO;
}



UNITTEST_TESTCASE_BEGIN(remove)
    int tmpints [10] = {5,1,5,2,5,5,3,5,4,5};
    slist_node_t(int) tmpnodes [10];
    int tmp;


    for (tmp = 0; tmp < 10; tmp++)
    	tmpnodes[tmp].item = tmpints[tmp];

	slist_init(&MyList);
	UNITTEST_ASSERT("List has to be empty",!slist_size(&MyList));

	// remove from an emty list

	for (tmp = 0; tmp <100; tmp++)
	{
		slist_remove(&MyList,intcompare,&tmp);
		UNITTEST_ASSERT("List has to be empty",!slist_size(&MyList));
	}

	// remove from a list with one item
	slist_push_front(&MyList,&tmpnodes[0]);
	for (tmp = 0; !slist_empty(&MyList); tmp++)
	{
		UNITTEST_ASSERT("List may not be empty",slist_size(&MyList));
		slist_remove(&MyList,intcompare,&tmp);
	}

	UNITTEST_ASSERT("Expected another item",tmp-1 == *(int*)slist_item(&tmpnodes[0]));
	UNITTEST_ASSERT("List has to be empty", slist_empty(&MyList));

	// remove from a list with two items
	slist_push_front(&MyList,&tmpnodes[0]);
	slist_push_front(&MyList,&tmpnodes[1]);
	UNITTEST_ASSERT("Expected 2 items",slist_size(&MyList) == 2);
	slist_remove(&MyList,intcompare,slist_item(&tmpnodes[0]));
	UNITTEST_ASSERT("Expected 1 items",slist_size(&MyList) == 1);
	slist_remove(&MyList,intcompare,slist_item(&tmpnodes[1]));
	UNITTEST_ASSERT("Expected 0 items",slist_size(&MyList) == 0);
	UNITTEST_ASSERT("List has to be empty", slist_empty(&MyList));
	// remove the other way around
	slist_push_front(&MyList,&tmpnodes[0]);
	slist_push_front(&MyList,&tmpnodes[1]);
	UNITTEST_ASSERT("Expected 2 items",slist_size(&MyList) == 2);
	slist_remove(&MyList,intcompare,slist_item(&tmpnodes[1]));
	UNITTEST_ASSERT("Expected 1 items",slist_size(&MyList) == 1);
	slist_remove(&MyList,intcompare,slist_item(&tmpnodes[0]));
	UNITTEST_ASSERT("Expected 0 items",slist_size(&MyList) == 0);
	UNITTEST_ASSERT("List has to be empty", slist_empty(&MyList));


	for (tmp = 0; tmp < 10; tmp++)
		slist_push_front(&MyList,&tmpnodes[tmp]);

	UNITTEST_ASSERT("List size has to be 10",slist_size(&MyList)==10);

	tmp = 5;

	slist_remove(&MyList,intcompare,&tmp);

	UNITTEST_ASSERT("List size has to be 4",slist_size(&MyList)==4);
	UNITTEST_ASSERT("Expected front item to be 4",*(int*)slist_front(&MyList) == 4);
	UNITTEST_ASSERT("Expected front item to be 1",*(int*)slist_back(&MyList) == 1);
	slist_pop_front(&MyList);
	slist_pop_back(&MyList);
	UNITTEST_ASSERT("List size has to be 2",slist_size(&MyList)==2);
	UNITTEST_ASSERT("Expected front item to be 3",*(int*)slist_front(&MyList) == 3);
	UNITTEST_ASSERT("Expected front item to be 2",*(int*)slist_back(&MyList) == 2);
	slist_pop_front(&MyList);
	slist_pop_back(&MyList);
	UNITTEST_ASSERT("List has to be empty",slist_empty(&MyList));
	UNITTEST_ASSERT("List size has to be 0",slist_size(&MyList)==0);

	for (tmp = 0; tmp < 10; tmp++)
		slist_push_front(&MyList,&tmpnodes[tmp]);

	for (tmp = 1; tmp <= 4; tmp++)
	{
		slist_remove(&MyList,intcompare,&tmp);
		UNITTEST_ASSERT("Wrong list size",slist_size(&MyList)==10-tmp);
	}

	tmp = 5;

	slist_remove(&MyList,intcompare,&tmp);

	UNITTEST_ASSERT("List has to be empty",slist_empty(&MyList));




UNITTEST_TESTCASE_END()




UNITTEST_TESTCASE_BEGIN(unique)

	int tmp;
	int tmpints [] = {1,2,2,3,3,3,1,2,3,1,2,3,3,2,1,3,2,1,9,7,8,5,6,6,6,5,4,3,2,1,2,3,4,6,7,8,9,0,7,6,1};
	slist_node_t(int)  tmpnodes [sizeof(tmpints)/sizeof(*tmpints)];

	for (tmp = 0; tmp < sizeof(tmpints)/sizeof(*tmpints); tmp++)
		(*(int*)slist_item(&tmpnodes[tmp])) = tmpints[tmp];

	slist_init(&MyList);

	UNITTEST_ASSERT("Wrong list size",slist_size(&MyList)==0);

	for (tmp = 0; tmp < sizeof(tmpints)/sizeof(*tmpints); tmp++)
		slist_push_front(&MyList,&tmpnodes[tmp]);

	UNITTEST_ASSERT("Wrong list size",slist_size(&MyList)==sizeof(tmpints)/sizeof(*tmpints));

	unittest_print_list (&MyList);

	slist_unique(&MyList,intcompare);
	unittest_print_list (&MyList);
	UNITTEST_ASSERT("Wrong list size",slist_size(&MyList)==10);
	slist_reverse(&MyList);
	unittest_print_list (&MyList);
	slist_sort(&MyList,intcompare);
	unittest_print_list (&MyList);

UNITTEST_TESTCASE_END()


UNITTEST_TESTCASE_BEGIN(sort)

	int tmp;
	int tmpints [] = {1,2,2,3,3,3,1,2,3,1,2,3,3,2,1,3,2,1,9,7,8,5,6,6,6,5,4,3,2,1,2,3,4,6,7,8,9,0,7,6,1};
	slist_node_t(int)  tmpnodes [sizeof(tmpints)/sizeof(*tmpints)];

	for (tmp = 0; tmp < sizeof(tmpints)/sizeof(*tmpints); tmp++)
		(*(int*)slist_item(&tmpnodes[tmp])) = tmpints[tmp];

	slist_init(&MyList);

	UNITTEST_ASSERT("Wrong list size",slist_size(&MyList)==0);

	for (tmp = 0; tmp < sizeof(tmpints)/sizeof(*tmpints); tmp++)
		slist_push_front(&MyList,&tmpnodes[tmp]);

	UNITTEST_ASSERT("Wrong list size",slist_size(&MyList)==sizeof(tmpints)/sizeof(*tmpints));

	unittest_print_list (&MyList);

	slist_sort(&MyList,intcompare);

	unittest_print_list (&MyList);

	UNITTEST_ASSERT("Wrong list size",slist_size(&MyList)==sizeof(tmpints)/sizeof(*tmpints));

UNITTEST_TESTCASE_END()

UNITTEST_TESTSUITE_BEGIN(slist)

	unittest_slist_init_items();

	UNITTEST_ADD_TESTCASE(iterator);
	UNITTEST_ADD_TESTCASE(push_pop_front);
	UNITTEST_ADD_TESTCASE(remove);
	UNITTEST_ADD_TESTCASE(unique);
	UNITTEST_ADD_TESTCASE(sort);

UNITTEST_TESTSUITE_END()
