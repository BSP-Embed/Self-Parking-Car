#ifndef _APP_H
#define _APP_H

/************* LCD CONFIGURATION ****************/
#define LCD_DDR           	   		DDRC 
#define LCD_DATA_PORT          		PORTC
#define LCD_ENABLE_PIN        		PC3 
#define LCD_REGISTER_SELECT_PIN     PC2
#define DISPLAY_INIT				1
#define LCD_NSCRL					1
#define FLOAT_T0_STRING				1
#define DECIMAL_PRECISION			100
/******** LCD CONFIGURATION ENDS ****************/

/******** BUZZER: CONFIGURATION ****************/
#define	BUZ_DDR				DDRC
#define	BUZ_PORT			PORTC
#define	BUZ_PIN				PC1
#define OFF_TIME			100
/******** BUZZER CONFIGURATION ENDS ************/

/********* LED: CONFIGURATION ******************/
#define	LED_DDR				DDRC
#define	LED_PORT			PORTC
#define	LED_PIN				PC0
#define OFF_TIME			100
/******** LED CONFIGURATION ENDS *************/

/******** MOTOR CONFIGURATION   *************/
#define MOT_PORT			PORTA
#define MOT_DDR				DDRA
#define M1_AN				PA3
#define M1_CA				PA4
#define M2_AN				PA5
#define M2_CA				PA6
/******** MOTOR CONFIGURATION ENDS  *********/

/***** SERVO MOTOR CONFIGURATION   *********/
#define SERVO_DDR			DDRD
#define SERVO_PORT			PORTD
#define SERVO1				PD5
/***** SERVO MOTOR CONFIGURATION  END *****/

/******* ALCOHOL SENSOR CONFIG *********/
#define ALSENS_DDR			DDRD
#define ALSENS_PORT			PORTD
#define ALSENS_PPIN			PIND
#define ALSENS_PIN			PD2
/************************************/

/******* DOOR SENSOR CONFIG  *********/
#define DOOR_SENS_PORT		PORTD
#define DOOR_SENS_DDR		DDRD
#define DOOR_SENS_PPIN		PIND
#define DOOR_SENS_PIN		PD7
/************************************/

/******* ULTRASONIC SENSOR PIN DEFINITION *******/
#define ULTSEN_DDR			DDRA
#define	ULTSEN_PORT			PORTA
#define ULTSEN_PIN			PINA
#define TRIG_PIN			PA1
#define ECHO_PIN			PA0
/*****************************************/

/******* IR SENSOR PIN DEFINITION ******/
#define IR_SENS_DDR			DDRD
#define IR_SENS_PORT		PORTD
#define IR_SENS_PPIN		PIND
#define IR_SENS1_PIN		PD4
#define IR_SENS2_PIN		PD6
#define IR_SENSORS_2
/**************************************/

/*********** EXTERNAL INTERRUPT PINS *************/
#define INTDDR				DDRD
#define INTPORT				PORTD
#define INTPIN				PIND
#define INT1_PIN			PD3
/**********************************************/

#endif
