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
    \file   xlist.c

    \brief

    \details
*/

#include "xlist.h"

xlist_node_t* xlist_find(xlist_t* xlist, void* node)
{
    xlist_node_t *iterator = xlist->head;
    xlist_node_t *prev = NULL;
    xlist_node_t *next;


    while(iterator)
    {
        if (iterator == node) return iterator;
        next = xlist_xor(prev,iterator->nextprev);
        prev = iterator;
        iterator = next;
    }

    return iterator;
}


xlist_node_t* xlist_next(xlist_t* xlist, xlist_node_t* node)
{
    xlist_node_t *iterator = xlist->head;
    xlist_node_t *prev = NULL;
    xlist_node_t *next;


    while(iterator)
    {
        next = xlist_xor(prev,iterator->nextprev);

        if (iterator == node) return next;

        prev = iterator;
        iterator = next;
    }

    return NULL;
}

xlist_node_t* xlist_prev(xlist_t* xlist, xlist_node_t* node)
{
    xlist_node_t *iterator = xlist->head;
    xlist_node_t *prev = NULL;
    xlist_node_t *next;


    while(iterator)
    {
        if (iterator == node) return prev;
        next = xlist_xor(prev,iterator->nextprev);
        prev = iterator;
        iterator = next;
    }

    return NULL;
}

void xlist_push_front(xlist_t* xlist, void* node)
{
    if(xlist->head)
    {
        xlist->head->nextprev = xlist_xor(xlist->head->nextprev,node);
        ((xlist_node_t*)node)->nextprev = xlist_xor(NULL,xlist->head);
        xlist->head = node;
    }
    else
    {
        ((xlist_node_t*)node)->nextprev = xlist_xor(NULL,NULL);
        xlist->head = xlist->tail = node;
    }
}


void xlist_push_back(xlist_t* xlist, void* node)
{
    if(xlist->tail)
    {
        xlist->tail->nextprev = xlist_xor(xlist->tail->nextprev,node);
        ((xlist_node_t*)node)->nextprev = xlist_xor(NULL,xlist->tail);
        xlist->tail = node;
    }
    else
    {
        ((xlist_node_t*)node)->nextprev = xlist_xor(NULL,NULL);
        xlist->head = xlist->tail = node;
    }
}

void xlist_pop_front(xlist_t* xlist)
{
    xlist_node_t *tmp;

    if (!xlist->head) return;

    tmp = xlist_xor(NULL,xlist->head->nextprev);

    if (tmp)
    {
        tmp->nextprev = xlist_xor(xlist->head,tmp->nextprev);
        xlist->head = tmp;

    }
    else
    {
        xlist->head = xlist->tail = NULL;
    }
}

void xlist_pop_back(xlist_t* xlist)
{
    xlist_node_t *tmp;

    if (!xlist->tail) return;

     tmp = xlist_xor(NULL,xlist->tail->nextprev);

    if (tmp)
    {
        tmp->nextprev = xlist_xor(xlist->tail,tmp->nextprev);
        xlist->tail = tmp;

    }
    else
    {
        xlist->head = xlist->tail = NULL;
    }
}


void xlist_insert_after(xlist_t* xlist, void* position, void* node)
{
    xlist_node_t* next = xlist_next(xlist,position);

    if(next)
    {
        ((xlist_node_t*)node)->nextprev = xlist_xor(position,next);
        next->nextprev = xlist_xor(xlist_xor(next->nextprev,position),node);
        ((xlist_node_t*)position)->nextprev =xlist_xor(xlist_xor(((xlist_node_t*)position)->nextprev,next),node);
    }
    else
    {
        xlist_push_back(xlist,node);
    }

}

void xlist_insert_before(xlist_t* xlist, void* position, void* node)
{
    xlist_node_t* prev = xlist_prev(xlist,position);

    if(prev)
    {
        ((xlist_node_t*)node)->nextprev = xlist_xor(position,prev);
        prev->nextprev = xlist_xor(xlist_xor(prev->nextprev,position),node);
        ((xlist_node_t*)position)->nextprev =xlist_xor(xlist_xor(((xlist_node_t*)position)->nextprev,prev),node);
    }
    else
    {
        xlist_push_front(xlist,node);
    }

}


size_t xlist_size(xlist_t *xlist)
{
    xlist_node_t *iterator = xlist->head;
    xlist_node_t *prev = NULL;
    xlist_node_t *next;
    size_t size = 0;

    while(iterator)
    {
        size++;
        next = xlist_xor(prev,iterator->nextprev);
        prev = iterator;
        iterator = next;
    }

    return size;
}


void xlist_erase(xlist_t *xlist, void *node)
{
    xlist_node_t *prev,*next;


    if (node == xlist->head)
    {
        xlist_pop_front(xlist);
        return;
    }

    if (node == xlist->tail)
    {
        xlist_pop_back(xlist);
        return;
    }

    prev = xlist_prev(xlist,node);
    next = xlist_xor(((xlist_node_t*)node)->nextprev,prev);
    prev->nextprev = xlist_xor(xlist_xor(prev->nextprev,node),next);
    next->nextprev = xlist_xor(xlist_xor(next->nextprev,node),prev);
}


void xlist_remove(xlist_t* xlist, item_compare_t compare, item_t* item)
{
    xlist_node_t *iterator = xlist->head;
    xlist_node_t *prev = NULL;
    xlist_node_t *next;


    while(iterator)
    {
        if(compare(item,xlist_item(iterator)) == ITEM_EQUALS_TO)
        {
            xlist_erase(xlist,iterator);
            iterator = xlist->head;
            prev = NULL;
            continue;
        }

        next = xlist_xor(prev,iterator->nextprev);
        prev = iterator;
        iterator = next;


    }
}



void xlist_reverse (xlist_t * xlist)
{
    xlist_t tmp;
    xlist_node_t* iterator;

    xlist_init(&tmp);

    while(xlist->head)
    {
        iterator = xlist->head;
        xlist_pop_front(xlist);
        xlist_push_front(&tmp,iterator);
    }

    *xlist = tmp;
}


void xlist_unique(xlist_t* xlist, item_compare_t compare)
{

    xlist_node_t *iterator = xlist->head;

     if(!iterator) return;

     while(xlist_next(xlist,iterator))
     {
         if (compare(xlist_item(iterator),xlist_item(xlist_next(xlist,iterator))) == ITEM_EQUALS_TO)
         {
             xlist_erase(xlist,xlist_next(xlist,iterator));
             continue;
         }

         iterator = xlist_next(xlist,iterator);
     }
}

void xlist_sort(xlist_t* xlist, item_compare_t compare)
{
    xlist_node_t *iterator;
    xlist_node_t *largest,*next,*prev,*largest_prev;
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

        // manually erase largest node
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

