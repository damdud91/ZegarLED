#include "SPI.h"

////////////////////////////////////////////////////////////////////////////////////
#define CK_W_0 PORT(W_PORT) &= ~(1<<W_CLOCK)
#define CK_W_1 PORT(W_PORT) |= (1<<W_CLOCK)
#define MOSI_W_0 PORT(W_PORT) &= ~(1<<W_DATA)
#define MOSI_W_1 PORT(W_PORT) |= (1<<W_DATA)

#define CK_D_0 PORT(D_PORT) &= ~(1<<D_CLOCK)
#define CK_D_1 PORT(D_PORT) |= (1<<D_CLOCK)
#define MOSI_D_0 PORT(D_PORT) &= ~(1<<D_DATA)
#define MOSI_D_1 PORT(D_PORT) |= (1<<D_DATA)

////////////////////////////////////////////////////////////////////////////////////
/* ustawienie kierunku wyjœciowego dla linii MOSI, SCK i CS */
void InitSpi(void) 
{
	DDR(D_PORT) |= (1<<D_DATA)|(1<<D_CLOCK);
}

////////////////////////////////////////////////////////////////////////////////////
/* definicja  funkcji wysy³aj¹cej bajt */
void SendSpiOne(uint8_t bajt)
{
	uint16_t cnt=0x80;
	
	CK_D_0;
	while (cnt)
	{
		if (bajt & cnt) MOSI_D_1;
		else MOSI_D_0;
		asm volatile (
		"nop	\n\t"\
		"nop	\n\t"\
		"nop	\n\t"\
		"nop	\n\t");
		CK_D_1;
		asm volatile (
		"nop	\n\t"\
		"nop	\n\t"\
		"nop	\n\t"\
		"nop	\n\t");
		CK_D_0;
		cnt >>= 1;
	}
// 	PORT(W_PORT) |= (1<<W_LATCH);
// 	PORT(W_PORT) &= ~(1<<W_LATCH);
}

////////////////////////////////////////////////////////////////////////////////////
/* definicja  funkcji wysy³aj¹cej bajt */
void SendSpi(uint8_t bajt1,uint8_t bajt2)
{
	uint16_t cnt=0x8000;
	uint16_t data;

	data = (bajt1<<8)|(bajt2);
	CK_W_0;
	while (cnt)
	{
		if (data & cnt) MOSI_W_1;
		else MOSI_W_0;
		CK_W_1;
		CK_W_0;
		cnt >>= 1;
	}
	PORT(W_PORT) |= (1<<W_LATCH);
	PORT(W_PORT) &= ~(1<<W_LATCH);
}