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

/*!
    \file       bitarray_tests.c

    \brief      Unit tests for Bit Array functionality

    \details    This file contains a suite of unit tests designed to verify the
                correct implementation and behavior of bit array operations within
                the software system. It utilizes a custom unit testing framework
                to perform various checks on initializing, setting,
                resetting, toggling, and retrieving bits in arrays of different sizes.

                The following test cases are included to verify the correctness of the implementation:

                - bit_array_size_tests: Tests the functionality related to determining the size of the bit array.
                - bitarray_initialization_and_setting: Tests the initialization of the bit array and setting individual bits to 1.
                - bitarray_initialization_and_resetting: Tests the initialization of the bit array and resetting individual bits to 0.
                - bitarray_toggle_operations: Tests the toggling of individual bits within the bit array.
*/

#include "myunit.h"
#include <stdint.h>
#include"bitarray.h"

// Define the bit array sizes
#define BIT_SIZE_1   1
#define BIT_SIZE_7   7
#define BIT_SIZE_8   8
#define BIT_SIZE_9   9
#define BIT_SIZE_15  15
#define BIT_SIZE_16  16
#define BIT_SIZE_17  17
#define BIT_SIZE_31  31
#define BIT_SIZE_32  32
#define BIT_SIZE_33  33


/*!
   \brief     Tests the size of bit arrays with different bit sizes.

   \details   This test case verifies that the `BITARRAY_SIZE` macro correctly
               calculates the size (in 8 bit steps) of a bit array based on its
               configured bit size. It covers various bit sizes to ensure
               correctness across different configurations.
*/
MYUNIT_TESTCASE(bit_array_size_tests)
{
    // PRECONDITIONS :
    // -------------------------------------------------
    // Arrange
    BITARRAY(bit_array_1, BIT_SIZE_1);
    BITARRAY(bit_array_7, BIT_SIZE_7);
    BITARRAY(bit_array_8, BIT_SIZE_8);
    BITARRAY(bit_array_9, BIT_SIZE_9);
    BITARRAY(bit_array_15, BIT_SIZE_15);
    BITARRAY(bit_array_16, BIT_SIZE_16);
    BITARRAY(bit_array_17, BIT_SIZE_17);
    BITARRAY(bit_array_31, BIT_SIZE_31);
    BITARRAY(bit_array_32, BIT_SIZE_32);
    BITARRAY(bit_array_33, BIT_SIZE_33);


    // EXECUTE TESTCASE :
    // -------------------------------------------------
    // Act & Assert
    MYUNIT_ASSERT_EQUAL(BITARRAY_SIZE(bit_array_1), 8);
    MYUNIT_ASSERT_EQUAL(BITARRAY_SIZE(bit_array_7), 8);
    MYUNIT_ASSERT_EQUAL(BITARRAY_SIZE(bit_array_8), 8);
    MYUNIT_ASSERT_EQUAL(BITARRAY_SIZE(bit_array_9), 16);
    MYUNIT_ASSERT_EQUAL(BITARRAY_SIZE(bit_array_15), 16);
    MYUNIT_ASSERT_EQUAL(BITARRAY_SIZE(bit_array_16), 16);
    MYUNIT_ASSERT_EQUAL(BITARRAY_SIZE(bit_array_17), 24);
    MYUNIT_ASSERT_EQUAL(BITARRAY_SIZE(bit_array_31), 32);
    MYUNIT_ASSERT_EQUAL(BITARRAY_SIZE(bit_array_32), 32);
    MYUNIT_ASSERT_EQUAL(BITARRAY_SIZE(bit_array_33), 40);

    // POSTCONDITIONS :
    // -------------------------------------------------

}

#define ARRAY_SIZE 32 // Adjust size as needed for testing


/*!
   \brief Tests bit array initialization and setting/clearing of bits.

   \details This test case verifies that the bit array is initialized correctly,
            and that bits can be set and cleared as expected. It tests setting
            even bits, then odd bits, and verifies the state of all bits after
            each operation.

*/
MYUNIT_TESTCASE(bitarray_initialization_and_setting)
{


    // PRECONDITIONS :
    // -------------------------------------------------
    int i;
    BITARRAY(test,ARRAY_SIZE);

    BITARRAY_INIT(test); // Ensure all bits are initially cleared

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // All bits should not be set
    }

    // EXECUTE TESTCASE :
    // -------------------------------------------------

    // First Scenario: Set even bits, clear odd bits

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
       if (i % 2 == 0)
       {
           BITARRAY_SET(test, i); // Set even-indexed bits
       }
    }


    for (i = 0; i < ARRAY_SIZE; ++i)
    {
       if (i % 2 == 0)
       {
           MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // Even bits should be set
       }
       else
       {
           MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // Odd bits should not be set
       }
    }


    // Reinitialize the bit array to clear all bits
    BITARRAY_INIT(test);

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        if (i % 2 != 0)
        {
            BITARRAY_SET(test, i); // Set odd-indexed bits
        }
    }

    // EXECUTE TESTCASE: Check new even and odd bit states
    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        if (i % 2 == 0)
        {
            MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // Even bits should not be set
        }
        else
        {
            MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // Odd bits should be set
        }
    }


    // POSTCONDITIONS :
    // -------------------------------------------------

    BITARRAY_INIT(test); // Ensure all bits are initially cleared

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // All bits should not be set
    }
}


/*!
  \brief Tests bit array initialization and resetting of bits.

  \details This test case verifies that the bit array is initialized correctly,
          and that bits can be set and reset as expected. It tests resetting
          even bits, then odd bits, and verifies the state of all bits after
          each operation.
*/
MYUNIT_TESTCASE(bitarray_initialization_and_resetting)
{


    // PRECONDITIONS :
    // -------------------------------------------------
    int i;
    BITARRAY(test,ARRAY_SIZE);

    BITARRAY_INIT(test); // Ensure all bits are initially cleared

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        BITARRAY_SET(test, i); // Set all indexed bits
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // All bits should not be set
    }


    // EXECUTE TESTCASE :
    // -------------------------------------------------

    // First Scenario: Reset even bits, clear odd bits

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
       if (i % 2 == 0)
       {
           BITARRAY_RESET(test, i); // Set even-indexed bits
       }
    }


    for (i = 0; i < ARRAY_SIZE; ++i)
    {
       if (i % 2 == 0)
       {
           MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // Even bits should be reset
       }
       else
       {
           MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // Odd bits should not be reset
       }
    }


    BITARRAY_INIT(test); // Ensure all bits are initially cleared

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        BITARRAY_SET(test, i); // Set all indexed bits
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // All bits should not be set
    }


    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        if (i % 2 != 0)
        {
            BITARRAY_RESET(test, i); // Set odd-indexed bits
        }
    }

    // EXECUTE TESTCASE: Check new even and odd bit states
    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        if (i % 2 == 0)
        {
            MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // Even bits should not be rset
        }
        else
        {
            MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // Odd bits should be rset
        }
    }


    // POSTCONDITIONS :
    // -------------------------------------------------

    BITARRAY_INIT(test); // Ensure all bits are initially cleared

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // All bits should not be set
    }
}

/*!
 \brief Tests bit array toggle operations.

 \details This test case verifies that the bit array toggle operation works as expected.
         It toggles odd and even bits in multiple iterations and asserts the state of
         all bits after each operation.
*/
MYUNIT_TESTCASE(bitarray_toggle_operations)
{


    unsigned int i;
    BITARRAY(test,ARRAY_SIZE);

    // 1. Initialize all bits to 0
    BITARRAY_INIT(test); // Ensure all bits are initially cleared


    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // Assert that all bits are not set
    }

    // 2. Toggle odd bits and verify state
    for (i = 1; i < ARRAY_SIZE; i += 2) // Odd indices
    {
        BITARRAY_TOGGLE(test, i);
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        if (i % 2 == 0)
        {
            MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // Even bits should remain reset
        }
        else
        {
            MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // Odd bits should be set
        }
    }

    // 3. Toggle even bits and verify state
    for (i = 0; i < ARRAY_SIZE; i += 2) // Even indices
    {
        BITARRAY_TOGGLE(test, i);
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // All bits should now be set
    }

    // 4. Toggle odd bits again and verify state
    for (i = 1; i < ARRAY_SIZE; i += 2) // Odd indices
    {
        BITARRAY_TOGGLE(test, i);
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        if (i % 2 == 0)
        {
            MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // Even bits should remain set
        }
        else
        {
            MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // Odd bits should be reset
        }
    }

    // 5. Toggle even bits again and verify state
    for (i = 0; i < ARRAY_SIZE; i += 2) // Even indices
    {
        BITARRAY_TOGGLE(test, i);
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // All bits should now be reset
    }
}


/*!
 \brief Tests bit array set value operations.

 \details This test case verifies that the bit array set value operation works as expected.
         It tests setting and resetting individual bits, setting all bits to 1, resetting
         all bits to 0, and performing mixed operations to set odd and even indices to
         specific values.
*/
MYUNIT_TESTCASE(bitarray_set_value_operations)
{
    BITARRAY(test,ARRAY_SIZE);

    unsigned int i;

    // Test setting and resetting individual bits
    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        // Set the bit to 1
        BITARRAY_SET_VALUE(test, i, 1);
        MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // Assert that the bit is set

        // Reset the bit to 0
        BITARRAY_SET_VALUE(test, i, 0);
        MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // Assert that the bit is reset
    }

    // Test setting all bits to 1
    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        BITARRAY_SET_VALUE(test, i, 1);
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // Assert all bits are set
    }

    // Test resetting all bits to 0
    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        BITARRAY_SET_VALUE(test, i, 0);
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // Assert all bits are reset
    }

    // Mixed operations: set odd indices to 1 and even indices to 0
    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        if (i % 2 == 0)
        {
            BITARRAY_SET_VALUE(test, i, 0);
        }
        else
        {
            BITARRAY_SET_VALUE(test, i, 1);
        }
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        if (i % 2 == 0)
        {
            MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // Even indices should be reset
        }
        else
        {
            MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // Odd indices should be set
        }
    }

    // Recheck the whole array
    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        BITARRAY_SET_VALUE(test, i, i % 2); // Set even to 0 and odd to 1 again
        if (i % 2 == 0)
        {
            MYUNIT_ASSERT_FALSE(BITARRAY_GET(test, i)); // Even indices should be reset
        }
        else
        {
            MYUNIT_ASSERT_TRUE(BITARRAY_GET(test, i)); // Odd indices should be set
        }
    }
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


MYUNIT_TESTSUITE(bitarray)
{
    MYUNIT_TESTSUITE_BEGIN();


    MYUNIT_EXEC_TESTCASE(bit_array_size_tests);
    MYUNIT_EXEC_TESTCASE(bitarray_initialization_and_setting);
    MYUNIT_EXEC_TESTCASE(bitarray_initialization_and_resetting);
    MYUNIT_EXEC_TESTCASE(bitarray_toggle_operations);
    MYUNIT_EXEC_TESTCASE(bitarray_set_value_operations);
    MYUNIT_TESTSUITE_END();
}
