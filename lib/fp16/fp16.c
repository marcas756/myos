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
    \file   fp16.c

    \brief  Signed fixed point implementation for small embedded project

    \details
*/

#include "fp16.h"
#include "math.h"


/*!
    \brief      Converts a float to a fixed point type
    \details    Converts a float variable to a fixed point variable. Result gets
                saturated if float exceeds fixed point limits.
    \param[in]  var     Float variable to be converted
    \param[in]  frac    Number of fracional bits

    \returns    Fixed point interpretation of provided floating point number
*/
fp16_t fp16_ftofp(float var, uint8_t frac)
{
    var += (var >= 0)?(0.5/(1<<frac)):(-0.5/(1<<frac));
    var *= (1 << frac);
    fp16_sat_m(var);
    return (fp16_t)var;
}

/*!
    \brief      Converts a a fixed point type to float
    \details    Converts a fixed point variable to a float variable.
    \param[in]  var     Fixed point variable to be converted
    \param[in]  frac    Number of fracional bits

    \returns Floating point interpretation of provided fixed point number
*/
float fp16_fptof(fp16_t var, uint8_t frac)
{
    return ((float)(var)) / (1 << frac); /* Bitwise shift operations are not defined for negative values */
}

/*!
    \brief      Adds two fixed point numbers
    \details    Adds two fixed point numbers. Result gets saturated if it exceeds fixed point limits.

                result = a + b

                Be aware of that both fixed point numbers must be of same type (same number of fractional bits)!
                Otherwise the result may be undefined.

    \param[in]  summand1       First fixed point summand
    \param[in]  summand2       Second fixed point summand


    \returns Sum of first summand and second summand in fixed point format
*/
fp16_t fp16_add(fp16_t summand1, fp16_t summand2)
{
    int32_t result;
    result = summand1+summand2;
    fp16_sat_m(result);
    return(fp16_t)result;
}

/*!
    \brief     Subtracts two fixed point numbers
    \details    Adds two fixed point number. Result gets saturated if it exceeds fixed point limits.

                result = a - b

                Be aware of that both fixed point numbers must be of same type (same number of fractional bits)!
                Otherwise the result may be undefined.

    \param[in]  minuend     Minuend
    \param[in]  subtrahend  Subtrahend


    \returns Difference of minuend and subtrahend in fixed point format
*/

fp16_t fp16_sub(fp16_t minuend, fp16_t subtrahend)
{
   int32_t result;
   result = minuend-subtrahend;
   fp16_sat_m(result);
   return(fp16_t)result;
}


/*!
    \brief      Multiplies two fixed point numbers
    \details    Multiplies two fixed point numbers. The numbers may be of different fixed point format.
                The result is in the fixed point format of the multiplicand (1st fixed point parameter).
                Result gets saturated if it exceeds fixed point limits.

                When performing an integer multiplication the product is 2xWL if both the multiplier and
                multiplicand are WL long. If the integer multiplication is on fixed-point variables, the number of
                integer and fractional bits in the product is the sum of the corresponding multiplier and
                multiplicand Q-points.

                result = a*b


    \param[in]  mult1     multiplicator
    \param[in]  mult2     multiplicant


    \returns Product of multiplicator and multiplicant in fixed point format of multiplicator
*/
fp16_t fp16_mult(fp16_t mult1, uint8_t frac1, fp16_t mult2, uint8_t frac2)
{
    int32_t result;
    result = mult1*mult2;
    result >>= frac2; /* Bitwise shift operations are not defined for negative values */
    fp16_sat_m(result);
    return (fp16_t)result;
}



fp16_t fp16_div(fp16_t divident, uint8_t frac1, fp16_t divisor, uint8_t frac2)
{
  int32_t result = (divident<<frac2)/divisor;
  fp16_sat_m(result);
  return (fp16_t)result;
}


/*
  fixed-point multiplication & scaling.
  Substitute inline assembly for hardware-specific
  optimization suited to a particluar DSP processor.
  Scaling ensures that result remains 16-bit.
*/
fp16_t fp16_mult_q15(fp16_t a, fp16_t b)
{
    /* shift right one less bit (i.e. 15-1) */
    int32_t c = ((int32_t)a * (int32_t)b) >> 14;
    /* last bit shifted out = rounding-bit */
    int32_t result = c & 0x01;
    /* last shift + rounding bit */
    result = (c >> 1) + result;

    /* -1.0*-1.0 = +1.0 which exceeds fp16 range! thus saturation is required */
    fp16_sat_m(result);

    return (fp16_t) result;
}




/**
 * \brief    Fast Square root algorithm, with rounding
 *
 * This does arithmetic rounding of the result. That is, if the real answer
 * would have a fractional part of 0.5 or greater, the result is rounded up to
 * the next integer.
 *      - SquareRootRounded(2) --> 1
 *      - SquareRootRounded(3) --> 2
 *      - SquareRootRounded(4) --> 2
 *      - SquareRootRounded(6) --> 2
 *      - SquareRootRounded(7) --> 3
 *      - SquareRootRounded(8) --> 3
 *      - SquareRootRounded(9) --> 3
 *
 * \param[in] a_nInput - unsigned integer for which to find the square root
 *
 * \return Integer square root of the input value.
 */
fp16_t fp16_sqrt(uint32_t a_nInput)
{
    uint32_t op  = a_nInput;
    uint32_t res = 0;
    uint32_t one = 1uL << 30; // The second-to-top bit is set: use 1u << 14 for uint16_t type; use 1uL<<30 for uint32_t type

    // "one" starts at the highest power of four <= than the argument.
    while (one > op)
    {
        one >>= 2;
    }

    while (one != 0)
    {
        if (op >= res + one)
        {
            op = op - (res + one);
            res = res +  (one<<1);
        }
        res >>= 1;
        one >>= 2;
    }

    /* Do arithmetic rounding to nearest integer */
    if (op > res)
    {
        res++;
    }

    if (res > INT16_MAX) { res = INT16_MAX; }

    return res;
}



int16_t fp16_fptoint(fp16_t fp, uint8_t frac)
{
	return fp/(1<<frac);
}


fp16_t fp16_inttofp(int16_t intpart, uint8_t frac)
{
	return intpart*(1<<frac);
}

