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
    \file binary.h

    \brief Provides utilities for converting binary strings into numerical values.

    This header file defines macros for converting 8-bit, 16-bit, and 32-bit binary string representations
    into their corresponding integer values. It includes definitions for binary digit macros (b0 to b11111111)
    that facilitate these conversions. The provided functions are useful in contexts where binary data needs
    to be manipulated or interpreted as numerical values.
*/
#ifndef BINARY_H_
#define BINARY_H_

#include <stdint.h>



#define BINARY8(val) (((uint8_t)(b##val))&0xFF)


/*!
    \brief Converts an 8-bit binary value into its corresponding 8-bit numerical value.

    This macro takes a sequence of characters representing an 8-bit binary number (e.g., '10101100')
    and converts it to the equivalent 8-bit integer.

    \param val A sequence of up to 8 binary digits, representing an 8-bit number.

    \return An 8-bit integer that corresponds to the input binary string.
*/
#define BINARY16(val1,val2) \
    ((((uint16_t)BINARY8(val1))<<8)|((uint16_t)BINARY8(val2)))


/*!
    \brief Combines four 8-bit binary values into a single 32-bit value.

    This macro constructs a 32-bit integer from four 8-bit values by shifting and combining them.
    It shifts each of the four bytes to its correct position within the final 32-bit result before using bitwise OR to combine them.

    \param val1 The most significant byte for the final 32-bit value.
    \param val2 The second most significant byte for the final 32-bit value.
    \param val3 The third byte for the final 32-bit value.
    \param val4 The least significant byte for the final 32-bit value.

    \return A 32-bit integer constructed from four 8-bit values.
*/
#define BINARY32(val1,val2,val3,val4) \
    ((((uint32_t)BINARY16(val1,val2))<<16)|((uint32_t)BINARY16(val3,val4)))

/* 1 bit */
#define b0  0x0
#define b1  0x1

/* 2 bits */
#define b00 0x0
#define b01 0x1
#define b10 0x2
#define b11 0x3

/* 3 bits */
#define b000    0x0
#define b001    0x1
#define b010    0x2
#define b011    0x3
#define b100    0x4
#define b101    0x5
#define b110    0x6
#define b111    0x7

/* 4 bits (Nibble) */
#define b0000 0x0
#define b0001 0x1
#define b0010 0x2
#define b0011 0x3
#define b0100 0x4
#define b0101 0x5
#define b0110 0x6
#define b0111 0x7
#define b1000 0x8
#define b1001 0x9
#define b1010 0xA
#define b1011 0xB
#define b1100 0xC
#define b1101 0xD
#define b1110 0xE
#define b1111 0xF

/* 5 bits */
#define b00000 0x0
#define b00001 0x1
#define b00010 0x2
#define b00011 0x3
#define b00100 0x4
#define b00101 0x5
#define b00110 0x6
#define b00111 0x7
#define b01000 0x8
#define b01001 0x9
#define b01010 0xA
#define b01011 0xB
#define b01100 0xC
#define b01101 0xD
#define b01110 0xE
#define b01111 0xF
#define b10000 0x10
#define b10001 0x11
#define b10010 0x12
#define b10011 0x13
#define b10100 0x14
#define b10101 0x15
#define b10110 0x16
#define b10111 0x17
#define b11000 0x18
#define b11001 0x19
#define b11010 0x1A
#define b11011 0x1B
#define b11100 0x1C
#define b11101 0x1D
#define b11110 0x1E
#define b11111 0x1F


/* 6 bits */
#define b000000 0x0
#define b000001 0x1
#define b000010 0x2
#define b000011 0x3
#define b000100 0x4
#define b000101 0x5
#define b000110 0x6
#define b000111 0x7
#define b001000 0x8
#define b001001 0x9
#define b001010 0xA
#define b001011 0xB
#define b001100 0xC
#define b001101 0xD
#define b001110 0xE
#define b001111 0xF
#define b010000 0x10
#define b010001 0x11
#define b010010 0x12
#define b010011 0x13
#define b010100 0x14
#define b010101 0x15
#define b010110 0x16
#define b010111 0x17
#define b011000 0x18
#define b011001 0x19
#define b011010 0x1A
#define b011011 0x1B
#define b011100 0x1C
#define b011101 0x1D
#define b011110 0x1E
#define b011111 0x1F
#define b100000 0x20
#define b100001 0x21
#define b100010 0x22
#define b100011 0x23
#define b100100 0x24
#define b100101 0x25
#define b100110 0x26
#define b100111 0x27
#define b101000 0x28
#define b101001 0x29
#define b101010 0x2A
#define b101011 0x2B
#define b101100 0x2C
#define b101101 0x2D
#define b101110 0x2E
#define b101111 0x2F
#define b110000 0x30
#define b110001 0x31
#define b110010 0x32
#define b110011 0x33
#define b110100 0x34
#define b110101 0x35
#define b110110 0x36
#define b110111 0x37
#define b111000 0x38
#define b111001 0x39
#define b111010 0x3A
#define b111011 0x3B
#define b111100 0x3C
#define b111101 0x3D
#define b111110 0x3E
#define b111111 0x3F


/* 7 bits */
#define b0000000 0x0
#define b0000001 0x1
#define b0000010 0x2
#define b0000011 0x3
#define b0000100 0x4
#define b0000101 0x5
#define b0000110 0x6
#define b0000111 0x7
#define b0001000 0x8
#define b0001001 0x9
#define b0001010 0xA
#define b0001011 0xB
#define b0001100 0xC
#define b0001101 0xD
#define b0001110 0xE
#define b0001111 0xF
#define b0010000 0x10
#define b0010001 0x11
#define b0010010 0x12
#define b0010011 0x13
#define b0010100 0x14
#define b0010101 0x15
#define b0010110 0x16
#define b0010111 0x17
#define b0011000 0x18
#define b0011001 0x19
#define b0011010 0x1A
#define b0011011 0x1B
#define b0011100 0x1C
#define b0011101 0x1D
#define b0011110 0x1E
#define b0011111 0x1F
#define b0100000 0x20
#define b0100001 0x21
#define b0100010 0x22
#define b0100011 0x23
#define b0100100 0x24
#define b0100101 0x25
#define b0100110 0x26
#define b0100111 0x27
#define b0101000 0x28
#define b0101001 0x29
#define b0101010 0x2A
#define b0101011 0x2B
#define b0101100 0x2C
#define b0101101 0x2D
#define b0101110 0x2E
#define b0101111 0x2F
#define b0110000 0x30
#define b0110001 0x31
#define b0110010 0x32
#define b0110011 0x33
#define b0110100 0x34
#define b0110101 0x35
#define b0110110 0x36
#define b0110111 0x37
#define b0111000 0x38
#define b0111001 0x39
#define b0111010 0x3A
#define b0111011 0x3B
#define b0111100 0x3C
#define b0111101 0x3D
#define b0111110 0x3E
#define b0111111 0x3F
#define b1000000 0x40
#define b1000001 0x41
#define b1000010 0x42
#define b1000011 0x43
#define b1000100 0x44
#define b1000101 0x45
#define b1000110 0x46
#define b1000111 0x47
#define b1001000 0x48
#define b1001001 0x49
#define b1001010 0x4A
#define b1001011 0x4B
#define b1001100 0x4C
#define b1001101 0x4D
#define b1001110 0x4E
#define b1001111 0x4F
#define b1010000 0x50
#define b1010001 0x51
#define b1010010 0x52
#define b1010011 0x53
#define b1010100 0x54
#define b1010101 0x55
#define b1010110 0x56
#define b1010111 0x57
#define b1011000 0x58
#define b1011001 0x59
#define b1011010 0x5A
#define b1011011 0x5B
#define b1011100 0x5C
#define b1011101 0x5D
#define b1011110 0x5E
#define b1011111 0x5F
#define b1100000 0x60
#define b1100001 0x61
#define b1100010 0x62
#define b1100011 0x63
#define b1100100 0x64
#define b1100101 0x65
#define b1100110 0x66
#define b1100111 0x67
#define b1101000 0x68
#define b1101001 0x69
#define b1101010 0x6A
#define b1101011 0x6B
#define b1101100 0x6C
#define b1101101 0x6D
#define b1101110 0x6E
#define b1101111 0x6F
#define b1110000 0x70
#define b1110001 0x71
#define b1110010 0x72
#define b1110011 0x73
#define b1110100 0x74
#define b1110101 0x75
#define b1110110 0x76
#define b1110111 0x77
#define b1111000 0x78
#define b1111001 0x79
#define b1111010 0x7A
#define b1111011 0x7B
#define b1111100 0x7C
#define b1111101 0x7D
#define b1111110 0x7E
#define b1111111 0x7F

/* 8 bits (Byte) */
#define b00000000 0x00
#define b00000001 0x01
#define b00000010 0x02
#define b00000011 0x03
#define b00000100 0x04
#define b00000101 0x05
#define b00000110 0x06
#define b00000111 0x07
#define b00001000 0x08
#define b00001001 0x09
#define b00001010 0x0A
#define b00001011 0x0B
#define b00001100 0x0C
#define b00001101 0x0D
#define b00001110 0x0E
#define b00001111 0x0F
#define b00010000 0x10
#define b00010001 0x11
#define b00010010 0x12
#define b00010011 0x13
#define b00010100 0x14
#define b00010101 0x15
#define b00010110 0x16
#define b00010111 0x17
#define b00011000 0x18
#define b00011001 0x19
#define b00011010 0x1A
#define b00011011 0x1B
#define b00011100 0x1C
#define b00011101 0x1D
#define b00011110 0x1E
#define b00011111 0x1F
#define b00100000 0x20
#define b00100001 0x21
#define b00100010 0x22
#define b00100011 0x23
#define b00100100 0x24
#define b00100101 0x25
#define b00100110 0x26
#define b00100111 0x27
#define b00101000 0x28
#define b00101001 0x29
#define b00101010 0x2A
#define b00101011 0x2B
#define b00101100 0x2C
#define b00101101 0x2D
#define b00101110 0x2E
#define b00101111 0x2F
#define b00110000 0x30
#define b00110001 0x31
#define b00110010 0x32
#define b00110011 0x33
#define b00110100 0x34
#define b00110101 0x35
#define b00110110 0x36
#define b00110111 0x37
#define b00111000 0x38
#define b00111001 0x39
#define b00111010 0x3A
#define b00111011 0x3B
#define b00111100 0x3C
#define b00111101 0x3D
#define b00111110 0x3E
#define b00111111 0x3F
#define b01000000 0x40
#define b01000001 0x41
#define b01000010 0x42
#define b01000011 0x43
#define b01000100 0x44
#define b01000101 0x45
#define b01000110 0x46
#define b01000111 0x47
#define b01001000 0x48
#define b01001001 0x49
#define b01001010 0x4A
#define b01001011 0x4B
#define b01001100 0x4C
#define b01001101 0x4D
#define b01001110 0x4E
#define b01001111 0x4F
#define b01010000 0x50
#define b01010001 0x51
#define b01010010 0x52
#define b01010011 0x53
#define b01010100 0x54
#define b01010101 0x55
#define b01010110 0x56
#define b01010111 0x57
#define b01011000 0x58
#define b01011001 0x59
#define b01011010 0x5A
#define b01011011 0x5B
#define b01011100 0x5C
#define b01011101 0x5D
#define b01011110 0x5E
#define b01011111 0x5F
#define b01100000 0x60
#define b01100001 0x61
#define b01100010 0x62
#define b01100011 0x63
#define b01100100 0x64
#define b01100101 0x65
#define b01100110 0x66
#define b01100111 0x67
#define b01101000 0x68
#define b01101001 0x69
#define b01101010 0x6A
#define b01101011 0x6B
#define b01101100 0x6C
#define b01101101 0x6D
#define b01101110 0x6E
#define b01101111 0x6F
#define b01110000 0x70
#define b01110001 0x71
#define b01110010 0x72
#define b01110011 0x73
#define b01110100 0x74
#define b01110101 0x75
#define b01110110 0x76
#define b01110111 0x77
#define b01111000 0x78
#define b01111001 0x79
#define b01111010 0x7A
#define b01111011 0x7B
#define b01111100 0x7C
#define b01111101 0x7D
#define b01111110 0x7E
#define b01111111 0x7F
#define b10000000 0x80
#define b10000001 0x81
#define b10000010 0x82
#define b10000011 0x83
#define b10000100 0x84
#define b10000101 0x85
#define b10000110 0x86
#define b10000111 0x87
#define b10001000 0x88
#define b10001001 0x89
#define b10001010 0x8A
#define b10001011 0x8B
#define b10001100 0x8C
#define b10001101 0x8D
#define b10001110 0x8E
#define b10001111 0x8F
#define b10010000 0x90
#define b10010001 0x91
#define b10010010 0x92
#define b10010011 0x93
#define b10010100 0x94
#define b10010101 0x95
#define b10010110 0x96
#define b10010111 0x97
#define b10011000 0x98
#define b10011001 0x99
#define b10011010 0x9A
#define b10011011 0x9B
#define b10011100 0x9C
#define b10011101 0x9D
#define b10011110 0x9E
#define b10011111 0x9F
#define b10100000 0xA0
#define b10100001 0xA1
#define b10100010 0xA2
#define b10100011 0xA3
#define b10100100 0xA4
#define b10100101 0xA5
#define b10100110 0xA6
#define b10100111 0xA7
#define b10101000 0xA8
#define b10101001 0xA9
#define b10101010 0xAA
#define b10101011 0xAB
#define b10101100 0xAC
#define b10101101 0xAD
#define b10101110 0xAE
#define b10101111 0xAF
#define b10110000 0xB0
#define b10110001 0xB1
#define b10110010 0xB2
#define b10110011 0xB3
#define b10110100 0xB4
#define b10110101 0xB5
#define b10110110 0xB6
#define b10110111 0xB7
#define b10111000 0xB8
#define b10111001 0xB9
#define b10111010 0xBA
#define b10111011 0xBB
#define b10111100 0xBC
#define b10111101 0xBD
#define b10111110 0xBE
#define b10111111 0xBF
#define b11000000 0xC0
#define b11000001 0xC1
#define b11000010 0xC2
#define b11000011 0xC3
#define b11000100 0xC4
#define b11000101 0xC5
#define b11000110 0xC6
#define b11000111 0xC7
#define b11001000 0xC8
#define b11001001 0xC9
#define b11001010 0xCA
#define b11001011 0xCB
#define b11001100 0xCC
#define b11001101 0xCD
#define b11001110 0xCE
#define b11001111 0xCF
#define b11010000 0xD0
#define b11010001 0xD1
#define b11010010 0xD2
#define b11010011 0xD3
#define b11010100 0xD4
#define b11010101 0xD5
#define b11010110 0xD6
#define b11010111 0xD7
#define b11011000 0xD8
#define b11011001 0xD9
#define b11011010 0xDA
#define b11011011 0xDB
#define b11011100 0xDC
#define b11011101 0xDD
#define b11011110 0xDE
#define b11011111 0xDF
#define b11100000 0xE0
#define b11100001 0xE1
#define b11100010 0xE2
#define b11100011 0xE3
#define b11100100 0xE4
#define b11100101 0xE5
#define b11100110 0xE6
#define b11100111 0xE7
#define b11101000 0xE8
#define b11101001 0xE9
#define b11101010 0xEA
#define b11101011 0xEB
#define b11101100 0xEC
#define b11101101 0xED
#define b11101110 0xEE
#define b11101111 0xEF
#define b11110000 0xF0
#define b11110001 0xF1
#define b11110010 0xF2
#define b11110011 0xF3
#define b11110100 0xF4
#define b11110101 0xF5
#define b11110110 0xF6
#define b11110111 0xF7
#define b11111000 0xF8
#define b11111001 0xF9
#define b11111010 0xFA
#define b11111011 0xFB
#define b11111100 0xFC
#define b11111101 0xFD
#define b11111110 0xFE
#define b11111111 0xFF


#endif /* BINARY_H_ */
