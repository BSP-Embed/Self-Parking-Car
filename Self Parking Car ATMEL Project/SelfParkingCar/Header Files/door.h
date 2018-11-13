#ifndef DOOR_SENSOR_H
#define DOOR_SENSOR_H

#include "includes.h"

#define ReadDoor()		(DOOR_SENS_PPIN & _BV(DOOR_SENS_PIN))

void	DoorSensInit	(void);
int8u 	DoorRead		(void);

#endif