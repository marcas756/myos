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



#ifndef UILEDS_H_
#define UILEDS_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


#define UILEDS_STATE_OFF    0
#define UILEDS_STATE_ON     1

#define UILEDS_INV          1
#define UILEDS_ORIG         0

typedef void (*uileds_set_t) (bool);

typedef struct {
    unsigned lstate      :1;
    unsigned duration   :7;
} uileds_state_t;

typedef struct uileds_t uileds_t;

struct uileds_t{
    uileds_set_t set_led;
    uileds_state_t *pattern;
    unsigned pstate     :7;
    unsigned inverted   :1;
    unsigned timer      :8;
};

extern const uileds_t* const uileds_all_leds [];

#define UILEDS_PATTERN_BEGIN(name) \
        const uileds_state_t uileds_pattern_##name [] = {

#define EXTERN_UILEDS_PATTERN(name) \
        extern const uileds_state_t uileds_pattern_##name []

#define UILEDS_STATE(state,duration) \
        {state,duration},

#define UILEDS_PATTERN_END() {0,0} };

#define UILEDS_LED(led_name,setfunc) \
        uileds_t led_name = {setfunc,NULL,0,0,0}

#define EXTERN_UILEDS_LED(led_name) \
        extern uileds_t led_name

#define UILEDS_SET_PATTERN(led_name,pattern_name,invert) \
        uileds_set_pattern(&led_name,(uileds_state_t*)&uileds_pattern_##pattern_name,invert)

#define UILEDS_LEDS(...) \
    const uileds_t* const uileds_all_leds [] = { __VA_ARGS__ }; \
    const unsigned uileds_count = (sizeof(uileds_all_leds)/sizeof(*uileds_all_leds));

#define UILEDS_COUNT (uileds_count)

#define UILEDS_SYNC(which,with,inverted) uileds_sync (&which,&with,inverted)

#define ULEDS_DISABLE_LED(led_name) do { led_name.pattern = NULL; led_name.set_led(UILEDS_STATE_OFF);}while(0)

void uileds_set_pattern (uileds_t* led, uileds_state_t* pattern, bool inverted);
void uileds_handler(void);
extern const unsigned uileds_count;
void uileds_sync (uileds_t* which, uileds_t* with, bool inverted);

#endif /* UILEDS_H_ */
