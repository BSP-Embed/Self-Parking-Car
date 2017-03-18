#ifndef LCD_H
#define LCD_H

//INCLUDES
#include "includes.h"

//DEFINE CONSTANT
#define OUTPUT 		 0xFF
#define LCD_DOT		'.'
#define LCD_SPC		' '

//DEFINE PROTOTYPES
void	lcdwc			(int8u command);
void	lcdwd			(char ch);
void	lcdws			(char *s);
void	lcdinit			(void);
void	lcddinit		(void);
void	lcdclrr			(int8u rowno);
void	lcdclr			(void);
void	lcdr1			(void);
void	lcdr2			(void);
void	itoa			(signed int n, char s[]);
void	reverse			(char s[]);
void	lcdwint			(int8u loc,signed int x);
void	lcdwlng			(int8u loc,unsigned long x);
void	ltoa			(unsigned long n, char s[]);
void	lcdclrr			(int8u rowno);
void	lcdscrolinit	(void);
double	atof			(char *s);


#if defined FLOAT_T0_STRING > 0
void ftoa(double n, char *res, int afterpoint);
int intToStr(int x, char str[], int d);
void rever(char *str, int len);
#endif

#endif

