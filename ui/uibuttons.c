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



#include <stdio.h>
#include <stdlib.h>
#include "uibuttons.h"



#define debounce_timer hold_timer

#define UIBUTTONS_TRANSITION_PRESSED() (button->prev_state == UIBUTTONS_STATE_RELEASED && curr_state == UIBUTTONS_STATE_PRESSED)
#define UIBUTTONS_TRANSITION_RELEASED() (button->prev_state == UIBUTTONS_STATE_PRESSED && curr_state == UIBUTTONS_STATE_RELEASED)
#define UIBUTTONS_TRANSITION_HELD() (button->prev_state == UIBUTTONS_STATE_PRESSED && curr_state == UIBUTTONS_STATE_PRESSED)
                  

#define UIBUTTONS_DEBOUNCING() (button->prev_state >= UIBUTTONS_STATE_RELEASED_DEBOUNCE)

#if UIBUTTONS_ENABLE_EDGES
extern void uibuttons_fire_rising_edge(uibutton_t *button);
extern void uibuttons_fire_falling_edge(uibutton_t *button);
#endif

#if (UIBUTTONS_ENABLE_SINGLE_PRESS || UIBUTTONS_ENABLE_LONG_PRESS)
extern void uibuttons_fire_short_press(uibutton_t *button);
#endif
#if UIBUTTONS_ENABLE_LONG_PRESS
extern void uibuttons_fire_long_press(uibutton_t *button);
extern void uibuttons_fire_longer_press(uibutton_t *button);
extern void uibuttons_fire_longest_press(uibutton_t *button);
extern void uibuttons_fire_long_release(uibutton_t *button);
extern void uibuttons_fire_longer_release(uibutton_t *button);
extern void uibuttons_fire_longest_release(uibutton_t *button);
#endif

#if UIBUTTONS_ENABLE_REPEAT_PRESS
extern void uibuttons_fire_repeat_press(uibutton_t *button);
#endif

#if UIBUTTONS_ENABLE_MULTI_CLICK
extern void uibuttons_fire_single_click(uibutton_t *button);
extern void uibuttons_fire_double_click(uibutton_t *button);
extern void uibuttons_fire_triple_click(uibutton_t *button);
#endif

/*!
    \fn
    \brief      Polling function for buttons
    \details    This function polls a button identified by the button callback and the button variables.

                Edges Engine:

                EVT_BUTTON_RISING_EDGE is fired on rising edge (Button transition from released to pressed)
                EVT_BUTTON_FALLING_EDGE is fired on falling edge (Button transition from pressed to released)

                Single Press Engine:

                EVT_BUTTON_SINGLE_PRESS is fired on falling edge (Button transition from pressed to released).
                Actually this is the same as EVT_BUTTON_FALLING_EDGE, but it can be used without the Edges Engine
                in case of need.

                Multi Press Engine:

                A single-click is raised if the button is not pressed again within the multi press timeout after
                the first press-release transition.

                A double-click is the act of pressing a computer mouse button twice quickly without moving
                the mouse. Double-clicking allows two different actions to be associated with the same mouse
                button. Often, single-clicking selects (or highlights) an object, while a double-click executes
                the function associated with that object.
                (http://en.wikipedia.org/wiki/Double-click)

                A triple-click is the action of clicking a computer mouse button three times quickly
                without moving the mouse. Along with clicking and double-clicking, triple-clicking
                allows three different actions to be associated with the same mouse button. Criticism
                of the double-click mechanism is even more valid[original research?] for triple-clicks.
                However, few applications assign critical actions to a triple click.
                (http://en.wikipedia.org/wiki/Triple-click)

                Repeat Press Engine:
                (http://www.dummies.com/how-to/content/set-your-keyboards-repeat-delay-and-repeat-rate.html)

                Initial repeat delay: When you press and hold a button, it repeats itself, spewing out
                repeat events to the system like bullets from a machine gun.
                The pause between pressing the key and when it starts repeating is the initial repeat delay.
                The first rising edge also causes a repeat press event!

                Repeat rate: After you press and hold down a button, it starts repeating itself.
                The speed at which it repeats is the repeat rate.

                Long press engine:
                The long press engine has 3 timeouts, long press timout, longer press timeout and longest press timeout.
                If a button is pressed for a longer time, the engine will pass long, longer and longest timeout and will fire
                an event at each timeout. As soon as the button is released, the according release event will be sent.




    \param
    \return
*/

void uibuttons_poll(uibutton_t *button)
{
    bool curr_state;
    curr_state = button->get();
    
    
    /* DEBOUNCING */
    /* --------------------------------------------------------------------*/
#if UIBUTTONS_ENABLE_DEBOUNCING
    
    if(UIBUTTONS_TRANSITION_PRESSED())
    {
      button->prev_state = UIBUTTONS_STATE_PRESSED_DEBOUNCE;
      button->debounce_timer = UIBUTTONS_DEBOUNCE_COUNT;
    }
    else if(UIBUTTONS_TRANSITION_RELEASED())
    {
      button->prev_state = UIBUTTONS_STATE_RELEASED_DEBOUNCE;
      button->debounce_timer = UIBUTTONS_DEBOUNCE_COUNT;
    }
    
    
    if(button->prev_state == UIBUTTONS_STATE_PRESSED_DEBOUNCE)
    {
      if(curr_state == UIBUTTONS_STATE_PRESSED)
      {
        if( button->debounce_timer != 0 )
        {
          button->debounce_timer--;
          return;          
        }
        else
        {
          button->prev_state = UIBUTTONS_STATE_RELEASED;          
        } 
      }
      else
      {
        button->prev_state = UIBUTTONS_STATE_RELEASED;
        return;
      }
    }
    else if(button->prev_state == UIBUTTONS_STATE_RELEASED_DEBOUNCE)
    {
      if(curr_state == UIBUTTONS_STATE_RELEASED)
      {
        if( button->debounce_timer != 0 )
        {
          button->debounce_timer--;
          return;          
        }
        else
        {
          button->prev_state = UIBUTTONS_STATE_PRESSED;          
        } 
      }
      else
      {
        button->prev_state = UIBUTTONS_STATE_PRESSED;
        return;
      }      
    }
#endif
    
    
    /* BUTTON HANDLING*/
    /* --------------------------------------------------------------------*/   

    if(UIBUTTONS_TRANSITION_PRESSED())
    {     
#if UIBUTTONS_ENABLE_MULTI_CLICK
        button->click_timer = UIBUTTONS_CLICK_TIMEOUT;
#endif
#if UIBUTTONS_ENABLE_EDGES
        uibuttons_fire_rising_edge(button);
#endif
#if UIBUTTONS_ENABLE_LONG_PRESS
        button->hold_timer = 0;
#endif
#if UIBUTTONS_ENABLE_REPEAT_PRESS
        uibuttons_fire_repeat_press(button);
        button->repeat_timer = UIBUTTONS_REPEAT_DELAY;
#endif
    }

    if (UIBUTTONS_TRANSITION_HELD())
    {
#if UIBUTTONS_ENABLE_MULTI_CLICK
        button->click_timer = UIBUTTONS_CLICK_TIMEOUT;
#endif
#if UIBUTTONS_ENABLE_LONG_PRESS
        if (button->hold_timer != UINT8_MAX) button->hold_timer++;
#endif
#if UIBUTTONS_ENABLE_REPEAT_PRESS
        if(!--button->repeat_timer)
        {
            uibuttons_fire_repeat_press(button);
            button->repeat_timer = UIBUTTONS_REPEAT_RATE;
        }
#endif
#if UIBUTTONS_ENABLE_LONG_PRESS
        switch(button->hold_timer)
        {
            case UIBUTTONS_LONG_PRESS_TIMEOUT:
                uibuttons_fire_long_press(button);
                break;
            case UIBUTTONS_LONGER_PRESS_TIMEOUT:
                uibuttons_fire_longer_press(button);
                break;
            case UIBUTTONS_LONGEST_PRESS_TIMEOUT:
                uibuttons_fire_longest_press(button);
                break;
        }
#endif
    }


    if(UIBUTTONS_TRANSITION_RELEASED())
    {
#if UIBUTTONS_ENABLE_MULTI_CLICK
        button->click_timer = UIBUTTONS_CLICK_TIMEOUT;
        button->click_count++;
#endif
#if UIBUTTONS_ENABLE_EDGES
        uibuttons_fire_falling_edge(button);
#endif
#if UIBUTTONS_ENABLE_LONG_PRESS
        if (button->hold_timer < UIBUTTONS_LONG_PRESS_TIMEOUT)
        {
            uibuttons_fire_short_press(button);
        }
        else if (button->hold_timer < UIBUTTONS_LONGER_PRESS_TIMEOUT)
        {
            uibuttons_fire_long_release(button);
        }
        else if (button->hold_timer < UIBUTTONS_LONGEST_PRESS_TIMEOUT)
        {
            uibuttons_fire_longer_release(button);
        }
        else
        {
            uibuttons_fire_longest_release(button);
        }
#else
#if UIBUTTONS_ENABLE_SINGLE_PRESS
        uibuttons_fire_short_press(button);
#endif
#endif
    }

#if UIBUTTONS_ENABLE_MULTI_CLICK
    if(button->click_timer)
    {
        button->click_timer--;
    }
    else
    {
        switch(button->click_count)
        {
            case 0:
                break;
            case 1:
                uibuttons_fire_single_click(button);
                break;
            case 2:
                uibuttons_fire_double_click(button);
                break;
            default:
                uibuttons_fire_triple_click(button);
                break;
        }
        button->click_count = 0;
    }
#endif

    button->prev_state = curr_state;
}

