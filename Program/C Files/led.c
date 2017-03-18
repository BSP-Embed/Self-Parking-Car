/* led.c : LED interface programs */
#include "led.h"

void ledinit(void)
{
	LED_DDR 		|= _BV(LED_PIN);
	LED_PORT 		&= ~_BV(LED_PIN);
}

void blink(int8u nblink, int8u ontime)
{
	while(nblink--){
		ledon();
		dlyms(ontime);
		ledoff();
		dlyms(100);
	}
}

	
