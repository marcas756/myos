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


#include "uigfx_font4x6.h"

static const uint16_t uigfx_font4x6_data [96] = {
 0x0000 , /*   */
 0x4124 , /* ! */
 0x005a , /* " */
 0xbefa , /* # */
 0x7bbc , /* $ */
 0xa54a , /* % */
 0x7554 , /* & */
 0x0024 , /* ' */
 0x8928 , /* ( */
 0x5244 , /* ) */
 0x1550 , /* * */
 0x0ba0 , /* + */
 0x2800 , /* , */
 0x0380 , /* - */
 0x4000 , /* . */
 0x2548 , /* / */
 0x76dc , /* 0 */
 0xe934 , /* 1 */
 0xe746 , /* 2 */
 0x7146 , /* 3 */
 0x9e92 , /* 4 */
 0x739e , /* 5 */
 0x779c , /* 6 */
 0x254e , /* 7 */
 0x77dc , /* 8 */
 0x73dc , /* 9 */
 0x0820 , /* : */
 0x2820 , /* ; */
 0x88a8 , /* < */
 0x1c70 , /* = */
 0x2a22 , /* > */
 0x414e , /* ? */
 0xc6d4 , /* @ */
 0xb7dc , /* A */
 0x75dc , /* B */
 0xc49c , /* C */
 0x76d6 , /* D */
 0xe79c , /* E */
 0x279c , /* F */
 0xd69c , /* G */
 0xb7da , /* H */
 0xe92e , /* I */
 0x564c , /* J */
 0xb5da , /* K */
 0xe492 , /* L */
 0xb6fa , /* M */
 0xb6d6 , /* N */
 0x56d4 , /* O */
 0x27d6 , /* P */
 0xdedc , /* Q */
 0xb5dc , /* R */
 0x711c , /* S */
 0x492e , /* T */
 0xd6da , /* U */
 0x56da , /* V */
 0xbeda , /* W */
 0xb55a , /* X */
 0x495a , /* Y */
 0xe54e , /* Z */
 0xc92c , /* [ */
 0x9112 , /* \ */
 0xd24c , /* ] */
 0x0054 , /* ^ */
 0xe000 , /* _ */
 0x0044 , /* ` */
 0xd6e0 , /* a */
 0x76b2 , /* b */
 0xc4e0 , /* c */
 0xd6e8 , /* d */
 0xcee0 , /* e */
 0x2cd4 , /* f */
 0x7355 , /* g */
 0xb592 , /* h */
 0x8904 , /* i */
 0x2905 , /* j */
 0xb5d2 , /* k */
 0x8924 , /* l */
 0xb7d0 , /* m */
 0xb6b0 , /* n */
 0x56a0 , /* o */
 0x2ed7 , /* p */
 0x9add , /* q */
 0x25d0 , /* r */
 0x71e0 , /* s */
 0xc4b2 , /* t */
 0xd6d0 , /* u */
 0x76d0 , /* v */
 0xbed0 , /* w */
 0xb550 , /* x */
 0x535b , /* y */
 0xea70 , /* z */
 0xc9ac , /* { */
 0x4924 , /* | */
 0x6b26 , /* } */
 0x0054 , /* ~ */
 0x1ed4 , /*  */
};


static void uigfx_draw_char_font4x6(uint8_t* buf, int16_t x0, int16_t y0, char ch, uigfx_color_t c)
{
    uint8_t x,y;
    uint16_t chdat = uigfx_font4x6_data[ch-32];

    if(chdat&1)
    {
        y0++;
    }

    chdat>>=1;

    for(y=0; y < 5; y++)
    {
        for(x=0; x < 3; x++)
        {

            if(chdat&1)
            {
                uigfx_draw_pixel(buf,x0+x,y0+y,c);
            }

            chdat>>=1;
        }
    }
}



const uigfx_font_t uigfx_font4x6 = {4,6,uigfx_font4x6_data,uigfx_draw_char_font4x6};






