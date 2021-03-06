/*
 * gpio_arch.h
 *
 *  Created on: Jul 14, 2021
 *      Author: marco
 */

#ifndef GPIO_ARCH_H_
#define GPIO_ARCH_H_

#include "main.h"

#define GPIO_ARCH_STATE_SET   GPIO_PIN_SET
#define GPIO_ARCH_STATE_RST   GPIO_PIN_RESET

#define GPIO_ARCH_SET(name) HAL_GPIO_WritePin(name##_GPIO_Port, name##_Pin, GPIO_PIN_SET)
#define GPIO_ARCH_RST(name) HAL_GPIO_WritePin(name##_GPIO_Port, name##_Pin, GPIO_PIN_RESET)
#define GPIO_ARCH_TGL(name) HAL_GPIO_TogglePin(name##_GPIO_Port, name##_Pin)
#define GPIO_ARCH_WR(name,value) HAL_GPIO_WritePin(name##_GPIO_Port, name##_Pin, value)
#define GPIO_ARCH_RD(name) HAL_GPIO_ReadPin(name##_GPIO_Port, name##_Pin)

#endif /* GPIO_ARCH_H_ */
