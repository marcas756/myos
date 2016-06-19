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
    \file   unittest_dlist.h

    \brief

    \details
*/

#ifndef UNITTEST_DLIST_H_
#define UNITTEST_DLIST_H_

#include "dlist.h"

#define unittest_list_type dlist

typedef dlist_node_t list_node_t;
typedef dlist_t list_t;

#define list_node_typedef(type)                     dlist_node_typedef(type)
#define list_node_t(type)                           dlist_node_t(type)
#define list_init(listptr)                          dlist_init(listptr)
#define list_next(listptr,nodeptr)                  dlist_next(listptr,nodeptr)
#define list_prev(listptr,nodeptr)                  dlist_prev(listptr,nodeptr)
#define list_item(nodeptr)                          dlist_item(nodeptr)
#define list_begin(listptr)                         dlist_begin(listptr)
#define list_end(listptr)                           dlist_end(listptr)
#define list_empty(listptr)                         dlist_empty(listptr)
#define list_size(listptr)                          dlist_size(listptr)
#define list_front(listptr)                         dlist_front(listptr)
#define list_back(listptr)                          dlist_back(listptr)
#define list_push_front(listptr,nodeptr)            dlist_push_front(listptr,nodeptr)
#define list_pop_front(listptr)                     dlist_pop_front(listptr)
#define list_push_back(listptr,nodeptr)             dlist_push_back(listptr,nodeptr)
#define list_pop_back(listptr)                      dlist_pop_back(listptr)
#define list_insert_after(listptr,posptr,nodeptr)   dlist_insert_after(listptr,posptr,nodeptr)
#define list_insert_before(listptr,posptr,nodeptr)  dlist_insert_before(listptr,posptr,nodeptr)
#define list_clear(listptr)                         dlist_clear(listptr)
#define list_erase(listptr,nodeptr)                 dlist_erase(listptr,nodeptr)
#define list_remove(listptr,compfptr,itemptr)       dlist_remove(listptr,compfptr,itemptr)
#define list_unique(listptr,compfptr)               dlist_unique(listptr,compfptr)
#define list_reverse(listptr)                       dlist_reverse(listptr)
#define list_sort(listptr,compfptr)                 dlist_sort(listptr,compfptr)
#define list_find(listptr,nodeptr)                  dlist_find(listptr,nodeptr)
#define list_swap(listptr1,listptr2)                dlist_swap(listptr1,listptr2)

#endif /* UNITTEST_DLIST_H_ */
