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
    \file   unittest_list.c

    \brief

    \details
*/


#define UNITTEST_CONF_VERBOSE
#define UNITTEST_CONF_TIMESTAMPS
#define UNITTEST_CONF_BENCHMARK

#include "unittest.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

UNITTEST_TESTSUITE_INIT();


#ifdef UNITTEST_SLIST
    #include"unittest_slist.h"
#elif UNITTEST_DLIST
    #include"unittest_dlist.h"
#elif UNITTEST_XLIST
    #include"unittest_xlist.h"
#else
   #error "Error: No list type defined"
#endif

#define UNITTEST_TESTSUITE_BEGIN_EXP(x) \
    UNITTEST_TESTSUITE_BEGIN(x)

#define SIZE 200
#define RANDOM_SEED 12345
#define GARBAGE 0xAA

list_t mylist;
list_node_typedef(int);
list_node_t(int) intnodes [SIZE];

void print_list(list_t *list)
{
    list_node_t *iterator = list_begin(list);

    if(!iterator)
    {
        UNITTEST_PRINTF("List is empty\n");
        return;
    }
    else
    {
        UNITTEST_PRINTF("List [%d] : ",(int)list_size(list));
    }

    while(iterator)
    {
        UNITTEST_PRINTF("[%d]",*(int*)list_item(iterator));
        iterator = list_next(list,iterator);
    }

    UNITTEST_PRINTF("\n");
}




UNITTEST_TESTCASE_BEGIN(init)

    list_init(&mylist);
    UNITTEST_ASSERT("Begin of list must be NULL", list_begin(&mylist) == NULL);
    UNITTEST_ASSERT("Tail of list must be NULL", list_end(&mylist) == NULL);
    UNITTEST_ASSERT("Size of list must be 0", list_size(&mylist) == 0);
    UNITTEST_ASSERT("List must be empty", list_empty(&mylist));

UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(push_front_pop_back)

    int tmp;
    list_init(&mylist);

    for(tmp=0; tmp < SIZE; tmp++)
    {
        intnodes[tmp].item = tmp;
        list_push_front(&mylist,&intnodes[tmp]);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == tmp+1);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
    }

    UNITTEST_ASSERT("Size of list must be SIZE", list_size(&mylist) == SIZE);

    for(tmp=0; tmp < SIZE; tmp++)
    {

        UNITTEST_ASSERT("Expected another item content", *(int*)list_item(list_end(&mylist)) == tmp);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
        list_pop_back(&mylist);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == SIZE-(tmp+1));
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&mylist));


UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(push_back_pop_front)

    int tmp;
    list_init(&mylist);

    for(tmp=0; tmp < SIZE; tmp++)
    {
        intnodes[tmp].item = tmp;
        list_push_back(&mylist,&intnodes[tmp]);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == tmp+1);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
    }

    UNITTEST_ASSERT("Size of list must be SIZE", list_size(&mylist) == SIZE);

    for(tmp=0; tmp < SIZE; tmp++)
    {

        UNITTEST_ASSERT("Expected another item content", *(int*)list_item(list_begin(&mylist)) == tmp);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
        list_pop_front(&mylist);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == SIZE-(tmp+1));
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&mylist));


UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(push_front_pop_front)

    int tmp;
    list_init(&mylist);

    UNITTEST_ASSERT("List must be empty", list_empty(&mylist));

    for(tmp = 0; tmp < SIZE; tmp++)
    {
        intnodes[tmp].item = tmp;
        list_push_front(&mylist,&intnodes[tmp]);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == tmp+1);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
    }

    for(tmp = SIZE-1; tmp >= 0 ; tmp--)
    {
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == tmp+1);
        UNITTEST_ASSERT("Expected another item content", *(int*)list_front(&mylist) == tmp);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
        list_pop_front(&mylist);
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&mylist));

UNITTEST_TESTCASE_END()



UNITTEST_TESTCASE_BEGIN(push_back_pop_back)

    int tmp;
    list_init(&mylist);

    UNITTEST_ASSERT("List must be empty", list_empty(&mylist));

    for(tmp = 0; tmp < SIZE; tmp++)
    {
        intnodes[tmp].item = tmp;
        list_push_back(&mylist,&intnodes[tmp]);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == tmp+1);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
    }

    for(tmp = SIZE-1; tmp >= 0 ; tmp--)
    {
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == tmp+1);
        UNITTEST_ASSERT("Expected another item content", *(int*)list_back(&mylist) == tmp);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
        list_pop_back(&mylist);
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&mylist));

UNITTEST_TESTCASE_END()


UNITTEST_TESTCASE_BEGIN(iterator)

    int tmp;
    list_node_t* iterator;
    list_init(&mylist);

    UNITTEST_ASSERT("List must be empty", list_empty(&mylist));

    for(tmp = 0; tmp < SIZE; tmp++)
    {
        intnodes[tmp].item = tmp;
        list_push_back(&mylist,&intnodes[tmp]);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == tmp+1);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
    }

    UNITTEST_ASSERT("Size of list must be SIZE", list_size(&mylist) == SIZE);

    for (iterator = list_begin(&mylist), tmp = 0; iterator; iterator = list_next(&mylist,iterator), tmp++)
        UNITTEST_ASSERT("Expected another item value", *(int*)list_item(iterator) == tmp);



    for (iterator = list_end(&mylist), tmp = SIZE-1; iterator; iterator = list_prev(&mylist,iterator), tmp--)
        UNITTEST_ASSERT("Expected another item value", *(int*)list_item(iterator) == tmp);

UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(front_back_item)

    list_init(&mylist);
    list_node_typedef(char);
    list_node_t(char) autonodes [3];


    autonodes[0].item = 11;
    autonodes[1].item = 22;
    autonodes[2].item = 33;

    list_push_front(&mylist,&autonodes[2]);
    list_push_front(&mylist,&autonodes[1]);
    list_push_front(&mylist,&autonodes[0]);


    UNITTEST_ASSERT("Expected another item value", *(char*)list_front(&mylist) == 11);
    UNITTEST_ASSERT("Expected another item value", *(char*)list_back(&mylist) == 33);
    UNITTEST_ASSERT("Expected another item value",*(char*)list_item(list_next(&mylist,list_begin(&mylist))) == 22);
    UNITTEST_ASSERT("Expected another item value",*(char*)list_item(list_prev(&mylist,list_end(&mylist))) == 22);

UNITTEST_TESTCASE_END()


UNITTEST_TESTCASE_BEGIN(find_and_erase)

    list_node_typedef(char);
    list_node_t(int) autonodes [3];
    int tmp;
    list_node_t *tmpnode;
    list_init(&mylist);


    UNITTEST_ASSERT("List must be empty", list_empty(&mylist));

    for(tmp = 0; tmp < SIZE; tmp++)
    {
        intnodes[tmp].item = tmp;
        list_push_back(&mylist,&intnodes[tmp]);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == tmp+1);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
    }

    srand(RANDOM_SEED);

    while(!list_empty(&mylist))
    {
        tmp = list_size(&mylist);
        tmpnode = list_find(&mylist,&intnodes[rand()%SIZE]);
        if(tmpnode)
        {
            list_erase(&mylist,tmpnode);
            UNITTEST_ASSERT("Expected list size to be decreased by one", tmp-list_size(&mylist) == 1);
        }

    }




    list_clear(&mylist);

    autonodes[0].item = 11;
    autonodes[1].item = 22;
    autonodes[2].item = 33;

    list_push_front(&mylist,&autonodes[2]);
    list_push_front(&mylist,&autonodes[1]);
    list_push_front(&mylist,&autonodes[0]);

    tmpnode = list_find(&mylist,&autonodes[1]);

    UNITTEST_ASSERT("Did not find node",tmpnode != NULL);

    UNITTEST_ASSERT("Expected list size of 3", list_size(&mylist) == 3);

    list_erase(&mylist,&autonodes[1]);

    UNITTEST_ASSERT("Expected list size of 2", list_size(&mylist) == 2);

    UNITTEST_ASSERT("Expected another item value", *(char*)list_front(&mylist) == 11);
    UNITTEST_ASSERT("Expected another item value", *(char*)list_back(&mylist) == 33);
    UNITTEST_ASSERT("Expected another item value",*(char*)list_item(list_next(&mylist,list_begin(&mylist))) == 33);
    UNITTEST_ASSERT("Expected another item value",*(char*)list_item(list_prev(&mylist,list_end(&mylist))) == 11);

    tmpnode = list_find(&mylist,&autonodes[1]);

    UNITTEST_ASSERT("Did not expect to find node",tmpnode == NULL);

    tmpnode = list_find(&mylist,&autonodes[2]);

    UNITTEST_ASSERT("Did not find node",tmpnode != NULL);

    list_erase(&mylist,&autonodes[2]);

    UNITTEST_ASSERT("Expected list size of 1", list_size(&mylist) == 1);

    UNITTEST_ASSERT("Expected NULL", list_next(&mylist,list_begin(&mylist)) == NULL);
    UNITTEST_ASSERT("Expected NULL", list_prev(&mylist,list_end(&mylist)) == NULL);
    UNITTEST_ASSERT("Expected node Nr. 0", list_end(&mylist) == (list_node_t*)&autonodes[0]);
    UNITTEST_ASSERT("Expected node Nr. 0", list_begin(&mylist) == (list_node_t*)&autonodes[0]);

UNITTEST_TESTCASE_END()

item_result_t intcompare(item_t* int1, item_t* int2)
{
    if(*(int*)int1 > *(int*)int2)
        return ITEM_LARGER_THAN;

    if(*(int*)int1 < *(int*)int2)
        return ITEM_LESS_THAN;

    return ITEM_EQUALS_TO;
}

UNITTEST_TESTCASE_BEGIN(remove)

    int tmp;
    int removeval;
    list_node_t* iterator;

    removeval = rand();

    list_init(&mylist);

    for(tmp = 0; tmp < SIZE; tmp++)
    {
        if(rand()%5)
            intnodes[tmp].item = removeval;
        else
            intnodes[tmp].item = rand();

        list_push_back(&mylist,&intnodes[tmp]);
        UNITTEST_ASSERT("Expected another list size", list_size(&mylist) == tmp+1);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&mylist));
    }

    iterator = list_begin(&mylist);
    tmp = 0;

    while(iterator)
    {
        if(*(int*)list_item(iterator) == removeval)
            tmp++;

        iterator = list_next(&mylist,iterator);
    }



    list_remove(&mylist,intcompare,&removeval);

    UNITTEST_ASSERT("Wrong list size", list_size(&mylist) == SIZE-tmp);

    iterator = list_begin(&mylist);

    while(iterator)
    {
        UNITTEST_ASSERT("Did not expect to find removed value", *(int*)list_item(iterator) != removeval);
        iterator = list_next(&mylist,iterator);
    }

UNITTEST_TESTCASE_END()

UNITTEST_TESTCASE_BEGIN(sort)

    int tmp,tmp2;
    list_node_t(int) intnodes [20];
    list_node_t *iterator;

    srand(time(NULL));


    for (tmp2 = 0; tmp2 <= sizeof(intnodes)/sizeof(*intnodes); tmp2++)
    {
        list_init(&mylist);

        for(tmp = 0; tmp < tmp2; tmp++)
        {
            *(int*)list_item(&intnodes[tmp]) = rand()%10;
            list_push_front(&mylist,&intnodes[tmp]);
        }
        UNITTEST_PRINTF("Unsorted ");
        print_list(&mylist);
        list_sort(&mylist,intcompare);
        UNITTEST_PRINTF("Sorted   ");
        print_list(&mylist);

        iterator = list_begin(&mylist);

        if(!iterator) continue;

        while(list_next(&mylist,iterator))
        {
            UNITTEST_ASSERT("List is not sorted", intcompare(list_item(iterator),list_item(list_next(&mylist,iterator))) != ITEM_LARGER_THAN );
            iterator = list_next(&mylist,iterator);
        }
    }

UNITTEST_TESTCASE_END()


UNITTEST_TESTCASE_BEGIN(unique)

    int tmp,tmp2;
    list_node_t(int) intnodes [20];
    list_node_t *iterator;

    for (tmp2 = 0; tmp2 <= sizeof(intnodes)/sizeof(*intnodes); tmp2++)
    {
       list_init(&mylist);

       for(tmp = 0; tmp < tmp2; tmp++)
       {
           *(int*)list_item(&intnodes[tmp]) = rand()%10;
           list_push_front(&mylist,&intnodes[tmp]);
       }

       UNITTEST_PRINTF("Unsorted ");
       print_list(&mylist);
       list_sort(&mylist,intcompare);
       UNITTEST_PRINTF("Sorted   ");
       print_list(&mylist);
       list_unique(&mylist,intcompare);
       UNITTEST_PRINTF("Unique   ");
       print_list(&mylist);

       while (!list_empty(&mylist))
       {
           iterator = list_begin(&mylist);
           list_pop_front(&mylist);

           if (!list_empty(&mylist))
           {
               UNITTEST_ASSERT("Succeeding node is equal",intcompare(list_item(iterator),list_item(list_begin(&mylist))) != ITEM_EQUALS_TO);
           }

       }
    }

UNITTEST_TESTCASE_END()


UNITTEST_BENCHMARK_BEGIN(push_front_pop_back)

    int tmp;
    list_init(&mylist);

    for(tmp=0; tmp < SIZE; tmp++)
        list_push_front(&mylist,&intnodes[tmp]);

    while(!list_empty(&mylist))
        list_pop_back(&mylist);

UNITTEST_BENCHMARK_END()

UNITTEST_BENCHMARK_BEGIN(push_back_pop_front)

    int tmp;
    list_init(&mylist);

    for(tmp=0; tmp < SIZE; tmp++)
        list_push_back(&mylist,&intnodes[tmp]);

    while(!list_empty(&mylist))
        list_pop_front(&mylist);

UNITTEST_BENCHMARK_END()

UNITTEST_BENCHMARK_BEGIN(push_front_pop_front)

    int tmp;
    list_init(&mylist);

    for(tmp=0; tmp < SIZE; tmp++)
        list_push_front(&mylist,&intnodes[tmp]);

    while(!list_empty(&mylist))
        list_pop_front(&mylist);

UNITTEST_BENCHMARK_END()

UNITTEST_BENCHMARK_BEGIN(push_back_pop_back)

    int tmp;
    list_init(&mylist);

    for(tmp=0; tmp < SIZE; tmp++)
        list_push_back(&mylist,&intnodes[tmp]);

    while(!list_empty(&mylist))
        list_pop_back(&mylist);

UNITTEST_BENCHMARK_END()

UNITTEST_BENCHMARK_BEGIN(remove)

    int tmp,remove;
    list_init(&mylist);

    remove = ~GARBAGE;

    for(tmp=0; tmp < SIZE; tmp++)
    {
        intnodes[tmp].item = (tmp&1)?(~GARBAGE):(GARBAGE);
        list_push_front(&mylist,&intnodes[tmp]);
    }

    list_remove(&mylist,intcompare,&remove);

UNITTEST_BENCHMARK_END()

UNITTEST_BENCHMARK_BEGIN(find)

    bool init = false;

    if(!init)
    {
        int tmp;
        list_init(&mylist);

        for(tmp=0; tmp < SIZE; tmp++)
            list_push_front(&mylist,&intnodes[tmp]);

        init = true;
    }

    list_find(&mylist,&intnodes[rand()%SIZE]);

UNITTEST_BENCHMARK_END()


UNITTEST_BENCHMARK_BEGIN(erase)

    size_t tmp;

    int cnt;
    list_init(&mylist);

    for(tmp=0; tmp < SIZE; tmp++)
        list_push_front(&mylist,&intnodes[tmp]);


    while(!list_empty(&mylist))
    {
        tmp = rand()%SIZE;
        if(list_find(&mylist,&intnodes[tmp]))
        {

            list_erase(&mylist,&intnodes[tmp]);
        }
    }

UNITTEST_BENCHMARK_END()


UNITTEST_BENCHMARK_BEGIN(sort)

    int tmp;

    list_init(&mylist);

    for(tmp = 0; tmp < SIZE; tmp++)
    {
        intnodes[tmp].item = rand()%10;
        list_push_front(&mylist,&intnodes[tmp]);
    }

    list_sort(&mylist,intcompare);

UNITTEST_BENCHMARK_END()


UNITTEST_BENCHMARK_BEGIN(sort_and_unique)

    int tmp;

    list_init(&mylist);

    for(tmp = 0; tmp < SIZE; tmp++)
    {
        intnodes[tmp].item = rand()%10;
        list_push_front(&mylist,&intnodes[tmp]);
    }

    list_sort(&mylist,intcompare);
    list_unique(&mylist,intcompare);

UNITTEST_BENCHMARK_END()

#define BENCHMARK_REPETITONS 100

UNITTEST_TESTSUITE_BEGIN_EXP(unittest_list_type)

    UNITTEST_ADD_TESTCASE(init);
    UNITTEST_ADD_TESTCASE(push_front_pop_back);
    UNITTEST_ADD_TESTCASE(push_back_pop_front);
    UNITTEST_ADD_TESTCASE(push_front_pop_front);
    UNITTEST_ADD_TESTCASE(push_back_pop_back);
    UNITTEST_ADD_TESTCASE(iterator);
    UNITTEST_ADD_TESTCASE(front_back_item);
    UNITTEST_ADD_TESTCASE(find_and_erase);
    UNITTEST_ADD_TESTCASE(remove);
    UNITTEST_ADD_TESTCASE(sort);
    UNITTEST_ADD_TESTCASE(unique);


    UNITTEST_ADD_BENCHMARK(push_front_pop_back,BENCHMARK_REPETITONS);
    UNITTEST_ADD_BENCHMARK(push_back_pop_front,BENCHMARK_REPETITONS);
    UNITTEST_ADD_BENCHMARK(push_front_pop_front,BENCHMARK_REPETITONS);
    UNITTEST_ADD_BENCHMARK(push_back_pop_back,BENCHMARK_REPETITONS);
    UNITTEST_ADD_BENCHMARK(remove,BENCHMARK_REPETITONS);
    UNITTEST_ADD_BENCHMARK(find,BENCHMARK_REPETITONS);
    UNITTEST_ADD_BENCHMARK(erase,BENCHMARK_REPETITONS);
    UNITTEST_ADD_BENCHMARK(sort,BENCHMARK_REPETITONS);
    UNITTEST_ADD_BENCHMARK(sort_and_unique,BENCHMARK_REPETITONS);

UNITTEST_TESTSUITE_END()
