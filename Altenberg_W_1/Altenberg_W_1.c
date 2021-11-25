#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <inttypes.h>



#define S11     !(PINA & 1<<PA0)
#define S12     !(PINA & 1<<PA1)
#define S13     !(PINA & 1<<PA2)
#define S14     !(PINA & 1<<PA3)
#define S21     !(PINA & 1<<PA4)
#define S22     !(PINA & 1<<PA5)
#define S23     !(PINA & 1<<PA6)
#define S24     !(PINA & 1<<PA7)
#define S25     !(PINC & 1<<PC7)
#define S26     !(PINC & 1<<PC6)
#define S27     !(PIND & 1<<PD7)
#define S28     !(PINC & 1<<PC0)

#define W1_AUS  (PORTB &= ~(1<<PB3))	
#define W1_EIN	(PORTB |= (1<<PB3))
#define W2_AUS  (PORTB &= ~(1<<PB4))
#define W2_EIN	(PORTB |= (1<<PB4))
#define W3_AUS  (PORTD &= ~(1<<PD0))	
#define W3_EIN	(PORTD |= (1<<PD0))
#define W4_AUS  (PORTD &= ~(1<<PD1))
#define W4_EIN	(PORTD |= (1<<PD1))
#define W5_AUS  (PORTD &= ~(1<<PD2))
#define W5_EIN	(PORTD |= (1<<PD2))
#define W6_AUS  (PORTD &= ~(1<<PD3))
#define W6_EIN	(PORTD |= (1<<PD3))
#define W7_AUS  (PORTD &= ~(1<<PD4))	
#define W7_EIN	(PORTD |= (1<<PD4))
#define W8_AUS  (PORTD &= ~(1<<PD5))
#define W8_EIN	(PORTD |= (1<<PD5))


#define BIT_1   SPI_Data (1)
#define _BIT_1	SPI_Data (5)
#define BIT_2  	SPI_Data (2)
#define _BIT_2	SPI_Data (6)
#define BIT_3  	SPI_Data (3)
#define _BIT_3	SPI_Data (7)
#define BIT_4  	SPI_Data (4)
#define _BIT_4	SPI_Data (8)


	void master_init (void) {
	DDRB |= (1<<PB5) | (1<<PB7);				// setze SCK,MOSI als Ausgang
//	PORTB = (1<<PB7);							// SCK  high
	SPCR = (1 << MSTR) | (1 << SPE) | (1 << SPR1) | (1 << CPHA);	// Master, SPI enable, Interrupt disable, CPU/4, Polarität0
	SPDR =0;
	_delay_ms(25);
//	while(!(SPDR & (1<<SPIF)));
	PORTD |= (1<<PD6);							// PD6  high (ist mit SS am Slave verbunden)								//Status löschen
	}

	void SPI_Data (int data)
	{
		PORTD &= ~(1<<PD6);			//SS am Slave Low --> Beginn der Übertragung
		SPDR = data;				//Daten schicken
		_delay_ms(25);
//		while(!(SPDR & (1<<SPIF))); //warten bis alles gesendet ist
		PORTD |= (1<<PD6);			// PD7  high --> Ende Übertragung

	}	

//################################MAIN############################################

int main( void )
{
  
  // I/O Initialisierung
	DDRA &= ~( (1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) | (1<<PA4) | (1<<PA5) | (1<<PA6) | (1<<PA7) );  /* PA0 und PA3 als Eingaenge */
	PORTA |= (1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) | (1<<PA4) | (1<<PA5) | (1<<PA6) | (1<<PA7);      /* Interne Pull-Up fuer beide einschalten */
	DDRC &= ~( (1<<PC0) | (1<<PC5) | (1<<PC6) | (1<<PC7) );  /* PCx als Eingaenge */
	DDRD &= ~(1<<PD7);
	PORTD |= (1<<PD7);
	PORTC |= (1<<PC0) | (1<<PC5) | (1<<PC6) | (1<<PC7) ;      /* Interne Pull-Up einschalten */
	DDRD |= (1<<PD0) | (1<<PD1) | (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6); // Ausgänge
	DDRB |= (1<<PB3) | (1<<PB4);														// Ausgänge
									
  //Initialisierung

PORTC &= ~(1<<PC1);	//Ausgang ausschalten weil sonst eingeschaltet

	master_init ();




//Endlosschleife
while(1)
{
	
	if( S11 && S21 )	{_delay_ms(255);if( S11 && S21 ){W1_EIN;W5_EIN;W6_EIN;}}				

	if( S11 && S22 )	{_delay_ms(255);if( S11 && S22 ){W1_EIN;W5_AUS;W6_EIN;}}
					
	if( S11 && S23 )	{_delay_ms(255);if( S11 && S23 ){W1_AUS;W7_EIN;W8_EIN;BIT_1;}}			

	if( S11 && S24 )	{_delay_ms(255);if( S11 && S24 ){W1_AUS;W7_EIN;W8_EIN;_BIT_1;}}		

	if( S11 && S25 )	{_delay_ms(255);if( S11 && S25 ){W1_AUS;W7_AUS;W8_EIN;_BIT_2;_BIT_3;}}

	if( S11 && S26 )	{_delay_ms(255);if( S11 && S26 ){W1_AUS;W7_AUS;W8_EIN;_BIT_2;BIT_3;}}
	
	if( S11 && S27 )	{_delay_ms(255);if( S11 && S27 ){W1_AUS;W7_AUS;W8_EIN;BIT_2;}}



	if( S12 && S21 )	{_delay_ms(255);if( S12 && S21 ){W3_EIN;W4_AUS;W5_EIN;W6_AUS;}}			

	if( S12 && S22 )	{_delay_ms(255);if( S12 && S22 ){W3_EIN;W4_AUS;W5_AUS;W6_AUS;}}		

	if( S12 && S23 )	{_delay_ms(255);if( S12 && S23 ){W3_AUS;W4_AUS;W7_EIN;W8_AUS;BIT_1;}}		

	if( S12 && S24 )	{_delay_ms(255);if( S12 && S24 ){W3_AUS;W4_AUS;W7_EIN;W8_AUS;_BIT_1;}}		

	if( S12 && S25 )	{_delay_ms(255);if( S12 && S25 ){W3_AUS;W4_AUS;W7_AUS;W8_AUS;_BIT_2;_BIT_3;}}

	if( S12 && S26 )	{_delay_ms(255);if( S12 && S26 ){W3_AUS;W4_AUS;W7_AUS;W8_AUS;_BIT_2;BIT_3;}}

	if( S12 && S27 )	{_delay_ms(255);if( S12 && S27 ){W3_AUS;W4_AUS;W7_AUS;W8_AUS;BIT_2;}}


	if( S13 && S21 )	{_delay_ms(255);if( S13 && S21 ){W2_AUS;W3_EIN;W4_EIN;W5_EIN;W6_AUS;}}			

	if( S13 && S22 )	{_delay_ms(255);if( S13 && S22 ){W2_AUS;W3_EIN;W4_EIN;W5_AUS;W6_AUS;}}		

	if( S13 && S23 )	{_delay_ms(255);if( S13 && S23 ){W2_AUS;W3_AUS;W4_EIN;W7_EIN;W8_AUS;BIT_1;}}		

	if( S13 && S24 )	{_delay_ms(255);if( S13 && S24 ){W2_AUS;W3_AUS;W4_EIN;W7_EIN;W8_AUS;_BIT_1;}}		

	if( S13 && S25 )	{_delay_ms(255);if( S13 && S25 ){W2_AUS;W3_AUS;W4_EIN;W7_AUS;W8_AUS;_BIT_2;_BIT_3;}}

	if( S13 && S26 )	{_delay_ms(255);if( S13 && S26 ){W2_AUS;W3_AUS;W4_EIN;W7_AUS;W8_AUS;_BIT_2;BIT_3;}}

	if( S13 && S27 )	{_delay_ms(255);if( S13 && S27 ){W2_AUS;W3_AUS;W4_EIN;W7_AUS;W8_AUS;BIT_2;}}



	if( S14 && S21 )	{_delay_ms(255);if( S14 && S21 ){W2_EIN;W3_EIN;W4_EIN;W5_EIN;W6_AUS;}}			

	if( S14 && S22 )	{_delay_ms(255);if( S14 && S22 ){W2_EIN;W3_EIN;W4_EIN;W5_AUS;W6_AUS;}}		

	if( S14 && S23 )	{_delay_ms(255);if( S14 && S23 ){W2_EIN;W3_AUS;W4_EIN;W7_EIN;W8_AUS;BIT_1;}}		

	if( S14 && S24 )	{_delay_ms(255);if( S14 && S24 ){W2_EIN;W3_AUS;W4_EIN;W7_EIN;W8_AUS;_BIT_1;}}	

	if( S14 && S25 )	{_delay_ms(255);if( S14 && S25 ){W2_EIN;W3_AUS;W4_EIN;W7_AUS;W8_AUS;_BIT_2;_BIT_3;}}

	if( S14 && S26 )	{_delay_ms(255);if( S14 && S26 ){W2_EIN;W3_AUS;W4_EIN;W7_AUS;W8_AUS;_BIT_2;BIT_3;}}

	if( S14 && S27 )	{_delay_ms(255);if( S14 && S27 ){W2_EIN;W3_AUS;W4_EIN;W7_AUS;W8_AUS;BIT_2;}}


	if( S28 )	{_delay_ms(255);if( S28 ) BIT_4;
				}
	else _BIT_4;



}


return(0);
}




/*_delay_ms(255);_delay_ms(255);
	PORTD &= ~(1<<PD0);PORTD &= ~(1<<PD1);PORTD &= ~(1<<PD2);PORTD &= ~(1<<PD3);PORTD &= ~(1<<PD4);
	_delay_ms(255);_delay_ms(255);
	PORTD |= (1<<PD0);PORTD |= (1<<PD1);PORTD |= (1<<PD2);PORTD |= (1<<PD3);PORTD |= (1<<PD4);
	_delay_ms(255);_delay_ms(255);
*/


