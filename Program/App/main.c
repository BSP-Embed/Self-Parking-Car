/*	Main.c: Application program for Self Parking Car	*/
/*	Written By	: Prashanth BS (info@bspembed.com)		*/
/*	Demo at		: www.youtube.com/c/bspembed			*/

#include"main.h"

static struct App Flags;

int main(void) {
	Init();
	while (TRUE) {
		if (Flags.Moni) {
			CheckAlco();
			ChkDoor();
			MeasDist(0xcc);
			Flags.Moni = FALSE;
		}
		if (Flags.AutoPark) {
			beep(1,150);
			if (Flags.Parked)
				Unpark();
			else
				AutoPark();
			Flags.AutoPark = FALSE;
		}
		sleep_cpu();
	}
	return 0;
}
static void Init(void) {
	buzinit();
	ledinit();
	beep(2,100);
	lcdinit();
	IRSensInit();
	AlcoSensInit();
	DoorSensInit();
	MotInit();
	servoinit();
	ultinit();
	Tmr2Init();
	EXTINTinit();
	inittest();
	DispTitle();
	sei();
	sleep_enable();
	sleep_cpu();
}
static void DispTitle(void) {
	lcdclr();
	lcdws("Auto Parking Veh");
	lcdr2();
	lcdws("Distance:");
}
static int8u AutoPark(void){
	int8u ParkDist = 0;
	int16u Count = 0;
	Flags.Parked = FALSE;
	lcdclrr(1);
	lcdws("Find'g Par Space");
	Front();
	lcdclrr(0);
	while (++Count < ITERATIONS) {
		if (MeasDist(0x80) > PARKING_DEPTH) {
			if(++ParkDist > PARKING_DISTANCE) {
				ParkVehicle();
				Flags.Parked = TRUE;
				return 1;
			}
			dlyms(100);
		} else
			ParkDist = 0;
		lcdwint(0x88, ParkDist);
		lcdwint(0x8c,Count);
	}
	lcdclrr(1);
	lcdws("No Parking Dist");
	MotStop();
	beep(3,150);
	dlyms(1000);
	DispTitle();
}
static void ParkVehicle(void) {
	int8u i;
	lcdclr();
	lcdws(" Distance Found");
	beep(2,150);
	Front();
	dlyms(4000);
	MotStop();
	lcdr2();
	lcdws("    Parking.");
	Flags.Back = TRUE;
	Strt2Left();
	Back();
	i = 0;
	while (i < 100) {
		if (!Flags.Obstacle) {
			Back(); 
			i++;
		} else
			MotStop();
		dlyms(55);
	}
	Left2Strt();
	Strt2Right();
	i = 0;
	while (i < 100) {
		if (!Flags.Obstacle) {
			Back();
			i++;
		} else
		MotStop();
		dlyms(55);
	}
	MotStop();
	Right2Strt();
	Mot1Aclk();
	dlyms(750);
	MotStop();
	lcdclr();
	lcdws("*****Parked*****");
	Flags.Back = FALSE;
	beep(3,150);
	dlyms(2000);
	DispTitle();
}
static void Unpark(void) {
	int8u i;
	lcdclr();
	lcdws("   Unparking");
	Back();
	dlyms(750);
	MotStop();
	Strt2Right();
	Flags.Front = TRUE;
	i = 0;
	while (i < 100) {
		if (!Flags.FrontObstacle) {
			Front();
			i++;
		} else
		MotStop();
		dlyms(47);
	}
	Right2Strt();
	Strt2Left();
	i = 0;
	while (i < 100) {
		if (!Flags.FrontObstacle) {
			Front();
			i++;
		} else
		MotStop();
		dlyms(40);
	}
	Left2Strt();
	dlyms(2000);
	MotStop();
	lcdclr();
	lcdws("****UNPARKED****");
	Flags.Parked = FALSE;
	Flags.Front = FALSE;
	beep(3,150);
	dlyms(2000);
	DispTitle();
}
static void inittest(void) {
	lcdclr();
	lcdws("Chk Alcol:");
	if (ReadAlco()) {
		lcdws(" NOT OK");
		while (ReadAlco()) {
			beep(1,100);
			dlyms(2000);
		}
	} else {
		lcdws(" OK");
		dlyms(1000);
	}
	lcdclr();
	lcdws("Chk Doors:");
	if (DoorRead()) {
		lcdws(" NOT OK");
		while (DoorRead()) {
			beep(1,100);
			dlyms(2000);
		}
	} else {
		lcdws(" OK");
		dlyms(1000);
	}
}
static void Tmr2Init(void) {
	TCNT2	= 0;
	TIMSK	|= _BV(TOIE2);							/* ENABLE OVERFLOW INTERRUPT */
	TCCR2	|=  _BV(CS22) | _BV(CS21) | _BV(CS20); /* PRESCALAR BY 1024 */
}

/* overflows at every 32msec */
ISR(TIMER2_OVF_vect) {
	static int8u i, j, k, l;
	TCNT2 = 0;
	if (++i >= 156) i = 0;
	switch(i) {
		case 0: case 6: ledon(); break;
		case 3: case 9: ledoff(); break;
	}
	if (!Flags.Moni && ++j >= 31) {
		Flags.Moni = TRUE;
		j = 0;
	}
	if (Flags.Alco || Flags.Door) {
		if (++k >= 94)
		k = 0;
		switch (k) {
			case 0: case 6: buzon(); break;
			case 3: case 9: buzoff(); break;
		}
	}
	if (Flags.Back) {
		if (BackIRRead())
			Flags.Obstacle = TRUE;
		else
			Flags.Obstacle = FALSE;
		if (++l >= 31)
			l = 0;
		switch (l) {
			case 0: case 6: buzon(); break;
			case 3: case 9: buzoff(); break;
		}
	}
	if (Flags.Front) {
		if (FrntIRRead())
			Flags.FrontObstacle = TRUE;
		else
			Flags.FrontObstacle = FALSE;
	}
}
static void EXTINTinit(void) {
	INTDDR 	&=  ~_BV(INT1_PIN);
	INTPORT |=  _BV(INT1_PIN);
	GICR	|= _BV(INT1);		//ENABLE EXTERNAL INTERRUPT
	MCUCR	|= _BV(ISC11);		//FALLING EDGE INTERRUPT
}
ISR(INT1_vect) {
	Flags.AutoPark	=  TRUE;
	GICR			|= _BV(INT1);
}
static void CheckAlco(void) {
	if (ReadAlco()) {
		if (!Flags.DispAlco) {
			Flags.DispAlco = TRUE;
			lcdclrr(1);
			lcdws("Alcohol Consumed");
			Flags.Alco = TRUE;
		}
	}else {
		if (Flags.DispAlco) {
			Flags.Alco = FALSE;
			Flags.DispAlco = FALSE;
			buzoff();
			DispTitle();
		}
	}
}
static void ChkDoor(void) {
	if (DoorRead()) {
		if (!Flags.DispDoor) {
			Flags.DispDoor = TRUE;
			lcdclrr(1);
			lcdws("Door Opened");
			Flags.Door = TRUE;
		}
	}else {
		if (Flags.DispDoor) {
			Flags.Door = FALSE;
			Flags.DispDoor = FALSE;
			buzoff();
			DispTitle();
		}
	}
}