/*! \copyright
 
   https://opensource.org/licenses/BSD-3-Clause
 
   Copyright 2013-2021 Marco Bacchi <marco@bacchi.at>
   
   Redistribution and use in source and binary forms, with or without 
   modification, are permitted provided that the following conditions are met:
   
   1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.
   
   2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

   3. Neither the name of the copyright holder nor the names of its 
   contributors may be used to endorse or promote products derived from this 
   software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
   POSSIBILITY OF SUCH DAMAGE.
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
