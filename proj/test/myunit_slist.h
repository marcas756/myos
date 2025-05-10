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
#ifndef MYUNIT_SLIST_H_
#define MYUNIT_SLIST_H_


#include "slist.h"

#define myunit_list_type slist

typedef slist_t list_t;
typedef slist_node_t list_node_t;

#define list_next(list,node)                slist_next(list,node)
#define list_prev(list,node)                slist_prev(list,node)
#define list_prev_prev(list,node)           slist_prev_prev(list,node)
#define list_init(list)                     slist_init(list)
#define list_begin(list)                    slist_begin(list)
#define list_front(list)                    slist_front(list)
#define list_end(list)                      slist_end(list)
#define list_back(list)                     slist_back(list)
#define list_foreach(list,it)               slist_foreach(list,it)
#define list_empty(list)                    slist_empty(list)
#define list_push_front(list,node)          slist_push_front(list,node)
#define list_pop_front(list)                slist_pop_front(list)
#define list_push_back(list,node)           slist_push_back(list,node)
#define list_pop_back(list)                 slist_pop_back(list)
#define list_insert_after(list,pos,node)    slist_insert_after(list,pos,node)
#define list_insert_before(list,pos,node)   slist_insert_before(list,pos,node)
#define list_erase(list,node)               slist_erase(list,node)
#define list_size(list)                     slist_size(list)
#define list_find(list,node)                slist_find(list,node)


#endif /* MYUNIT_SLIST_H_ */
