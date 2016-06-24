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


TASK_THREAD(task_stub)
{
    return *(task_state_t*)data;
}

extern void task_invoke(task_t *task ,event_id_t event_id, void *data);
extern task_list_t task_list;
UNITTEST_TESTCASE(task_invoke)
{
    task_t task;
    event_id_t event_id = 123;
    task_state_t data = PT_STATE_WAITING;

    task.thread = task_stub;
    task.data = &data;
    task_list_push_front(&task);


    UNITTEST_ASSERT("Task must be in task list", task_list_find(&task));
    UNITTEST_ASSERT("Task must be in task list", task_list_size() == 1);

    task.state = PT_STATE_TERMINATED;

    task_invoke(&task,event_id,&data);

    UNITTEST_ASSERT("Task must be in task list", task_list_find(&task));
    UNITTEST_ASSERT("Task must be in task list", task_list_size() == 1);

    task.state = PT_STATE_WAITING;
    data = PT_STATE_TERMINATED;

    task_invoke(&task,event_id,&data);

    UNITTEST_ASSERT("Task must not be in task list", !task_list_find(&task));
    UNITTEST_ASSERT("Task must not be in task list", task_list_size() == 0);
}




UNITTEST_TESTSUITE(task)
{
    UNITTEST_TESTSUITE_BEGIN();

    UNITTEST_EXEC_TESTCASE(task_invoke);


    UNITTEST_TESTSUITE_END();
}
