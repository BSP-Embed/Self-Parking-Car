#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include "includes.h"

#define FrntIRRead()		IRRead1()
#define BackIRRead()		IRRead2()
#define IRRead()			IRRead1()

void	IRSensInit	(void);
int8u	IRRead1		(void);
int8u	IRRead2		(void);

#endif