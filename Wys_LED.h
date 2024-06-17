#ifndef WYS_LED_H_
#define WYS_LED_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "SPI.h"

////////////////////////////////////////////////////////////////////////////////////
// nazwy znaków wyœwietlaczy
#define digit_A 10
#define digit_C 11
#define digit_E 12
#define digit_F 13
#define digit_stopien 14
#define digit_pusto 15

////////////////////////////////////////////////////////////////////////////////////
typedef union
{
	volatile uint8_t cy[8];
	struct 
	{
		uint8_t temp_jednostka;
		uint8_t temp_ulst;
		uint8_t temp_jst;
		uint8_t temp_dst;
		uint8_t time_jmin;
		uint8_t time_dmin;
		uint8_t time_jgodz;
		uint8_t time_dgodz;
	};
}WYSWIETLACZ_t;
	
extern volatile WYSWIETLACZ_t cyfry;
extern volatile uint8_t wys_brightness;
////////////////////////////////////////////////////////////////////////////////////
void InitWys_LED(void);

////////////////////////////////////////////////////////////////////////////////////

#endif /* WYS_LED_H_ */