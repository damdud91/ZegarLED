#include "OneWire.h"

////////////////////////////////////////////////////////////////////////////////////
//MAKRA
#define DQ_LO	DDR(DQ_PORT) |= (1<<DQ)			// wyzerowanie stanu na magistrali
#define DQ_HI	DDR(DQ_PORT) &= ~(1<<DQ)		// ustawienie stanu na magistrali

////////////////////////////////////////////////////////////////////////////////////
//FUNKCJE
void OneWire_Reset(void)
{
	PORT(DQ_PORT) &= ~(1<<DQ);
	do{
		DQ_LO;
		_delay_us(490);
		DQ_HI;
		_delay_us(70);
	}while(PIN(DQ_PORT) & (1<<DQ));
	_delay_us(490);
}

////////////////////////////////////////////////////////////////////////////////////
void OneWire_WriteByte(uint8_t byte)
{
	uint8_t i;
	
	for(i=0;i<8;i++)
	{
		DQ_LO;
		_delay_us(5);
		if(byte & 0x01)
		DQ_HI;
		_delay_us(60);
		DQ_HI;
		_delay_us(5);
		byte = byte>>1;
	}
}

////////////////////////////////////////////////////////////////////////////////////
uint8_t OneWire_ReadByte(void)
{
	uint8_t i,byte=0;
	
	for (i=0;i<8;i++)
	{
		byte = byte>>1;
		DQ_LO;
		_delay_us(3);
		DQ_HI;
		_delay_us(3);
		if(PIN(DQ_PORT) & (1<<DQ))
		byte |= (1<<7);
		_delay_us(60);
	}
	return (byte);
}

////////////////////////////////////////////////////////////////////////////////////
void OneWire_DelayNormal(void)
{
	do{
		DQ_LO;
		_delay_us(3);
		DQ_HI;
		_delay_us(3);
	}while(PIN(DQ_PORT) & (1<<DQ));
}

////////////////////////////////////////////////////////////////////////////////////
void OneWire_WriteBit(uint8_t bit)
{
	DQ_LO;
	_delay_us(2);
	if(bit)
	DQ_HI;
	_delay_us(60);
	DQ_HI;
	_delay_us(1);
}

////////////////////////////////////////////////////////////////////////////////////
uint8_t OneWire_ReadBit(void)
{
	uint8_t bit=0;
	
	DQ_LO;
	_delay_us(3);
	DQ_HI;
	_delay_us(3);
	if(PIN(DQ_PORT) & (1<<DQ))
	bit = 1;
	_delay_us(60);
	
	return(bit);
}

////////////////////////////////////////////////////////////////////////////////////