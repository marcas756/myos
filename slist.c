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
    \file       slist.h

    \brief      Circular singly linked list

    \details    In computer science, a linked list is a linear collection of data elements,
                whose order is not given by their physical placement in memory.
                Instead, each element points to the next. It is a data structure consisting
                of a collection of nodes which together represent a sequence. In its most basic form,
                each node contains: data, and a reference (in other words, a link) to the next node
                in the sequence. This structure allows for efficient insertion or removal of elements
                from any position in the sequence during iteration.
                [https://en.wikipedia.org/wiki/Linked_list]

                Singly linked lists contain nodes which have a data field as well as 'next' field,
                which points to the next node in line of nodes. Operations that can be performed on
                singly linked lists include insertion, deletion and traversal.
                [https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list]

                In the last node of a list, the link field often contains a null reference, a
                special value is used to indicate the lack of further nodes. A less common convention
                is to make it point to the first node of the list; in that case, the list is said to
                be 'circular' or 'circularly linked'; otherwise, it is said to be 'open' or 'linear'.
                It is a list where the last pointer points to the first node.
                [https://en.wikipedia.org/wiki/Linked_list#Circular_linked_list]
*/

#include <stdlib.h>
#include "slist.h"

slist_node_t* slist_find(slist_t *slist, void *node)
{
   slist_node_t* iterator;

   slist_foreach(slist,iterator)
   {
       if ( iterator == node )
       {
           return node;
       }
   }

   return NULL;
}

slist_node_t* slist_back(slist_t* slist)
{
    slist_node_t *iterator = slist_end(slist);

    while( slist_next(slist,iterator) != slist_end(slist) )
    {
        iterator = slist_next(slist,iterator);
    }

    return iterator;
}



void slist_pop_back(slist_t *slist)
{
    slist_node_t *iterator = slist_end(slist);

    while( iterator->next->next != slist_end(slist) )
    {
        iterator = slist_next(slist,iterator);
    }

    iterator->next = slist_end(slist);
}



slist_node_t* slist_prev(slist_t *slist, void* node)
{
    slist_node_t *iterator = node;

    while( slist_next(slist,iterator) != node )
    {
        iterator = slist_next(slist,iterator);
    }

    return iterator;
}


size_t slist_size(slist_t *slist)
{
    slist_node_t *iterator;
    size_t size = 0;

    slist_foreach(slist,iterator)
    {
        size++;
    }

    return size;
}


