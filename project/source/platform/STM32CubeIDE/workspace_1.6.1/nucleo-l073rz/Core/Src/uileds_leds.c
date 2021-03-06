/*!
	/file	uileds_leds.c

*/



#include "myos.h"
#include "uileds_leds.h"
#include "gpio.h"



void set_ld2(bool state)
{
    (state)?GPIO_SET(LD2):GPIO_RST(LD2);
}

UILEDS_LED(LD2,set_ld2);
UILEDS_LEDS(&LD2);



void uileds_leds_module_init(void)
{
    UILEDS_SET_PATTERN(LD2,fast_flashing,UILEDS_ORIG);
    uileds_process_module_init();
}


