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
   \file      bitarray.h

   \brief     Bit array header file

   \details   This file defines a bit array data structure and associated macros
              for efficient manipulation of individual bits. It provides a
              compact way to store and manage boolean flags or other
              single-bit information.
*/

#ifndef BITARRAY_H_
#define BITARRAY_H_
#include <stdint.h>
#include <string.h>


#define BITARRAY_RESET_STATE    0
#define BITARRAY_SET_STATE      1

typedef uint8_t bitarray_t;

/*!
  \brief Defines a bit array with a specified name and size.
  \details Creates a bit array to store a specified number of bits.

  \param name The name of the bit array.
  \param size The number of bits in the bit array.
*/
#define BITARRAY(name,size) \
    bitarray_t name##_bitarray[((size)+7)>>3]




/*!
  \brief Calculates the total number of bits in a bit array.
  \details Determines the size of the bit array (in bits) based on its name.

  \param name The name of the bit array.

  \return The total number of bits in the bit array.
*/
#define BITARRAY_SIZE(name) \
    ((sizeof(name##_bitarray)/sizeof(name##_bitarray[0]))<<3)

/*!
 \brief Initializes a bit array to all zeros.
 \details Sets all bits in the specified bit array to 0.

 \param name The name of the bit array to initialize.
*/
#define BITARRAY_INIT(name) \
    memset(name##_bitarray,0x00,sizeof(name##_bitarray))

/*!
 \brief Sets a specific bit in a bit array to 1.
 \details Sets the bit at the specified index in the bit array to 1, leaving other bits unchanged.

 \param name The name of the bit array.
 \param bit The index of the bit to set (0-based).
*/
#define BITARRAY_SET(name,bit) \
    name##_bitarray[((unsigned)(bit))>>3] |= (1<<(((unsigned)(bit))&0x07))

/*!
 \brief Resets a specific bit in a bit array to 0.
 \details Sets the bit at the specified index in the bit array to 0, leaving other bits unchanged.

 \param name The name of the bit array.
 \param bit The index of the bit to reset (0-based).
*/
#define BITARRAY_RESET(name,bit) \
    name##_bitarray[((unsigned)(bit))>>3] &= ~(1<<(((unsigned)(bit))&0x07))

/*!
 \brief Gets the value of a specific bit in a bit array.
 \details Returns 1 if the bit at the specified index is set, and 0 otherwise.

 \param name The name of the bit array.
 \param bit The index of the bit to get (0-based).

 \return 1 if the bit is set, 0 otherwise.
*/
#define BITARRAY_GET(name,bit) \
    ((unsigned)((name##_bitarray[((unsigned)(bit))>>3] & ((1<<(((unsigned)(bit))&0x07)))) > 0))



/*!
 \brief Toggles the value of a specific bit in a bit array.
 \details Flips the bit at the specified index in the bit array (0 becomes 1, and 1 becomes 0).

 \param name The name of the bit array.
 \param bit The index of the bit to toggle (0-based).
*/
#define BITARRAY_TOGGLE(name,bit) \
     name##_bitarray[((unsigned)(bit))>>3] ^= (1<<(((unsigned)(bit))&0x07))

/*!
 \brief Sets the value of a specific bit in a bit array.
 \details Sets the bit at the specified index to either 0 or 1.

 \param name The name of the bit array.
 \param bit The index of the bit to set (0-based).
 \param value The value to set the bit to (0 or non-zero).
*/
#define BITARRAY_SET_VALUE(name,bit,value) \
    do{if((value) == 0){BITARRAY_RESET(name,bit);}else{BITARRAY_SET(name,bit);}}while(0)


#endif /* BITARRAY_H_ */
