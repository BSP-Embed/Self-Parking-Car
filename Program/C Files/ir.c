#include "ir.h"

void IRSensInit(void) {
	IR_SENS_DDR 	&= ~_BV(IR_SENS1_PIN);
	IR_SENS_PORT 	|= _BV(IR_SENS1_PIN);
	#ifdef IR_SENSORS_2
		IR_SENS_DDR 	&= ~_BV(IR_SENS2_PIN);
		IR_SENS_PORT 	|= _BV(IR_SENS2_PIN);
	#endif
}

int8u IRRead1(void) {
	if (IR_SENS_PPIN & _BV(IR_SENS1_PIN))
		return 1;
	else
		return 0;
}
#ifdef IR_SENSORS_2 
	int8u IRRead2(void) {
		if (IR_SENS_PPIN & _BV(IR_SENS2_PIN))
			return 1;
		else
			return 0;
	}
#endif