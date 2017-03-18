#ifndef _LED_H
#define _LED_H

#include 	<avr/io.h>
#include	"types.h"

//DEFINE LED PORT
#define	LED_DDR			DDRC
#define	LED_PORT		PORTC
#define	LED_PIN			PC0

#define OFF_TIME		100

//DEFINE MACRO
#define	ledon()			LED_PORT |= _BV(LED_PIN)
#define	ledoff()		LED_PORT &= ~_BV(LED_PIN)


//FUNCTION PROTOTYPES
void blink		(int8u nblink, int8u ontime);
void ledinit	(void);

#endif
