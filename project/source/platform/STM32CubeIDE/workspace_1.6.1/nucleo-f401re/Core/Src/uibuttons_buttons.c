/*!
  \file

  \brief

  \details

  \author

  \copyright    Copyright (c) 2013, Marco Bacchi (marco@bacchi.at)
                All rights reserved.

                Redistribution and use in source and binary forms, with or without modification,
                are permitted provided that the following conditions are met:

                - Redistributions of source code must retain the above copyright notice, this list of
                  conditions and the following disclaimer.
                - Redistributions in binary form must reproduce the above copyright notice, this list
                  of conditions and the following disclaimer in the documentation and/or other materials
                  provided with the distribution.
                - Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to
                  endorse or promote products derived from this software without specific prior written permission.

                THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
                IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
                FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
                CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
                DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
                DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
                WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
                WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  \date 17.10.2013
*/
#include "uibuttons_buttons.h"
#include "uibuttons_process.h"
#include "gpio.h"
#include "uileds_leds.h"

static bool uibuttons_get_b1()
{  
	if ( GPIO_RD(B1) == GPIO_STATE_SET )
	{
		return false;
	}

	return true;
}


UIBUTTON_LIST_BEGIN     
UIBUTTON(uibuttons_get_b1)
/* add further buttons here */
UIBUTTON_LIST_END

typedef enum{
   UIBUTTON_B1 = 0
/* add further buttons here in same order as in uibutton list*/
} uibuttons_id_t;


void uibuttons_fire_rising_edge(uibutton_t *button)
{

}

void uibuttons_fire_falling_edge(uibutton_t *button)
{

}

void uibuttons_fire_long_press(uibutton_t *button)
{

}

void uibuttons_fire_longer_press(uibutton_t *button)
{

}

void uibuttons_fire_longest_press(uibutton_t *button)
{

}

void uibuttons_fire_short_press(uibutton_t *button)
{

}

void uibuttons_fire_long_release(uibutton_t *button)
{

}

void uibuttons_fire_longer_release(uibutton_t *button)
{

}

void uibuttons_fire_longest_release(uibutton_t *button)
{

}

void uibuttons_fire_repeat_press(uibutton_t *button)
{

}

void uibuttons_fire_single_click(uibutton_t *button)
{
	  switch( UIBUTTONS_GET_ID(button) )
	  {
	    case  UIBUTTON_B1:
			UILEDS_SET_PATTERN(LD2,single_flash,UILEDS_ORIG);
			break;
	  }
}

void uibuttons_fire_double_click(uibutton_t *button)
{
	  switch( UIBUTTONS_GET_ID(button) )
	  {
	    case  UIBUTTON_B1:
			UILEDS_SET_PATTERN(LD2,double_flash,UILEDS_ORIG);
			break;
	  }
}

void uibuttons_fire_triple_click(uibutton_t *button)
{
	  switch( UIBUTTONS_GET_ID(button) )
	  {
	    case  UIBUTTON_B1:
			UILEDS_SET_PATTERN(LD2,triple_flash,UILEDS_ORIG);
			break;
	  }
}

void uibuttons_buttons_module_init(void)
{
   uibuttons_process_module_init();
}
