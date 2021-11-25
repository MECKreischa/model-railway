#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <inttypes.h>


#define TS0      (PINA & 1<<PA0)	//Relais Rangierfahrt
#define TS11     !(PINA & 1<<PA1)	//Relais Signal Gleis 11
#define TS21     !(PINA & 1<<PA2)
#define TS22     !(PINA & 1<<PA3)
#define TS24     !(PINA & 1<<PA4)

#define W9_AUS  (PORTB &= ~(1<<PB2))	
#define W9_EIN	(PORTB |= (1<<PB2))
#define W11_AUS  (PORTD &= ~(1<<PD0))	
#define W11_EIN	(PORTD |= (1<<PD0))
#define W12_AUS  (PORTD &= ~(1<<PD1))		
#define W12_EIN	(PORTD |= (1<<PD1))
#define W13_AUS  (PORTD &= ~(1<<PD2))	
#define W13_EIN	(PORTD |= (1<<PD2))
#define W14_AUS  (PORTD &= ~(1<<PD3))		
#define W14_EIN	(PORTD |= (1<<PD3))
#define W15_AUS  (PORTD &= ~(1<<PD4))		
#define W15_EIN	(PORTD |= (1<<PD4))
#define W16_AUS  (PORTD &= ~(1<<PD5))		
#define W16_EIN	(PORTD |= (1<<PD5))
#define W10_AUS  (PORTB &= ~(1<<PB3))		
#define W10_EIN	(PORTB |= (1<<PB3))

#define KS11_AUS  	(PORTC &= ~(1<<PC0))	
#define KS11_EIN	(PORTC |= (1<<PC0))
#define KS11_TOGGLE	(PORTC ^= (1<<PC0))
#define KS21_AUS  	(PORTC &= ~(1<<PC1))		
#define KS21_EIN	(PORTC |= (1<<PC1))
#define KS21_TOGGLE	(PORTC ^= (1<<PC1))
#define KS22_AUS  	(PORTC &= ~(1<<PC2))	
#define KS22_EIN	(PORTC |= (1<<PC2))
#define KS22_TOGGLE	(PORTC ^= (1<<PC2))
#define KS24_AUS  	(PORTC &= ~(1<<PC3))		
#define KS24_EIN	(PORTC |= (1<<PC3))
#define KS24_TOGGLE	(PORTC ^= (1<<PC3))
#define LED_K0_AUS  (PORTC &= ~(1<<PC4))		
#define LED_K0_EIN	(PORTC |= (1<<PC4))
#define LED_K0_TOGGLE (PORTC ^= (1<<PC4))
#define FREI2_AUS  	(PORTC &= ~(1<<PC5))		
#define FREI2_EIN	(PORTC |= (1<<PC5))
#define K0_AUS  	(PORTC &= ~(1<<PC6))		
#define K0_EIN		(PORTC |= (1<<PC6))
#define K0_TOGGLE	(PORTC ^= (1<<PC6))


volatile unsigned int cnt = 0;
volatile unsigned int sek = 0;
volatile char flanke = 0;
volatile char contine = 0;


ISR(TIMER1_OVF_vect){
	TCNT1 = 53036;
	cnt++;
}

unsigned char compareTime(unsigned int throld, unsigned int cur_time, unsigned int last_time) {
	if(cur_time < last_time)
		cur_time = cur_time + last_time;

	if(cur_time >= (last_time + throld))
		return 1;
	else if((cur_time >= (last_time + throld - 10)) && cnt % 2) {
		LED_K0_TOGGLE;
		contine = 1;
	}
	return 0;
}


//################################MAIN############################################

int main( void )
{
  
  // I/O Initialisierung

	DDRD |= (1<<PD0) | (1<<PD1) | (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6); // Ausgänge
	DDRB |= (1<<PB2) | (1<<PB3);
	DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3) | (1<<PC4) | (1<<PC5) | (1<<PC6);

	DDRA &= ~( (1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) | (1<<PA4) | (1<<PA5) | (1<<PA6) | (1<<PA7) );  /* PA0 und PA3 als Eingaenge */
	PORTA |= (1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) | (1<<PA4) | (1<<PA5) | (1<<PA6) | (1<<PA7);      /* Interne Pull-Up fuer beide einschalten */


	//Timer 1 initialisieren:
	TIMSK |= (1<<TOIE1); 									//aktivieren des Ûeberlaufinterrupts von Timer1 
	TCCR1B = (1<<CS11); 									//Prescaler = 8
	sei();



  //Initialisierung
	DDRB |= (1<<PB6);

			//SPI EIN	 Daten nach2. Flanke übernehmen
	SPCR |= (1 << SPE) | (1 << CPHA); // Slave, SPI enable

	int i=0;
	unsigned char time = 0;


//Endlosschleife
while(1)
{

	if(cnt >= 10) {
		cnt = 0;
		sek++;
		if(sek == 600)
			sek = 0;
	}

	i=SPDR;

	if( i==1)	{W9_EIN;}

	if( i==2)	{W10_EIN;}


	if( i==3)	{W11_EIN;}

	if( i==4)	{W12_AUS;W13_EIN;}

	if( i==5)	{W9_AUS;}

	if( i==6)	{W10_AUS;}

	if( i==7)	{W11_AUS;}

	if( i==8)	{W12_EIN;W13_AUS;}

	if((!TS0 && !(flanke & 1)) || (!TS0 && contine)) {
		_delay_ms(100);
		flanke |= 1; 
		K0_TOGGLE; LED_K0_TOGGLE;KS11_AUS;KS21_AUS;KS22_AUS;KS24_AUS;
		time = sek;
		contine = 0;
		_delay_ms(255);
	}
	if( TS0 && (flanke & 1)) 
		flanke &= 0xfe;
	

	if( TS11 )	{_delay_ms(255);if( TS11 ){KS11_TOGGLE;LED_K0_AUS;K0_AUS;}}

	if( TS21 )	{_delay_ms(255);if( TS21 ){KS21_TOGGLE;LED_K0_AUS;K0_AUS;}}

	if( TS22 )	{_delay_ms(255);if( TS22 ){KS22_TOGGLE;LED_K0_AUS;K0_AUS;}}

	if( TS24 )	{_delay_ms(255);if( TS24 ){KS24_TOGGLE;LED_K0_AUS;K0_AUS;}}

	if(compareTime(120, sek, time)) {
		K0_AUS;
		LED_K0_AUS;
	}
	
}


return(0);
}


/*
	if( BIT_1 && !BIT_2)	{_delay_ms(255);W9_EIN;}
	else {_delay_ms(255);W9_AUS;}
	if( BIT_2)	{_delay_ms(255);W10_EIN;}
	else {_delay_ms(255);W10_AUS;}
	if( BIT_3)	{_delay_ms(255);W11_EIN;}
	else {_delay_ms(255);W11_AUS;}
	if( BIT_4)	{_delay_ms(255);W12_AUS;W13_EIN;}
	else {_delay_ms(255);W12_EIN;W13_AUS;}
*/

/*
	if( BIT_1) && !BIT_2 && !BIT_3 && !BIT_4  )	{W9_AUS;}

	if( !BIT_1 && BIT_2 && !BIT_3 && !BIT_4  )	{W10_EIN;}

	if( BIT_1 && BIT_2 && !BIT_3 && !BIT_4  )	{W11_AUS;}

	if( !BIT_1 && !BIT_2 && BIT_3 && !BIT_4  )	{W12_AUS;}

	if( BIT_1 && !BIT_2 && BIT_3 && !BIT_4  )	{W13_AUS;}

_delay_ms(255);_delay_ms(255);
	PORTD &= ~(1<<PD0);PORTD &= ~(1<<PD1);PORTD &= ~(1<<PD2);PORTD &= ~(1<<PD3);PORTD &= ~(1<<PD4);
	_delay_ms(255);_delay_ms(255);
	PORTD |= (1<<PD0);PORTD |= (1<<PD1);PORTD |= (1<<PD2);PORTD |= (1<<PD3);PORTD |= (1<<PD4);
	_delay_ms(255);_delay_ms(255);
*/
