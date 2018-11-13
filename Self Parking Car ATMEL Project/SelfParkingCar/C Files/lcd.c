
#include "LCD.h"

static void  LCDEnable		(void);
static void  LCDReset		(void);
static void  LCDWriteByte	(char  ch);

int8u lcdptr;

static void  LCDEnable(void)
{
    LCD_DATA_PORT &= ~ (_BV(LCD_ENABLE_PIN)); 
    dlyus(1);
    LCD_DATA_PORT |=  _BV(LCD_ENABLE_PIN);  
}

void lcdwc(int8u x)
{
    LCD_DATA_PORT &= ~ (_BV(LCD_REGISTER_SELECT_PIN)); 
    LCDWriteByte(x);
}

void lcdwd(char ch)
{
    LCD_DATA_PORT |=  _BV(LCD_REGISTER_SELECT_PIN);
    LCDWriteByte(ch);
}

void lcdws(char *s){
	while (*s) {
			#ifdef LCD_20X4
		switch(lcdptr) {
			case 0x80+20:
				lcdptr = 0xC0;
				break;
			case 0xC0+20:
				lcdptr = 0x94;
				break;
			case 0x94+20:
				lcdptr = 0xD4;
				break;
			case 0xD4+20:
				lcdptr = 0x80;
				break;
		}
		#else
			switch(lcdptr) {
				case 0x80+16:
				lcdptr = 0xC0;
				break;
				case 0xC0+16:
				lcdptr = 0x80;
				break;
			}
		#endif
		lcdwc(lcdptr++);
		lcdwd(*s++);
	}
}

void lcdinit(void)
{
    LCD_DDR = (LCD_DDR & 0x03) | 0xfc;
	LCD_DATA_PORT    &=  0x03;

	dlyms(40);
	LCDReset();
    lcdwc(0x28);
    lcdwc(0x0C);
    lcdwc(0x06);
    lcdwc(0x01); 
	lcdclr();
	#if DISPLAY_INIT > 0
		lcddinit();
	#endif
}
static void LCDReset(void)
{
	lcdwc(0x33);
	dlyms(5);
	lcdwc(0x33);
	dlyus(500);
	lcdwc(0x32);
	dlyus(500);
}
void lcdscrolinit(void)
{
	lcdwc(0x01);
	lcdwc(0x20);
	lcdwc(0x07);
	lcdwc(0x8f);
}
void lcddinit(void)
{
	int8u i, j, adr;
	
	lcdws("  INITIALIZING");
	lcdr2();
	for ( j = 0; j < LCD_NSCRL; j++ ) {
		adr = 0xc0;						// 2nd row, first coloumn
		for ( i = 0; i < 16; i++ ) {
			lcdwc(adr);			
			lcdwd(LCD_DOT);				
			if ( i < 8 ) dlyms(200+(50*i)); else dlyms(25);
			lcdwc(adr);			
			lcdwd(LCD_SPC);			
			adr++;					// increment display aadress
		}
	} 
}

static void  LCDWriteByte(char  LCDData)
{
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F)|(LCDData & 0xF0);
    LCDEnable();
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F)|((LCDData << 4) & 0xF0);
    LCDEnable();
    dlyus(750);
}
void lcdclr(void)
{
	lcdwc(0x01);
	lcdptr = 0x80;	  /* Clear display LCD */
}
void lcdclrr(int8u rowno){
	int8u i;
	switch (rowno) {
		case 0:
				lcdr1();
				break;
		case 1:
				lcdr2();
				break;
	}
	for (i = 0; i < 16; i++)
		lcdwd(LCD_SPC);
	switch (rowno) {
		case 0:
				lcdr1();
				break;
		case 1:
				lcdr2();
				break;
	}
 }
 void lcdr1(void)
 {
	lcdwc(0x80); 	  /* Begin at Line 1 */
	lcdptr = 0x80;
 }
  void lcdr2(void)
 {
	lcdwc(0xc0); 	  /* Begin at Line 1 */
	lcdptr = 0xc0;
 }
 void lcdwint(int8u loc,signed int x)
 {
	 int8u str[10];
	 lcdptr = loc;
	 lcdws("   ");
	 lcdptr = loc;
	 itoa(x, str);
	 lcdws(str);
 }
 void lcdwlng(int8u loc,unsigned long x)
 {
	 int8u str[24];
	 lcdptr = loc;
	 lcdws("           ");
	 lcdptr = loc;
	 ltoa(x, str);
	 lcdws(str);
}

void ltoa(unsigned long n, char s[])
{
	int i;
	
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	s[i] = '\0';
	reverse(s);
}
 void itoa(signed int n, char s[])
{
	int i, sign;
	
	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

#if FLOAT_T0_STRING > 0

// reverses a string 'str' of length 'len'
void rever(char *str, int len)
{
	int i=0, j=len-1, temp;
	while (i<j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++; j--;
	}
}

// Converts a given integer x to string str[].  d is the number
// of digits required in output. If d is more than the number
// of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x)
	{
		str[i++] = (x%10) + '0';
		x = x/10;
	}
	
	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
	str[i++] = '0';
	
	rever(str, i);
	str[i] = '\0';
	return i;
}

// Converts a floating point number to string.
void ftoa(double n, char *res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;
	
	// Extract floating part
	double fpart = n - (float)ipart;
	
	// convert integer part to string
	int i = intToStr(ipart, res, 0);
	
	// check for display option after point
	if (afterpoint != 0)
	{
		res[i] = '.';  // add dot
		
		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter is needed
		// to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);
		
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}


#endif
/* atof: convert string s to double ; pointer version */
double atof(char *s)
{
	double val,power;
	int sign;
	
	for(; isspace(*s); s++);	/* skip white spaces */
	sign = (*s == '-')? -1:1;
	if (*s == '+' || *s == '-')
		s++;
	for (val = 0.0; isdigit(*s); s++)
		val = 10.0 * val + (*s - '0');
	if (*s == '.')
		s++;
	for (power = 1.0; isdigit(*s); s++) {
		val = 10.0 * val + (*s - '0');
		power *= 10.0;
	}
	return (float)(sign * val) / power;
}

	 
void reverse(char s[])
{
	int c,i,j;
	for (i = 0, j = strlen(s)-1; i < j; i++,j--) 
		c = s[i], s[i] = s[j], s[j] = c;
} 
