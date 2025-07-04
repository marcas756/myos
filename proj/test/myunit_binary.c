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
#include"binary.h"



const uint8_t binary_numbers[] = {
    b00000000, b00000001, b00000010, b00000011, b00000100, b00000101, b00000110,
    b00000111, b00001000, b00001001, b00001010, b00001011, b00001100, b00001101,
    b00001110, b00001111,

    b00010000, b00010001, b00010010, b00010011, b00010100, b00010101, b00010110,
    b00010111, b00011000, b00011001, b00011010, b00011011, b00011100, b00011101,
    b00011110, b00011111,

    b00100000, b00100001, b00100010, b00100011, b00100100, b00100101, b00100110,
    b00100111, b00101000, b00101001, b00101010, b00101011, b00101100, b00101101,
    b00101110, b00101111,

    b00110000, b00110001, b00110010, b00110011, b00110100, b00110101, b00110110,
    b00110111, b00111000, b00111001, b00111010, b00111011, b00111100, b00111101,
    b00111110, b00111111,

    b01000000, b01000001, b01000010, b01000011, b01000100, b01000101, b01000110,
    b01000111, b01001000, b01001001, b01001010, b01001011, b01001100, b01001101,
    b01001110, b01001111,

    b01010000, b01010001, b01010010, b01010011, b01010100, b01010101, b01010110,
    b01010111, b01011000, b01011001, b01011010, b01011011, b01011100, b01011101,
    b01011110, b01011111,

    b01100000, b01100001, b01100010, b01100011, b01100100, b01100101, b01100110,
    b01100111, b01101000, b01101001, b01101010, b01101011, b01101100, b01101101,
    b01101110, b01101111,

    b01110000, b01110001, b01110010, b01110011, b01110100, b01110101, b01110110,
    b01110111, b01111000, b01111001, b01111010, b01111011, b01111100, b01111101,
    b01111110, b01111111,

    b10000000, b10000001, b10000010, b10000011, b10000100, b10000101, b10000110,
    b10000111, b10001000, b10001001, b10001010, b10001011, b10001100, b10001101,
    b10001110, b10001111,

    b10010000, b10010001, b10010010, b10010011, b10010100, b10010101, b10010110,
    b10010111, b10011000, b10011001, b10011010, b10011011, b10011100, b10011101,
    b10011110, b10011111,

    b10100000, b10100001, b10100010, b10100011, b10100100, b10100101, b10100110,
    b10100111, b10101000, b10101001, b10101010, b10101011, b10101100, b10101101,
    b10101110, b10101111,

    b10110000, b10110001, b10110010, b10110011, b10110100, b10110101, b10110110,
    b10110111, b10111000, b10111001, b10111010, b10111011, b10111100, b10111101,
    b10111110, b10111111,

    b11000000, b11000001, b11000010, b11000011, b11000100, b11000101, b11000110,
    b11000111, b11001000, b11001001, b11001010, b11001011, b11001100, b11001101,
    b11001110, b11001111,

    b11010000, b11010001, b11010010, b11010011, b11010100, b11010101, b11010110,
    b11010111, b11011000, b11011001, b11011010, b11011011, b11011100, b11011101,
    b11011110, b11011111,

    b11100000, b11100001, b11100010, b11100011, b11100100, b11100101, b11100110,
    b11100111, b11101000, b11101001, b11101010, b11101011, b11101100, b11101101,
    b11101110, b11101111,

    b11110000, b11110001, b11110010, b11110011, b11110100, b11110101, b11110110,
    b11110111, b11111000, b11111001, b11111010, b11111011, b11111100, b11111101,
    b11111110, b11111111
};

MYUNIT_TESTCASE(test_binary_value_matches_index)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    int i;

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    for (i = 0; i < sizeof(binary_numbers); ++i)
    {
        MYUNIT_ASSERT_EQUAL(binary_numbers[i], (uint8_t)i);
    }
}


MYUNIT_TESTCASE(test_binary_numbers_size)
{
    // PRECONDITIONS:
    // -------------------------------------------------


    // EXECUTE TESTCASE:
    // -------------------------------------------------
    size_t array_size = sizeof(binary_numbers) / sizeof(binary_numbers[0]);

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(array_size, 256);
}



MYUNIT_TESTCASE(BINARY8)
{
    // PRECONDITIONS:
    // -------------------------------------------------


    // EXECUTE TESTCASE:
    // -------------------------------------------------

    MYUNIT_ASSERT_EQUAL(BINARY8(0), 0);
    MYUNIT_ASSERT_EQUAL(BINARY8(00), 0);
    MYUNIT_ASSERT_EQUAL(BINARY8(000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY8(0000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY8(00000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY8(000000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY8(0000000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY8(00000000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY8(11111111), UINT8_MAX);

    MYUNIT_ASSERT_EQUAL(BINARY8(10001110), 142);
    MYUNIT_ASSERT_EQUAL(BINARY8(00100111), 39);
    MYUNIT_ASSERT_EQUAL(BINARY8(10000010), 130);
    MYUNIT_ASSERT_EQUAL(BINARY8(00010101), 21);
    MYUNIT_ASSERT_EQUAL(BINARY8(00110001), 49);
    MYUNIT_ASSERT_EQUAL(BINARY8(00110111), 55);
    MYUNIT_ASSERT_EQUAL(BINARY8(01111011), 123);
    MYUNIT_ASSERT_EQUAL(BINARY8(11110110), 246);
    MYUNIT_ASSERT_EQUAL(BINARY8(10110001), 177);
    MYUNIT_ASSERT_EQUAL(BINARY8(10001010), 138);
    MYUNIT_ASSERT_EQUAL(BINARY8(11111100), 252);
    MYUNIT_ASSERT_EQUAL(BINARY8(10001100), 140);
    MYUNIT_ASSERT_EQUAL(BINARY8(00011101), 29);
    MYUNIT_ASSERT_EQUAL(BINARY8(11111101), 253);
    MYUNIT_ASSERT_EQUAL(BINARY8(11010110), 214);
    MYUNIT_ASSERT_EQUAL(BINARY8(00010010), 18);
    MYUNIT_ASSERT_EQUAL(BINARY8(11001010), 202);
    MYUNIT_ASSERT_EQUAL(BINARY8(00001110), 14);
    MYUNIT_ASSERT_EQUAL(BINARY8(00101100), 44);
    MYUNIT_ASSERT_EQUAL(BINARY8(11010010), 210);

    // POSTCONDITIONS:
    // -------------------------------------------------

}


MYUNIT_TESTCASE(BINARY16)
{
    // PRECONDITIONS:
    // -------------------------------------------------


    // EXECUTE TESTCASE:
    // -------------------------------------------------

    MYUNIT_ASSERT_EQUAL(BINARY16(0,0), 0);
    MYUNIT_ASSERT_EQUAL(BINARY16(00,00), 0);
    MYUNIT_ASSERT_EQUAL(BINARY16(000,000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY16(0000,0000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY16(00000,00000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY16(000000,000000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY16(0000000,0000000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY16(00000000,00000000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY16(000,0000000), 0);

    MYUNIT_ASSERT_EQUAL(BINARY16(11111111,11111111), UINT16_MAX);

    MYUNIT_ASSERT_EQUAL(BINARY16(01010110,11000101), 22213);
    MYUNIT_ASSERT_EQUAL(BINARY16(00001100,00101010), 3114);
    MYUNIT_ASSERT_EQUAL(BINARY16(01011011,11101011), 23531);
    MYUNIT_ASSERT_EQUAL(BINARY16(01101001,10110101), 27061);
    MYUNIT_ASSERT_EQUAL(BINARY16(01001011,00101111), 19247);
    MYUNIT_ASSERT_EQUAL(BINARY16(00100011,00110111), 9015);
    MYUNIT_ASSERT_EQUAL(BINARY16(11010000,01000101), 53317);
    MYUNIT_ASSERT_EQUAL(BINARY16(00001100,00010001), 3089);
    MYUNIT_ASSERT_EQUAL(BINARY16(00001010,01111101), 2685);
    MYUNIT_ASSERT_EQUAL(BINARY16(01110110,00101111), 30255);
    MYUNIT_ASSERT_EQUAL(BINARY16(10111100,10011010), 48282);
    MYUNIT_ASSERT_EQUAL(BINARY16(11100101,10000011), 58755);
    MYUNIT_ASSERT_EQUAL(BINARY16(01010111,11101100), 22508);
    MYUNIT_ASSERT_EQUAL(BINARY16(00100001,10011111), 8607);
    MYUNIT_ASSERT_EQUAL(BINARY16(00110011,00110000), 13104);
    MYUNIT_ASSERT_EQUAL(BINARY16(01101010,11001010), 27338);
    MYUNIT_ASSERT_EQUAL(BINARY16(11110100,11000001), 62657);
    MYUNIT_ASSERT_EQUAL(BINARY16(00110100,00110000), 13360);
    MYUNIT_ASSERT_EQUAL(BINARY16(00101010,01110001), 10865);
    MYUNIT_ASSERT_EQUAL(BINARY16(10011101,00110101), 40245);

    // POSTCONDITIONS:
    // -------------------------------------------------
}



MYUNIT_TESTCASE(BINARY32)
{
    // PRECONDITIONS:
    // -------------------------------------------------


    // EXECUTE TESTCASE:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(BINARY32(0,0,0,0), 0);
    MYUNIT_ASSERT_EQUAL(BINARY32(00,00,00,00), 0);
    MYUNIT_ASSERT_EQUAL(BINARY32(000,000,000,000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY32(0000,0000,0000,0000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY32(00000,00000,00000,00000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY32(000000,000000,000000,000000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY32(0000000,0000000,0000000,0000000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY32(00000000,00000000,00000000,00000000), 0);
    MYUNIT_ASSERT_EQUAL(BINARY32(00,0000,000000,00000000), 0);


    MYUNIT_ASSERT_EQUAL(BINARY32(11111111,11111111,11111111,11111111), UINT32_MAX);


    MYUNIT_ASSERT_EQUAL(BINARY32(10111001,00100010,01111100,10111111), 3106045119);
    MYUNIT_ASSERT_EQUAL(BINARY32(11110111,11111011,11100101,01000011), 4160480579);
    MYUNIT_ASSERT_EQUAL(BINARY32(00000101,01111010,10110010,01100001), 91927137);
    MYUNIT_ASSERT_EQUAL(BINARY32(11010000,11010011,10111011,01111101), 3503537021);
    MYUNIT_ASSERT_EQUAL(BINARY32(11111111,00010110,10111011,10011111), 4279679903);
    MYUNIT_ASSERT_EQUAL(BINARY32(01110001,10101010,10010111,00001000), 1907005192);
    MYUNIT_ASSERT_EQUAL(BINARY32(10110010,11110110,10010100,10011011), 3002504347);
    MYUNIT_ASSERT_EQUAL(BINARY32(11011011,11010101,10111111,11000001), 3688218561);
    MYUNIT_ASSERT_EQUAL(BINARY32(00110010,00101100,00000001,11010100), 841744852);
    MYUNIT_ASSERT_EQUAL(BINARY32(01000100,10101000,10111001,01111110), 1151908222);
    MYUNIT_ASSERT_EQUAL(BINARY32(01010000,10001010,00100110,01011101), 1351231069);
    MYUNIT_ASSERT_EQUAL(BINARY32(10100010,01110010,11000010,11011110), 2725429982);
    MYUNIT_ASSERT_EQUAL(BINARY32(00111010,10011001,00000110,10100010), 983107234);
    MYUNIT_ASSERT_EQUAL(BINARY32(01111001,00010001,01010000,00110101), 2031177781);
    MYUNIT_ASSERT_EQUAL(BINARY32(10110000,00000100,00000110,01011011), 2953053787);
    MYUNIT_ASSERT_EQUAL(BINARY32(11110011,01011000,11010000,01010101), 4082683989);
    MYUNIT_ASSERT_EQUAL(BINARY32(00010100,10110010,00101111,11011000), 347221976);
    MYUNIT_ASSERT_EQUAL(BINARY32(01110101,01001011,10001100,11011111), 1967885535);
    MYUNIT_ASSERT_EQUAL(BINARY32(11100101,01110110,11011011,11000010), 3849771970);
    MYUNIT_ASSERT_EQUAL(BINARY32(01111011,01000111,11010011,00111101), 2068304701);


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



MYUNIT_TESTSUITE(binary)
{
    MYUNIT_TESTSUITE_BEGIN();

    MYUNIT_EXEC_TESTCASE(test_binary_numbers_size);
    MYUNIT_EXEC_TESTCASE(test_binary_value_matches_index);

    MYUNIT_EXEC_TESTCASE(BINARY8);
    MYUNIT_EXEC_TESTCASE(BINARY16);
    MYUNIT_EXEC_TESTCASE(BINARY32);

    MYUNIT_TESTSUITE_END();
}
