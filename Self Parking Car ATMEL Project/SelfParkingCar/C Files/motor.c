#include "motor.h"

void motorinit(void) {
	M1Init();
	M2Init(); 
}
void M1Init(void){
	MOT_DDR	|= _BV(M1_AN) | _BV(M1_CA);
	MOT_PORT	&= ~(_BV(M1_AN) | _BV(M1_CA));
}
void M2Init(void){
	MOT_DDR	|= _BV(M2_AN) | _BV(M2_CA);
	MOT_PORT	&= ~(_BV(M2_AN) | _BV(M2_CA));
}
void  Mot1Clk(void) {
	MOT_PORT |= _BV(M1_AN);
	MOT_PORT &= ~_BV(M1_CA);
}
void Mot1Aclk(void) {
	MOT_PORT |= _BV(M1_CA);
	MOT_PORT &= ~_BV(M1_AN);
}
void  Mot2Clk(void) {
	MOT_PORT |= _BV(M2_AN);
	MOT_PORT &= ~_BV(M2_CA);
}
void Mot2Aclk(void) {
	MOT_PORT |= _BV(M2_CA);
	MOT_PORT &= ~_BV(M2_AN);
}
void MotStop(void) {
	MOT_PORT &= ~(_BV(M1_AN) | _BV(M1_CA));
}
void Forward(void) {
	Mot1Clk();
	Mot2Aclk();
}
void Backward(void) {
	Mot1Aclk();
	Mot2Clk();
}
void Right(void) {
	Mot1Aclk();
	Mot2Aclk();
}
void Left(void) {
	Mot1Clk();
	Mot2Clk();
}
void Stop(void) {
	MOT_PORT &= ~(_BV(M1_AN) | _BV(M1_CA));
	MOT_PORT &= ~(_BV(M2_AN) | _BV(M2_CA));
}