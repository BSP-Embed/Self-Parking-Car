#ifndef SLEEP_H
#define SLEEP_H

#include "includes.h"


#define sleep()				do {									\
								set_sleep_mode(SLEEP_MODE_IDLE);	\
								sleep_mode();						\
							} while (0);

#endif
