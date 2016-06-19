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
	\file	unittest_task.c

    \brief

    \details
*/

#define UNITTEST_CONF_VERBOSE

#include "unittest.h"
#include "task.h"
#include <string.h>

UNITTEST_TESTSUITE_INIT

TASK_THREAD(task_init_test_thread)
{
    return 0xAC;
}


UNITTEST_TESTCASE(task_init)
{
    task_t task = {0};
    task_list_node_t link = {0};

    task_init(&task);

    UNITTEST_ASSERT("Invalid task data",task.data == NULL);
    UNITTEST_ASSERT("Invalid task state",task.state == TASK_STATE_TERMINATED);
    UNITTEST_ASSERT("Invalid task link",!memcmp(&task.link,&link,sizeof(task.link)));
    UNITTEST_ASSERT("Invalid task thread",task.thread == NULL);
    UNITTEST_ASSERT("Invalid task pollreq",task.pollreq == 0);
    UNITTEST_ASSERT("Invalid task pt",task.pt.lc == 0);
}



UNITTEST_TESTCASE(task_event_init)
{
    event_t event = {0};
    task_t target;
    int data = 0;

    task_event_init(&event,&target,1234,&data);

    UNITTEST_ASSERT("Invalid target",event.target == &target);
    UNITTEST_ASSERT("Invalid id",event.id == 1234);
    UNITTEST_ASSERT("Invalid data",event.data == &data);
}




UNITTEST_TESTSUITE(task)
{
    UNITTEST_TESTSUITE_BEGIN();

    UNITTEST_EXEC_TESTCASE(task_init);
    UNITTEST_EXEC_TESTCASE(task_event_init);

    UNITTEST_TESTSUITE_END();
}
