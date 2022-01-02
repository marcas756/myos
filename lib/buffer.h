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
	\file	buffer.h

    \brief

    \details
*/

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>
#include <stddef.h>



/*!
    Declares a buffer type. The argumnents are \a name for a unique identification
    of the buffer type, the \a type of the items and the number of items of \a type
    the buffer can hold (\a size).
*/
#define BUFFER_TYPEDEF(name,type,size)  \
    typedef struct {                    \
            size_t count;               \
            type items [size];          \
    } name##_buffer_t


/*!
     Defines a buffer of type \a name. Can also be combined with different storage classifiers.
    (static, extern, volatile ...)
*/
#define BUFFER_T(name) \
    name##_buffer_t


/*!
    Returns a pointer to the buffer items.
    Type of returned pointer is of buffer item type.
*/
#define BUFFER_ITEMS(buffer) \
    ((buffer).items)

/*!
    Returns an pointer to the buffer items.
    Type of pointer is void.
*/
#define BUFFER_RAW(buffer) \
	((uint8_t*)BUFFER_ITEMS(buffer))

/*!
    Returns the size of the buffer in bytes.
*/
#define BUFFER_SIZEOF(buffer) \
    (sizeof(BUFFER_ITEMS(buffer)))


/*!
     Returns the maximum number of items the buffer can hold.
*/
#define BUFFER_SIZE(buffer) \
    (BUFFER_SIZEOF(buffer)/sizeof(BUFFER_ITEMS(buffer)[0]))

/*!
    Returns the current number of items used in the buffer.
*/
#define BUFFER_COUNT(buffer) \
    ((buffer).count)

/*!
    Initializes the buffer.
*/
#define BUFFER_INIT(buffer) \
    do{BUFFER_COUNT(buffer)=0;}while(0)


/*!
    Checks if no further buffer items are available.
    Returns 1 if buffer is full, otherwise 0.
*/
#define BUFFER_FULL(buffer) \
    (BUFFER_COUNT(buffer)>=BUFFER_SIZE(buffer))

/*!
    Checks if the buffer has no items stored.
    Returns 1 if buffer is empty, otherwise 0.
*/
#define BUFFER_EMPTY(buffer) \
    (!BUFFER_COUNT(buffer))
/*!
    Moves to next free item in the buffer.
    It does not check for buffer overflow.
    In case of buffer overflow the behaviour is undefined.
    Use BUFFER_FULL to check if buffer is full before using this macro.
*/
#define BUFFER_NEXT(buffer) \
    (++BUFFER_COUNT(buffer))

/*!
    Returns the current free item by value.
*/
#define BUFFER_VAL(buffer) \
    (BUFFER_ITEMS(buffer)[BUFFER_COUNT(buffer)])

/*!
    Returns a pointer to the current free item.
*/
#define BUFFER_PTR(buffer) \
    (&BUFFER_VAL(buffer))

/*!
    Append an item to the buffer by value.
    Automatically increases the buffer count.
    It does not check for buffer overflow.
    In case of buffer overflow the behaviour is undefined.
    Use BUFFER_FULL to check if buffer is full before using this macro.
*/
#define BUFFER_APPEND(buffer,item) \
	do{BUFFER_VAL(buffer) = item; BUFFER_NEXT(buffer);}while(0)


#endif /* BUFFER_H_ */
