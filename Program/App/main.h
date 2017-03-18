#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define PARKING_DEPTH		0.16	/* in Meters */
#define ITERATIONS			250
#define PARKING_DISTANCE	40		/* in Centimeters */


struct  App {
	volatile char AutoPark		:1;
	volatile char Moni			:1;
	volatile char Door			:1;
	volatile char Alco			:1;
	volatile char DispDoor		:1;
	volatile char DispAlco		:1;
	volatile char Back			:1;
	volatile char Front			:1;
	volatile char Obstacle		:1;
	volatile char FrontObstacle	:1;
	volatile char Parked		:1;
};

//DEFINE FUNCTION PROTOTYPE
static	void	Init		(void);
static	void	inittest	(void);
static	void	DispTitle	(void);
static	void	CheckAlco	(void);
static	void	ChkDoor		(void);
static	void	EXTINTinit	(void);
static	void	Tmr2Init	(void);
static	int8u	AutoPark	(void);
static	void	ParkVehicle	(void);
static	void	Unpark		(void);

#endif

