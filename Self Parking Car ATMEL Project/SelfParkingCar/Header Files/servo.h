#ifndef SERVO_H
#define SERVO_H

#include "includes.h"

//DEFINE CONSTANT
#define 	ZERO_DEGREE		1500

//#define		RIGHT_EXTM		2175
//#define		LEFT_EXTM		925

#define		RIGHT_EXTM		2000
#define		LEFT_EXTM		1025

#define		DELTA_ANGLE		25
#define		DELTA_SPEED		25

#define		TURN_LDELAY		2000
#define		TURN_RDELAY		5000

//FUNCTION PROTOTYPES 

void servoinit		(void);
void Strt2Right		(void);
void Right2Strt		(void);
void Left2Strt		(void);
void Strt2Left		(void);
void TurnRight		(void);
void TurnLeft		(void);
#endif
