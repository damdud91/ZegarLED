#ifndef CONFIG_H_
#define CONFIG_H_

#include <avr/io.h>
////////////////////////////////////////////////////////////////////////////////////
// Wyœwietlacze LED
#define W_PORT B
#define W_DATA 0
#define W_CLOCK 2
#define W_LATCH 1

// Diody LED
#define D_PORT B
#define D_DATA 5
#define D_CLOCK 3

// Zegar
#define I2C_PORT C
#define I2C_SDA 4
#define I2C_SCL 5
#define I2C_PORT_INT D
#define I2C_INT 2

// Czujnik temperatury
#define T_PORT C
#define T_DATA 3

// Przyciski
#define SW_PORT C
#define SW_3 0
#define SW_2 1
#define SW_1 2

// Pomiar natê¿enia œwiat³a

////////////////////////////////////////////////////////////////////////////////////
// Makra upraszczaj¹ce dostêp do portów
// *** PORT
#define PORT(x) XPORT(x)
#define XPORT(x) (PORT##x)
// *** PIN
#define PIN(x) XPIN(x)
#define XPIN(x) (PIN##x)
// *** DDR
#define DDR(x) XDDR(x)
#define XDDR(x) (DDR##x)

////////////////////////////////////////////////////////////////////////////////////
extern volatile uint8_t Timer1, Timer3, Timer4,Timer5;	// sta³a czasowa: 10ms
extern volatile uint16_t Timer2;

////////////////////////////////////////////////////////////////////////////////////
#endif /* CONFIG_H_ */