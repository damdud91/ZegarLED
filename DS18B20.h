#ifndef DS18B20_H_
#define DS18B20_H_

#include <avr/io.h>

#include "OneWire.h"

////////////////////////////////////////////////////////////////////////////////////
//USTAWIENIA
#define MAXSENSORS 1		// maksymalna liczba obs�ugiwanych czujnik�w na magistrali
#define RESOLUTION 12		// rozdzielczo�� czujnik�w
//kody b��d�w
#define DS18B20_OK 0x01
#define DS18B20_ERROR_CRC 0x00

////////////////////////////////////////////////////////////////////////////////////
//ZMIENNE GLOBALNE
typedef struct
{
	uint8_t znak;
	uint8_t cz_calkowita;
	uint8_t cz_ulamkowa;
}t_temp;

typedef struct
{
	uint8_t kod_rom[8];
	t_temp	temperatura;
	uint8_t alarm[2];
} t_czujnik_temp;							//definicja cech charakterystycznych dla czujnika

extern t_czujnik_temp czujniki[MAXSENSORS];	//definicja tablicy czujnik�w
extern uint8_t liczba_czujnikow;

////////////////////////////////////////////////////////////////////////////////////
//FUNKCJE

//----------------------------
// Inicjalizacja czujnik�w
//----------------------------
void DS18B20_Init(void);

//----------------------------
// Wprowadza ustawienia do czujnika
// Alarm temperatury i rozdzielczo��
// Przed wywo�aniem nalezy ustawi� parametry
// alarmu dla wybranego czujnika.
// Przy wywo�aniu podajemy nr czujnika
//----------------------------
void DS18B20_GiveSettings(uint8_t);

//----------------------------
// Funkcja zwraca
// 1 je�li czujniki zasilane s� normalnie
// 0 je�li s� w trybie paso�ytniczym
//----------------------------
uint8_t DS18B20_GetPowerStatus(void);

//----------------------------
// Start pomiaru. Do zako�czenia nale�y odczeka�:
// 9b:  93.75ms
// 10b: 187.5ms
// 11b: 375ms
// 12b: 750ms
//----------------------------
void DS18B20_StartMeas(void);

//----------------------------
// Oczekiwanie na koniec pomiaru
//----------------------------
void DS18B20_WaitForMeas(void);

//----------------------------
// Odczyt pomiaru dla konkretnego czujnika
// zwraca stan powodzenia operacji
//----------------------------
uint8_t DS18B20_ReadMeasSingle(uint8_t);

//----------------------------
// Odczyt pomiaru dla wszystkich czujnik�w
// zwraca stan powodzenia operacji
//----------------------------
uint8_t DS18B20_ReadMeas(void);

////////////////////////////////////////////////////////////////////////////////////
#endif /* DS18B20_H_ */