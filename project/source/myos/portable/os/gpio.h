/*
 * gpio.h
 *
 *  Created on: Jul 14, 2021
 *      Author: marco
 */

#ifndef GPIO_H_
#define GPIO_H_

#include"gpio_arch.h"

#define GPIO_STATE_SET GPIO_ARCH_STATE_SET
#define GPIO_STATE_RST GPIO_ARCH_STATE_RST

#define GPIO_SET(name)         GPIO_ARCH_SET(name)
#define GPIO_RST(name)         GPIO_ARCH_RST(name)
#define GPIO_TGL(name)         GPIO_ARCH_TGL(name)
#define GPIO_WR(name,value)    GPIO_ARCH_WR(name,value)
#define GPIO_RD(name)          GPIO_ARCH_RD(name)

#endif /* GPIO_H_ */
