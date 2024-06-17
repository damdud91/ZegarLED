#include "DS18B20.h"

////////////////////////////////////////////////////////////////////////////////////
// ZMIENNE GLOBALNE
t_czujnik_temp czujniki[MAXSENSORS];	//definicja tablicy czujników
uint8_t liczba_czujnikow;
static uint8_t power_status;

////////////////////////////////////////////////////////////////////////////////////
//MAKRA I DEFINICJE
#define PARASITE_POWER	0x00

//komendy ROM
#define SEARCH_ROM 0xF0
#define READ_ROM 0x33
#define MATCH_ROM 0x55
#define SKIP_ROM 0xCC
#define ALARM_SEARCH 0xEC

//komendy funkcji
#define CONVERT_T 0x44
#define READ_SCR 0xBE
#define WRITE_SCR 0x4E
#define COPY_SCR 0x48
#define RECALL_E 0xB8
#define READ_POWER_SUPPLY 0xB4

////////////////////////////////////////////////////////////////////////////////////
//FUNKCJE POMOCNICZE
uint8_t DS18B20_CRC(uint8_t *ptr,uint8_t ilosc)
{
	uint8_t i,j,crc=0,tmp;
	
	for(i=0;i<ilosc;i++,ptr++)
	{
		tmp=*ptr;
		for(j=0;j<8;j++)
		{
			if((crc & 0x01) ^ (tmp & 0x01))
			{
				crc^=((1<<3)|(1<<4));
				crc>>=1;
				crc|=(1<<7);
				tmp>>=1;
			}
			else
			{
				crc>>=1;
				tmp>>=1;
			}
		}
	}
	return crc;
}

////////////////////////////////////////////////////////////////////////////////////
uint8_t DS18B20_Reg_GetBit(uint8_t last_licznik_konfliktow,uint8_t *licznik_konfliktow)
{
	uint8_t a=0,b=0;
	
	a = OneWire_ReadBit();
	b = OneWire_ReadBit();
	if(a^b)
	{
		OneWire_WriteBit(a);
		return (a);
	}
	else
	{
		(*licznik_konfliktow)++;
		if(*licznik_konfliktow == last_licznik_konfliktow)
		{
			OneWire_WriteBit(1);
			(*licznik_konfliktow)--;
			return (1);
		}
		else
		{
			OneWire_WriteBit(0);
			return (0);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
void DS18B20_RegistrationSensors(void)
{
	uint8_t i,j,data,licznik_konfliktow,last_licznik_konfliktow=0;
	
	do
	{							//_________________________________________________ czujniki
		OneWire_Reset();
		OneWire_WriteByte(SEARCH_ROM);

		licznik_konfliktow = 0;	//_________________________________________________ 1 czujnik
		for (i=0;i<8;i++)
		{
			data = 0;
			for (j=0;j<8;j++)	//_________________________________________________ 1 bajt
			{
				data |= (DS18B20_Reg_GetBit(last_licznik_konfliktow,&licznik_konfliktow) << j);
			}
			czujniki[liczba_czujnikow].kod_rom[i] = data;
		}
		if(!(DS18B20_CRC(czujniki[liczba_czujnikow].kod_rom,8)))
		{
			last_licznik_konfliktow = licznik_konfliktow;
			liczba_czujnikow++;
		}
	} while ((licznik_konfliktow) && (liczba_czujnikow<(MAXSENSORS)));
}

////////////////////////////////////////////////////////////////////////////////////
void DS18B20_AdresSensor(uint8_t nr)
{
	uint8_t i;
	
	OneWire_Reset();
	OneWire_WriteByte(MATCH_ROM);
	for (i=0;i<8;i++)
	{
		OneWire_WriteByte(czujniki[nr].kod_rom[i]);
	}
}

////////////////////////////////////////////////////////////////////////////////////
//FUNKCJE ZEWNÊTRZNE
uint8_t DS18B20_GetPowerStatus(void)
{
	OneWire_Reset();
	OneWire_WriteByte(SKIP_ROM);
	OneWire_WriteByte(READ_POWER_SUPPLY);
	return (OneWire_ReadBit());
}

////////////////////////////////////////////////////////////////////////////////////
void DS18B20_GiveSettings(uint8_t nr)
{
	DS18B20_AdresSensor(nr);
	OneWire_WriteByte(WRITE_SCR);
	OneWire_WriteByte(czujniki[nr].alarm[0]);
	OneWire_WriteByte(czujniki[nr].alarm[1]);
	#if   (RESOLUTION == 9)
	OneWire_WriteByte(0b00011111);
	#elif (RESOLUTION == 10)
	OneWire_WriteByte(0b00111111);
	#elif (RESOLUTION == 11)
	OneWire_WriteByte(0b01011111);
	#elif (RESOLUTION == 12)
	OneWire_WriteByte(0b01111111);
	#else
	OneWire_WriteByte(0b00011111);
	#endif
	DS18B20_AdresSensor(nr);
	OneWire_WriteByte(COPY_SCR);
/*	_delay_us(15);*/
}

////////////////////////////////////////////////////////////////////////////////////
void DS18B20_Init(void)
{
	uint8_t i;
	
	DS18B20_RegistrationSensors();
	power_status = DS18B20_GetPowerStatus();
	for (i=0;i<liczba_czujnikow;i++)
	{
		DS18B20_GiveSettings(i);
	}
	czujniki[0].temperatura.cz_calkowita = 85;
}

////////////////////////////////////////////////////////////////////////////////////
void DS18B20_StartMeas(void)
{
	OneWire_Reset();
	OneWire_WriteByte(SKIP_ROM);
	OneWire_WriteByte(CONVERT_T);
}

////////////////////////////////////////////////////////////////////////////////////
void DS18B20_WaitForMeas(void)
{
	if (power_status)
	OneWire_DelayNormal();
	else
	{
		#if   (RESOLUTION == 9)
		_delay_ms(100);
		#elif (RESOLUTION == 10)
		_delay_ms(200);
		#elif (RESOLUTION == 11)
		_delay_ms(400);
		#elif (RESOLUTION == 12)
		_delay_ms(800);
		#else
		_delay_ms(800);
		#endif
	}
}

////////////////////////////////////////////////////////////////////////////////////
uint8_t DS18B20_ReadMeasSingle(uint8_t nr)
{
	uint8_t i,bufor[9];
	
	DS18B20_AdresSensor(nr);
	OneWire_WriteByte(READ_SCR);
	for (i=0;i<9;i++)
	{
		bufor[i] = OneWire_ReadByte();
	}
	if (!(DS18B20_CRC(bufor,9)))
	{	//-----								//znak
		czujniki[nr].temperatura.znak = (bufor[1] & 0x80) ? 0xFF : 0x00;
		//-----								//cz. ca³kowita
		czujniki[nr].temperatura.cz_calkowita = (((bufor[1] & 0x07)<<4) | (bufor[0]>>4));
		//-----								//cz.u³amkowa
		#if   (RESOLUTION == 9)
		czujniki[nr].temperatura.cz_ulamkowa = (bufor[0] & 0x08) ? 5 : 0;
		#elif (RESOLUTION == 10)
		czujniki[nr].temperatura.cz_ulamkowa = ((bufor[0] & 0x08) ? 5 : 0) \
		+ ((bufor[0] & 0x04) ? 3 : 0);
		#elif (RESOLUTION == 11)
		czujniki[nr].temperatura.cz_ulamkowa = (((bufor[0] & 0x08) ? 50 : 0) \
		+ ((bufor[0] & 0x04) ? 25 : 0) \
		+ ((bufor[0] & 0x02) ? 13 : 0))/10;
		#elif (RESOLUTION == 12)
		czujniki[nr].temperatura.cz_ulamkowa = (((bufor[0] & 0x08) ? 50 : 0) \
		+ ((bufor[0] & 0x04) ? 25 : 0) \
		+ ((bufor[0] & 0x02) ? 13 : 0) \
		+ ((bufor[0] & 0x01) ? 6 : 0))/10;
		#else
		czujniki[nr].temperatura.cz_ulamkowa = (bufor[0] & 0x08) ? 5 : 0;
		#endif
		return (DS18B20_OK);
	}
	else
	return (DS18B20_ERROR_CRC);
}

////////////////////////////////////////////////////////////////////////////////////
uint8_t DS18B20_ReadMeas(void)
{
	uint8_t i,a=DS18B20_OK;
	
	for(i=0;i<liczba_czujnikow;i++)
	{
		a |= DS18B20_ReadMeasSingle(i);
	}
	
	return (a);
}

////////////////////////////////////////////////////////////////////////////////////