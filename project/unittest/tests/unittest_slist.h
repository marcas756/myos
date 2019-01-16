/*! \copyright
    Copyright (c) 2013, marco@bacchi.at
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
    \file   unittest_slist.h

    \brief

    \details
*/

#ifndef UNITTEST_SLIST_H_
#define UNITTEST_SLIST_H_

#include "slist.h"

#define unittest_list_type slist


typedef slist_t list_t;



#define LIST_NODE_TYPE                              SLIST_NODE_TYPE
#define list_node_t(type)                           slist_node_t(type)
#define list_init(listptr)                          slist_init(listptr)
#define list_next(listptr,nodeptr)                  slist_next(listptr,nodeptr)
#define list_prev(listptr,nodeptr)                  slist_prev(listptr,nodeptr)
#define list_begin(listptr)                         slist_begin(listptr)
#define list_end(listptr)                           slist_end(listptr)
#define list_empty(listptr)                         slist_empty(listptr)
#define list_size(listptr)                          slist_size(listptr)
#define list_front(listptr)                         slist_front(listptr)
#define list_back(listptr)                          slist_back(listptr)
#define list_push_front(listptr,nodeptr)            slist_push_front(listptr,nodeptr)
#define list_pop_front(listptr)                     slist_pop_front(listptr)
#define list_push_back(listptr,nodeptr)             slist_push_back(listptr,nodeptr)
#define list_pop_back(listptr)                      slist_pop_back(listptr)
#define list_insert_after(listptr,posptr,nodeptr)   slist_insert_after(listptr,posptr,nodeptr)
#define list_insert_before(listptr,posptr,nodeptr)  slist_insert_before(listptr,posptr,nodeptr)
#define list_clear(listptr)                         slist_clear(listptr)
#define list_erase(listptr,nodeptr)                 slist_erase(listptr,nodeptr)
#define list_remove(listptr,compfptr,itemptr)       slist_remove(listptr,compfptr,itemptr)
#define list_unique(listptr,compfptr)               slist_unique(listptr,compfptr)
#define list_reverse(listptr)                       slist_reverse(listptr)
#define list_sort(listptr,compfptr)                 slist_sort(listptr,compfptr)
#define list_find(listptr,nodeptr)                  slist_find(listptr,nodeptr)


#endif /* UNITTEST_SLIST_H_ */
