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



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "uigfx.h"
#include "uigfx_win_conf.h"



const uigfx_widget_t uigfx_screen_widget = { 0, 0, UIGFX_XRES, UIGFX_YRES };
uigfx_widget_t *uigfx_current_widget = &uigfx_screen_widget;

void uigfx_set_widget(uigfx_widget_t *widget)
{
    uigfx_current_widget = widget;
}

void uigfx_select_screen_widget()
{
    uigfx_current_widget = &uigfx_screen_widget;
}


void uigfx_init_widget(uigfx_widget_t *widget, int16_t xpos, int16_t ypos, uint16_t xres, uint16_t yres)
{
    widget->xpos = xpos;
    widget->ypos = ypos;
    widget->xres = xres;
    widget->yres = yres;
}




void uigfx_draw_pixel(uint8_t* buff, int16_t x, int16_t y, uigfx_color_t c)
{

    /* ... shift coordinates relative to widget ...  */
    x+=uigfx_current_widget->xpos;
    y+=uigfx_current_widget->ypos;

    /* ..., check if the coordinates to draw are within within screen limits ...*/
    if( x < 0 || y < 0 ) return;
    if( x >= UIGFX_XRES || y >= UIGFX_YRES ) return;
    /* ... and as last check if the coordinates are within the widget */
    if( x < uigfx_current_widget->xpos || y < uigfx_current_widget->ypos ) return;
    if( x >= (uigfx_current_widget->xpos + uigfx_current_widget->xres) ||  y >= (uigfx_current_widget->ypos + uigfx_current_widget->yres)  ) return;

    uint16_t idx = ((y/8)*UIGFX_XRES+x);
    uint8_t bit = (1<<(y%8));


    if(c)
    {
        buff[idx]|=bit;
    }
    else
    {
        buff[idx]&=~bit;
    }
}


void uigfx_draw_hline(uint8_t* buf, int16_t x0, int16_t y0, int16_t w, uigfx_color_t c)
{
    if( w > 0 )
    {
        while(w--)
        {
            uigfx_draw_pixel(buf,x0++,y0,c);
        }
    }
    else if ( w < 0 )
    {
        while(w++)
        {
            uigfx_draw_pixel(buf,x0--,y0,c);
        }
    }
    else
    {
        uigfx_draw_pixel(buf,x0,y0,c);
    }
}



void uigfx_draw_vline(uint8_t* buf, int16_t x0, int16_t y0, int16_t h, uigfx_color_t c)
{
    if( h > 0 )
    {
        while(h--)
        {
            uigfx_draw_pixel(buf,x0,y0++,c);
        }
    }
    else if ( h < 0 )
    {
        while(h++)
        {
            uigfx_draw_pixel(buf,x0,y0--,c);
        }
    }
    else
    {
        uigfx_draw_pixel(buf,x0,y0,c);
    }
}

void uigfx_draw_line(uint8_t* buf,int16_t x0, int16_t y0, int16_t x1, int16_t y1, uigfx_color_t c)
{
    int dx = abs(x1-x0);
    int sx = (x0<x1)?(1):(-1);
    int dy = -abs(y1-y0);
    int sy = (y0<y1)?(1):(-1);
    int err = dx+dy;
    int e2;

    while(1)
    {
        uigfx_draw_pixel(buf,x0,y0,c);
        if((x0==x1) && (y0==y1)) break;
        e2=2*err;
        if (e2>dy) {err+=dy; x0+=sx;}
        if (e2<dx) {err+=dx; y0+=sy;}
    }
}

void uigfx_draw_rectangle(uint8_t* buf, int16_t x0, int16_t y0, int16_t l, int16_t h, uigfx_color_t c)
{

    uigfx_draw_vline(buf, x0, y0, h, c);
    uigfx_draw_hline(buf, x0, y0, l, c);

    if( l > 0 )
    {
        uigfx_draw_vline(buf, x0+l-1, y0, h, c);
    }
    else
    {
        uigfx_draw_vline(buf, x0+l+1, y0, h, c);
    }


    if ( h > 0 )
    {
        uigfx_draw_hline(buf, x0, y0+h-1, l, c);
    }
    else
    {
    uigfx_draw_hline(buf, x0, y0+h+1, l, c);

    }


}

void uigfx_draw_filled_rectangle(uint8_t* buf, int16_t x0, int16_t y0, int16_t l, int16_t h, uigfx_color_t c)
{

    if( h > 0 )
    {
        while(h--)
        {
            uigfx_draw_hline(buf,x0,y0++,l,c);
        }
    }
    else if (h < 0 )
    {
        while(h++)
        {
            uigfx_draw_hline(buf,x0,y0--,l,c);
        }
    }
    else
    {
        uigfx_draw_hline(buf,x0,y0,l,c);
    }
}



void uigfx_draw_circle(uint8_t* buf, int16_t x0, int16_t y0, int16_t r,uigfx_color_t c)
{
    int16_t x,y,err;
    x = -r;
    y = 0;
    err = 2-(r+r);

    do {
        uigfx_draw_pixel(buf,x0-x,y0+y,c);
        uigfx_draw_pixel(buf,x0-y,y0-x,c);
        uigfx_draw_pixel(buf,x0+x,y0-y,c);
        uigfx_draw_pixel(buf,x0+y,y0+x,c);

        r = err;

        if (r <= y)
        {
            y++;
            err+=(y+y)+1;
        }

        if (r > x || err > y)
        {
            x++;
            err += (x+x)+1;
        }

    } while (x < 0);
}


void uigfx_draw_filled_circle(uint8_t* buf, int16_t x0, int16_t y0, int16_t r,uigfx_color_t c)
{
    int16_t x,y,err;
    x = -r;
    y = 0;
    err = 2-(r+r);

    do {
        uigfx_draw_hline(buf,x0-x,y0+y,x+x,c);
        uigfx_draw_hline(buf,x0-x,y0-y,x+x,c);

        r = err;

        if (r <= y)
        {
            y++;
            err+=(y+y)+1;
        }

        if (r > x || err > y)
        {
            x++;
            err += (x+x)+1;
        }

    } while (x < 0);
}





void uigfx_draw_ellipse(uint8_t* buf, int16_t x0, int16_t y0, int16_t a, int16_t b, uigfx_color_t c)
{
    int32_t e2,dx,dy,err;
    int16_t x,y;
    x = -a;
    y = 0;
    e2 = b;
    dx = (1+(x+x))*e2*e2;
    dy = x+x;
    err = dx+dy;

    do {
        uigfx_draw_pixel(buf,x0-x,y0+y,c);
        uigfx_draw_pixel(buf,x0+x,y0+y,c);
        uigfx_draw_pixel(buf,x0+x,y0-y,c);
        uigfx_draw_pixel(buf,x0-x,y0-y,c);
        e2 = (err+err);
        if (e2 >= dx)
        {
            x++;
            dx += ((b*b)<<1);
            err += dx;
        }
        if (e2 <= dy)
        {
            y++;
            dy += ((a*a)<<1);
            err += dy;
        }
    } while (x <= 0);

    while (y++ < b) {
        uigfx_draw_pixel(buf,x0,y0+y,c);
        uigfx_draw_pixel(buf,x0,y0-y,c);
    }
}

void uigfx_draw_filled_ellipse(uint8_t* buf, int16_t x0, int16_t y0, int16_t a, int16_t b, uigfx_color_t c)
{
    int32_t e2,dx,dy,err;
    int16_t x,y;
    x = -a;
    y = 0;
    e2 = b;
    dx = (1+(x+x))*e2*e2;
    dy = x*x;
    err = dx+dy;

    do {
        uigfx_draw_hline(buf,x0-x,y0+y,x+x,c);
        uigfx_draw_hline(buf,x0-x,y0-y,x+x,c);
        e2 = err+err;
        if (e2 >= dx)
        {
            x++;
            dx += (b*b)<<1;
            err += dx;
        }
        if (e2 <= dy)
        {
            y++;
            dy += (a*a)<<1;
            err += dy;
        }
    } while (x <= 0);

    while (y++ < b) {

        uigfx_draw_vline(buf,x0,y0-y,y+y,c);
    }
}


void uigfx_draw_char(uint8_t* buf, uigfx_font_t *font, int16_t x0, int16_t y0, char ch, uigfx_color_t c)
{
    font->draw(buf,x0,y0,ch,c);
}

int16_t uigfx_draw_put_char(uint8_t* buf, uigfx_font_t *font, int16_t x0, int16_t y0, char ch, uigfx_color_t c)
{
    font->draw(buf,x0,y0,ch,c);
    return(x0+font->xsz);
}


void uigfx_draw_string(uint8_t* buf, uigfx_font_t *font, int16_t x0, int16_t y0, char* str, uigfx_color_t c)
{
    while(*str != '\0')
    {
        uigfx_draw_char(buf, font, x0, y0, *str++, c);
        x0+=font->xsz;
    }
}

int16_t uigfx_string_newline(uigfx_font_t *font, int16_t y0)
{
    return y0+font->ysz;
}

void uigfx_clear(uint8_t* buf, uigfx_color_t c)
{
    for(int16_t x = 0; x < uigfx_current_widget->xres; x++)
    {
        for(int16_t y = 0; y < uigfx_current_widget->yres; y++)
        {
            uigfx_draw_pixel(buf,x,y,c);
        }
    }
}




void uigfx_draw_image(uint8_t* buf, uigfx_image_t *image, int16_t x0, int16_t y0)
{

    uint16_t xstart = (x0 < 0)?(-x0):(0);
    uint16_t ystart = (y0 < 0)?(-y0):(0);
    uint16_t xres = (xstart+uigfx_current_widget->xres > image->xres)?(image->xres):(xstart+uigfx_current_widget->xres);
    uint16_t yres = (ystart+uigfx_current_widget->yres > image->yres)?(image->yres):(ystart+uigfx_current_widget->yres);

    for (int16_t x = xstart ; x < xres; x++)
    {
        for (int16_t y = ystart; y < yres; y++)
        {
            uint8_t byte = image->data[y*(image->xres>>3)+(x>>3)];
            uint8_t bit = 7-x%8;
            uigfx_color_t c = !!(byte&(1<<bit));
            uigfx_draw_pixel(buf,x+x0,y+y0,c);
        }
    }
}





void uigfx_draw_widget(uint8_t* buf, uigfx_widget_t* widget)
{




}







