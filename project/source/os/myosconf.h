/*
 * myosconf.h
 *
 *  Created on: 26.06.2021
 *      Author: marco
 */

#ifndef MYOSCONF_H_
#define MYOSCONF_H_
#include <stdint.h>

#define MYOSCONF_SLIST 0
#define MYOSCONF_DLIST 1
#define MYOSCONF_YES 1
#define MYOSCONF_NO  0

#define MYOSCONF_PROC_LIST_TYPE          MYOSCONF_SLIST
#define MYOSCONF_PROC_EVENT_QUEUE_SIZE   8
#define MYOSCONF_PROC_EVENT_FROM         MYOSCONF_YES


#define MYOSCONF_ETIMER                  MYOSCONF_YES
#define MYOSCONF_CTIMER                  MYOSCONF_YES


typedef uint8_t process_event_id_t;




#endif /* MYOSCONF_H_ */
