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
    \file       itempool.c

    \brief      Provides utilities for managing a pool of pre-allocated items.

    \details    see header file
*/

#include "itempool.h"

void* itempool_alloc(uint8_t* items, uint8_t* status, size_t itemsize, size_t poolsize)
{
    size_t tmp;
	
    for (tmp=0; tmp < poolsize; tmp++)
    {
        if (status[tmp] == ITEMPOOL_ITEM_FREE)
        {
            status[tmp] =  ITEMPOOL_ITEM_USED;
            return items;
        }
        items+=itemsize;
    }

    return NULL;
}


void* itempool_calloc(uint8_t* items, uint8_t* status, size_t itemsize, size_t poolsize)
{
    items = itempool_alloc(items,status,itemsize,poolsize);

    if (items)
    {
        memset(items,0x00,itemsize);
    }

    return items;
}

