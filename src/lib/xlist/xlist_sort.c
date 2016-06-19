/*! \copyright
    Copyright (c) 2013, marcas756@gmail.com.
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
    \file   xlist_sort.c

    \brief

    \details
*/

#include "xlist.h"

void xlist_sort(xlist_t* xlist, item_compare_t compare)
{
    xlist_node_t *iterator;
    xlist_node_t *largest,*next,*prev,*largest_prev=NULL;
    xlist_t sorted;

    xlist_init(&sorted);

    while(xlist->head)
    {
        largest = iterator = xlist->head;
        prev = NULL;

        while(iterator)
        {
            if(compare(xlist_item(iterator),xlist_item(largest)) != ITEM_LESS_THAN)
            {
                largest = iterator;
                largest_prev = prev;
            }

            next = xlist_xor(prev,iterator->nextprev);
            prev = iterator;
            iterator = next;
        }

        /* manually erase largest node */
        if (largest == xlist->head)
        {
            xlist_pop_front(xlist);
        }
        else  if (largest == xlist->tail)
        {
            xlist_pop_back(xlist);
        }
        else
        {
            next = xlist_xor(((xlist_node_t*)largest)->nextprev,largest_prev);

            largest_prev->nextprev = xlist_xor(xlist_xor(largest_prev->nextprev,largest),next);
            next->nextprev = xlist_xor(xlist_xor(next->nextprev,largest),largest_prev);
        }

        xlist_push_front(&sorted,largest);
    }

    *xlist = sorted;
}
