#include "DS3231.h"

////////////////////////////////////////////////////////////////////////////////////
static uint8_t bcdtodec(uint8_t bcd);
uint8_t dectobcd(uint8_t dec);

////////////////////////////////////////////////////////////////////////////////////
void InitDS3231(void)
{
	uint8_t ctrl = 0;
	
	TWI_SetBitrate(100);
	TWI_write_buf(DS3231_ADDRES, 0x0E, 1, &ctrl);	//
	
	DDR(I2C_PORT_INT) &= ~(1<<I2C_INT);
	PORT(I2C_PORT_INT) |= (1<<I2C_INT);
	
	EICRA |= (1<<ISC01)|(1<<ISC00);		// zbocze narastaj¹ce na INT 0
	EIFR |= (1<<INTF0);		// kasowanie flagi
}

///////////////////////////////////////////////////////////////////////////////////
void DS3231_getdatetime(DATETIME_t *dt)
{
	uint8_t i;
	uint8_t buff[7];
	
	TWI_read_buf(DS3231_ADDRES, 0x00, 7, buff);
	for(i=0; i<7; i++)
	{
		dt->bytes[i] = bcdtodec(buff[i]);
	}
}

///////////////////////////////////////////////////////////////////////////////////
void DS3231_givedatetime(DATETIME_t *dt)
{
	uint8_t i;
	uint8_t buff[7];
	
	for(i=0; i<7; i++)
	{
		buff[i] = dectobcd(dt->bytes[i]);
	}
	TWI_write_buf(DS3231_ADDRES,0x00,7,buff);
}

///////////////////////////////////////////////////////////////////////////////////
void DS3231_gettemp(TEMP_t *tmp)
{
	uint8_t buff[2];
	
	TWI_read_buf(DS3231_ADDRES, 0x11, 2, buff);
	tmp->stopnie = buff[0];
	tmp->dziesiate = buff[1]>>6;
	
	TWI_read_buf(DS3231_ADDRES,0x0E,1,buff);
	buff[0] |= (1<<5);
	TWI_write_buf(DS3231_ADDRES,0x0E,1,buff);
}

////////////////////////////////////////////////////////////////////////////////////
uint8_t dectobcd(uint8_t dec)
{
	return ((dec/10)<<4) | (dec%10);
}

////////////////////////////////////////////////////////////////////////////////////
static uint8_t bcdtodec(uint8_t bcd)
{
	return ((((bcd)>>4) & 0x0F) * 10) + ((bcd) & 0x0F);
}