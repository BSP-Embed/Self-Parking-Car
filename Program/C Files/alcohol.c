#include "alcohol.h"

void AlcoSensInit(void) {
	ALSENS_DDR &= ~_BV(ALSENS_PIN);
	ALSENS_PORT |= _BV(ALSENS_PIN);
	
	lcdclrr(1);
	lcdws("AlcoSens Init:");
	while ((ALSENS_PPIN & _BV(ALSENS_PIN)) == 0);
	lcdws("OK");
	dlyms(DISP_DLY);
	lcdclrr(1);
}
int8u ReadAlco(void) {
	if ((ALSENS_PPIN & _BV(ALSENS_PIN)) == 0)
		return 1;
	else
		return 0;
}