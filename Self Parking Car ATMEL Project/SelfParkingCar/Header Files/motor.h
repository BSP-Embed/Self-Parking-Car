#ifndef _MOTOR_H
#define _MOTOR_H

#include "includes.h"

#define mot1on()			MOT_PORT |= _BV(MOT1_AN)
#define mot1off()			MOT_PORT &= ~_BV(MOT1_AN)

#define mot2on()			MOT_PORT |= _BV(MOT2_AN)
#define mot2off()			MOT_PORT &= ~_BV(MOT2_AN)

#define MotClk()			Mot1Clk()
#define MotOn()				mot1on();
#define MotOff()			mot1off();

#define MotInit()			M1Init()
#define Front()				Forward()
#define Back()				Backward()


void	motorinit	(void);
void	Mot1Clk		(void);
void	Mot1Aclk	(void);
void	Mot2Clk		(void);
void	Mot2Aclk	(void);
void	MotStop		(void);

#endif
