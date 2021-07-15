/*
 * myos.h
 *
 *  Created on: 04.07.2021
 *      Author: marco
 */

#ifndef MYOS_H_
#define MYOS_H_


#include "myosconf.h"


#include "critical.h"
#include "pt.h"
#include "process.h"

#include "timestamp.h"
#include "timer.h"
#include "ptimer.h"
#include "ctimer.h"
#include "etimer.h"
#include "rtimer.h"

void myos_module_init(void);

#endif /* MYOS_H_ */
