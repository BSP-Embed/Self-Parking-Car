/*
 * dlyms.c
 *
 * Created: 12/8/2015 12:37:33 PM
 *  Author: bsp
 */ 
#include "dly.h"

void dlyms(int16u dly) {
	while (dly--)
		_delay_ms(1);
}

void dlyus(int16u dly) {
	while (dly--)
		_delay_us(1);
}