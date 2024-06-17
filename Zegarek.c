#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "Zegarek.h"
#include "SPI.h"
#include "Wys_LED.h"
#include "DS3231.h"
#include "DS18B20.h"
#include "Animacje.h"
#include "ADC.h"

////////////////////////////////////////////////////////////////////////////////////
// STA£E
//----------------------------------------------------------------------------------
// korekcja gamma dla diod LED
const uint8_t gamma_correctionR[] PROGMEM = {
	0,  1,  1,  1,  2,  4,  6,  8, 11, 14, 18, 22, 27, 32, 38, 45, 52, 61,
	69, 79, 89,100,112,124,138,152,167,183,199,217,236,255
};

////////////////////////////////////////////////////////////////////////////////////
// ZMIENNE
//----------------------------------------------------------------------------------
// timery programowe
volatile uint8_t Timer1, Timer3, Timer4,Timer5;	// sta³a czasowa: 10ms
volatile uint16_t Timer2;

//----------------------------------------------------------------------------------
// zmienne steruj¹ce przebiegiem programu g³ównego
struct
{
	uint8_t Menu:1;
	uint8_t Date:1;
	uint8_t Clock:1;
	uint8_t Temp:1;
	uint8_t Leds:1;
}DisplayFlag;

enum{UstawGodz,UstawMin,UstawDzien,UstawMiesiac} MenuGlowne;
	
//----------------------------------------------------------------------------------
// zmienne steruj¹ce stanem diod LED
struct{
	uint8_t leds[18];
	uint8_t id_anim;
	enum{Iddle=0,Start,Go}Status;
}SPIstatus = {{},1,0};

//----------------------------------------------------------------------------------
// wskaŸniki na funkcje wykonywane przy klikniêciu przycisków
void* FuncShort1;
void* FuncShort2;
void* FuncShort3;
void* FuncLong1;
void* FuncLong2;
void* FuncLong3;

////////////////////////////////////////////////////////////////////////////////////
// DEKLARACJE
//----------------------------------------------------------------------------------
void DS3231_Event(void);
void DS18B20_Event(void);
void SendSpiToWS_Event(void);
void ADC_Event(void);

void SuperDebounce( volatile uint8_t *KPIN,uint8_t key_mask, uint16_t rep_time,
uint16_t rep_wait,void (*push_proc)(void), void (*rep_proc)(void) );
void RegisterClickFunc(uint8_t nr_przycisku,void (*funcshort)(void),void (*funclong)(void));
void ShowDate(void);
void ShowMenu(void);
void ShowShift(void);
void ChangeUp(void);
void ChangeDown(void);
void ChangeAnimation(void);

void DisplayAnimation(void);

////////////////////////////////////////////////////////////////////////////////////
// PROGRAM G£ÓWNY
//----------------------------------------------------------------------------------
int main(void)
{
	//------------------------------------------------------------------------------
	// Inicjalizacja Timera programowego
	OCR1A = 24999;			// f_osc / 25000
	TCCR1A = 0;
	TCCR1B |= (1<<WGM12);	// tryb CTC
	TCCR1B |= (1<<CS11);	// f_osc / 8
	TCCR1C = 0;
	TIMSK1 = (1<<OCIE1A);	// przerwanie od porównania z OCR1A
	
	//------------------------------------------------------------------------------
	// Inicjalizacja Przycisków
	DDR(SW_PORT) &= ~((1<<SW_1)|(1<<SW_2)|(1<<SW_3));
	PORT(SW_PORT) |= (1<<SW_1)|(1<<SW_2)|(1<<SW_3);
	
	//------------------------------------------------------------------------------
	InitSpi();
	InitWys_LED();
	InitDS3231();
	DS18B20_Init();
	InitADC();
	
	RegisterClickFunc(1,ShowDate,ShowMenu);
	RegisterClickFunc(2,ShowDate,0);
	RegisterClickFunc(3,ChangeAnimation,0);
	
	wdt_enable(WDTO_15MS); //inicjalizacja watchdoga
	sei();

	//------------------------------------------------------------------------------
	while (1)
	{
		//------------------------------------------------------------------------------
		DisplayAnimation();		// animacja
		if (DisplayFlag.Leds && !Timer2) DisplayFlag.Leds = 0;
		//------------------------------------------------------------------------------
		if(DisplayFlag.Clock)	// odœwierz wyœwietlacze?
		{
			SPIstatus.leds[16] ^= 0xFF;
			SPIstatus.leds[17] ^= 0xFF;	
			SPIstatus.Status = Start;
					
			if (DisplayFlag.Date) //wyœwietlanie daty
			{
				if( DisplayFlag.Menu && (MenuGlowne == UstawDzien) && (czas.sek%2) )
				{
					cyfry.time_dgodz = digit_pusto;
					cyfry.time_jgodz = digit_pusto;
				}
				else
				{
					cyfry.time_dgodz = czas.dzien / 10;
					cyfry.time_jgodz = czas.dzien % 10;
				}
				if( DisplayFlag.Menu && (MenuGlowne == UstawMiesiac) && (czas.sek%2) )
				{
					cyfry.time_dmin = digit_pusto;
					cyfry.time_jmin = digit_pusto;
				}
				else
				{
					cyfry.time_dmin = czas.mies / 10;
					cyfry.time_jmin = czas.mies % 10;
				}
			}
			else //jeœli data niewyœwietlana - wyœwietlanie czasu
			{
				if( DisplayFlag.Menu && (MenuGlowne == UstawGodz) && (czas.sek%2) )
				{
					cyfry.time_dgodz = digit_pusto;
					cyfry.time_jgodz = digit_pusto;
				}
				else
				{
					cyfry.time_dgodz = czas.godz / 10;
					cyfry.time_jgodz = czas.godz % 10;
				}					
				if( DisplayFlag.Menu && (MenuGlowne == UstawMin) && (czas.sek%2) )
				{
					cyfry.time_dmin = digit_pusto;
					cyfry.time_jmin = digit_pusto;
				}
				else
				{
					cyfry.time_dmin = czas.min / 10;
					cyfry.time_jmin = czas.min % 10;
				}
			}
			DisplayFlag.Clock = 0;
		}
						
		if (!Timer2 && (DisplayFlag.Menu || DisplayFlag.Date))  // Jeœli wyœwietlane by³o menu lub data 
		{														// a odmierzany czas siê skoñczy³ to przywróæ domyœlne
			DisplayFlag.Date = 0;
			DisplayFlag.Menu = 0;
			DisplayFlag.Clock = 1;
			
			RegisterClickFunc(1,ShowDate,ShowMenu);
			RegisterClickFunc(2,ShowDate,0);
			RegisterClickFunc(3,ChangeAnimation,0);
		}
		//------------------------------------------------------------------------------
		
		if (DisplayFlag.Temp) // wyœwietl temperaturê
		{
			cyfry.temp_dst = czujniki[0].temperatura.cz_calkowita / 10;
			cyfry.temp_jst = czujniki[0].temperatura.cz_calkowita % 10;
			cyfry.temp_ulst = czujniki[0].temperatura.cz_ulamkowa;
			cyfry.temp_jednostka = digit_stopien;
			DisplayFlag.Temp = 0;
		}	
		
		//------------------------------------------------------------------------------	
		SuperDebounce(&PIN(SW_PORT),(1<<SW_1),5,250,FuncShort1,FuncLong1); //obs³uga klawisza 1
		SuperDebounce(&PIN(SW_PORT),(1<<SW_2),5,250,FuncShort2,FuncLong2); //obs³uga klawisza 2
		SuperDebounce(&PIN(SW_PORT),(1<<SW_3),5,250,FuncShort3,FuncLong3); //obs³uga klawisza 3

		ADC_Event(); // obs³uga ADC
		DS18B20_Event(); // obs³uga scalaka od temperatury
		DS3231_Event(); // obs³uga scalaka od czasu
		SendSpiToWS_Event(); // obs³uga scalaka od pwmów
		
		wdt_reset(); // reset watchdoga
	}
}

////////////////////////////////////////////////////////////////////////////////////
ISR(TIMER1_COMPA_vect)
{
	if (Timer1) Timer1--;		// SuperDebounce
	if (Timer2) Timer2--;		// Main
	if (Timer3) Timer3--;		// DS18B20
	if (Timer4) Timer4--;		// WS28030
	if (Timer5) Timer5--;		// Animacje
}

////////////////////////////////////////////////////////////////////////////////////
void DS3231_Event(void)
{	
	if (EIFR & (1<<INTF0))
	{	
		DS3231_getdatetime(&czas);
//		DS3231_gettemp(&temperatura);	
		DisplayFlag.Clock = 1;
		EIFR |= (1<<INTF0);		// kasowanie flagi
	}
}

////////////////////////////////////////////////////////////////////////////////////
void DS18B20_Event(void)
{	
	if (!Timer3)
	{
		if(DS18B20_OK == DS18B20_ReadMeasSingle(0))
		{
			DS18B20_StartMeas();
			if(czujniki[0].temperatura.cz_calkowita != 85) DisplayFlag.Temp = 1;
		}
		Timer3 = 200;
	}
}

////////////////////////////////////////////////////////////////////////////////////
void SendSpiToWS_Event(void)
{
	uint8_t i;
	
	if(SPIstatus.Status)
	{
		if (SPIstatus.Status == Start)
		{
			PORT(D_PORT) |= (1<<D_CLOCK);
			asm volatile (
			"nop	\n\t"\
			"nop	\n\t"\
			"nop	\n\t"\
			"nop	\n\t");
			PORT(D_PORT) &= ~(1<<D_CLOCK);
			SPIstatus.Status = Go;
			Timer4 = 1;
		}
		if((SPIstatus.Status == Go) && (!Timer4))
		{
			for (i=0;i < 18;i++)
			{
				if(wys_brightness < 11) SendSpiOne((SPIstatus.leds[i]!=0) ? (SPIstatus.leds[i]/((11-wys_brightness)*4)) : (SPIstatus.leds[i]));
				else SendSpiOne(SPIstatus.leds[i]);
			}
			SPIstatus.Status = Iddle;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
void ADC_Event(void)
{
	static uint16_t ostatnia_wartosc = 0;
	static uint8_t Licznik = 0;
	uint8_t tmp;
	
	if((ADCSRA & (1<<ADIF)) && !Licznik) //&& (!Timer3))
	{
		tmp = ADCL;
		tmp = ADCH; // interesuje nas tylko górna po³ówka
		
		ostatnia_wartosc = (tmp + ostatnia_wartosc) / 2;
		
		if ((czujniki[0].temperatura.cz_calkowita != 85) && !DisplayFlag.Menu && !DisplayFlag.Date)
		{
			if(ostatnia_wartosc <= 15) {wys_brightness = 0;}
			else if(ostatnia_wartosc <= 30) {wys_brightness = 1;}
			else if(ostatnia_wartosc <= 50) {wys_brightness = 2;}
			else if(ostatnia_wartosc <= 75) {wys_brightness = 3;}
			else if(ostatnia_wartosc <= 100) {wys_brightness = 4;}
			else if(ostatnia_wartosc <= 125) {wys_brightness = 5;}
			else if(ostatnia_wartosc <= 150) {wys_brightness = 6;}
			else if(ostatnia_wartosc <= 175) {wys_brightness = 7;}
			else if(ostatnia_wartosc <= 195) {wys_brightness = 8;}
			else if(ostatnia_wartosc <= 220) {wys_brightness = 9;}
			else if(ostatnia_wartosc <= 240) {wys_brightness = 10;}
			else {wys_brightness = 11;}
		}
		
		ADCSRA |= (1<<ADIF);
		ADCSRA |= (1<<ADSC); // Start konwersji
		Licznik = 250;
	}
	else
	{
		Licznik--;
	}
}

////////////////////////////////////////////////////////////////////////////////////
/************** funkcja SuperDebounce do obs³ugi pojedynczych klawiszy ***************
 * 							AUTOR: Miros³aw Kardaœ
 * ZALETY:
 * 		- nie wprowadza najmniejszego spowalnienia
 * 		- posiada funkcjê REPEAT (powtarzanie akcji dla d³u¿ej wciœniêtego przycisku)
 * 		- mo¿na przydzieliæ ró¿ne akcje dla trybu REPEAT i pojedynczego klikniêcia
 * 		- mo¿na przydzieliæ tylko jedn¹ akcjê wtedy w miejsce drugiej przekazujemy 0 (NULL)
 * 		- zabezpieczenie przed naciœniêciem dwóch klawiszy jednoczeœnie
 *
 * Wymagania:
 * 	Timer programowy utworzony w oparciu o Timer sprzêtowy (przerwanie 100Hz)
 *
 * 	Parametry wejœciowe - 6 :
 *  *KPIN - nazwa PINx portu na którym umieszczony jest klawisz, np: PINB
 *  key_mask - maska klawisza np: (1<<PB3)
 *  rep_time - czas powtarzania funkcji rep_proc w trybie REPEAT
 *  rep_wait - czas oczekiwania do przejœcia do trybu REPEAT
 *  push_proc - wskaŸnik do w³asnej funkcji wywo³ywanej raz po zwolenieniu przycisku
 *  rep_proc - wskaŸnik do w³asnej funkcji wykonywanej w trybie REPEAT
 **************************************************************************************/
void SuperDebounce(volatile uint8_t *KPIN, uint8_t key_mask, uint16_t rep_time, 
		uint16_t rep_wait, void (*push_proc)(void), void (*rep_proc)(void) )
{

	enum KS {idle, debounce, go_rep, wait_rep, rep};

	static enum KS key_state;
	static uint8_t last_key;
	uint8_t key_press;

	// zabezpieczenie przed wykonywaniem tej samej funkcji dla
	// dwóch klawiszy wciskanych jednoczeœnie (zawsze bêdzie
	// wykonywana odpowiednia akcja dla tego, który zosta³
	// wciœniêty jako pierwszy
	if( last_key && last_key != key_mask ) return;

	key_press = !(*KPIN & key_mask);

	if( key_press && !key_state ) {
		key_state = debounce;
		Timer1 = 5;
	} else
	if( key_state  ) {
		if( key_press && debounce==key_state && !Timer1 ) {
			key_state = go_rep;
			Timer1=3;
			last_key = key_mask;
		} else
		if( !key_press && key_state>debounce && key_state<rep ) {
			if(push_proc) push_proc();						/* KEY_UP */
			key_state=idle;
			last_key = 0;
		} else
		if( key_press && go_rep==key_state && !Timer1 ) {
			if(!rep_time) rep_time=20;
			if(!rep_wait) rep_wait=150;
			key_state = wait_rep;
			Timer1=rep_wait;
		} else
		if( key_press && wait_rep==key_state && !Timer1 ) {
			key_state = rep;
		} else
		if( key_press && rep==key_state && !Timer1 ) {
			Timer1 = rep_time;
			if(rep_proc) rep_proc();						/* KEY_REP */
		}
	}

	if( key_state>=wait_rep && !key_press ) {
		key_state = idle;
		last_key = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////
void RegisterClickFunc(uint8_t nr_przycisku,void (*funcshort)(void),void (*funclong)(void))
{
	switch (nr_przycisku)
	{
	case 1:
		FuncShort1 = funcshort;
		FuncLong1 = funclong;
		break;
	case 2:
		FuncShort2 = funcshort;
		FuncLong2 = funclong;
		break;
	case 3:
		FuncShort3 = funcshort;
		FuncLong3 = funclong;
		break;
	}	
}

////////////////////////////////////////////////////////////////////////////////////
void ShowDate(void)
{
	DisplayFlag.Date = 1;
	Timer2 = 500;
}

////////////////////////////////////////////////////////////////////////////////////
void ShowMenu(void)
{
	DisplayFlag.Menu = 1;
	RegisterClickFunc(1,ShowShift,0);
	RegisterClickFunc(2,ChangeUp,ChangeUp);
	RegisterClickFunc(3,ChangeDown,ChangeDown);
	Timer2 = 1500;
}

////////////////////////////////////////////////////////////////////////////////////
void ShowShift(void)
{
	if((++MenuGlowne) > UstawMiesiac) MenuGlowne = UstawGodz;
	if(MenuGlowne > UstawMin)	DisplayFlag.Date = 1;
	else 						DisplayFlag.Date = 0;
	
	DisplayFlag.Clock = 1;
	Timer2 = 1500;
}

////////////////////////////////////////////////////////////////////////////////////
void ChangeUp(void)
{
	switch(MenuGlowne)
	{
		case UstawMiesiac:
			if((++czas.mies) > 12) czas.mies = 1;
			break;
		case UstawDzien:
			if((++czas.dzien) > 31) czas.dzien = 1;
			break;
		case UstawGodz:
			if((++czas.godz) > 23) czas.godz = 0;
			break;
		case UstawMin:
			if((++czas.min) > 59) czas.min = 0;
			czas.sek = 0;
			break;
	}
	DS3231_givedatetime(&czas);
	DisplayFlag.Clock = 1;
	Timer2 = 1500;		
}

////////////////////////////////////////////////////////////////////////////////////
void ChangeDown(void)
{
	switch(MenuGlowne)
	{
		case UstawMiesiac:
			if(!(--czas.mies)) czas.mies = 12;
			break;
		case UstawDzien:
			if(!(--czas.dzien)) czas.dzien = 31;
			break;
		case UstawGodz:
			if((--czas.godz) > 23) czas.godz = 23;
			break;
		case UstawMin:
			if((--czas.min) > 59) czas.min = 59;
			break;
	}
	DS3231_givedatetime(&czas);
	DisplayFlag.Clock = 1;
	Timer2 = 1500;
}

////////////////////////////////////////////////////////////////////////////////////
void ChangeAnimation(void)
{
	uint8_t a;
	
	if((!SPIstatus.Status) && (!DisplayFlag.Leds))
	{
		SPIstatus.id_anim++;
		if(SPIstatus.id_anim == 3) SPIstatus.id_anim = 0;
		for(a=0; a < 12; a++)
			SPIstatus.leds[a] = 0;
		SPIstatus.leds[16] = 0xFF;
		SPIstatus.leds[17] = 0xFF;
		SPIstatus.Status = Start;
		DisplayFlag.Leds = 1;
		Timer2 = 100;
	}
}

////////////////////////////////////////////////////////////////////////////////////
void DisplayAnimation(void)
{
	static uint8_t counter=0;
	uint8_t tmp;
	
	if ((!Timer5) && ((czujniki[0].temperatura.cz_calkowita == 85) || DisplayFlag.Menu || DisplayFlag.Date) && (!SPIstatus.Status))
	{
		counter++;
		if(counter == 60) counter = 0;
		for(tmp=0; tmp < 12; tmp++)
			SPIstatus.leds[tmp] = pgm_read_byte(&gamma_correctionR[pgm_read_byte(&duszki[counter][tmp])]);
		SPIstatus.Status = Start;
		Timer5 = 2;
		return;
	}
//--------------------------------------------------------------------------------
	if((DisplayFlag.Clock) && (SPIstatus.id_anim == 1) && (!SPIstatus.Status))
	{
		for(tmp=0; tmp < 12; tmp++)
			SPIstatus.leds[tmp] = pgm_read_byte(&gamma_correctionR[pgm_read_byte(&waz[czas.sek][tmp])]);
		SPIstatus.Status = Start;
		return;
	}
//--------------------------------------------------------------------------------
	if((DisplayFlag.Clock) && (SPIstatus.id_anim == 2) && (!SPIstatus.Status))
	{
		for(tmp=0; tmp < 12; tmp++)
			SPIstatus.leds[tmp] = pgm_read_byte(&gamma_correctionR[pgm_read_byte(&tiktik[czas.sek][tmp])]);
		SPIstatus.Status = Start;
		return;
	}
}