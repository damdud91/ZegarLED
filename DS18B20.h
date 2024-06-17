#ifndef DS18B20_H_
#define DS18B20_H_

#include <avr/io.h>

#include "OneWire.h"

////////////////////////////////////////////////////////////////////////////////////
//USTAWIENIA
#define MAXSENSORS 1		// maksymalna liczba obs³ugiwanych czujników na magistrali
#define RESOLUTION 12		// rozdzielczoœæ czujników
//kody b³êdów
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

extern t_czujnik_temp czujniki[MAXSENSORS];	//definicja tablicy czujników
extern uint8_t liczba_czujnikow;

////////////////////////////////////////////////////////////////////////////////////
//FUNKCJE

//----------------------------
// Inicjalizacja czujników
//----------------------------
void DS18B20_Init(void);

//----------------------------
// Wprowadza ustawienia do czujnika
// Alarm temperatury i rozdzielczoœæ
// Przed wywo³aniem nalezy ustawiæ parametry
// alarmu dla wybranego czujnika.
// Przy wywo³aniu podajemy nr czujnika
//----------------------------
void DS18B20_GiveSettings(uint8_t);

//----------------------------
// Funkcja zwraca
// 1 jeœli czujniki zasilane s¹ normalnie
// 0 jeœli s¹ w trybie paso¿ytniczym
//----------------------------
uint8_t DS18B20_GetPowerStatus(void);

//----------------------------
// Start pomiaru. Do zakoñczenia nale¿y odczekaæ:
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
// Odczyt pomiaru dla wszystkich czujników
// zwraca stan powodzenia operacji
//----------------------------
uint8_t DS18B20_ReadMeas(void);

////////////////////////////////////////////////////////////////////////////////////
#endif /* DS18B20_H_ */