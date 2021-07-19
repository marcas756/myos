/*
 * critical_arch.h
 *
 *  Created on: 20.06.2021
 *      Author: marco
 */

#ifndef CRITICAL_ARCH_H_
#define CRITICAL_ARCH_H_

#include "main.h"



/* Read PRIMASK register, check interrupt status before you disable them */
/* Returns 0 if they are enabled, or non-zero if disabled */
/* Disable interrupts */
#define CRITICAL_ARCH_SECTION_BEGIN() \
	do{ \
		bool istate = !__get_PRIMASK(); \
		__disable_irq();

/* Enable interrupts back only if they were enabled before we disable it here in this function */
#define CRITICAL_ARCH_SECTION_END()   \
		if( istate ) __enable_irq(); \
	}while(0)

#define CRITICAL_ARCH_EXPRESSION(x) \
   CRITICAL_SECTION_BEGIN(); \
   x; \
   CRITICAL_SECTION_END();

#endif /* CRITICAL_ARCH_H_ */
