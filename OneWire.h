#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include <avr/io.h>
#include <util/delay.h>

#include "Zegarek.h"

////////////////////////////////////////////////////////////////////////////////////
#define DQ_PORT	T_PORT		// port do kt�rego pod��czono magistral�
#define DQ T_DATA			// linia pod��czonej magistrali
////////////////////////////////////////////////////////////////////////////////////
//FUNKCJE

//----------------------------------
// Rozpoczyna transmisj� 1-wire
//----------------------------------
void OneWire_Reset(void);

//----------------------------------
// Wysy�a 1 bajt na magistral�
//----------------------------------
void OneWire_WriteByte(uint8_t);

//----------------------------------
// Odbiera 1 bajt od urz�dzenia pod��czonego do magistrali
//----------------------------------
uint8_t OneWire_ReadByte(void);

//----------------------------------
// Blokuje tok programu a� uzyska odpowied� uk�adu o ko�cu dzia�ania
//----------------------------------
void OneWire_DelayNormal(void);

//----------------------------------
// Wysy�a 1 bit na magistral�
//----------------------------------
void OneWire_WriteBit(uint8_t);

//----------------------------------
// Odbiera 1 bit z magistrali
//----------------------------------
uint8_t OneWire_ReadBit(void);

////////////////////////////////////////////////////////////////////////////////////

#endif /* ONEWIRE_H_ */