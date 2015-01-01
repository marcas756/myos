/*! \copyright
    Copyright (c) 2014, marcas756@gmail.com.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. The name of the author may not be used to endorse or promote
       products derived from this software without specific prior
       written permission.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
    GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/*!
    \file   itempool.h

    \brief

    \details
*/
#ifndef ITEMPOOL_H_
#define ITEMPOOL_H_

#include "item.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define ITEMPOOL_ITEM_FREE 0
#define ITEMPOOL_ITEM_USED 1

#define ITEMPOOL_TYPEDEF(name,type,size) \
    typedef struct { \
        uint8_t status[size]; \
        type items[size]; \
    }name##_itempool_t;

#define ITEMPOOL_T(name) \
    name##_itempool_t

#define ITEMPOOL_INIT(itempool) \
        memset(ITEMPOOL_STATUS(itempool), \
               ITEMPOOL_ITEM_FREE, \
               ITEMPOOL_SIZE(itempool))

#define ITEMPOOL_SIZE(itempool) \
    (sizeof(ITEMPOOL_STATUS(itempool))/ \
     sizeof(*ITEMPOOL_STATUS(itempool)))

#define ITEMPOOL_ITEM_SIZE(itempool) \
    (sizeof(*ITEMPOOL_ITEMS(itempool)))

#define ITEMPOOL_STATUS(itempool) \
        ((itempool).status)

#define ITEMPOOL_ITEMS(itempool) \
        ((itempool).items)

#define ITEMPOOL_ALLOC(itempool) \
    itempool_alloc( \
        (uint8_t*)ITEMPOOL_ITEMS(itempool), \
        ITEMPOOL_STATUS(itempool), \
        ITEMPOOL_ITEM_SIZE(itempool), \
        ITEMPOOL_SIZE(itempool))

#define ITEMPOOL_CALLOC(itempool) \
    itempool_calloc( \
        (uint8_t*)ITEMPOOL_ITEMS(itempool), \
        ITEMPOOL_STATUS(itempool), \
        ITEMPOOL_ITEM_SIZE(itempool), \
        ITEMPOOL_SIZE(itempool))


/*
 ITEMPOOL_FREE(pool,tmp);
 00445C    4A0F               mov.w   R10,R15
 00445E    803F 1C06          sub.w   #0x1C06,R15
 004462    035F               rrum.w  #1,R15
 004464    43CF 1C00          clr.b   0x1C00(R15)
 */
#define ITEMPOOL_FREE(itempool,itemptr) \
        do{ITEMPOOL_STATUS(itempool) \
            [((uint8_t*)itemptr-(uint8_t*)ITEMPOOL_ITEMS(itempool))/ \
             ITEMPOOL_ITEM_SIZE(itempool)] \
             =ITEMPOOL_ITEM_FREE;}while(0)


item_t* itempool_alloc(uint8_t* items, uint8_t* status, size_t itemsize, size_t poolsize);
item_t* itempool_calloc(uint8_t* items, uint8_t* status, size_t itemsize, size_t poolsize);

#endif /* ITEMPOOL_H_ */
