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

#ifndef UIGFX_H_
#define UIGFX_H_

#include <stdint.h>
#include <stdbool.h>


#define UIGFX_XRES            128
#define UIGFX_YRES            64
#define UIGFX_BPP             1

#if (UIGFX_BPP == 1)
typedef bool uigfx_color_t;
#else
#error "uigfx : color type not defined"
#endif


typedef struct {
    const uint8_t xsz;
    const uint8_t ysz;
    const void* data;
    const void (*draw)(uint8_t* buf, int16_t x0, int16_t y0, char ch, uigfx_color_t c);
}uigfx_font_t;

typedef struct {
   int16_t xpos,ypos;
   uint16_t xres, yres;
} uigfx_widget_t;

typedef struct {
    const uint8_t *data;
    uint16_t xres;
    uint16_t yres;
    uint8_t bbp;
} uigfx_image_t;






void uigfx_set_widget( uigfx_widget_t *widget );
void uigfx_init_widget(uigfx_widget_t *widget, int16_t xpos, int16_t ypos, uint16_t xres, uint16_t yres);
void uigfx_select_screen_widget();

const uigfx_widget_t uigfx_screen_widget;
uigfx_widget_t *uigfx_current_widget;



void uigfx_draw_pixel(uint8_t* buff, int16_t x, int16_t y, uigfx_color_t c);
void uigfx_draw_hline(uint8_t* buf, int16_t x0, int16_t y0, int16_t w, uigfx_color_t c);
void uigfx_draw_vline(uint8_t* buf, int16_t x0, int16_t y0, int16_t h, uigfx_color_t c);
void uigfx_draw_line(uint8_t* buf,int16_t x0, int16_t y0, int16_t x1, int16_t y1, uigfx_color_t c);
void uigfx_draw_rectangle(uint8_t* buf, int16_t x0, int16_t y0, int16_t l, int16_t h, uigfx_color_t c);
void uigfx_draw_filled_rectangle(uint8_t* buf, int16_t x0, int16_t y0, int16_t l, int16_t h, uigfx_color_t c);
void uigfx_draw_circle(uint8_t* buf, int16_t x0, int16_t y0, int16_t r,uigfx_color_t c);
void uigfx_draw_filled_circle(uint8_t* buf, int16_t x0, int16_t y0, int16_t r,uigfx_color_t c);
void uigfx_draw_ellipse(uint8_t* buf, int16_t x0, int16_t y0, int16_t a, int16_t b, uigfx_color_t c);
void uigfx_draw_filled_ellipse(uint8_t* buf, int16_t x0, int16_t y0, int16_t a, int16_t b, uigfx_color_t c);

void uigfx_draw_char(uint8_t* buf, uigfx_font_t *font, int16_t x0, int16_t y0, char ch, uigfx_color_t c);
void uigfx_draw_string(uint8_t* buf, uigfx_font_t *font, int16_t x0, int16_t y0, char* str, uigfx_color_t c);
int16_t uigfx_draw_put_char(uint8_t* buf, uigfx_font_t *font, int16_t x0, int16_t y0, char ch, uigfx_color_t c);
int16_t uigfx_string_newline(uigfx_font_t *font, int16_t y0);


void uigfx_draw_image(uint8_t* buf, uigfx_image_t *image, int16_t x0, int16_t y0);

#endif /* _UIGFX_H_ */
