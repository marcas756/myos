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
    \file   task.h

    \brief

    \details
*/

#ifndef TASK_H_
#define TASK_H_

#include "oz_conf.h"
#include "pt.h"
#include "event.h"

#if (OZCONF_TASK_LIST_TYPE == DLIST)
    #include "dlist.h"
    typedef dlist_node_t task_list_node_t;
    typedef dlist_t task_list_t;
    #define task_list_find(nodeptr)                         dlist_find(&task_list,nodeptr)
    #define task_list_begin()                               dlist_begin(&task_list)
    #define task_list_next(nodeptr)                         dlist_next(&task_list,nodeptr)
#elif (OZCONF_TASK_LIST_TYPE == XLIST)
    #include "xlist.h"
    typedef xlist_node_t task_list_node_t;
    typedef xlist_t task_list_t;
    #define task_list_find(nodeptr)                         xlist_find(&task_list,nodeptr)
    #define task_list_begin()                               xlist_begin(&task_list)
    #define task_list_next(nodeptr)                         xlist_next(&task_list,nodeptr)
#else /* SLIST */
    #include "slist.h"
    typedef slist_node_t task_list_node_t;
    typedef slist_t task_list_t;
    #define task_list_find(nodeptr)                         slist_find(&task_list,nodeptr)
    #define task_list_begin()                               slist_begin(&task_list)
    #define task_list_next(nodeptr)                         slist_next(&task_list,nodeptr)
#endif


#define TASK_THREAD_ARGS pt_t *pt, event_t *event

typedef char (*task_thread_t)(TASK_THREAD_ARGS);

typedef struct {
    task_list_node_t link;
    pt_t pt;
    task_thread_t task_thread;
} task_t;

extern task_list_t task_list;

#endif /* TASK_H_ */
