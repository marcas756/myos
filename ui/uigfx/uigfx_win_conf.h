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


#ifndef UIGFX_WIN_CONF_H_
#define UIGFX_WIN_CONF_H_

#include "fonts/uigfx_font4x6.h"
#include "fonts/uigfx_font8x8_c64.h"
#include "fonts/uigfx_font8x8_vic.h"

#define UIGFX_COLOR_BLACK  0
#define UIGFX_COLOR_WHITE  1

#define UIGFX_WIN_TITLE_FONT        uigfx_font8x8_c64
#define UIGFX_WIN_TITLE_FONT_COLOR  UIGFX_COLOR_BLACK
#define UIGFX_WIN_TITLE_BG_COLOR    UIGFX_COLOR_WHITE
#define UIGFX_WIN_TITLE_BORDER      1

#define UIGFX_WIN_BORDER_COLOR      UIGFX_WIN_TITLE_BG_COLOR
#define UIGFX_WIN_WIDGET_BG_COLOR   UIGFX_COLOR_BLACK




#endif /* UIGFX_UIGFX_WIN_CONF_H_ */
