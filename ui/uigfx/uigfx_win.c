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

#include "uigfx_win.h"
#include "uigfx_win_conf.h"
#include "string.h"
#include "uigfx.h"



void uigfx_draw_desktop_wallpaper(uint8_t* buff, uigfx_image_t *wallpaper)
{
    uigfx_widget_t *tmp = uigfx_current_widget;
    uigfx_set_widget((uigfx_widget_t*)&uigfx_screen_widget);

    for(uint16_t y = 0; y < uigfx_current_widget->yres; y+=wallpaper->yres)
    {
        for(uint16_t x = 0; x < uigfx_current_widget->xres; x+=wallpaper->xres)
        {
            uigfx_draw_image(buff,wallpaper,x,y);
        }
    }

    uigfx_set_widget(tmp);
}



void uigfx_draw_window(uint8_t* buff, uigfx_window_t *win)
{
    uigfx_widget_t *tmp = uigfx_current_widget;
    uigfx_set_widget(&win->title_widget);
    uigfx_draw_filled_rectangle(buff,0,0,win->title_widget.xres, win->title_widget.yres, UIGFX_WIN_TITLE_BG_COLOR);
    uigfx_draw_string(buff,(uigfx_font_t*)&UIGFX_WIN_TITLE_FONT,UIGFX_WIN_TITLE_BORDER,UIGFX_WIN_TITLE_BORDER,win->title,UIGFX_WIN_TITLE_FONT_COLOR);
    uigfx_set_widget(&win->window_widget);
    uigfx_draw_filled_rectangle(buff,0,0,win->window_widget.xres, win->window_widget.yres, UIGFX_WIN_WIDGET_BG_COLOR);
    uigfx_set_widget(tmp);
    uigfx_draw_rectangle(buff,win->title_widget.xpos-1,win->title_widget.ypos-1,win->title_widget.xres+2, win->title_widget.yres+win->window_widget.yres+2, UIGFX_WIN_BORDER_COLOR);
}

void uigfx_init_window(uigfx_window_t *win, char* title, int16_t xpos, int16_t ypos, uint16_t xres, uint16_t yres)
{
    win->title = title;
    win->title_widget.xpos = xpos;
    win->title_widget.ypos = ypos;

    win->title_widget.xres = strlen(title)*UIGFX_WIN_TITLE_FONT.xsz+ 2*UIGFX_WIN_TITLE_BORDER;

    if(xres > win->title_widget.xres)
    {
        win->title_widget.xres = xres;
    }

    win->title_widget.yres = UIGFX_WIN_TITLE_FONT.ysz + 2*UIGFX_WIN_TITLE_BORDER;

    win->window_widget.xpos = xpos;
    win->window_widget.ypos = ypos+win->title_widget.yres;
    win->window_widget.xres = win->title_widget.xres;
    win->window_widget.yres = yres-win->title_widget.yres;

}



void uigfx_select_window_widget(uigfx_window_t *win)
{
    uigfx_current_widget =  &win->window_widget;
}




