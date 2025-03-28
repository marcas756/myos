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
#include"ringbuffer.h"

#define GARBAGE 0xAA

RINGBUFFER_TYPEDEF(intrbuff,uint32_t,3);

/*
1. Initialization Tests
Purpose
Verify that the ring buffer is correctly initialized with zero elements and that head, tail, and count are set to 0, and that empty/full macros behave as expected.

Test Case 1.1: Fresh Initialization

Setup:

Define a ring buffer type via RINGBUFFER_TYPEDEF(my, int, 5);
Declare an instance: my_ringbuffer_t ring;
Invoke RINGBUFFER_INIT(ring);

Actions:

Check the values of ring.head, ring.tail, ring.count.
Check RINGBUFFER_EMPTY(ring) and RINGBUFFER_FULL(ring).

Expected Results:

ring.head == 0
ring.tail == 0
ring.count == 0
RINGBUFFER_EMPTY(ring) == true
RINGBUFFER_FULL(ring) == false
*/
MYUNIT_TESTCASE(ringbuffer_initialization)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    RINGBUFFER_T(intrbuff) intrbuff;
    memset(&intrbuff,GARBAGE,sizeof(intrbuff));

    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD(intrbuff), 0);
    MYUNIT_ASSERT_DIFFER(RINGBUFFER_TAIL(intrbuff), 0);
    MYUNIT_ASSERT_DIFFER(RINGBUFFER_COUNT(intrbuff), 0);


    // EXECUTE TESTCASE:
    // -------------------------------------------------
    RINGBUFFER_INIT(intrbuff);

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff), 0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff), 0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff), 0);
    MYUNIT_ASSERT_TRUE(RINGBUFFER_EMPTY(intrbuff));
    MYUNIT_ASSERT_FALSE(RINGBUFFER_FULL(intrbuff));
}

/*
Test Case 2.1: Single Push

Setup:

Initialize the ring buffer as in Test Case 1.1.

Actions:

Write a single value, e.g., int value = 42;
RINGBUFFER_WRITE(&ring, value);
Inspect ring.count, ring.tail, and optionally the stored item at ring.items[0].
Check RINGBUFFER_EMPTY(ring) and RINGBUFFER_FULL(ring).

Expected Results:

ring.count == 1
ring.head == 0
ring.tail == 1 (wrapped from 0 to 1 because of the push)
ring.items[0] == 42
RINGBUFFER_EMPTY(ring) == false
RINGBUFFER_FULL(ring) == false
*/
MYUNIT_TESTCASE(ringbuffer_single_push)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    RINGBUFFER_T(intrbuff) intrbuff;
    RINGBUFFER_INIT(intrbuff)   ;

    MYUNIT_ASSERT_TRUE(RINGBUFFER_EMPTY(intrbuff));
    MYUNIT_ASSERT_FALSE(RINGBUFFER_FULL(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),RINGBUFFER_TAIL(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD_PTR(intrbuff),RINGBUFFER_TAIL_PTR(intrbuff));


    // EXECUTE TESTCASE:
    // -------------------------------------------------
    uint32_t value = 42;
    RINGBUFFER_WRITE(intrbuff, value);

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD_PTR(intrbuff),RINGBUFFER_TAIL_PTR(intrbuff));
    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD(intrbuff),RINGBUFFER_TAIL(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),1);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),1);  // Tail should have moved to index 1
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD_VAL(intrbuff),value);      // The value should be at the head

    MYUNIT_ASSERT_FALSE(RINGBUFFER_EMPTY(intrbuff));
    MYUNIT_ASSERT_FALSE(RINGBUFFER_FULL(intrbuff));
}


/*
Test Case 2.2: Single Pop

Setup:

After Test Case 2.1, we already have one item in the buffer (42).

Actions:

Read (or pop) the value:
int poppedValue;
RINGBUFFER_READ(&ring, poppedValue);
Check poppedValue, ring.count, ring.head, and RINGBUFFER_EMPTY(ring).

Expected Results:

poppedValue == 42
ring.count == 0
ring.head == 1 (wrapped from 0 to 1 by the pop)
ring.tail == 1 (unchanged by pop)
RINGBUFFER_EMPTY(ring) == true
RINGBUFFER_FULL(ring) == false
*/
MYUNIT_TESTCASE(ringbuffer_single_pop)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    RINGBUFFER_T(intrbuff) intrbuff;
    RINGBUFFER_INIT(intrbuff)   ;

    uint32_t writeval = 42;
    RINGBUFFER_WRITE(intrbuff, writeval);

    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD_PTR(intrbuff),RINGBUFFER_TAIL_PTR(intrbuff));
    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD(intrbuff),RINGBUFFER_TAIL(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),1);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),1);  // Tail should have moved to index 1
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),0);  // Head should still be at 0
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD_VAL(intrbuff),writeval);      // The value should be at the head


    // EXECUTE TESTCASE:
    // -------------------------------------------------

    uint32_t readval;
    RINGBUFFER_READ(intrbuff,readval);




    // POSTCONDITIONS:
    // -------------------------------------------------


    MYUNIT_ASSERT_EQUAL(readval,writeval);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD_PTR(intrbuff),RINGBUFFER_TAIL_PTR(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),RINGBUFFER_TAIL(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),1);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),1);


    MYUNIT_ASSERT_TRUE(RINGBUFFER_EMPTY(intrbuff));
    MYUNIT_ASSERT_FALSE(RINGBUFFER_FULL(intrbuff));
}


/*
Test Case 3.1: Push Several and Pop in Order

Setup:

RINGBUFFER_INIT(ring);

Suppose ring size = 5, and we push three values in sequence: 10, 20, 30.

RINGBUFFER_WRITE(&ring, 10);
RINGBUFFER_WRITE(&ring, 20);
RINGBUFFER_WRITE(&ring, 30);

Actions:

Read them back using RINGBUFFER_READ and verify FIFO order:

int v1, v2, v3;
RINGBUFFER_READ(&ring, v1); // expect 10
RINGBUFFER_READ(&ring, v2); // expect 20
RINGBUFFER_READ(&ring, v3); // expect 30

Expected Results:

The ring buffer returns items in order: v1 == 10, v2 == 20, v3 == 30.

After these reads, ring.count == 0, and RINGBUFFER_EMPTY(ring) == true.

Indices (head, tail) track the correct positions (they should have incremented in sync with the pushes and pops).
*/
MYUNIT_TESTCASE(ringbuffer_push_several_and_pop_in_order)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    RINGBUFFER_T(intrbuff) intrbuff;
    RINGBUFFER_INIT(intrbuff);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    RINGBUFFER_WRITE(intrbuff, 111);

    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD_PTR(intrbuff),RINGBUFFER_TAIL_PTR(intrbuff));
    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD(intrbuff),RINGBUFFER_TAIL(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),1);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),1);  // Tail should have moved to index 1
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),0);  // Head should still be at 0
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD_VAL(intrbuff),111);

    RINGBUFFER_WRITE(intrbuff, 222);

    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD_PTR(intrbuff),RINGBUFFER_TAIL_PTR(intrbuff));
    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD(intrbuff),RINGBUFFER_TAIL(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),2);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),2);  // Tail should have moved to index 2
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),0);  // Head should still be at 0
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD_VAL(intrbuff),111);

    RINGBUFFER_WRITE(intrbuff, 333);

    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD_PTR(intrbuff),RINGBUFFER_TAIL_PTR(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),RINGBUFFER_TAIL(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),3);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),0);  // Tail should have moved to index 0 (WRAP AROUND!)
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),0);  // Head should still be at 0
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD_VAL(intrbuff),111);      // The value should be at the head

    MYUNIT_ASSERT_TRUE(RINGBUFFER_FULL(intrbuff));


    uint32_t readval;


    RINGBUFFER_READ(intrbuff, readval);

    MYUNIT_ASSERT_EQUAL(readval,111);
    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD_PTR(intrbuff),RINGBUFFER_TAIL_PTR(intrbuff));
    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD(intrbuff),RINGBUFFER_TAIL(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),2);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),1);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD_VAL(intrbuff),222);

    RINGBUFFER_READ(intrbuff, readval);

    MYUNIT_ASSERT_EQUAL(readval,222);
    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD_PTR(intrbuff),RINGBUFFER_TAIL_PTR(intrbuff));
    MYUNIT_ASSERT_DIFFER(RINGBUFFER_HEAD(intrbuff),RINGBUFFER_TAIL(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),1);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),2);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD_VAL(intrbuff),333);

    RINGBUFFER_READ(intrbuff, readval);

    MYUNIT_ASSERT_EQUAL(readval,333);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD_PTR(intrbuff),RINGBUFFER_TAIL_PTR(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),RINGBUFFER_TAIL(intrbuff));
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD_VAL(intrbuff),111);



    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_TRUE(RINGBUFFER_EMPTY(intrbuff));
    MYUNIT_ASSERT_FALSE(RINGBUFFER_FULL(intrbuff));
}

/*
Test Case 4.1: Tail Wrap-Around

Setup:

Ring size = 5.
RINGBUFFER_INIT(ring);

Actions:

Push 5 items: 1, 2, 3, 4, 5. (This should fill the buffer and place tail at index 0 again because of wrap.)
Check that RINGBUFFER_FULL(ring) == true, ring.count == 5, and ring.tail == 0 (it wrapped after the 5th push).
Pop 1 item; check that popped item is 1.
Now ring.head should be 1, ring.tail still 0, and count is 4.
Push 1 more item: 6. This should go into the location previously occupied by the popped item.
Check that ring.tail == 1 and ring.count == 5 again.

Expected Results:

Initial fill sets count to 5 and tail wraps to 0.
After one pop, the next push reuses the freed position.
All indexing and read‐back ordering remain correct.
*/
MYUNIT_TESTCASE(ringbuffer_tail_wrap_around)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    RINGBUFFER_T(intrbuff) intrbuff;
    RINGBUFFER_INIT(intrbuff);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),0);

    RINGBUFFER_PUSH(intrbuff);

    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),1);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),1);


    RINGBUFFER_PUSH(intrbuff);

    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),2);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),2);


    RINGBUFFER_PUSH(intrbuff); // causes tail wrap-around


    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),3);

    MYUNIT_ASSERT_FALSE(RINGBUFFER_EMPTY(intrbuff));
    MYUNIT_ASSERT_TRUE(RINGBUFFER_FULL(intrbuff));
}


/*
Test Case 4.2: Head Wrap-Around

Setup:

As above, fill the buffer completely.

Actions:

Pop all 5 items so that ring.head wraps around to 0 again.
Check that ring.count == 0, ring.head == 0, ring.tail == 0.
Confirm RINGBUFFER_EMPTY(ring) == true.

Expected Results:

Head index wraps properly to 0 after popping 5 items.
Buffer is empty again with consistent indices.
*/
MYUNIT_TESTCASE(ringbuffer_head_wrap_around)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    RINGBUFFER_T(intrbuff) intrbuff;
    RINGBUFFER_INIT(intrbuff);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),0);

    RINGBUFFER_PUSH(intrbuff);
    RINGBUFFER_PUSH(intrbuff);

    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),2);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),2);

    RINGBUFFER_POP(intrbuff);
    RINGBUFFER_POP(intrbuff);

    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),2);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),2);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),0);
    MYUNIT_ASSERT_TRUE(RINGBUFFER_EMPTY(intrbuff));


    RINGBUFFER_PUSH(intrbuff);
    RINGBUFFER_PUSH(intrbuff);

    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),1);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),2);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),2);

    RINGBUFFER_POP(intrbuff); // causes head wrap-around

    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),1);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),0);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),1);

    RINGBUFFER_POP(intrbuff);



    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_EQUAL(RINGBUFFER_TAIL(intrbuff),1);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_HEAD(intrbuff),1);
    MYUNIT_ASSERT_EQUAL(RINGBUFFER_COUNT(intrbuff),0);

    MYUNIT_ASSERT_TRUE(RINGBUFFER_EMPTY(intrbuff));
    MYUNIT_ASSERT_FALSE(RINGBUFFER_FULL(intrbuff));
}

MYUNIT_TESTCASE(ringbuffer_source_and_drain_one)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    RINGBUFFER_T(intrbuff) intrbuff;
    RINGBUFFER_INIT(intrbuff);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    for(int trial = 0; trial < 1000; trial++)
    {
        uint32_t readval;

        srand(12345+trial);

        RINGBUFFER_WRITE(intrbuff,rand());

        srand(12345+trial);

        RINGBUFFER_READ(intrbuff,readval);

        MYUNIT_ASSERT_EQUAL(readval,rand());
    }

    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_TRUE(RINGBUFFER_EMPTY(intrbuff));
}

MYUNIT_TESTCASE(ringbuffer_source_and_drain_two)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    RINGBUFFER_T(intrbuff) intrbuff;
    RINGBUFFER_INIT(intrbuff);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    for(int trial = 0; trial < 1000; trial++)
    {
        uint32_t readval;

        srand(12345+trial);

        RINGBUFFER_WRITE(intrbuff,rand());
        RINGBUFFER_WRITE(intrbuff,rand());

        srand(12345+trial);

        RINGBUFFER_READ(intrbuff,readval);

        MYUNIT_ASSERT_EQUAL(readval,rand());

        RINGBUFFER_READ(intrbuff,readval);

        MYUNIT_ASSERT_EQUAL(readval,rand());
    }

    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_TRUE(RINGBUFFER_EMPTY(intrbuff));
}


MYUNIT_TESTCASE(ringbuffer_source_and_drain_three)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    RINGBUFFER_T(intrbuff) intrbuff;
    RINGBUFFER_INIT(intrbuff);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    for(int trial = 0; trial < 1000; trial++)
    {
        uint32_t readval;

        srand(12345+trial);

        RINGBUFFER_WRITE(intrbuff,rand());
        RINGBUFFER_WRITE(intrbuff,rand());
        RINGBUFFER_WRITE(intrbuff,rand());

        srand(12345+trial);

        RINGBUFFER_READ(intrbuff,readval);

        MYUNIT_ASSERT_EQUAL(readval,rand());

        RINGBUFFER_READ(intrbuff,readval);

        MYUNIT_ASSERT_EQUAL(readval,rand());

        RINGBUFFER_READ(intrbuff,readval);

        MYUNIT_ASSERT_EQUAL(readval,rand());
    }

    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_TRUE(RINGBUFFER_EMPTY(intrbuff));
}



MYUNIT_TESTCASE(ringbuffer_fill_and_empty)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    RINGBUFFER_T(intrbuff) intrbuff;
    RINGBUFFER_INIT(intrbuff);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    // make an offset
    RINGBUFFER_PUSH(intrbuff);
    RINGBUFFER_POP(intrbuff);

    for(int trial = 0; trial < 1000; trial++)
    {
        uint32_t readval;

        srand(12345+trial);

        while(!RINGBUFFER_FULL(intrbuff))
        {
            RINGBUFFER_WRITE(intrbuff,rand());
        }

        srand(12345+trial);

        while(!RINGBUFFER_EMPTY(intrbuff))
        {
            RINGBUFFER_READ(intrbuff,readval);
            MYUNIT_ASSERT_EQUAL(readval,rand());
        }
    }

    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_TRUE(RINGBUFFER_EMPTY(intrbuff));
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



MYUNIT_TESTSUITE(ringbuffer)
{
    MYUNIT_TESTSUITE_BEGIN();

    MYUNIT_EXEC_TESTCASE(ringbuffer_initialization);
    MYUNIT_EXEC_TESTCASE(ringbuffer_single_push);
    MYUNIT_EXEC_TESTCASE(ringbuffer_single_pop);
    MYUNIT_EXEC_TESTCASE(ringbuffer_push_several_and_pop_in_order);
    MYUNIT_EXEC_TESTCASE(ringbuffer_tail_wrap_around);
    MYUNIT_EXEC_TESTCASE(ringbuffer_head_wrap_around);
    MYUNIT_EXEC_TESTCASE(ringbuffer_source_and_drain_one);
    MYUNIT_EXEC_TESTCASE(ringbuffer_source_and_drain_two);
    MYUNIT_EXEC_TESTCASE(ringbuffer_source_and_drain_three);
    MYUNIT_EXEC_TESTCASE(ringbuffer_fill_and_empty);

    MYUNIT_TESTSUITE_END();
}
