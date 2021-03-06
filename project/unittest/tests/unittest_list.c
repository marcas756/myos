/*! \copyright
    Copyright (c) 2013, marco@bacchi.at
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




#include "unittest.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#ifdef UNITTEST_SLIST
    #include"unittest_slist.h"
#elif UNITTEST_DLIST
    #include"unittest_dlist.h"
#else
    #include"unittest_slist.h"
    #error "Unknown list type"
#endif

#define SIZE 3


typedef struct {
    LIST_NODE_TYPE;
    int testint;
}int_node_t;

int_node_t intnodes [SIZE];




UNITTEST_TESTCASE(init)
{
   list_t list;
   list_init(&list);
   UNITTEST_ASSERT("Expected empty list",list_empty(&list));
   UNITTEST_ASSERT("Expected empty list",list_size(&list) == 0);
}


#define UNITTEST_TESTSUITE_EXP(x) \
    UNITTEST_TESTSUITE(x)

UNITTEST_TESTSUITE_EXP(unittest_list_type)
{
    UNITTEST_TESTSUITE_BEGIN();

    UNITTEST_EXEC_TESTCASE(init);
    /*
    UNITTEST_EXEC_TESTCASE(push_front_pop_back);
    UNITTEST_EXEC_TESTCASE(push_back_pop_front);
    UNITTEST_EXEC_TESTCASE(push_front_pop_front);
    UNITTEST_EXEC_TESTCASE(push_back_pop_back);


    UNITTEST_EXEC_TESTCASE(iterator);
    UNITTEST_EXEC_TESTCASE(front_back_item);
    UNITTEST_EXEC_TESTCASE(find_and_erase);
    UNITTEST_EXEC_TESTCASE(remove);
    UNITTEST_EXEC_TESTCASE(sort);
    UNITTEST_EXEC_TESTCASE(unique);
    UNITTEST_EXEC_TESTCASE(double_iterator_erase_problem);
    */

    UNITTEST_TESTSUITE_END();
}
