/*!
    Copyright (c) 2025, Marco Bacchi <marco@bacchi.at>

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software
       without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS”
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "myunit.h"
#include "pt.h"
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

enum {
   CHECKPOINT_1 = 0,
   CHECKPOINT_2,
   CHECKPOINT_3,
   CHECKPOINT_4,

   LOCK,
};


/*!
    \brief Test the initialization of a protothread.

    This unit test verifies that the `PT_INIT` function correctly initializes
    the state of a protothread to `PT_STATE_INITIALIZED`.
*/
MYUNIT_TESTCASE(init)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt;
    pt.lc = 1234;
    MYUNIT_ASSERT_DIFFER(PT_GET_STATE(&pt), PT_STATE_INITIALIZED);


    // EXECUTE TESTCASE:
    // -------------------------------------------------
    PT_INIT(&pt);

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_INITIALIZED);

}


PT_THREAD(empty_run(pt_t *pt))
{
    PT_BEGIN(pt);

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_1);

    PT_END(pt);
}

/*!
    \brief Test the execution of an empty protothread.

    This unit test verifies that an empty protothread runs exactly once, transitioning
    its state directly from `PT_STATE_INITIALIZED` to `PT_STATE_TERMINATED`.
*/
MYUNIT_TESTCASE(empty_run)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt;
    ptstate_t state;

    PT_INIT(&pt);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_INITIALIZED);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_1);

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    state = PT_SCHEDULE(empty_run(&pt));

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_TERMINATED);
}




PT_THREAD(wait_until(pt_t *pt))
{
    PT_BEGIN(pt);

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_1);

    PT_WAIT_UNTIL(pt,MYUNIT_FLAG_IS_CLR(LOCK));

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_2);

    PT_END(pt);
}

/*!
    \brief Test the behavior of a protothread waiting for a condition.

    This unit test verifies that a protothread correctly waits until a specified
    flag is cleared before proceeding. It checks transitions through various states
    from initialization to termination, ensuring appropriate checkpoint settings
    and state assertions at each step.


    - Preconditions: The protothread is initialized with its state set to
      `PT_STATE_INITIALIZED`. A lock flag is set, and relevant checkpoints are cleared.
    - Execution:
        1. The test schedules the `wait_until` function which checks if the LOCK
           is not set before proceeding to a termination checkpoint.
        2. Initial scheduling ensures that only the first checkpoint is reached due
           to the lock being active, with the protothread state transitioning from
           `PT_STATE_INITIALIZED` to `PT_STATE_RUNNING`.
    - Postconditions: After clearing the lock, the second checkpoint should be
      passed, and the protothread transitions to `PT_STATE_TERMINATED`.
*/
MYUNIT_TESTCASE(wait_until_locked)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt;
    ptstate_t state;


    PT_INIT(&pt);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_INITIALIZED);

    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_1);
    MYUNIT_FLAG_SET(LOCK);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_1);
    MYUNIT_ASSERT_FLAG_SET(LOCK);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);

    // EXECUTE TESTCASE:
    // -------------------------------------------------



    state = PT_SCHEDULE(wait_until(&pt));

    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);
    MYUNIT_ASSERT_FLAG_SET(LOCK);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_WAITING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_WAITING);

    MYUNIT_FLAG_CLR(LOCK);
    state = PT_SCHEDULE(wait_until(&pt));



    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);
    MYUNIT_ASSERT_FLAG_CLR(LOCK);

    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_TERMINATED);
}

/*!
    \brief Test the behavior of a protothread when waiting for an already cleared condition.


    This unit test verifies that a protothread proceeds immediately when it waits
    for a flag that is already in the desired state. It ensures that all checkpoints
    are correctly passed and the final state transitions to `PT_STATE_TERMINATED`.


    - Preconditions: The protothread is initialized with its state set to
      `PT_STATE_INITIALIZED`. A lock flag is cleared, and relevant checkpoints are also cleared.
    - Execution:
        1. Schedules the `wait_until` function which checks if the LOCK is not set, allowing it
           to proceed immediately because the condition is already satisfied.
    - Postconditions: Both checkpoints should be passed as there's no wait needed due to
      the flag being already cleared, and the protothread transitions to `PT_STATE_TERMINATED`.
*/
MYUNIT_TESTCASE(wait_until_unlocked)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt;
    ptstate_t state;


    PT_INIT(&pt);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_INITIALIZED);

    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_1);
    MYUNIT_FLAG_CLR(LOCK);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_1);
    MYUNIT_ASSERT_FLAG_CLR(LOCK);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    state = PT_SCHEDULE(wait_until(&pt));

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);
    MYUNIT_ASSERT_FLAG_CLR(LOCK);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_TERMINATED);
}



PT_THREAD(wait_while(pt_t *pt))
{
    PT_BEGIN(pt);

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_1);

    PT_WAIT_WHILE(pt,MYUNIT_FLAG_IS_SET(LOCK));

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_2);

    PT_END(pt);
}

/*!
    \brief Test the behavior of a protothread while waiting for a condition.


    This unit test verifies that a protothread correctly waits as long as a specified
    flag is set before proceeding. It checks transitions through various states from
    initialization to termination, ensuring appropriate checkpoint settings and state
    assertions at each step.


    - Preconditions: The protothread is initialized with its state set to
      `PT_STATE_INITIALIZED`. A lock flag is set, and relevant checkpoints are cleared.
    - Execution:
        1. The test schedules the `wait_while` function which checks if the LOCK
           is still set before proceeding to a termination checkpoint.
        2. Initial scheduling ensures that only the first checkpoint is reached due
           to the lock being active, with the protothread state transitioning from
           `PT_STATE_INITIALIZED` to `PT_STATE_RUNNING`.
    - Postconditions: After clearing the lock, the second checkpoint should be
      passed, and the protothread transitions to `PT_STATE_TERMINATED`.
*/
MYUNIT_TESTCASE(wait_while_locked)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt;
    ptstate_t state;


    PT_INIT(&pt);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_INITIALIZED);

    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_1);
    MYUNIT_FLAG_SET(LOCK);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_1);
    MYUNIT_ASSERT_FLAG_SET(LOCK);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    state = PT_SCHEDULE(wait_while(&pt));

    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);
    MYUNIT_ASSERT_FLAG_SET(LOCK);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_WAITING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_WAITING);

    MYUNIT_FLAG_CLR(LOCK);
    state = PT_SCHEDULE(wait_while(&pt));

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);
    MYUNIT_ASSERT_FLAG_CLR(LOCK);

    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_TERMINATED);
}

/*!
    \brief Test the behavior of a protothread while waiting for an already cleared condition.

    This unit test verifies that a protothread proceeds immediately when it waits
    as long as a flag is set, but the flag is already in the desired state (not set).
    It ensures that all checkpoints are correctly passed and the final state transitions to `PT_STATE_TERMINATED`.


    - Preconditions: The protothread is initialized with its state set to
      `PT_STATE_INITIALIZED`. A lock flag is cleared, and relevant checkpoints are also cleared.
    - Execution:
        1. Schedules the `wait_while` function which checks if the LOCK is still set, allowing it
           to proceed immediately because the condition is already satisfied (LOCK is not set).
    - Postconditions: Both checkpoints should be passed as there's no wait needed due to
      the flag being already cleared, and the protothread transitions to `PT_STATE_TERMINATED`.
*/
MYUNIT_TESTCASE(wait_while_unlocked)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt;
    ptstate_t state;


    PT_INIT(&pt);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_INITIALIZED);

    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_1);
    MYUNIT_FLAG_CLR(LOCK);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_1);
    MYUNIT_ASSERT_FLAG_CLR(LOCK);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    state = PT_SCHEDULE(wait_while(&pt));

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);
    MYUNIT_ASSERT_FLAG_CLR(LOCK);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_TERMINATED);
}



PT_THREAD(wait_thread_child(pt_t *pt))
{
    PT_BEGIN(pt);

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_2);

    PT_WAIT_WHILE(pt,MYUNIT_FLAG_IS_SET(LOCK));

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_3);

    PT_END(pt);
}


PT_THREAD(wait_thread_parent(pt_t *pt, pt_t *child))
{

    PT_BEGIN(pt);

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_1);

    PT_INIT(child);

    PT_WAIT_THREAD(pt, wait_thread_child(child));

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_4);

    PT_END(pt);
}


/*!
    \brief Test the interaction between a parent and child protothread with locking mechanism.

    This unit test verifies that a parent protothread correctly manages its execution
    in conjunction with a child protothread, particularly when dealing with lock-based
    waiting conditions. The test ensures proper checkpoint handling and state transitions
    for both the parent and child threads during various phases of their lifecycles.

    - Preconditions:
        1. Two protothreads (`parent` and `child`) are initialized.
        2. A lock flag is set, indicating that the `child` thread should wait.
        3. All relevant checkpoints are cleared before test execution begins.
        4. It's verified that the parent thread starts in an initialized state.

    - Execution:
        1. The `wait_thread_parent` function schedules and runs the `child` thread.
           Initially, due to the lock being active, CHECKPOINT_3 and CHECKPOINT_4 are not reached.
        2. The test verifies state transitions: both threads running, waiting (due to lock),
           then running again after the lock is cleared.

    - Postcondition :
        1. After clearing the lock, all checkpoints for both parent and child should be passed.
        2. Final assertions ensure that both protothreads transition to a terminated state,
           and the lock flag remains cleared.
*/
MYUNIT_TESTCASE(wait_thread_locked)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t parent, child;
    ptstate_t state;


    PT_INIT(&parent);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&parent), PT_STATE_INITIALIZED);


    MYUNIT_FLAG_SET(LOCK);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_1);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_2);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_3);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_4);


    MYUNIT_ASSERT_FLAG_SET(LOCK);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_3);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_4);

    // EXECUTE TESTCASE:
    // -------------------------------------------------



    state = PT_SCHEDULE(wait_thread_parent(&parent,&child));

    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_3);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_4);
    MYUNIT_ASSERT_FLAG_SET(LOCK);

    MYUNIT_ASSERT_EQUAL(state, PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&parent), PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_WAITING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&parent), PT_STATE_WAITING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&child), PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&child), PT_STATE_WAITING);

    MYUNIT_FLAG_CLR(LOCK);
    state = PT_SCHEDULE(wait_thread_parent(&parent,&child));



    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_3);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_4);
    MYUNIT_ASSERT_FLAG_CLR(LOCK);

    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&parent), PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&child), PT_STATE_TERMINATED);
}

/*!
    \brief Test the interaction between a parent and child protothread without initial locking.

    This unit test verifies that a parent protothread correctly manages its execution
    in conjunction with a child protothread when there are no initial lock-based waiting
    conditions. The test ensures proper checkpoint handling and state transitions for both
    the parent and child threads throughout their lifecycles, focusing on immediate progression
    through states.

    - Preconditions:
        1. Two protothreads (`parent` and `child`) are initialized.
        2. A lock flag is cleared to indicate no initial wait condition for the `child` thread.
        3. All relevant checkpoints are cleared before test execution begins.
        4. It's verified that the parent thread starts in an initialized state.

    - Execution:
        1. The `wait_thread_parent` function schedules and runs the `child` thread.
           Since there is no lock, both CHECKPOINT_3 and CHECKPOINT_4 for the child are reached immediately upon scheduling.

    - Postconditions:
        1. All checkpoints for both parent and child should be passed without any waiting period.
        2. Final assertions ensure that both protothreads transition to a terminated state,
           and the lock flag remains cleared.
*/
MYUNIT_TESTCASE(wait_thread_unlocked)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t parent, child;
    ptstate_t state;


    PT_INIT(&parent);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&parent), PT_STATE_INITIALIZED);


    MYUNIT_FLAG_CLR(LOCK);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_1);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_2);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_3);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_4);


    MYUNIT_ASSERT_FLAG_CLR(LOCK);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_3);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_4);


    // EXECUTE TESTCASE:
    // -------------------------------------------------

    state = PT_SCHEDULE(wait_thread_parent(&parent,&child));

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_3);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_4);
    MYUNIT_ASSERT_FLAG_CLR(LOCK);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&parent), PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&child), PT_STATE_TERMINATED);
}



PT_THREAD(spawn_parent(pt_t *pt, pt_t *child))
{

    PT_BEGIN(pt);

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_1);

    PT_SPAWN(pt, child, wait_thread_child(child));

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_4);

    PT_END(pt);
}

/*!
    \brief Test the interaction between a parent and child protothread with locking conditions.

    This unit test verifies that a parent protothread can correctly manage its execution
    in conjunction with a spawned child protothread, particularly when dealing with lock-based
    waiting conditions. The test ensures proper checkpoint handling and state transitions
    for both the parent and child threads during various phases of their lifecycles.

    - Preconditions:
        1. Two protothreads (`parent` and `child`) are initialized.
        2. A lock flag is set, indicating that the `child` thread should wait initially.
        3. All relevant checkpoints are cleared before test execution begins.
        4. It's verified that the parent thread starts in an initialized state.

    - Execution:
        1. The `spawn_parent` function spawns a child protothread using `PT_SPAWN`.
           Initially, due to the lock being active, CHECKPOINT_3 and CHECKPOINT_4 are not reached.
        2. The test verifies state transitions: both threads start running, then wait (due to lock),
           and proceed when the lock is cleared.

    - Postconditions:
        1. After clearing the lock, all checkpoints for both parent and child should be passed.
        2. Final assertions ensure that both protothreads transition to a terminated state,
           and the lock flag remains cleared.
*/
MYUNIT_TESTCASE(spawn_locked)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t parent, child;
    ptstate_t state;


    PT_INIT(&parent);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&parent), PT_STATE_INITIALIZED);


    MYUNIT_FLAG_SET(LOCK);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_1);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_2);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_3);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_4);


    MYUNIT_ASSERT_FLAG_SET(LOCK);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_3);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_4);

    // EXECUTE TESTCASE:
    // -------------------------------------------------



    state = PT_SCHEDULE(spawn_parent(&parent,&child));

    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_3);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_4);
    MYUNIT_ASSERT_FLAG_SET(LOCK);

    MYUNIT_ASSERT_EQUAL(state, PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&parent), PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_WAITING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&parent), PT_STATE_WAITING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&child), PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&child), PT_STATE_WAITING);

    MYUNIT_FLAG_CLR(LOCK);
    state = PT_SCHEDULE(spawn_parent(&parent,&child));



    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_3);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_4);
    MYUNIT_ASSERT_FLAG_CLR(LOCK);

    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&parent), PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&child), PT_STATE_TERMINATED);
}


/*!
    \brief Test the interaction between a parent and child protothread without initial locking.

    This unit test verifies that a parent protothread can correctly manage its execution
    in conjunction with a spawned child protothread when there are no initial lock-based waiting
    conditions. The test ensures proper checkpoint handling and state transitions for both
    the parent and child threads throughout their lifecycles, focusing on immediate progression
    through states.

    - Preconditions:
        1. Two protothreads (`parent` and `child`) are initialized.
        2. A lock flag is cleared to indicate no initial wait condition for the `child` thread.
        3. All relevant checkpoints are cleared before test execution begins.
        4. It's verified that the parent thread starts in an initialized state.

    - Execution:
        1. The `spawn_parent` function spawns a child protothread using `PT_SPAWN`.
           Since there is no lock, both CHECKPOINT_3 and CHECKPOINT_4 for the child are reached immediately upon scheduling.

    - Postconditions:
        1. All checkpoints for both parent and child should be passed without any waiting period.
        2. Final assertions ensure that both protothreads transition to a terminated state,
           and the lock flag remains cleared.
*/
MYUNIT_TESTCASE(spawn_unlocked)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t parent, child;
    ptstate_t state;


    PT_INIT(&parent);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&parent), PT_STATE_INITIALIZED);


    MYUNIT_FLAG_CLR(LOCK);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_1);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_2);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_3);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_4);


    MYUNIT_ASSERT_FLAG_CLR(LOCK);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_3);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_4);


    // EXECUTE TESTCASE:
    // -------------------------------------------------

    state = PT_SCHEDULE(spawn_parent(&parent,&child));

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_3);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_4);
    MYUNIT_ASSERT_FLAG_CLR(LOCK);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&parent), PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&child), PT_STATE_TERMINATED);
}



PT_THREAD(yield(pt_t *pt))
{

    PT_BEGIN(pt);

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_1);

    PT_YIELD(pt);

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_2);

    PT_END(pt);
}

/*!
    \brief Test the execution of a protothread with yield operations.

    This unit test verifies that a protothread correctly handles yielding its execution,
    transitioning through various states from initialization to termination, and ensuring
    appropriate checkpoint settings and state assertions at each step. It focuses on
    cooperative multitasking where the protothread voluntarily yields control.

    - Preconditions:
        1. A protothread `pt` is initialized.
        2. The initial state of the protothread is verified to be `PT_STATE_INITIALIZED`.
        3. All relevant checkpoints are cleared before test execution begins.
        4. It's confirmed that both checkpoints have not been passed initially.

    - Execution:
        1. Schedules the `yield` thread which yields control after setting CHECKPOINT_1,
           then sets CHECKPOINT_2 upon resumption.
        2. The first yield leads to CHECKPOINT_1 being passed and transitions the protothread
           from running to waiting, without reaching CHECKPOINT_2.

    - Postconditions:
        1. After the second yield, both CHECKPOINT_1 and CHECKPOINT_2 should be passed.
        2. Final assertions ensure that the protothread reaches a terminated state,
           with all checkpoints properly set during its execution lifecycle.
*/
MYUNIT_TESTCASE(yield)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt;
    ptstate_t state;


    PT_INIT(&pt);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_INITIALIZED);

    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_1);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    state = PT_SCHEDULE(yield(&pt));

    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_WAITING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_WAITING);

    state = PT_SCHEDULE(yield(&pt));

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);

    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_TERMINATED);
}


PT_THREAD(yield_until(pt_t *pt))
{

    PT_BEGIN(pt);

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_1);

    PT_YIELD_UNTIL(pt,MYUNIT_FLAG_IS_CLR(LOCK));

    MYUNIT_CHECKPOINT_SET(CHECKPOINT_2);

    PT_END(pt);
}



MYUNIT_TESTCASE(yield_until_locked)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt;
    ptstate_t state;


    PT_INIT(&pt);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_INITIALIZED);

    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_1);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_2);
    MYUNIT_FLAG_SET(LOCK);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);
    MYUNIT_ASSERT_FLAG_SET(LOCK);

    // EXECUTE TESTCASE:
    // -------------------------------------------------


    state = PT_SCHEDULE(yield(&pt));

    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_WAITING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_WAITING);
    MYUNIT_FLAG_CLR(LOCK);

    state = PT_SCHEDULE(yield(&pt));

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);

    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_TERMINATED);
}

MYUNIT_TESTCASE(yield_until_unlocked)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt;
    ptstate_t state;


    PT_INIT(&pt);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_INITIALIZED);

    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_1);
    MYUNIT_CHECKPOINT_CLR(CHECKPOINT_2);
    MYUNIT_FLAG_CLR(LOCK);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);
    MYUNIT_ASSERT_FLAG_CLR(LOCK);

    // EXECUTE TESTCASE:
    // -------------------------------------------------


    state = PT_SCHEDULE(yield_until(&pt));

    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHECKPOINT_2);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_RUNNING);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_WAITING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_WAITING);


    state = PT_SCHEDULE(yield_until(&pt));

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHECKPOINT_2);

    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_TERMINATED);
}





#define XRES 80
#define YRES 40
#define MAGNIFY 1







PT_THREAD(mandelbrot_thread(pt_t *pt))
{
    static float x,xx,y,cx,cy;
    static int iteration,hx,hy;
    static int itermax;
    static const float magnify = MAGNIFY;     /* no magnification     */
    static const int hxres = XRES;        /* horizonal resolution     */
    static const int hyres = YRES;        /* vertical resolution      */
    static const char *cols = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

    PT_BEGIN(pt);

    itermax = strlen(cols)-1;


    /* header for PPM output */
    MYUNIT_PRINTF("CREATOR: Eric R Weeks / mandel program\n");

    for (hy=1;hy<=hyres;hy++)
    {
        for (hx=1;hx<=hxres;hx++)
        {
            cx = (((float)hx)/((float)hxres)-0.5)/magnify*3.0-0.7;
            cy = (((float)hy)/((float)hyres)-0.5)/magnify*3.0;
            x = 0.0; y = 0.0;
            for (iteration=1;iteration<itermax;iteration++)
            {
                xx = x*x-y*y+cx;
                y = 2.0*x*y+cy;
                x = xx;
                if (x*x+y*y>100.0)  break;
            }

            MYUNIT_PRINTF("%c",cols[iteration]);
            PT_YIELD(pt);
        }

        MYUNIT_PRINTF("\n");
    }

    PT_END(pt);
}

#define NUM_POINTS (XRES*YRES)

PT_THREAD(pi_thread(pt_t *pt))
{
    static int inside_circle,i;
    float x, y;


    PT_BEGIN(pt);

    for (i = 0; i < NUM_POINTS; i++)
    {
        // Generate random points between 0 and 1
        x = rand() / (float)RAND_MAX;
        y = rand() / (float)RAND_MAX;

        // Check if the point is inside the quarter circle
        if (x * x + y * y <= 1.0)
        {
            inside_circle++;
        }

        PT_YIELD(pt);
    }

    MYUNIT_PRINTF("Estimated value of Pi: %.10f\n", 4.0 * inside_circle / NUM_POINTS);

    PT_END(pt);
}


MYUNIT_TESTCASE(protothread_example)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t mandelbrot, pi;

    PT_INIT(&mandelbrot);
    PT_INIT(&pi);


    while (PT_GET_STATE(&mandelbrot) != PT_STATE_TERMINATED || PT_GET_STATE(&pi) != PT_STATE_TERMINATED)
    {
        PT_SCHEDULE(mandelbrot_thread(&mandelbrot));
        PT_SCHEDULE(pi_thread(&pi));
    }

}



void myunit_testsuite_setup()
{
    MYUNIT_CHECKPOINS_INIT();
}

void myunit_testsuite_teardown()
{

}

MYUNIT_TESTSUITE(protothread)
{
    MYUNIT_TESTSUITE_BEGIN();

    MYUNIT_EXEC_TESTCASE(init);
    MYUNIT_EXEC_TESTCASE(empty_run);
    MYUNIT_EXEC_TESTCASE(wait_until_locked);
    MYUNIT_EXEC_TESTCASE(wait_until_unlocked);
    MYUNIT_EXEC_TESTCASE(wait_while_locked);
    MYUNIT_EXEC_TESTCASE(wait_while_unlocked);
    MYUNIT_EXEC_TESTCASE(wait_thread_locked);
    MYUNIT_EXEC_TESTCASE(wait_thread_unlocked);
    MYUNIT_EXEC_TESTCASE(spawn_locked);
    MYUNIT_EXEC_TESTCASE(spawn_unlocked);
    MYUNIT_EXEC_TESTCASE(yield);
    MYUNIT_EXEC_TESTCASE(yield_until_locked);
    MYUNIT_EXEC_TESTCASE(yield_until_unlocked);

    MYUNIT_EXEC_TESTCASE(protothread_example);

    MYUNIT_TESTSUITE_END();
}


