#include "Wys_LED.h"

////////////////////////////////////////////////////////////////////////////////////

volatile WYSWIETLACZ_t cyfry = {.cy = {digit_pusto,digit_pusto,digit_pusto,digit_pusto,digit_pusto,digit_pusto,digit_pusto,digit_pusto}};
volatile uint8_t wys_brightness = 11;

// definicja tablicy zawieraj�cej definicje bitowe cyfr LED
const uint8_t znaki[16] PROGMEM = {
		(0b01000000),		// 0
		(0b01111001),		// 1
		(0b00100100),		// 2
		(0b00110000),		// 3
		(0b00011001),		// 4
		(0b00010010),		// 5
		(0b00000010),		// 6
		(0b01111000),		// 7
		(0b00000000),		// 8
		(0b00010000),		// 9
		(0b00001000),		// A
		(0b01000110),		// C
		(0b00000110),		// E
		(0b00001110),		// F
		(0b01110000),		// stopie� celcjusza
		(0b11111111),		// NIC (puste miejsce)
};

////////////////////////////////////////////////////////////////////////////////////
// ****** definicja funkcji inicjalizuj�cej prac� z wy�wietlaczem multipleksowanym
void InitWys_LED(void)
{
	//Inicjalizacja linii przesy�aj�cych dane do rejestr�w przesuwnych
	DDR(W_PORT) |= (1<<W_DATA)|(1<<W_CLOCK)|(1<<W_LATCH); 

	// ustawienie TIMER0
	OCR0A = 75;						// dodatkowy podzia� przez 75 (rej. przepe�nienia)
	TCCR0A = (1<<WGM01);			// tryb CTC
	TCCR0B = (1<<CS01)|(1<<CS00);	// preskaler = 64
	TIMSK0 = (1<<OCIE0A);			// zezwolenie na przerwanie CompareMatch
}

////////////////////////////////////////////////////////////////////////////////////
// ================= PROCEDURA OBS�UGI PRZERWANIA � COMPARE MATCH
ISR(TIMER0_COMPA_vect)
{
	static uint8_t licznik = 0; // zmienna do prze��czania kolejnych anod wy�wietlacza
	static uint8_t jasnosc = 0;

	if((jasnosc - wys_brightness) <= 0)
	{
		SendSpi(pgm_read_byte(&znaki[cyfry.cy[licznik]]),1<<licznik);
		licznik ++;
		if(licznik == 8) licznik = 0;
	}
	else
	{
		SendSpi(pgm_read_byte(&znaki[digit_pusto]),1<<licznik);
	}
	jasnosc++;
	if(jasnosc == 11) jasnosc = 0;
}
