/*
 * critical_arch.h
 *
 *  Created on: 20.06.2021
 *      Author: marco
 */

#ifndef CRITICAL_ARCH_H_
#define CRITICAL_ARCH_H_

#define CRITICAL_SECTION_BEGIN()    do{
#define CRITICAL_SECTION_END()      }while(0)

#define CRITICAL_EXPRESSION(x) \
   CRITICAL_SECTION_BEGIN(); \
   x; \
   CRITICAL_SECTION_END();

#endif /* CRITICAL_ARCH_H_ */
