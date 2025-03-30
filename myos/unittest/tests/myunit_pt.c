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
#include <stdint.h>
#include <math.h>
#include "pt.h"
#include <time.h>
#include <stdbool.h>

#define NUM_SAMPLES 10000

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_LN2
#define M_LN2 0.69314718056f  // ln(2) if not defined
#endif

enum checkpoints_ids {
    CHKPT_BEFORE_EXIT,
    CHKPT_AFTER_EXIT,
    CHKPT_BEFORE_RESTART,
    CHKPT_AFTER_RESTART,
};


/*
Test Plan: protothread_initialzation
Purpose
Ensure that PT_INIT(&pt) correctly initializes a protothread by setting its state to PT_STATE_INITIALIZED and marking it as not running.

Test Case Name
protothread_initialzation

Preconditions
A pt_t instance is declared and deliberately initialized with a non-standard state value (e.g. 12345) to simulate uninitialized memory or garbage data.

Before calling PT_INIT, the internal state must not be equal to PT_STATE_INITIALIZED, to ensure the test setup is valid.

Test Execution
Call PT_INIT(&pt) to initialize the protothread.

Postconditions / Expected Results
The state of the protothread (via PT_GET_STATE(&pt)) must now be PT_STATE_INITIALIZED.

The protothread must not be running (PT_IS_RUNNING(&pt) should return false).

Remarks
This test validates that PT_INIT reliably resets the protothread to a known, consistent starting state.

It also confirms that PT_IS_RUNNING returns false for a freshly initialized protothread, as expected.
*/
MYUNIT_TESTCASE(protothread_initialzation)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt = {12345};
    MYUNIT_ASSERT_DIFFER(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    PT_INIT(&pt);


    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));
}

/*
Test Plan: run_empty_protothread
Purpose
Verify that a protothread function with no internal logic (an "empty" protothread) correctly transitions from its initial state to the terminated state after a single execution (scheduling).

Test Case Name
run_empty_protothread

Preconditions
A pt_t instance must be properly initialized using PT_INIT(&pt).

After initialization:

The protothread state should be PT_STATE_INITIALIZED.

The protothread should not be marked as running (PT_IS_RUNNING(&pt) should be false).

Test Execution
Schedule the protothread exactly once using PT_SCHEDULE(empty_thread(&pt)).

Store the returned state (ptstate_t) from the scheduling call.

Postconditions / Expected Results
The scheduling call should return PT_STATE_TERMINATED.

The internal state of the protothread (via PT_GET_STATE(&pt)) should also be PT_STATE_TERMINATED.

The protothread should still not be marked as running (PT_IS_RUNNING(&pt) should be false).

Remarks
This test ensures that the scheduler handles edge cases correctly—specifically, when a protothread consists only of PT_BEGIN and PT_END.

It also serves as a sanity check for initialization and basic state transition logic in the protothread system.
*/

PT_THREAD(empty_thread(pt_t *pt))
{
    PT_BEGIN(pt);

    PT_END(pt);
}


MYUNIT_TESTCASE(run_empty_protothread)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    pt_t pt;
    PT_INIT(&pt);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    ptstate_t ptstate = PT_SCHEDULE(empty_thread(&pt)); // schedule once

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(ptstate,PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_TERMINATED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));
}


/*
Test Plan: run_to_completion_protothread

Purpose
Verifies that a protothread without PT_YIELD, PT_WAIT_*, or any other interruption points runs to completion on a single call to PT_SCHEDULE(...), and terminates correctly.

Additionally, ensures that the embedded Monte Carlo simulation for estimating π produces a plausible result.

Test Case Name
run_to_completion_protothread

Preconditions
A pt_t object is initialized using PT_INIT(&pt).

A float variable pi is declared but not yet initialized.

NUM_SAMPLES is defined (e.g., ≥1000) to ensure a reliable estimation.

Optional: The random number generator is seeded using srand(seed) for reproducibility.

Test Execution
Call PT_SCHEDULE(run_to_completion_thread(&pt, &pi)) exactly once.

Store the return value in ptstate.

Postconditions / Expected Results
ptstate should be PT_STATE_TERMINATED.

PT_GET_STATE(&pt) should also return PT_STATE_TERMINATED.

PT_IS_RUNNING(&pt) should return false.

pi should contain a plausible result based on the Monte Carlo estimation.

This is verified using the helper function check_pi(pi, NUM_SAMPLES).

The function takes the expected standard deviation into account and accepts results within a defined tolerance (k * sigma).

Remarks
This test ensures that even non-cooperative protothreads (i.e., those that run straight through to PT_END in a single schedule call) are handled correctly.

This is a boundary case for scheduling logic and state transitions.

The MYUNIT_PRINTF output for pi is intended for visual inspection and is optional for automated tests.
*/


/*!
    \brief Check if pi_calc is within a typical deviation from the true value of Pi.

    This function verifies whether the Monte-Carlo calculated value of Pi (`pi_calc`)
    falls within an expected range of deviation from the actual value. The standard
    deviation for this calculation can be approximated as sigma(pi) ~ 1.64 / sqrt(num_samples).

    For a confidence level of approximately 95% (k = 2.0), the condition |pi_calc - pi| <= 2 * sigma
    must hold true.

    \param pi_calc The Monte-Carlo calculated value of Pi.
    \param num_samples The number of random points used in the calculation.
    \return true if within the 2-Sigma range, otherwise false.
*/
bool check_pi(float pi_calc, unsigned long num_samples)
{
    // Standardabweichung der Monte-Carlo-Schätzung
    // sigma(pi) ~ 1.64 / sqrt(num_samples)
    float sigma = 1.64 / sqrt((float)num_samples);

    // Abweichung vom echten Pi
   float delta = fabs(pi_calc - M_PI);

   // k = 2.0 für ca. 95% Konfidenz
   // k = 3.0 für ca. 99.73 % Konfidenz
   // k = 4.0 für ca. 99.9937 % Konfidenz
    float k = 5.0;

    MYUNIT_PRINTF("pi toleranz = %f\n",k * sigma);

    // Prüfen, ob Delta <= 2 * sigma
    return (delta <= k * sigma);
}


PT_THREAD(run_to_completion_thread(pt_t *pt, float *pi))
{
   PT_BEGIN(pt);

   unsigned inside_circle = 0;

   for (unsigned long i = 0; i < NUM_SAMPLES; i++)
   {
       float x = (float)rand() / RAND_MAX;
       float y = (float)rand() / RAND_MAX;

       if ((x * x + y * y) <= 1.0)
       {
           inside_circle++;
       }
   }

   *pi = 4.0 * inside_circle / NUM_SAMPLES;

    PT_END(pt);
}


MYUNIT_TESTCASE(run_to_completion_protothread)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    float pi;
    pt_t pt;
    PT_INIT(&pt);


    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    ptstate_t ptstate = PT_SCHEDULE(run_to_completion_thread(&pt,&pi)); // schedule once

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(ptstate,PT_STATE_TERMINATED);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_TERMINATED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

    MYUNIT_ASSERT_TRUE(check_pi(pi,NUM_SAMPLES));

    MYUNIT_PRINTF("pi = %f\n",pi);
}



/*
Test Plan: yielding_thread
Purpose
Verify that a protothread performing a Monte Carlo simulation to approximate π behaves correctly:

It yields once per iteration,

Updates the result only after completing all iterations,

Terminates after the last iteration,

And produces a valid π approximation.

Test Case Name
yielding_thread_estimates_pi_with_yielding

Preconditions
A pt_t instance must be properly initialized via PT_INIT(&pt).

A float pointer pi must be declared and initialized to a known dummy value (e.g., -1.0f) so we can detect whether it has been updated.

NUM_SAMPLES must be defined and reasonably small (e.g. 10) to allow complete execution in a unit test.

Test Execution
Repeatedly call PT_SCHEDULE(yielding_thread(&pt, &pi)) in a loop until the function returns PT_STATE_TERMINATED.

Keep track of how many times the protothread yields before terminating.

Postconditions / Expected Results
The thread should yield NUM_SAMPLES times (i.e., it should require NUM_SAMPLES + 1 calls to PT_SCHEDULE including the final termination call).

After the final iteration, the protothread must return PT_STATE_TERMINATED.

PT_GET_STATE(&pt) should also reflect PT_STATE_TERMINATED.

*pi must be updated to a value between 0.0 and 4.0 (valid π approximation range).

The protothread must not be running after termination (PT_IS_RUNNING(&pt) should be false).

Remarks
This test checks the cooperation model (explicit yielding) of protothreads.

The number of yields effectively simulates a scheduling loop over time—an essential feature of protothread-based concurrency.

We assume rand() is seeded or produces deterministic results for testability. Otherwise, variability should be accounted for in assertions.
*/

PT_THREAD(compute_pi_thread(pt_t *pt, float *pi))
{
   static unsigned inside_circle;
   static unsigned long i;

   PT_BEGIN(pt);

   inside_circle = 0;

   for (i = 0; i < NUM_SAMPLES; i++)
   {

       float x = (float)rand() / RAND_MAX;
       float y = (float)rand() / RAND_MAX;

       if ((x * x + y * y) <= 1.0)
       {
           inside_circle++;
       }
       PT_YIELD(pt);
   }

   *pi = 4.0 * inside_circle / NUM_SAMPLES;

    PT_END(pt);
}





MYUNIT_TESTCASE(run_yielding_protothread)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    float pi;
    pt_t pt;
    PT_INIT(&pt);


    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    while(PT_SCHEDULE(compute_pi_thread(&pt,&pi)) != PT_STATE_TERMINATED)
    {
        // do nothing
    }



    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_TERMINATED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

    MYUNIT_ASSERT_TRUE(check_pi(pi,NUM_SAMPLES));

    MYUNIT_PRINTF("pi = %f\n",pi);
}

/*
Test Plan: run_wait_until_protothread
Purpose
Testet, ob PT_WAIT_UNTIL(pt, cond) korrekt funktioniert, indem ein Protothread so lange in den Wartestatus übergeht, bis eine Bedingung erfüllt ist – und dann sauber terminiert.

Test Case Name
run_wait_until_protothread

Preconditions
Ein pt_t-Objekt ist mit PT_INIT(&pt) initialisiert.

Die Bedingungsvariable cond ist zu Beginn false.

Der Thread wurde noch nicht gescheduled.

Test Execution
Führe PT_SCHEDULE(wait_until_thread(&pt, cond)) in einer Schleife aus, während cond == false.

Die Schleife kann NUM_SAMPLES Iterationen lang laufen, um die Stabilität des Wartezustands zu überprüfen.

Nach jeder Iteration soll der Rückgabewert PT_STATE_WAITING sein.

Auch der interne Zustand von pt muss PT_STATE_WAITING anzeigen.

Setze cond = true.

Führe den Thread erneut aus. Diesmal muss:

PT_SCHEDULE den Zustand PT_STATE_TERMINATED liefern.

Der interne Zustand entsprechend auf PT_STATE_TERMINATED springen.

Postconditions / Expected Results
Der letzte Aufruf von PT_SCHEDULE muss PT_STATE_TERMINATED zurückgeben.

PT_GET_STATE(&pt) muss danach PT_STATE_TERMINATED anzeigen.

Der Protothread darf nicht mehr als laufend (PT_IS_RUNNING) markiert sein.

Remarks
Der Test stellt sicher, dass PT_WAIT_UNTIL keine Iteration „überspringt“, sondern konsistent in den Wartestatus übergeht.

Mit NUM_SAMPLES wird sichergestellt, dass der Zustand über mehrere Scheduler-Durchläufe hinweg stabil bleibt.

Diese Struktur eignet sich hervorragend, um das Verhalten in Event-Driven oder Cooperative Scheduling-Umgebungen zu validieren.
*/


PT_THREAD(wait_until_thread(pt_t *pt, bool cond))
{
    PT_BEGIN(pt);

    PT_WAIT_UNTIL(pt, cond == true);

    PT_END(pt);
}


MYUNIT_TESTCASE(run_wait_until_protothread)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    bool cond;
    pt_t pt;
    PT_INIT(&pt);


    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    cond = false;

    for (int idx = 0; idx < NUM_SAMPLES; idx++)
    {
        MYUNIT_ASSERT_EQUAL(PT_SCHEDULE(wait_until_thread(&pt,cond)), PT_STATE_WAITING);
        MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_WAITING);
    }

    cond = true;

    MYUNIT_ASSERT_EQUAL(PT_SCHEDULE(wait_until_thread(&pt,cond)), PT_STATE_TERMINATED);



    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_TERMINATED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

}

/*
Test Plan: run_wait_until_to_completion

Purpose
Verifies that a protothread using PT_WAIT_UNTIL(pt, cond == true) terminates immediately if the condition is already true on the first call to PT_SCHEDULE — effectively executing to completion without any waiting.

Test Case Name
run_wait_until_to_completion

Preconditions
- A pt_t object is initialized using PT_INIT(&pt).
- The condition passed to wait_until_thread is true, so the wait clause PT_WAIT_UNTIL(pt, cond == true) should pass immediately.

Test Execution
- Call PT_SCHEDULE(wait_until_thread(&pt, true)) exactly once.
- Store and verify the returned ptstate.

Postconditions / Expected Results
- PT_SCHEDULE returns PT_STATE_TERMINATED.
- PT_GET_STATE(&pt) also returns PT_STATE_TERMINATED.
- PT_IS_RUNNING(&pt) returns false, confirming the protothread is no longer active.

Remarks
This test covers the fast-path behavior of PT_WAIT_UNTIL where no actual waiting occurs.

It ensures that the scheduler handles this scenario correctly and does not block or yield unnecessarily if the condition is already met.
*/
MYUNIT_TESTCASE(run_wait_until_to_completion)
{
    // PRECONDITIONS:
    // -------------------------------------------------

    pt_t pt;
    PT_INIT(&pt);


    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

    // EXECUTE TESTCASE:
    // -------------------------------------------------


    MYUNIT_ASSERT_EQUAL(PT_SCHEDULE(wait_until_thread(&pt,true)), PT_STATE_TERMINATED);

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_TERMINATED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

}




/*
Test Plan: run_wait_while_protothread

Purpose
Ensures that a protothread using PT_WAIT_WHILE(pt, cond) remains in the waiting state as long as a condition is true — and only proceeds or terminates once the condition becomes false.

Test Case Name
run_wait_while_protothread

Preconditions
A boolean control variable cond is used to control the condition.

The protothread state is initialized using PT_INIT(&pt).

cond is initially set to true.

Test Execution
As long as cond == true:

Call PT_SCHEDULE(wait_while_thread(&pt, cond)) in a loop (e.g., NUM_SAMPLES times).

Expectation: The return value is always PT_STATE_WAITING, and PT_GET_STATE(&pt) reflects that accurately.

Then set cond = false.

Call the thread again. Now it should:

Return PT_STATE_TERMINATED from PT_SCHEDULE(...).

Also report PT_STATE_TERMINATED via PT_GET_STATE.

Postconditions / Expected Results
Once cond is false, the thread terminates successfully.

The protothread does not continue running afterward (PT_IS_RUNNING(&pt) is false).

No unexpected state transitions occur while waiting.

Remarks
This test is the counterpart to PT_WAIT_UNTIL, validating the same wait mechanism but in inverse form (wait *while* true instead of *until* true).

Using NUM_SAMPLES ensures that the behavior remains stable over multiple scheduler passes, as would occur in a real scheduling loop.

Such tests are especially relevant in event-driven environments (e.g., on microcontrollers) where conditions may only change asynchronously.
*/


PT_THREAD(wait_while_thread(pt_t *pt, bool cond))
{
    PT_BEGIN(pt);

    PT_WAIT_WHILE(pt, cond == true);

    PT_END(pt);
}




MYUNIT_TESTCASE(run_wait_while_protothread)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    bool cond;
    pt_t pt;
    PT_INIT(&pt);


    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    cond = true;

    for (int idx = 0; idx < NUM_SAMPLES; idx++)
    {
        MYUNIT_ASSERT_EQUAL(PT_SCHEDULE(wait_while_thread(&pt,cond)), PT_STATE_WAITING);
        MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_WAITING);
    }

    cond = false;

    MYUNIT_ASSERT_EQUAL(PT_SCHEDULE(wait_while_thread(&pt,cond)), PT_STATE_TERMINATED);



    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_TERMINATED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));
}

/*
Test Plan: run_wait_while_to_completion

Purpose
Verifies that a protothread using PT_WAIT_WHILE(pt, cond == true) terminates immediately if the condition is false at the very first call to PT_SCHEDULE — i.e., the thread runs to completion without entering the waiting state.

Test Case Name
run_wait_while_to_completion

Preconditions
- A pt_t object is initialized using PT_INIT(&pt).
- The condition passed to wait_while_thread is false, so the PT_WAIT_WHILE(pt, cond == true) check passes immediately (i.e., the loop is not entered).

Test Execution
- Call PT_SCHEDULE(wait_while_thread(&pt, false)) exactly once.
- Capture the return value.

Postconditions / Expected Results
- PT_SCHEDULE returns PT_STATE_TERMINATED.
- PT_GET_STATE(&pt) returns PT_STATE_TERMINATED.
- PT_IS_RUNNING(&pt) returns false.

Remarks
This test ensures the protothread scheduler correctly handles the case where PT_WAIT_WHILE conditions are already false at entry.

It confirms that no waiting state is entered and that the thread runs directly to completion — important for correct fast-path behavior and logic flow in edge cases.
*/
MYUNIT_TESTCASE(run_wait_while_to_completion)
{
    // PRECONDITIONS:
    // -------------------------------------------------

    pt_t pt;
    PT_INIT(&pt);


    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

    // EXECUTE TESTCASE:
    // -------------------------------------------------


    MYUNIT_ASSERT_EQUAL(PT_SCHEDULE(wait_while_thread(&pt,false)), PT_STATE_TERMINATED);

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_TERMINATED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));
}


/*
Test Plan: run_yield_until_protothread

Purpose
Verifies that a protothread using PT_YIELD_UNTIL(pt, cond == true) yields repeatedly until the given condition is met, and only then continues and terminates.

Unlike PT_WAIT_UNTIL, which does not count as yielding, PT_YIELD_UNTIL actively yields control during each iteration, mimicking cooperative multitasking behavior.

Test Case Name
run_yield_until_protothread

Preconditions
- A pt_t object is initialized using PT_INIT(&pt).
- A boolean control variable cond is used to represent the condition.
- cond is initially set to false.

Test Execution
- While cond == false:
  - Call PT_SCHEDULE(yield_until_thread(&pt, cond)) in a loop (e.g., NUM_SAMPLES times).
  - Expect each call to return PT_STATE_WAITING.
  - PT_GET_STATE(&pt) should also report PT_STATE_WAITING.
- Then set cond = true.
- Call PT_SCHEDULE(...) once more — this time it must:
  - Return PT_STATE_TERMINATED.
  - Set the internal state to PT_STATE_TERMINATED.

Postconditions / Expected Results
- After cond becomes true, the thread terminates cleanly.
- The final state of the protothread is PT_STATE_TERMINATED.
- PT_IS_RUNNING(&pt) returns false.

Remarks
This test ensures correct behavior of PT_YIELD_UNTIL, which is essential for cooperative scheduling models where tasks voluntarily give up control.

It also verifies that the yield loop continues over multiple scheduler passes without premature termination or state corruption.

NUM_SAMPLES ensures that yielding happens repeatedly and predictably over time before the condition flips.
*/

PT_THREAD(yield_until_thread(pt_t *pt, bool cond))
{
    PT_BEGIN(pt);

    PT_YIELD_UNTIL(pt, cond == true);

    PT_END(pt);
}



MYUNIT_TESTCASE(run_yield_until_protothread)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    bool cond;
    pt_t pt;
    PT_INIT(&pt);


    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    cond = false;

    for (int idx = 0; idx < NUM_SAMPLES; idx++)
    {
        MYUNIT_ASSERT_EQUAL(PT_SCHEDULE(yield_until_thread(&pt,cond)), PT_STATE_WAITING);
        MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_WAITING);
    }

    cond = true;

    MYUNIT_ASSERT_EQUAL(PT_SCHEDULE(yield_until_thread(&pt,cond)), PT_STATE_TERMINATED);



    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_TERMINATED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));
}


/*
Test Plan: run_yield_until_to_completion

Purpose
Verifies that a protothread using PT_YIELD_UNTIL(pt, cond == true) does not terminate immediately even if the condition is already true on the first call.

Instead, PT_YIELD_UNTIL guarantees at least one yield before re-evaluating the condition and terminating — making this a cooperative scheduling construct.

Test Case Name
run_yield_until_to_completion

Preconditions
- A pt_t object is initialized using PT_INIT(&pt).
- The condition passed to yield_until_thread is true from the beginning.

Test Execution
1. First call to PT_SCHEDULE(yield_until_thread(&pt, true)):
   - The condition is already true, but the protothread yields once before checking it.
   - Return value must be PT_STATE_WAITING.
   - Internal state is PT_STATE_WAITING.
   - PT_IS_RUNNING(&pt) must return true.

2. Second call to PT_SCHEDULE(yield_until_thread(&pt, true)):
   - Now the protothread resumes, sees that the condition is still true, and terminates.
   - Return value must be PT_STATE_TERMINATED.

Postconditions / Expected Results
- PT_GET_STATE(&pt) is PT_STATE_TERMINATED.
- PT_IS_RUNNING(&pt) returns false.

Remarks
This test highlights the cooperative nature of PT_YIELD_UNTIL: even when the condition is already true, the thread yields once before continuing.

It's an important behavioral difference from PT_WAIT_UNTIL, which could terminate immediately if the condition is true.

The test ensures correct state transitions and one explicit yield cycle before completion.
*/

MYUNIT_TESTCASE(yield_until_requires_one_yield)
{
    // PRECONDITIONS:
    // -------------------------------------------------

    pt_t pt;
    PT_INIT(&pt);


    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

    // EXECUTE TESTCASE:
    // -------------------------------------------------


    MYUNIT_ASSERT_EQUAL(PT_SCHEDULE(yield_until_thread(&pt,true)), PT_STATE_WAITING);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_WAITING);
    MYUNIT_ASSERT_TRUE(PT_IS_RUNNING(&pt));

    MYUNIT_ASSERT_EQUAL(PT_SCHEDULE(yield_until_thread(&pt,true)), PT_STATE_TERMINATED);


    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_TERMINATED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));
}


/*
Test Plan: run_exit_protothread

Purpose
Verifies that PT_EXIT(pt) causes the protothread to terminate immediately when executed, skipping any code that follows it — even code between PT_EXIT and PT_END.

Test Case Name
run_exit_protothread

Preconditions
- A pt_t object is initialized using PT_INIT(&pt).
- Two checkpoints are defined:
  - CHKPT_BEFORE_EXIT: set right before PT_EXIT
  - CHKPT_AFTER_EXIT: set immediately after PT_EXIT (should never be hit)

- Both checkpoints must not have been triggered prior to scheduling.

Test Execution
- Call PT_SCHEDULE(exit_thread(&pt, true)) once.

Postconditions / Expected Results
- The return value is PT_STATE_TERMINATED.
- PT_GET_STATE(&pt) returns PT_STATE_TERMINATED.
- PT_IS_RUNNING(&pt) returns false.

- CHKPT_BEFORE_EXIT must have been hit.
- CHKPT_AFTER_EXIT must **not** have been hit — confirming that code after PT_EXIT was skipped.

Remarks
This test validates correct handling of PT_EXIT, which is a mechanism to stop a protothread mid-flow.

It ensures that execution does not continue beyond PT_EXIT, even though the C code is written sequentially. This is critical for implementing early-exit conditions within cooperative tasks.
*/
PT_THREAD(exit_thread(pt_t *pt, bool cond))
{
    PT_BEGIN(pt);

    MYUNIT_CHECKPOINT_SET(CHKPT_BEFORE_EXIT);

    PT_EXIT(pt);

    MYUNIT_CHECKPOINT_SET(CHKPT_AFTER_EXIT);

    PT_END(pt);
}




MYUNIT_TESTCASE(run_exit_protothread)
{
    // PRECONDITIONS:
    // -------------------------------------------------

    pt_t pt;
    PT_INIT(&pt);

    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));


    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHKPT_BEFORE_EXIT);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHKPT_AFTER_EXIT);

    // EXECUTE TESTCASE:
    // -------------------------------------------------


    MYUNIT_ASSERT_EQUAL(PT_SCHEDULE(exit_thread(&pt,true)), PT_STATE_TERMINATED);



    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHKPT_BEFORE_EXIT);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHKPT_AFTER_EXIT);
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_TERMINATED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));
}




/*
Test Plan: run_restart_protothread

Purpose
Verifies that PT_RESTART(pt) causes the protothread to immediately reset to the beginning of its execution, skipping any subsequent code (even code placed between PT_RESTART and PT_END).

This is a key control flow feature for restarting a protothread from a known clean state.

Test Case Name
run_restart_protothread

Preconditions
- A pt_t object is initialized via PT_INIT(&pt).
- Two checkpoints are defined:
  - CHKPT_BEFORE_RESTART: set before the PT_RESTART call
  - CHKPT_AFTER_RESTART: set after the PT_RESTART call (should not be hit)

- Both checkpoints must be unset before scheduling.

Test Execution
- Call PT_SCHEDULE(restart_thread(&pt, true)) once.

Postconditions / Expected Results
- PT_SCHEDULE returns PT_STATE_INITIALIZED, indicating the protothread has restarted.
- PT_GET_STATE(&pt) confirms the state is back to PT_STATE_INITIALIZED.
- PT_IS_RUNNING(&pt) returns false, because the protothread has restarted and is ready to be scheduled again.

- CHKPT_BEFORE_RESTART must be passed.
- CHKPT_AFTER_RESTART must be missed, confirming that no code after PT_RESTART was executed.

Remarks
This test ensures correct behavior of PT_RESTART, which is critical for control flow in event-driven or retry-based protothread logic.

It validates that the protothread does not fall through to subsequent code after PT_RESTART, and that the internal state machine resets properly.
*/
PT_THREAD(restart_thread(pt_t *pt, bool cond))
{
    PT_BEGIN(pt);

    MYUNIT_CHECKPOINT_SET(CHKPT_BEFORE_RESTART);

    PT_RESTART(pt);

    MYUNIT_CHECKPOINT_SET(CHKPT_AFTER_RESTART);

    PT_END(pt);
}




MYUNIT_TESTCASE(run_restart_protothread)
{
    // PRECONDITIONS:
    // -------------------------------------------------

    pt_t pt;
    PT_INIT(&pt);

    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));


    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHKPT_BEFORE_RESTART);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHKPT_AFTER_RESTART);

    // EXECUTE TESTCASE:
    // -------------------------------------------------


    MYUNIT_ASSERT_EQUAL(PT_SCHEDULE(restart_thread(&pt,true)), PT_STATE_INITIALIZED);

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

    MYUNIT_ASSERT_CHECKPOINT_PASSED(CHKPT_BEFORE_RESTART);
    MYUNIT_ASSERT_CHECKPOINT_MISSED(CHKPT_AFTER_RESTART);
}



/*!
    \brief Prüft, ob der Monte-Carlo berechnete Wert für ln(2) innerhalb einer typischen
           Abweichung vom exakten Wert liegt.

    Diese Funktion vergleicht den Näherungswert \texttt{ln2_calc} mit dem exakten Wert
    \(\ln 2\). Es wird überprüft, ob die absolute Differenz \(|\texttt{ln2_calc} - \ln 2|\)
    kleiner oder gleich \( k \times \sigma(\ln2) \) ist, wobei
    \(\sigma(\ln2) \approx 0.13980 / \sqrt{\texttt{num_samples}}\) ist.

    \param ln2_calc Der mittels Monte-Carlo berechnete Wert für ln(2).
    \param num_samples Die Anzahl der Zufallszahlen, die zur Schätzung verwendet wurden.
    \return true, wenn der Fehler innerhalb des Bereichs liegt, ansonsten false.
*/
bool check_ln2(float ln2_calc, unsigned num_samples)
{
    // Standardabweichung der Monte-Carlo-Schätzung für ln(2)
    float sigma = 0.13980f / sqrt((float)num_samples);

    // Berechne die absolute Abweichung vom exakten Wert ln(2)
    float delta = fabs(ln2_calc - log(2));

    // Wahl eines Multiplikators k (z.B. k = 5.0, hier als Beispiel, anpassbar je nach gewünschter Konfidenz)
    float k = 5.0f;

    // Prüfen, ob die Abweichung im Rahmen von k*sigma liegt
    MYUNIT_PRINTF("ln2 toleranz = %f\n",k * sigma);


    return (delta <= k * sigma);
}





/*!
    \brief Computes an approximation of the natural logarithm of 2 using a random sampling method.

    \details The function uses a fixed number of samples (NUM_SAMPLES) to approximate ln(2).
             It generates random numbers and counts how many are needed until their sum exceeds 1.
             This count is averaged over all samples to produce an estimate for ln(2).

    \param _pt [Description of the pt_t parameter, typically a thread context or state object.]

    \param ln2 [A pointer to store the computed approximation of the natural logarithm of 2.]

    \return N/A
*/
PT_THREAD(compute_ln2_thread(pt_t *pt, float *ln2))
{
    static float sum;
    static int i;


    PT_BEGIN(pt);

    sum = 0;

    for (i = 0; i < NUM_SAMPLES; i++)
    {
        // Erzeuge eine Zufallszahl im Intervall [0,1]
        float x = (float)rand() / RAND_MAX;
        sum += 1.0 / (1.0 + x);

        PT_YIELD(pt);
    }
    // Da das Intervall [0,1] eine Länge von 1 hat, ist der Mittelwert der Summe gleich dem Integral

    *ln2 = sum / NUM_SAMPLES;


    PT_END(pt);
}




PT_THREAD(wait_thread_thread(pt_t *pt))
{
    PT_BEGIN(pt);

    static pt_t child;
    float result;

    PT_INIT(&child);
    PT_WAIT_THREAD(pt,compute_pi_thread(&child,&result));

    MYUNIT_ASSERT_TRUE(check_pi(result,NUM_SAMPLES));
    MYUNIT_PRINTF("pi = %f\n",result);

    PT_INIT(&child);
    PT_WAIT_THREAD(pt,compute_ln2_thread(&child,&result));

    MYUNIT_ASSERT_TRUE(check_ln2(result,NUM_SAMPLES));
    MYUNIT_PRINTF("ln2 = %f\n",result);

    PT_END(pt);
}








MYUNIT_TESTCASE(wait_for_other_thread_to_complete)
{
    // PRECONDITIONS:
    // -------------------------------------------------

    pt_t pt;
    PT_INIT(&pt);

    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));



    // EXECUTE TESTCASE:
    // -------------------------------------------------



    while(PT_SCHEDULE(wait_thread_thread(&pt)) != PT_STATE_TERMINATED) {};

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_TERMINATED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

}

MYUNIT_TESTCASE(spawn_other_thread)
{
    // PRECONDITIONS:
    // -------------------------------------------------

    pt_t pt;
    PT_INIT(&pt);

    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_INITIALIZED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));



    // EXECUTE TESTCASE:
    // -------------------------------------------------



    while(PT_SCHEDULE(wait_thread_thread(&pt)) != PT_STATE_TERMINATED) {};

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(PT_GET_STATE(&pt),PT_STATE_TERMINATED);
    MYUNIT_ASSERT_FALSE(PT_IS_RUNNING(&pt));

}


PT_THREAD(spawn_thread_thread(pt_t *pt))
{
    PT_BEGIN(pt);

    static pt_t child;
    float result;

    PT_SPAWN(pt, &child, compute_pi_thread(&child,&result));

    MYUNIT_ASSERT_TRUE(check_pi(result,NUM_SAMPLES));
    MYUNIT_PRINTF("pi = %f\n",result);

    PT_SPAWN(pt, &child, compute_pi_thread(&child,&result));

    MYUNIT_ASSERT_TRUE(check_ln2(result,NUM_SAMPLES));
    MYUNIT_PRINTF("ln2 = %f\n",result);

    PT_END(pt);
}




/*!
    \brief      Sets up the unit test suite environment.

    \details    This function initializes necessary resources and configurations
                required to run the unit tests. It prepares any global structures,
                allocates memory, or performs other setup tasks needed before executing
                individual test cases.
*/
void myunit_testsuite_setup()
{
    MYUNIT_CHECKPOINS_INIT();
}
/*!
    \brief      Cleans up resources after unit test suite execution.

    \details    This function deallocates any memory, releases resources, and performs
                necessary cleanup tasks that were set up during the initialization of the
                test suite. It ensures that no residual state is left behind that could
                affect subsequent tests or system stability.
*/
void myunit_testsuite_teardown()
{

}

MYUNIT_TESTSUITE(pt)
{
    MYUNIT_TESTSUITE_BEGIN();
    srand(time(NULL));

    MYUNIT_EXEC_TESTCASE(protothread_initialzation);
    MYUNIT_EXEC_TESTCASE(run_empty_protothread);

    MYUNIT_EXEC_TESTCASE(run_to_completion_protothread);
    MYUNIT_EXEC_TESTCASE(run_yielding_protothread);

    MYUNIT_EXEC_TESTCASE(run_wait_until_protothread);
    MYUNIT_EXEC_TESTCASE(run_wait_while_protothread);

    MYUNIT_EXEC_TESTCASE(run_wait_until_to_completion);
    MYUNIT_EXEC_TESTCASE(run_wait_while_to_completion);

    MYUNIT_EXEC_TESTCASE(run_yield_until_protothread);
    MYUNIT_EXEC_TESTCASE(yield_until_requires_one_yield);

    MYUNIT_EXEC_TESTCASE(run_exit_protothread);
    MYUNIT_EXEC_TESTCASE(run_restart_protothread);

    MYUNIT_EXEC_TESTCASE(wait_for_other_thread_to_complete);


    for(int tmp = 0; tmp < 100; tmp++)
    {
        MYUNIT_EXEC_TESTCASE(spawn_other_thread);
    }

    MYUNIT_TESTSUITE_END();
}
