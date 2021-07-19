/*!
	/file	uileds_leds.c

*/



#include "myos.h"
#include "uileds_process.h"
#include "gpio.h"



void set_ld3(bool state)
{
    (state)?GPIO_SET(LD3):GPIO_RST(LD3);
}

void set_ld4(bool state)
{
    (state)?GPIO_SET(LD4):GPIO_RST(LD4);
}

UILEDS_LED(LD3,set_ld3);
UILEDS_LED(LD4,set_ld4);
UILEDS_LEDS(&LD3,&LD4);



void uileds_leds_module_init(void)
{
    UILEDS_SET_PATTERN(LD3,fast_flashing,UILEDS_ORIG);
    UILEDS_SYNC(LD4,LD3,UILEDS_INV);
    uileds_process_module_init();
}


