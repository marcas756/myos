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
#include "bits.h"
#include "binary.h"



MYUNIT_TESTCASE(BITS_IdentityTest)
{
    // PRECONDITIONS:
    // -------------------------------------------------

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    uint8_t result1 = BITS(0xFF, 0xFF);
    MYUNIT_ASSERT_EQUAL(result1, 0xFF);

    uint8_t result2 = BITS(0xA5, 0xFF);
    MYUNIT_ASSERT_EQUAL(result2, 0xA5);

    // POSTCONDITIONS:
    // -------------------------------------------------
}

MYUNIT_TESTCASE(BITS_ZeroOutTest)
{
    // PRECONDITIONS:
    // -------------------------------------------------

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    uint8_t result1 = BITS(0xFF, 0x00);
    MYUNIT_ASSERT_EQUAL(result1, 0x00);

    uint8_t result2 = BITS(0xA5, 0x00);
    MYUNIT_ASSERT_EQUAL(result2, 0x00);

    // POSTCONDITIONS:
    // -------------------------------------------------
}

MYUNIT_TESTCASE(BITS_PartialMaskTest)
{
    // PRECONDITIONS:
    // -------------------------------------------------

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    uint8_t result1 = BITS(0xF0, 0x0F);
    MYUNIT_ASSERT_EQUAL(result1, 0x00);

    uint8_t result2 = BITS(0xF0, 0xF0);
    MYUNIT_ASSERT_EQUAL(result2, 0xF0);

    uint8_t result3 = BITS(0xAA, 0x55);
    MYUNIT_ASSERT_EQUAL(result3, 0x00);

    uint8_t result4 = BITS(0xAA, 0xFF);
    MYUNIT_ASSERT_EQUAL(result4, 0xAA);

    // POSTCONDITIONS:
    // -------------------------------------------------
}

MYUNIT_TESTCASE(BITS_Edge_Cases)
{
    // PRECONDITIONS:
    unsigned int x1 = 0x80000000;
    unsigned int m1 = 0xFFFFFFFF;
    unsigned int x2 = 0xFFFFFFFF;
    unsigned int m2 = 0x80000000;

    // EXECUTE TESTCASE:
    unsigned int result1 = BITS(x1, m1);
    unsigned int result2 = BITS(x2, m2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(result1, 0x80000000);
    MYUNIT_ASSERT_EQUAL(result2, 0x80000000);
}

MYUNIT_TESTCASE(BITS_Negative_Values)
{
    // PRECONDITIONS:
    signed int x = -1;
    unsigned int m1 = 0xFF;
    unsigned int m2 = 0x0;
    unsigned int m3 = 0x80000000;

    // EXECUTE TESTCASE:
    unsigned int result1 = BITS(x, m1);
    unsigned int result2 = BITS(x, m2);
    unsigned int result3 = BITS(x, m3);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(result1, 0xFF);
    MYUNIT_ASSERT_EQUAL(result2, 0x0);
    MYUNIT_ASSERT_EQUAL(result3, 0x80000000);
}

MYUNIT_TESTCASE(BITS_INVERT_BasicExpectedBehaviour)
{
    // PRECONDITIONS:
    unsigned int x1 = 0x00000000;
    unsigned int x2 = 0xFFFFFFFF;

    // EXECUTE TESTCASE:
    unsigned int result1 = BITS_INVERT(x1);
    unsigned int result2 = BITS_INVERT(x2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(result1, 0xFFFFFFFF);
    MYUNIT_ASSERT_EQUAL(result2, 0x00000000);
}


MYUNIT_TESTCASE(BITS_INVERT_AlternatingBits)
{
    // PRECONDITIONS:
    unsigned int x1 = 0xAAAAAAAA;
    unsigned int x2 = 0x55555555;

    // EXECUTE TESTCASE:
    unsigned int result1 = BITS_INVERT(x1);
    unsigned int result2 = BITS_INVERT(x2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(result1, 0x55555555);
    MYUNIT_ASSERT_EQUAL(result2, 0xAAAAAAAA);
}

MYUNIT_TESTCASE(BITS_INVERT_NegativeValues)
{
    // PRECONDITIONS:
    signed int x1 = 0;
    signed int x2 = -1;
    signed int x3 = 1;
    signed int x4 = -2;

    // EXECUTE TESTCASE:
    signed int result1 = BITS_INVERT(x1);
    signed int result2 = BITS_INVERT(x2);
    signed int result3 = BITS_INVERT(x3);
    signed int result4 = BITS_INVERT(x4);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(result1, -1);      // 0xFFFFFFFF
    MYUNIT_ASSERT_EQUAL(result2, 0);
    MYUNIT_ASSERT_EQUAL(result3, -2);     // 0xFFFFFFFE
    MYUNIT_ASSERT_EQUAL(result4, 1);      // 0x00000001
}

MYUNIT_TESTCASE(BITS_INVERT_DoubleInversionIdentity)
{
    // PRECONDITIONS:
    unsigned int x1 = 0x12345678;
    signed int x2 = -42;
    unsigned int x3 = 0xFFFFFFFF;

    // EXECUTE TESTCASE:
    unsigned int result1 = BITS_INVERT(BITS_INVERT(x1));
    signed int result2 = BITS_INVERT(BITS_INVERT(x2));
    unsigned int result3 = BITS_INVERT(BITS_INVERT(x3));

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(result1, x1);
    MYUNIT_ASSERT_EQUAL(result2, x2);
    MYUNIT_ASSERT_EQUAL(result3, x3);
}


MYUNIT_TESTCASE(BITS_TEST_AllRequiredBitsPresent)
{
    // PRECONDITIONS:
    unsigned int x1 = 0xFF;
    unsigned int m1 = 0x0F;

    unsigned int x2 = 0x0F;
    unsigned int m2 = 0x05;

    // EXECUTE TESTCASE:
    MYUNIT_ASSERT_TRUE(BITS_TEST(x1, m1));
    MYUNIT_ASSERT_TRUE(BITS_TEST(x2, m2));

    // POSTCONDITIONS: Verified in assertions.
}

MYUNIT_TESTCASE(BITS_TEST_SomeRequiredBitsMissing)
{
    // PRECONDITIONS:
    unsigned int x1 = 0x0F;
    unsigned int m1 = 0xF0;

    unsigned int x2 = 0x05;
    unsigned int m2 = 0x07;

    // EXECUTE TESTCASE:
    MYUNIT_ASSERT_FALSE(BITS_TEST(x1, m1));
    MYUNIT_ASSERT_FALSE(BITS_TEST(x2, m2));

    // POSTCONDITIONS: Verified in assertions.
}

MYUNIT_TESTCASE(BITS_TEST_ExactMatch)
{
    // PRECONDITIONS:
    unsigned int x = 0xA5;
    unsigned int m = 0xA5;

    // EXECUTE TESTCASE:
    MYUNIT_ASSERT_TRUE(BITS_TEST(x, m));

    // POSTCONDITIONS: Verified in assertion.
}

MYUNIT_TESTCASE(BITS_TEST_MaskIsZero)
{
    // PRECONDITIONS:
    unsigned int x1 = 0x00;
    unsigned int m1 = 0x00;

    unsigned int x2 = 0xFF;
    unsigned int m2 = 0x00;

    // EXECUTE TESTCASE:
    MYUNIT_ASSERT_TRUE(BITS_TEST(x1, m1));
    MYUNIT_ASSERT_TRUE(BITS_TEST(x2, m2));

    // POSTCONDITIONS: Verified in assertions.
}

MYUNIT_TESTCASE(BITS_TEST_ZeroValueFailsUnlessMaskIsZero)
{
    // PRECONDITIONS:
    unsigned int x = 0x00;
    unsigned int m1 = 0x01;
    unsigned int m2 = 0x00;

    // EXECUTE TESTCASE:
    MYUNIT_ASSERT_FALSE(BITS_TEST(x, m1));
    MYUNIT_ASSERT_TRUE(BITS_TEST(x, m2));

    // POSTCONDITIONS: Verified in assertions.
}

MYUNIT_TESTCASE(BITS_TEST_EdgeBits)
{
    // PRECONDITIONS:
    unsigned int x1 = 0x80000000;
    unsigned int m1 = 0x80000000;

    unsigned int x2 = 0x00000000;
    unsigned int m2 = 0x80000000;

    // EXECUTE TESTCASE:
    MYUNIT_ASSERT_TRUE(BITS_TEST(x1, m1));
    MYUNIT_ASSERT_FALSE(BITS_TEST(x2, m2));

    // POSTCONDITIONS: Verified in assertions.
}



MYUNIT_TESTCASE(BITS_SET_BasicBitSetting)
{
    // PRECONDITIONS:
    unsigned int x1 = b0000;
    unsigned int m1 = b0001;

    unsigned int x2 = b0100;
    unsigned int m2 = b0010;

    // EXECUTE TESTCASE:
    BITS_SET(x1, m1);
    BITS_SET(x2, m2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x1, 0x0001);
    MYUNIT_ASSERT_EQUAL(x2, 0x006);
}

MYUNIT_TESTCASE(BITS_SET_SettingAlreadySetBits)
{
    // PRECONDITIONS:
    unsigned int x1 = b1111;
    unsigned int m1 = b0010;

    unsigned int x2 = b1010;
    unsigned int m2 = b0010;

    // EXECUTE TESTCASE:
    BITS_SET(x1, m1);
    BITS_SET(x2, m2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x1, 0x000F);
    MYUNIT_ASSERT_EQUAL(x2, 0x00A);
}

MYUNIT_TESTCASE(BITS_SET_MultipleBits)
{
    // PRECONDITIONS:
    unsigned int x1 = b0001;
    unsigned int m1 = b1110;

    unsigned int x2 = b01010101;
    unsigned int m2 = b10101010;

    // EXECUTE TESTCASE:
    BITS_SET(x1, m1);
    BITS_SET(x2, m2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x1, 0x0F);
    MYUNIT_ASSERT_EQUAL(x2, 0xFF);
}

MYUNIT_TESTCASE(BITS_SET_NoOpMask)
{
    // PRECONDITIONS:
    unsigned int x = b0101;
    unsigned int m = b0000;

    // EXECUTE TESTCASE:
    BITS_SET(x, m);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x, 0x0005);
}

MYUNIT_TESTCASE(BITS_SET_AllBitsMask)
{
    // PRECONDITIONS:
    unsigned int x1 = 0x00000000;
    unsigned int x2 = 0x12345678;

    unsigned int m = 0xFFFFFFFF;

    // EXECUTE TESTCASE:
    BITS_SET(x1, m);
    BITS_SET(x2, m);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x1, 0xFFFFFFFF);
    MYUNIT_ASSERT_EQUAL(x2, 0xFFFFFFFF);
}

MYUNIT_TESTCASE(BITS_SET_EdgeBits)
{
    // PRECONDITIONS:
    unsigned int x1 = 0x00000000;
    unsigned int m1 = 0x80000000;

    unsigned int x2 = 0x80000000;
    unsigned int m2 = 0x00000001;

    // EXECUTE TESTCASE:
    BITS_SET(x1, m1);
    BITS_SET(x2, m2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x1, 0x80000000);
    MYUNIT_ASSERT_EQUAL(x2, 0x80000001);
}



MYUNIT_TESTCASE(BITS_CLEAR_BasicBitClearing)
{
    // PRECONDITIONS:
    unsigned int x1 = b1111;
    unsigned int m1 = b0101;

    unsigned int x2 = b1100;
    unsigned int m2 = b1000;

    // EXECUTE TESTCASE:
    BITS_CLEAR(x1, m1);
    BITS_CLEAR(x2, m2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x1, 0x000A); // b1010
    MYUNIT_ASSERT_EQUAL(x2, 0x0004); // b0100
}

MYUNIT_TESTCASE(BITS_CLEAR_ClearingBitsNotSet)
{
    // PRECONDITIONS:
    unsigned int x1 = b0011;
    unsigned int m1 = b1100;

    unsigned int x2 = b0000;
    unsigned int m2 = b1111;

    // EXECUTE TESTCASE:
    BITS_CLEAR(x1, m1);
    BITS_CLEAR(x2, m2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x1, 0x0003); // b0011
    MYUNIT_ASSERT_EQUAL(x2, 0x0000); // b0000
}

MYUNIT_TESTCASE(BITS_CLEAR_ClearingAllBits)
{
    // PRECONDITIONS:
    unsigned int x1 = b1111;
    unsigned int m1 = b1111;

    unsigned int x2 = 0xFFFFFFFF;
    unsigned int m2 = 0xFFFFFFFF;

    // EXECUTE TESTCASE:
    BITS_CLEAR(x1, m1);
    BITS_CLEAR(x2, m2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x1, 0x0000); // b0000
    MYUNIT_ASSERT_EQUAL(x2, 0x00000000); // b00000000
}

MYUNIT_TESTCASE(BITS_CLEAR_ClearingNoBits)
{
    // PRECONDITIONS:
    unsigned int x = 0x12345678;
    unsigned int m = 0x00000000;

    // EXECUTE TESTCASE:
    BITS_CLEAR(x, m);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x, 0x12345678);
}

MYUNIT_TESTCASE(BITS_CLEAR_EdgeBits)
{
    // PRECONDITIONS:
    unsigned int x1 = 0xFFFFFFFF;
    unsigned int m1 = 0x80000000;

    unsigned int x2 = 0xFFFFFFFF;
    unsigned int m2 = 0x00000001;

    // EXECUTE TESTCASE:
    BITS_CLEAR(x1, m1);
    BITS_CLEAR(x2, m2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x1, 0x7FFFFFFF); // Clearing high bit
    MYUNIT_ASSERT_EQUAL(x2, 0xFFFFFFFE); // Clearing low bit
}

MYUNIT_TESTCASE(BITS_CLEAR_RandomMixedPattern)
{
    // PRECONDITIONS:
    unsigned int x =    b10101010;
    unsigned int m =    b11001100;

    // EXECUTE TESTCASE:
    BITS_CLEAR(x, m);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x, b00100010); // Resulting in b00100000
}

MYUNIT_TESTCASE(BITS_TOGGLE_BasicToggle)
{
    // PRECONDITIONS:
    unsigned int x1 = 0x00;
    unsigned int m1 = 0xFF;

    unsigned int x2 = 0xFF;
    unsigned int m2 = 0xFF;

    // EXECUTE TESTCASE:
    BITS_TOGGLE(x1, m1);
    BITS_TOGGLE(x2, m2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x1, 0x000000FF); // 0b1111 1111
    MYUNIT_ASSERT_EQUAL(x2, 0x00000000); // 0b0000 0000
}

MYUNIT_TESTCASE(BITS_TOGGLE_PartialMask)
{
    // PRECONDITIONS:
    unsigned int x1 = 0xAA; // 0b10101010
    unsigned int m1 = 0x0F; // 0b00001111

    unsigned int x2 = 0x0F;
    unsigned int m2 = 0xF0;

    unsigned int x3 = 0xF0;
    unsigned int m3 = 0x0F;

    // EXECUTE TESTCASE:
    BITS_TOGGLE(x1, m1);
    BITS_TOGGLE(x2, m2);
    BITS_TOGGLE(x3, m3);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x1, 0xA5); // Resulting in 0b10100101
    MYUNIT_ASSERT_EQUAL(x2, 0xFF); // Resulting in 0b1111 1111
    MYUNIT_ASSERT_EQUAL(x3, 0xFF); // Resulting in 0b1111 1111
}

MYUNIT_TESTCASE(BITS_TOGGLE_Idempotence)
{
    // PRECONDITIONS:
    unsigned int x = 0x5A; // Original value: 0b01011010
    unsigned int m = 0x0F; // Mask: 0b00001111

    unsigned int original_x = x;

    // EXECUTE TESTCASE:
    BITS_TOGGLE(x, m);         // First toggle
    BITS_TOGGLE(x, m);         // Second toggle (same mask)

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x, original_x); // Should return to original value: 0b01011010
}

MYUNIT_TESTCASE(BITS_TOGGLE_NoOpToggle)
{
    // PRECONDITIONS:
    unsigned int x = 0x33;
    unsigned int m = 0x00;

    // EXECUTE TESTCASE:
    BITS_TOGGLE(x, m);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x, 0x33); // Should remain unchanged
}

MYUNIT_TESTCASE(BITS_TOGGLE_EdgeBits)
{
    // PRECONDITIONS:
    unsigned int x1 = 0x80000000;
    unsigned int m1 = 0x80000000;

    unsigned int x2 = 0x00000000;
    unsigned int m2 = 0x80000000;

    // EXECUTE TESTCASE:
    BITS_TOGGLE(x1, m1);
    BITS_TOGGLE(x2, m2);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x1, 0x00000000); // Toggle high bit
    MYUNIT_ASSERT_EQUAL(x2, 0x80000000); // Set high bit
}

MYUNIT_TESTCASE(BITS_TOGGLE_FullWordToggle)
{
    // PRECONDITIONS:
    unsigned int x = 0x12345678;
    unsigned int m = 0xFFFFFFFF;

    // EXECUTE TESTCASE:
    BITS_TOGGLE(x, m);

    // POSTCONDITIONS:
    MYUNIT_ASSERT_EQUAL(x, 0xEDCBA987); // Complement result
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



MYUNIT_TESTSUITE(bits)
{
    MYUNIT_TESTSUITE_BEGIN();

    MYUNIT_EXEC_TESTCASE(BITS_IdentityTest);
    MYUNIT_EXEC_TESTCASE(BITS_ZeroOutTest);
    MYUNIT_EXEC_TESTCASE(BITS_PartialMaskTest);
    MYUNIT_EXEC_TESTCASE(BITS_Edge_Cases);
    MYUNIT_EXEC_TESTCASE(BITS_Negative_Values);

    MYUNIT_EXEC_TESTCASE(BITS_INVERT_BasicExpectedBehaviour);
    MYUNIT_EXEC_TESTCASE(BITS_INVERT_AlternatingBits);
    MYUNIT_EXEC_TESTCASE(BITS_INVERT_NegativeValues);
    MYUNIT_EXEC_TESTCASE(BITS_INVERT_DoubleInversionIdentity);

    MYUNIT_EXEC_TESTCASE(BITS_TEST_AllRequiredBitsPresent);
    MYUNIT_EXEC_TESTCASE(BITS_TEST_SomeRequiredBitsMissing);
    MYUNIT_EXEC_TESTCASE(BITS_TEST_ExactMatch);
    MYUNIT_EXEC_TESTCASE(BITS_TEST_MaskIsZero);
    MYUNIT_EXEC_TESTCASE(BITS_TEST_ZeroValueFailsUnlessMaskIsZero);
    MYUNIT_EXEC_TESTCASE(BITS_TEST_EdgeBits);

    MYUNIT_EXEC_TESTCASE(BITS_SET_BasicBitSetting);
    MYUNIT_EXEC_TESTCASE(BITS_SET_SettingAlreadySetBits);
    MYUNIT_EXEC_TESTCASE(BITS_SET_MultipleBits);
    MYUNIT_EXEC_TESTCASE(BITS_SET_NoOpMask);
    MYUNIT_EXEC_TESTCASE(BITS_SET_AllBitsMask);
    MYUNIT_EXEC_TESTCASE(BITS_SET_EdgeBits);

    MYUNIT_EXEC_TESTCASE(BITS_CLEAR_BasicBitClearing);
    MYUNIT_EXEC_TESTCASE(BITS_CLEAR_ClearingBitsNotSet);
    MYUNIT_EXEC_TESTCASE(BITS_CLEAR_ClearingAllBits);
    MYUNIT_EXEC_TESTCASE(BITS_CLEAR_ClearingNoBits);
    MYUNIT_EXEC_TESTCASE(BITS_CLEAR_EdgeBits);
    MYUNIT_EXEC_TESTCASE(BITS_CLEAR_RandomMixedPattern);

    MYUNIT_EXEC_TESTCASE(BITS_TOGGLE_BasicToggle);
    MYUNIT_EXEC_TESTCASE(BITS_TOGGLE_PartialMask);
    MYUNIT_EXEC_TESTCASE(BITS_TOGGLE_Idempotence);
    MYUNIT_EXEC_TESTCASE(BITS_TOGGLE_NoOpToggle);
    MYUNIT_EXEC_TESTCASE(BITS_TOGGLE_EdgeBits);
    MYUNIT_EXEC_TESTCASE(BITS_TOGGLE_FullWordToggle);

    MYUNIT_TESTSUITE_END();
}
