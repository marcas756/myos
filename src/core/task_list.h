/*
 * task_list.h
 *
 *  Created on: 16. Juni 2016
 *      Author: blackdigi
 */

#ifndef TASK_LIST_H_
#define TASK_LIST_H_

#include "project.h"

#if (TASK_LIST_TYPE == LIST_TYPE_DLIST)
    #error "Add doubly linked list mapping here"
#elif (TASK_LIST_TYPE == LIST_TYPE_XLIST)
    #error "Add xor linked list mapping here"
#else /*DEFAULT (TASK_LIST_TYPE == LIST_TYPE_SLIST)*/
    #include "slist.h"
    typedef slist_node_t task_list_node_t;
    typedef slist_t task_list_t;
    #define task_list_find(nodeptr)                         slist_find(&task_list,nodeptr)
    #define task_list_begin()                               slist_begin(&task_list)
    #define task_list_next(nodeptr)                         slist_next(&task_list,nodeptr)
    #define task_list_erase(nodeptr)                        slist_erase(&task_list,nodeptr)
    #define task_list_push_front(nodeptr)                   slist_push_front(&task_list,nodeptr)
    #define task_list_size()                                slist_size(&task_list)
#endif

#endif /* TASK_LIST_H_ */
