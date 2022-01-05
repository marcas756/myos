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
/*!
    \file   fp16.h

    \brief  Signed fixed point implementation for small embedded project

    \details
*/

#ifndef _FP16_H_
#define _FP16_H_

#include <stdint.h>

#define FP16_Q0             (0)
#define FP16_Q0_PREC        (1)
#define FP16_Q0_MAX         (32767)
#define FP16_Q0_MIN         (-32768)

#define FP16_Q1             (1)
#define FP16_Q1_PREC        (0.5)
#define FP16_Q1_MAX         (16383.5)
#define FP16_Q1_MIN         (-16384.0)

#define FP16_Q2             (2)
#define FP16_Q2_PREC        (0.25)
#define FP16_Q2_MAX         (8191.75)
#define FP16_Q2_MIN         (-8192.0)

#define FP16_Q3             (3)
#define FP16_Q3_PREC        (0.125)
#define FP16_Q3_MAX         (4095.875)
#define FP16_Q3_MIN         (-4096.0)

#define FP16_Q4             (4)
#define FP16_Q4_PREC        (0.0625)
#define FP16_Q4_MAX         (2047.9375)
#define FP16_Q4_MIN         (-2048.0)

#define FP16_Q5             (5)
#define FP16_Q5_PREC        (0.03125)
#define FP16_Q5_MAX         (1023.96875)
#define FP16_Q5_MIN         (-1024.0)

#define FP16_Q6             (6)
#define FP16_Q6_PREC        (0.015625)
#define FP16_Q6_MAX         (511.984375)
#define FP16_Q6_MIN         (-512.0)

#define FP16_Q7             (7)
#define FP16_Q7_PREC        (0.0078125)
#define FP16_Q7_MAX         (255.9921875)
#define FP16_Q7_MIN         (-256.0)

#define FP16_Q8             (8)
#define FP16_Q8_PREC        (0.00390625)
#define FP16_Q8_MAX         (127.99609375)
#define FP16_Q8_MIN         (-128.0)

#define FP16_Q9             (9)
#define FP16_Q9_PREC        (0.001953125)
#define FP16_Q9_MAX         (63.998046875)
#define FP16_Q9_MIN         (-64.0)

#define FP16_Q10            (10)
#define FP16_Q10_PREC       (0.0009765625)
#define FP16_Q10_MAX        (31.9990234375)
#define FP16_Q10_MIN        (-32.0)

#define FP16_Q11            (11)
#define FP16_Q11_PREC       (0.00048828125)
#define FP16_Q11_MAX        (15.99951171875)
#define FP16_Q11_MIN        (-16.0)

#define FP16_Q12            (12)
#define FP16_Q12_PREC       (0.000244140625)
#define FP16_Q12_MAX        (7.999755859375)
#define FP16_Q12_MIN        (-8.0)

#define FP16_Q13            (13)
#define FP16_Q13_PREC       (0.0001220703125)
#define FP16_Q13_MAX        (3.9998779296875)
#define FP16_Q13_MIN        (-4.0)

#define FP16_Q14            (14)
#define FP16_Q14_PREC       (6.103515625e-05)
#define FP16_Q14_MAX        (1.99993896484375)
#define FP16_Q14_MIN        (-2.0)

#define FP16_Q15            (15)
#define FP16_Q15_PREC       (3.0517578125e-05)
#define FP16_Q15_MAX        (0.999969482421875)
#define FP16_Q15_MIN        (-1.0)

typedef int16_t fp16_t; /*!< Type can be used for all Q configurations */

/*!
    \brief      Macro that saturates a result to fixed point limits
    \details    This macro checks if the int32_t result of a previously performed calculation
                results in a fixed point overflow. If so the result is saturated to the
                extends of the fixed point type.
    \param[in]  var     Fixed point int32_t result to be saturated
*/
#define fp16_sat_m(var) \
    do{ \
        if (var > INT16_MAX) { var = INT16_MAX; } \
        if (var < INT16_MIN) { var = INT16_MIN; } \
    }while(0)


fp16_t fp16_ftofp(float var, uint8_t frac);
float fp16_fptof(fp16_t var, uint8_t frac);
fp16_t fp16_add(fp16_t summand1, fp16_t summand2);
fp16_t fp16_sub(fp16_t minuend, fp16_t subtrahend);
fp16_t fp16_mult(fp16_t mult1, uint8_t frac1, fp16_t mult2, uint8_t frac2);
fp16_t fp16_mult_q15(fp16_t a, fp16_t b);
fp16_t fp16_div(fp16_t divident, uint8_t frac1, fp16_t divisor, uint8_t frac2);
int16_t fp16_fptoint(fp16_t fp, uint8_t frac);
fp16_t fp16_inttofp(int16_t intpart, uint8_t frac);





#endif /* _FP16_H_ */
