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
#include"buffer.h"

#define GARBAGE 0xAA


BUFFER_TYPEDEF(intbuffer,uint32_t,3);



/*
Test Case 1: Buffer Initialization
Objective: Ensure that a newly initialized buffer is in the correct state (empty, correct capacity, etc.).
Steps:

Initialize a buffer (e.g., buffer_init(&buf, capacity) or Buffer buf = buffer_create(capacity)).

Check buffer properties (e.g., buffer_size, buffer_capacity, etc.).

Assert buffer is empty and has the correct capacity.
Expected Result:

The buffer is reported as empty (size == 0).

The capacity matches the provided value.
*/

MYUNIT_TESTCASE(Buffer_Initialization)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    BUFFER_T(intbuffer) intbuffer;
    memset(&intbuffer,GARBAGE,sizeof(intbuffer));

    MYUNIT_ASSERT_DIFFER(BUFFER_COUNT(intbuffer),0);




    // EXECUTE TESTCASE:
    // -------------------------------------------------
    BUFFER_INIT(intbuffer);  // Initialize the buffer

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(intbuffer.count,0);
    MYUNIT_ASSERT_EQUAL(BUFFER_SIZE(intbuffer),3);

}


/*
Test Case 2: Single Write/Read
Objective: Verify writing one element to the buffer and then reading it out.
Steps:

Initialize buffer with a known capacity.

Write a single element/data chunk (e.g., buffer_write(&buf, 'A')).

Read the element/data chunk (e.g., char c = buffer_read(&buf)).

Check the returned data.
Expected Result:

Read value should match the written value.

Buffer should be empty after the read.?
*/
MYUNIT_TESTCASE(Buffer_Single_Write_Read)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    BUFFER_T(intbuffer) intbuffer = {0};
    BUFFER_INIT(intbuffer);  // Initialize the buffer





    // EXECUTE TESTCASE:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(BUFFER_COUNT(intbuffer),0);
    MYUNIT_ASSERT_TRUE(BUFFER_EMPTY(intbuffer));
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[0],0);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[1],0);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[2],0);

    BUFFER_APPEND(intbuffer,12345);

    MYUNIT_ASSERT_EQUAL(BUFFER_COUNT(intbuffer),1);
    MYUNIT_ASSERT_FALSE(BUFFER_EMPTY(intbuffer));
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[0],12345);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[1],0);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[2],0);

    BUFFER_INIT(intbuffer);
    MYUNIT_ASSERT_EQUAL(BUFFER_COUNT(intbuffer),0);
    MYUNIT_ASSERT_TRUE(BUFFER_EMPTY(intbuffer));
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[0],12345);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[1],0);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[2],0);



    // POSTCONDITIONS:
    // -------------------------------------------------

}


/*
Test Case 3: Multiple Writes/Reads
Objective: Check that the buffer can handle multiple writes and reads in sequence.
Steps:

Initialize buffer.

Write several data elements in a known order (e.g., A, B, C, D, E).

Read them back and store in a temporary array.

Compare the read array to the original array.
Expected Result:

Data read from the buffer matches exactly the data written (order must be preserved).

Buffer is empty at the end of the test.?
*/
MYUNIT_TESTCASE(Buffer_Multiple_Writes_Reads)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    BUFFER_T(intbuffer) intbuffer = {0};
    BUFFER_INIT(intbuffer);  // Initialize the buffer





    // EXECUTE TESTCASE:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(BUFFER_COUNT(intbuffer),0);
    MYUNIT_ASSERT_TRUE(BUFFER_EMPTY(intbuffer));
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[0],0);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[1],0);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[2],0);

    BUFFER_APPEND(intbuffer,123);

    MYUNIT_ASSERT_EQUAL(BUFFER_COUNT(intbuffer),1);
    MYUNIT_ASSERT_FALSE(BUFFER_EMPTY(intbuffer));
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[0],123);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[1],0);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[2],0);

    BUFFER_APPEND(intbuffer,456);

    MYUNIT_ASSERT_EQUAL(BUFFER_COUNT(intbuffer),2);
    MYUNIT_ASSERT_FALSE(BUFFER_EMPTY(intbuffer));
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[0],123);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[1],456);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[2],0);

    BUFFER_APPEND(intbuffer,789);

    MYUNIT_ASSERT_EQUAL(BUFFER_COUNT(intbuffer),3);
    MYUNIT_ASSERT_FALSE(BUFFER_EMPTY(intbuffer));
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[0],123);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[1],456);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[2],789);


    BUFFER_INIT(intbuffer);
    MYUNIT_ASSERT_TRUE(BUFFER_EMPTY(intbuffer));
    MYUNIT_ASSERT_EQUAL(BUFFER_COUNT(intbuffer),0);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[0],123);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[1],456);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[2],789);



    // POSTCONDITIONS:
    // -------------------------------------------------

}

/*
Test Case 4: Fill to Capacity
Objective: Ensure correct behavior when the buffer is filled to its stated capacity.
Steps:

Initialize buffer to a small capacity for easy testing (e.g., 3).

Write 3 elements to the buffer (exactly capacity).

Check the buffer size is 5 (full).

Optionally attempt one more write (if the API returns an error or refuses, verify correct behavior).
Expected Result:

The buffer accepts exactly capacity number of elements.

A subsequent write (if tested) fails or returns an error/indicates no space available.

The buffer size is capacity.
*/
MYUNIT_TESTCASE(Buffer_Fill_To_Capacity)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    BUFFER_T(intbuffer) intbuffer = {0};
    BUFFER_INIT(intbuffer);  // Initialize the buffer

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(BUFFER_COUNT(intbuffer),0);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[0],0);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[1],0);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[2],0);

    MYUNIT_ASSERT_FALSE(BUFFER_FULL(intbuffer));
    MYUNIT_ASSERT_TRUE(BUFFER_EMPTY(intbuffer));

    while(!BUFFER_FULL(intbuffer))
    {
        MYUNIT_ASSERT_DIFFER(BUFFER_COUNT(intbuffer),BUFFER_SIZE(intbuffer));
        BUFFER_APPEND(intbuffer,123-BUFFER_COUNT(intbuffer));
    }

    MYUNIT_ASSERT_EQUAL(BUFFER_COUNT(intbuffer),BUFFER_SIZE(intbuffer));
    MYUNIT_ASSERT_TRUE(BUFFER_FULL(intbuffer));
    MYUNIT_ASSERT_FALSE(BUFFER_EMPTY(intbuffer));

    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[0],123);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[1],122);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[2],121);


    BUFFER_INIT(intbuffer);
    MYUNIT_ASSERT_FALSE(BUFFER_FULL(intbuffer));
    MYUNIT_ASSERT_TRUE(BUFFER_EMPTY(intbuffer));
    MYUNIT_ASSERT_EQUAL(BUFFER_COUNT(intbuffer),0);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[0],123);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[1],122);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[2],121);



    // POSTCONDITIONS:
    // -------------------------------------------------
}


MYUNIT_TESTCASE(Buffer_For_Each_Item)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    BUFFER_T(intbuffer) intbuffer = {0};
    BUFFER_INIT(intbuffer);  // Initialize the buffer

    // EXECUTE TESTCASE:
    // -------------------------------------------------



    BUFFER_APPEND(intbuffer,11);
    BUFFER_APPEND(intbuffer,22);
    BUFFER_APPEND(intbuffer,33);

    uint32_t *it;
    uint8_t cnt = 0;

    BUFFER_FOREACH(intbuffer,it)
    {
        (*it)*=2;
        cnt++;
    }

    MYUNIT_ASSERT_EQUAL(cnt,3);

    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[0],22);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[1],44);
    MYUNIT_ASSERT_EQUAL(BUFFER_ITEMS(intbuffer)[2],66);


    // POSTCONDITIONS:
    // -------------------------------------------------
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



MYUNIT_TESTSUITE(buffer)
{
    MYUNIT_TESTSUITE_BEGIN();

    MYUNIT_EXEC_TESTCASE(Buffer_Initialization);
    MYUNIT_EXEC_TESTCASE(Buffer_Single_Write_Read);
    MYUNIT_EXEC_TESTCASE(Buffer_Multiple_Writes_Reads);
    MYUNIT_EXEC_TESTCASE(Buffer_Fill_To_Capacity);
    MYUNIT_EXEC_TESTCASE(Buffer_For_Each_Item);

    MYUNIT_TESTSUITE_END();
}
