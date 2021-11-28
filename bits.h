/*! \copyright
 
   https://opensource.org/licenses/BSD-3-Clause
 
   Copyright 2013-2021 Marco Bacchi <marco@bacchi.at>
   
   Redistribution and use in source and binary forms, with or without 
   modification, are permitted provided that the following conditions are met:
   
   1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.
   
   2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

   3. Neither the name of the copyright holder nor the names of its 
   contributors may be used to endorse or promote products derived from this 
   software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
   POSSIBILITY OF SUCH DAMAGE.
*/


/*!
    \file       bits.h

    \brief      Provides preprocessor macros for bit manipulations



    \details    Bit field

                A bit field is termed an unsigned integer in which single bits or
                group of bits are stringed together. It represents a kind of compound
                data type on bit level, in contrast to primitive data types, where the
                value is build by interpreting all positions of the primitive data type together.

                A bit field is always embedded in the data type of the binary number (in contrast to bit arrays).


                Bit mask

                Accessing a single bit, either in reading or writing manner,
                is supported by hardware in a similar way like accessing a
                byte or word - it will do with only one command for most machines.

                But support through compiler is often similar to an access on several
                bits, where a bit group has to be "removed" from the variable word before
                comparison or manipulation. This is done by using a a so called bit mask
                and some elementary boolean bit operations.

                Bit masks are called bit fields that do not represent any information themselves,
                but are used to read out or manipulate bit fields.


                Source: https://de.wikipedia.org/wiki/Bitfeld
                Source: https://de.wikipedia.org/wiki/Bitkette
*/
#ifndef BITS_H_
#define BITS_H_

/*!
     \brief     Read out bits from bit field by using a bit mask

     \details   To read out one or more specific bits of a bit field, it is logically AND-ed with a bit mask.

                Example

                1-Bit:

                    01001011 bit field
                AND 00001000 bit mask
                -------------
                =   00001000 result

                0-Bit:

                    01001011 bit field
                AND 00000100 bit mask
                -------------
                =   00000000 result
*/
#define BITS(x,m)           ((x)&(m))

/*!
     \brief Toggle all bits of integer
*/
#define BITS_INVERT(x)      (~x)

/*!
     \brief     Test if all of the bits defined by bit mask are set in the bit field
*/
#define BITS_TEST(x,m)      (((x)&(m))==(m)))

/*!
     \brief     Set bits defined by bit mask to logical 1 in bit field
     \details   To set one or more specific bits of a bit field, it is logically
                OR-ed with a bit mask defining the bits to be set.

                Example

                Set bits to  „1“:

                    01001011 bit field
                OR  00000100 bit mask
                -------------
                =   01001111 result

*/
#define BITS_SET(x,m)       ((x)|=(m))

/*!
    \brief      Set bits defined by bit mask to logical 0 in bit field
    \details    To clear one or more specific bits of a bit field, it is logically
                NAND-ed with a bit mask defining the bits to be cleared.

                Set bits to „0“:

                NOT 00001000 bit mask
                -------------
                =   11110111 inverted bit mask
                AND 01001011 bit field
                -------------
                =   01000011 result
*/
#define BITS_CLEAR(x,m)     ((x)&= ~(m))

/*!
    \brief      Toggle bits in bit field as defined by bit mask.
    \details    To toggle one or more specific bits of a bit field, it is logically
                XOR-ed with a bit mask defining the bits to be toggled.

                    01001011 bit field
                XOR 00000110 bit mask
                -------------
                =   01001101 result
*/
#define BITS_TOGGLE(x,m)    ((x)^=(m))

#endif /* BITS_H_ */
