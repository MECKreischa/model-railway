#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <inttypes.h>


#define TS0      !(PINA & 1<<PA0)	//Relais Rangierfahrt
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
#define K0_STATE    !(PINC & 1<<PC6)

#define MILIS 10	//10 * milis = 1 sek
#define SEK 600		//max delay_s Zeit -> 10 min

volatile unsigned int milis = 0; 	// millisekunden = milis*100
volatile unsigned int sek = 0;
volatile char m_flanke = 0;
volatile char contine = 0;

struct merker_t {
   unsigned int time;
   char flanke;			//Bit0=Tasten Merker | Bit1=Timer Merker
   char warn;
} merker[6];			//TS11, TS12, TS22, TS24

typedef struct merker_t MERKER;

ISR(TIMER1_OVF_vect){
	TCNT1 = 53036;		//aller 0,1s wird ISR ausgeführt
	milis++;
}

//max delay_s Zeit -> 10 min 
unsigned char delay_s(unsigned int  throld, MERKER *m) {
		  m->warn = 0;
		  if (sek <= m->time - 10)
				  m->warn = 1;
          if (!m->flanke & 1) {
                  m->flanke |= 3;
                  if ((sek + throld) >= SEK) {
                          m->time = sek + throld - SEK;
				  }
                  else {
                          m->time = sek + throld;
   				  }
          }
          if (sek == m->time) {
		  m->warn = 0;
                  return 1;
          }

          return 0;
}

//1/10 milis -> 10 * milis = 1 sek
unsigned char delay_ms(unsigned int  throld, MERKER *m) {
          if (!m->flanke & 1) {
                  m->flanke |= 3;
                  if ((milis + throld) >= MILIS)
                          m->time = milis + throld - MILIS;
                  else
                          m->time = milis + throld;
          }
          if (milis == m->time && m->flanke & 2) {
		  		  m->flanke &= ~2;
                  return 1;
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
	unsigned char m_time = 0;


//Endlosschleife
while(1)
{

	if(milis >= MILIS) {
		milis = 0;
		sek++;
		if(sek == SEK)
			sek = 0;
	}

	i=SPDR;

	if(i==1)	{W9_EIN;}

	if(i==2)	{W10_EIN;}


	if(i==3)	{W11_EIN;}

	if(i==4)	{W12_AUS;W13_EIN;}

	if(i==5)	{W9_AUS;}

	if(i==6)	{W10_AUS;}

	if(i==7)	{W11_AUS;}

	if(i==8)	{W12_EIN;W13_AUS;}

	if(TS0){	if(delay_ms(3,&merker[4]))	{K0_TOGGLE; LED_K0_TOGGLE; KS11_AUS;KS21_AUS;KS22_AUS;KS24_AUS;}}
	else		merker[4].flanke = 0;

//Problem: flanke wird nur zum Zeit aufziehen verwendet aber nicht das der Taster dauerhaft gedrückt wird
	if(TS11){	if(delay_ms(3,&merker[0]))	{KS11_TOGGLE;LED_K0_AUS;K0_AUS;}}
	else		merker[0].flanke = 0;

	if(TS21){	if(delay_ms(3,&merker[1])) 	{KS21_TOGGLE;LED_K0_AUS;K0_AUS;}}
	else		merker[1].flanke = 0;

	if(TS22){	if(delay_ms(3,&merker[2]))	{KS22_TOGGLE;LED_K0_AUS;K0_AUS;}}
	else		merker[2].flanke = 0;

	if(TS24){	if(delay_ms(3,&merker[3]))	{KS24_TOGGLE;LED_K0_AUS;K0_AUS;}}
	else		merker[3].flanke = 0;

	//if(!K0_STATE){	{KS11_EIN;}}
	//if(K0_STATE){	{KS11_AUS;}}

	if(!K0_STATE){	
		unsigned char tmp = delay_s(120,&merker[5]);
		if(tmp) {K0_AUS;}
		//LED Toggeln geht noch nicht!!! 9.9.22 noch nicht im git!!!
		//if(!merker[5].warn && sek % 2) LED_K0_TOGGLE;
	}

				//if(delay_s(59,&merker[5]))	{LED_K0_AUS;K0_AUS;KS11_EIN;}}
	else		merker[5].flanke = 0;
	
	//else LED_K0_AUS;
	
	
}


return(0);
}
