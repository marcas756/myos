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
 \file	    bitarray.h

 \brief

 \details
 */
#ifndef BITARRAY_H_
#define BITARRAY_H_
#include <stdint.h> /* uint8_t */
#include <string.h> /* memset */


#define BITARRAY_RESET_STATE    0
#define BITARRAY_SET_STATE      1

typedef uint8_t bitarray_t;


/*!
    \brief      Defines an bit array

    \param      name        Name of the bit array
    \param      size        Minimum number of bits required
*/
#define BITARRAY(name,size) \
    bitarray_t name##_bitarray[((size)+7)>>3]

#define BITARRAY_INIT(name) \
    memset(name##_bitarray,0x00,sizeof(name##_bitarray))




/*!
    \brief      Size of array in bits
    \details    Returns the size of a bit array in bits.
                The size is expressed as a multiple of 8.
    \param      name        Name of the bit array

*/
#define BITARRAY_SIZE(name) \
    ((sizeof(name##_bitarray)/sizeof(name##_bitarray[0]))<<3)
/*!
    \brief      Get a specific bit

    \param      name        Name of the bit array
    \param      bit         Specific bit index

    \return     Value of the specific bit. Either 0 or 1.
*/
#define BITARRAY_GET(name,bit) \
    ((unsigned)((name##_bitarray[((unsigned)(bit))>>3] & ((1<<(((unsigned)(bit))&0x07)))) > 0))


/*!
    \brief      Set a specific bit to 1

    \param      name        Name of the bit array
    \param      bit         Specific bit index


*/
#define BITARRAY_SET(name,bit) \
    name##_bitarray[((unsigned)(bit))>>3] |= (1<<(((unsigned)(bit))&0x07))

/*!
    \brief      Reset a specific bit to 0

    \param      name        Name of the bit array
    \param      bit         Specific bit index
*/
#define BITARRAY_RESET(name,bit) \
    name##_bitarray[((unsigned)(bit))>>3] &= ~(1<<(((unsigned)(bit))&0x07))

/*!
    \brief      Toggle a specific bit

    \param      name        Name of the bit array
    \param      bit         Specific bit index
*/
#define BITARRAY_TOGGLE(name,bit) \
     name##_bitarray[((unsigned)(bit))>>3] ^= (1<<(((unsigned)(bit))&0x07))

/*!
    \brief      Toggle a specific bit

    \param      name        Name of the bit array
    \param      bit         Specific bit index
*/
#define BITARRAY_SET_VALUE(name,bit,value) \
    do{if((value) == 0){BITARRAY_RESET(name,bit);}else{BITARRAY_SET(name,bit);}}while(0)


#endif /* BITARRAY_H_ */
