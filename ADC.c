#include "ADC.h"

////////////////////////////////////////////////////////////////////////////////////
void InitADC(void)
{
	ADMUX |= (1<<REFS1)|(1<<REFS0); // U odniesienia 1,1V
	ADMUX |= (1<<ADLAR); // Przesuniêcie wyniku w lewo
	ADMUX |= 0b00000110; // Pomiar z nó¿ki ADC6
	
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Preskaler 1/128
	ADCSRA |= (1<<ADEN); // W³¹cz ADC
	ADCSRA |= (1<<ADIF); // Zerowanie flagi
	ADCSRA |= (1<<ADSC); // Start konwersji
}