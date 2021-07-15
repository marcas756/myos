/*
 * critical.h
 *
 *  Created on: 20.06.2021
 *      Author: marco
 */

#ifndef CRITICAL_H_
#define CRITICAL_H_
#include "critical_arch.h"

#define CRITICAL_SECTION_BEGIN  CRITICAL_ARCH_SECTION_BEGIN
#define CRITICAL_SECTION_END    CRITICAL_ARCH_SECTION_END
#define CRITICAL_EXPRESSION     CRITICAL_ARCH_EXPRESSION

#endif /* CRITICAL_H_ */
