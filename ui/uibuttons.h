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


#ifndef UIBUTTONS_H_
#define UIBUTTONS_H_

#include <stdbool.h>
#include <stdint.h>
#include "uibuttons_conf.h"



#define UIBUTTONS_STATE_RELEASED            0
#define UIBUTTONS_STATE_PRESSED             1
#define UIBUTTONS_STATE_RELEASED_DEBOUNCE   2
#define UIBUTTONS_STATE_PRESSED_DEBOUNCE    3

#define UIBUTTONS_EVENT_BASE        0

enum {
    UIBUTTONS_EVENT_RISING_EDGE = UIBUTTONS_EVENT_BASE,
    UIBUTTONS_EVENT_FALLING_EDGE,
    UIBUTTONS_EVENT_SHORT_PRESS,
    UIBUTTONS_EVENT_LONG_PRESS,
    UIBUTTONS_EVENT_LONGER_PRESS,
    UIBUTTONS_EVENT_LONGEST_PRESS,
    UIBUTTONS_EVENT_REPEAT_PRESS,
    UIBUTTONS_EVENT_SINGLE_CLICK,
    UIBUTTONS_EVENT_DOUBLE_CLICK,
    UIBUTTONS_EVENT_TRIPLE_CLICK,
};



typedef bool (*uibuttons_get_t) ();

typedef struct {
  uibuttons_get_t get;
  uint8_t prev_state;
#if UIBUTTONS_ENABLE_LONG_PRESS || UIBUTTONS_ENABLE_DEBOUNCING
  uint8_t hold_timer;
#endif

#if UIBUTTONS_ENABLE_REPEAT_PRESS
  uint8_t repeat_timer;
#endif  
  
#if UIBUTTONS_ENABLE_MULTI_CLICK
  uint8_t click_timer;
  uint8_t click_count;
#endif  
 
}uibutton_t;

  
#define UIBUTTON_LIST_BEGIN      uibutton_t uibuttons[] = {
#define UIBUTTON(get_func)      {get_func}
#define UIBUTTON_LIST_END       }; const int uibuttons_count = sizeof(uibuttons)/sizeof(uibuttons[0]);

#define UIBUTTONS_COUNT uibuttons_count

#define UIBUTTONS_GET_ID(button) \
    ((int)(button-uibuttons))

#define UIBUTTONS_POLL_SINGLE(id) \
    uibuttons_poll(&uibuttons[id])

#define UIBUTTONS_POLL_ALL() \
    do{int tmp;for(tmp=0;tmp<UIBUTTONS_COUNT;tmp++)UIBUTTONS_POLL_SINGLE(tmp);}while(0)
      
#define UIBUTTONS_INIT_ALL() \
      do{int tmp;for(tmp=0;tmp<UIBUTTONS_COUNT;tmp++)uibuttons[tmp].prev_state=uibuttons[tmp].get();}while(0)

void uibuttons_poll(uibutton_t *button);

#endif /* UIBUTTONS_H_ */
