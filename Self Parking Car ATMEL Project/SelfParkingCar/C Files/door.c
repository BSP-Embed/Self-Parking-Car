#include "door.h"

void DoorSensInit(void) {
	DOOR_SENS_DDR &= ~_BV(DOOR_SENS_PIN);
	DOOR_SENS_PORT |= _BV(DOOR_SENS_PIN);
}
int8u DoorRead(void) {
	if ((DOOR_SENS_PPIN & _BV(DOOR_SENS_PIN)) == 0)
		return 0;
	else 
		return 1;
}
