
#include "servo.h"

int16u angle;

void servoinit(void) {
	SERVO_DDR  |= _BV(SERVO1);
	SERVO_PORT &= ~_BV(SERVO1);
	
	TCCR1A |= _BV(COM1A1)| _BV(WGM11) ;				  //FAST PWM ,TOP IS ICR1, CLEAR ON COMPARE MATCH
	TCCR1B |= _BV(WGM13)| _BV(WGM12)| _BV(CS11);      // CLOCK PRESCALAR BY 8
	ICR1 = 20000;					                  // FREQUENCY IS 50 HZ
	OCR1A =  ZERO_DEGREE;
	angle =  ZERO_DEGREE;
}

void Strt2Right(void) {
	while (angle < RIGHT_EXTM) {
		angle = angle + DELTA_ANGLE;
		OCR1A = angle;
		dlyms(DELTA_SPEED);
	}
	
}
void Right2Strt(void) {
	while (angle > ZERO_DEGREE) {
		angle = angle - DELTA_ANGLE;
		OCR1A = angle;
		dlyms(DELTA_SPEED);
	}
	
}
void Strt2Left(void){
	while (angle > LEFT_EXTM) {
		angle = angle - DELTA_ANGLE;
		OCR1A = angle;
		dlyms(DELTA_SPEED);
	}
	
}
void Left2Strt(void){
	while (angle < ZERO_DEGREE) {
		angle = angle + DELTA_ANGLE;
		OCR1A = angle;
		dlyms(DELTA_SPEED);
	}
}
void TurnRight(void){
	Strt2Right();
	dlyms(TURN_RDELAY);	/* Motor Speed */
	Right2Strt();
}
void TurnLeft(void){
	Strt2Left();
	dlyms(TURN_LDELAY);
	Left2Strt();
}