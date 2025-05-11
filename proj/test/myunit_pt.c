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


enum {
   CHKPT_CHECKPOINT_1 = 0,
   CHKPT_CHECKPOINT_2,
   CHKPT_LOCK,
};

bool busy = false;

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

    MYUNIT_CHECKPOINT_SET(CHKPT_CHECKPOINT_1);

    PT_END(pt);
}


MYUNIT_TESTCASE(empty_run)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt;
    ptstate_t state;

    PT_INIT(&pt);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_INITIALIZED);
    MYUNIT_CHECKPOINT_CLR(CHKPT_CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHKPT_CHECKPOINT_1);

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    state = PT_SCHEDULE(empty_run(&pt));

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHKPT_CHECKPOINT_1);
    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_TERMINATED);
}




PT_THREAD(wait_until(pt_t *pt))
{
    PT_BEGIN(pt);

    MYUNIT_CHECKPOINT_SET(CHKPT_CHECKPOINT_1);

    PT_WAIT_UNTIL(pt,MYUNIT_CHECKPOINT_MISSED(CHKPT_LOCK));

    MYUNIT_CHECKPOINT_SET(CHKPT_CHECKPOINT_2);

    PT_END(pt);
}


MYUNIT_TESTCASE(wait_until)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt;
    ptstate_t state;
    int idx;

    PT_INIT(&pt);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_INITIALIZED);

    MYUNIT_CHECKPOINT_CLR(CHKPT_CHECKPOINT_1);
    MYUNIT_CHECKPOINT_SET(CHKPT_LOCK);
    MYUNIT_CHECKPOINT_CLR(CHKPT_CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHKPT_CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHKPT_LOCK);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHKPT_CHECKPOINT_2);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    for (idx = 0; idx < 100; idx++)
    {

        state = PT_SCHEDULE(empty_run(&pt));
        MYUNIT_ASSERT_CHECKPOINT_PASSED(CHKPT_CHECKPOINT_1);
        MYUNIT_ASSERT_CHECKPOINT_MISSED(CHKPT_CHECKPOINT_2);
        MYUNIT_ASSERT_CHECKPOINT_PASSED(CHKPT_LOCK);
    }

    MYUNIT_CHECKPOINT_CLR(CHKPT_LOCK);
    state = PT_SCHEDULE(empty_run(&pt));

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHKPT_CHECKPOINT_1);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHKPT_CHECKPOINT_2);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHKPT_LOCK);

    MYUNIT_ASSERT_EQUAL(state, PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt), PT_STATE_TERMINATED);
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
    MYUNIT_EXEC_TESTCASE(wait_until);

    MYUNIT_TESTSUITE_END();
}


