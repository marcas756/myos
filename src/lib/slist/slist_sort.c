/*! \copyright
    Copyright (c) 2015, marcas756@gmail.com.
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
    \file   slist_sort.c

    \brief

    \details
*/

#include "slist.h"

#if DEBUG_SLIST
#define DBG(args) DEBUG_PRINTF(args)
#else
#define DBG(args)
#endif


void slist_sort(slist_t* slist, item_compare_t compare)
{
    slist_node_t *iterator;
    slist_node_t *largest;
    slist_t sorted;

    slist_init(&sorted);

    DBG(("SLIST !!! \n"));

    while(slist->head)
    {
        largest = iterator = slist->head;

        while(iterator)
        {
            if(compare(slist_item(iterator),slist_item(largest)) != ITEM_LESS_THAN)
            {
                largest = iterator;
            }

            iterator = iterator->next;
        }


        slist_erase(slist,largest);
        slist_push_front(&sorted,largest);
    }

    *slist = sorted;
}
