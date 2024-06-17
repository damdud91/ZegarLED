#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

#include "Zegarek.h"

////////////////////////////////////////////////////////////////////////////////////
void InitSpi(void);								// inicjalizacja SPI
void SendSpi(uint8_t bajt1,uint8_t bajt2);		// wysy³anie bajtu przez SPI
void SendSpiOne(uint8_t bajt);

////////////////////////////////////////////////////////////////////////////////////

#endif /* SPI_H_ */