#ifndef DS3231_H_
#define DS3231_H_

#include <avr/io.h>
#include "Zegarek.h"
#include "TWI_I2C.h"

////////////////////////////////////////////////////////////////////////////////////
#define DS3231_ADDRES 0xD0

////////////////////////////////////////////////////////////////////////////////////
typedef union
{
	uint8_t bytes[7];
	struct
	{
		uint8_t sek;
		uint8_t min;
		uint8_t godz;
		uint8_t dzien_tyg;
		uint8_t dzien;
		uint8_t mies;
		uint8_t rok;
	};
} DATETIME_t;

typedef struct
{
	int8_t stopnie;
	uint8_t dziesiate;
}TEMP_t;

DATETIME_t czas;
TEMP_t temperatura;

////////////////////////////////////////////////////////////////////////////////////
void InitDS3231(void);
void DS3231_getdatetime(DATETIME_t *dt);
void DS3231_givedatetime(DATETIME_t *dt);
void DS3231_gettemp(TEMP_t *tmp);
uint8_t dectobcd(uint8_t dec);

#endif /* DS3231_H_ */