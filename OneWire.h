#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include <avr/io.h>
#include <util/delay.h>

#include "Zegarek.h"

////////////////////////////////////////////////////////////////////////////////////
#define DQ_PORT	T_PORT		// port do którego pod³¹czono magistralê
#define DQ T_DATA			// linia pod³¹czonej magistrali
////////////////////////////////////////////////////////////////////////////////////
//FUNKCJE

//----------------------------------
// Rozpoczyna transmisjê 1-wire
//----------------------------------
void OneWire_Reset(void);

//----------------------------------
// Wysy³a 1 bajt na magistralê
//----------------------------------
void OneWire_WriteByte(uint8_t);

//----------------------------------
// Odbiera 1 bajt od urz¹dzenia pod³¹czonego do magistrali
//----------------------------------
uint8_t OneWire_ReadByte(void);

//----------------------------------
// Blokuje tok programu a¿ uzyska odpowiedŸ uk³adu o koñcu dzia³ania
//----------------------------------
void OneWire_DelayNormal(void);

//----------------------------------
// Wysy³a 1 bit na magistralê
//----------------------------------
void OneWire_WriteBit(uint8_t);

//----------------------------------
// Odbiera 1 bit z magistrali
//----------------------------------
uint8_t OneWire_ReadBit(void);

////////////////////////////////////////////////////////////////////////////////////

#endif /* ONEWIRE_H_ */