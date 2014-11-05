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
    \file   dlist.c

    \brief

    \details
*/

#include "dlist.h"

void dlist_push_front(dlist_t* dlist, void* node)
{
    ((dlist_node_t*)node)->prev = NULL;

    if((((dlist_node_t*)node)->next = dlist->head))
        dlist->head->prev = node;
    else
        dlist->tail = node;

    dlist->head = node;
}

void dlist_push_back(dlist_t* dlist, void* node)
{
    ((dlist_node_t*)node)->next = NULL;

    if((((dlist_node_t*)node)->prev = dlist->tail))
        dlist->tail->next = node;
    else
        dlist->head = node;

    dlist->tail = node;
}

void dlist_pop_front(dlist_t* dlist)
{
    if (dlist->head)
    {
        dlist->head = dlist->head->next;

        if(dlist->head)
            dlist->head->prev = NULL;
        else
            dlist->tail = NULL;
    }
}

void dlist_pop_back(dlist_t* dlist)
{
    if (dlist->tail)
    {
        dlist->tail = dlist->tail->prev;

        if(dlist->tail)
            dlist->tail->next = NULL;
        else
            dlist->head = NULL;
    }
}


void dlist_insert_after(dlist_t* dlist, void* position, void* node)
{
    if(((dlist_node_t*)position)->next)
    {
        ((dlist_node_t*)node)->prev = position;
        ((dlist_node_t*)node)->next = ((dlist_node_t*)position)->next;
        ((dlist_node_t*)position)->next = node;
    }
    else
    {
        dlist_push_back(dlist,node);
    }
}

void dlist_insert_before(dlist_t* dlist, void* position, void* node)
{
    if(((dlist_node_t*)position)->prev)
    {
        ((dlist_node_t*)node)->next = position;
        ((dlist_node_t*)node)->prev = ((dlist_node_t*)position)->prev;
        ((dlist_node_t*)position)->prev = node;
    }
    else
    {
        dlist_push_front(dlist,node);
    }
}

size_t dlist_size(dlist_t *dlist)
{
    dlist_node_t *iterator = dlist->head;
    size_t size = 0;

    while(iterator)
    {
        size++;
        iterator = iterator->next;
    }

    return size;
}

void dlist_erase(dlist_t *dlist, void *node)
{
    if(node == dlist->head)
    {
        dlist_pop_front(dlist);
        return;
    }

    if(node == dlist->tail)
    {
        dlist_pop_back(dlist);
        return;
    }

    ((dlist_node_t*)node)->next->prev = ((dlist_node_t*)node)->prev;
    ((dlist_node_t*)node)->prev->next = ((dlist_node_t*)node)->next;
}

void dlist_remove(dlist_t* dlist, item_compare_t compare, item_t* item)
{
    dlist_node_t *iterator = dlist->head;

    while(iterator)
    {
        if(compare(item,dlist_item(iterator)) == ITEM_EQUALS_TO)
            dlist_erase(dlist,iterator);

        iterator = iterator->next;
    }
}

void dlist_swap(dlist_t *list1, dlist_t *list2)
{
    dlist_t tmp = *list1;
    *list1 = *list2;
    *list2 = tmp;
}


void dlist_clear(dlist_t* dlist)
{
    dlist_init(dlist);
}

void dlist_reverse (dlist_t * dlist)
{
    dlist_t tmp;
    dlist_node_t* iterator;

    dlist_init(&tmp);

    while(dlist->head)
    {
        iterator = dlist->head;
        dlist_pop_front(dlist);
        dlist_push_front(&tmp,iterator);
    }

    slist_swap(dlist,&tmp);
}


void dlist_unique(dlist_t* dlist, item_compare_t compare)
{

}

void dlist_sort(dlist_t* dlist, item_compare_t compare)
{

}
