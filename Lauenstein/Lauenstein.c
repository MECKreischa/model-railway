

/*20-11
*/


#include <avr\io.h>
#include "WeichenTest.h"
#include <util\delay.h>


void init(void)
{
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);	//JTAG PORTC abschalten
	
	DDRD = 0b00000000;	//EEEEEEEE
	PORTD =0b11111111;	//PullUP R  an
	
	//DDRB = 0b00000000;	//EEEEEEEE
	//PORTB =0b11111111;	//PullUP R  an

	DDRB &= ~( (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB3) | (1<<PB4) | (1<<PB5) );  /* Eingaenge */
	PORTB |= (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB3) | (1<<PB4) | (1<<PB5);      /* Interne Pull-Up einschalten */




	DDRA = 0xFF;  //PORTA = Ausgang
	PORTA= 0x00;		//LEDREL aus

	DDRC = 0xFF;  //PORTC = Ausgang
	PORTC= 0x00;		//LEDREL aus

	DDRB |= (1 << PB6);		//MISO output
	//DDRB |= (1 << PB7);		//SCK output
    //PORTB &= ~( (1<<PB6) | (1<<PB7));
	SPCR |= (1 << SPE) | (1 << CPHA); //Slave, SPI enable


}
void warten()
{
_delay_ms(1000);       // 1 sekunde warten
}
 
main(void)
{

//Initialisierung
init();




//Endlosschleife Programm
while (1)
{



	if( S01 && S07)	{_delay_ms(255);if( S01 && S07 ){REL2_on;REL3_off;REL8_on;}}
	if( S01 && S04)	{_delay_ms(255);if( S01 && S04 ){REL8_off;REL10_on;REL11_off;REL12_off;}}
	if( S01 && S05)	{_delay_ms(255);if( S01 && S05 ){REL8_off;REL10_on;REL11_on;REL12_off;}}
	if( S01 && S06)	{_delay_ms(255);if( S01 && S06 ){REL3_on;REL8_off;REL10_off;}}


	if( S02 && S07)	{_delay_ms(255);if( S02 && S07 ){REL2_off;REL3_off;}}

	if( S03 && S04)	{_delay_ms(255);if( S03 && S04 ){REL12_on;REL11_off;}}

	if( S03 && S05)	{_delay_ms(255);if( S03 && S05 ){REL12_on;REL11_on;}}
		
    // Test SPI connection
	if( SPDR == 1 ){REL12_off;REL11_on;}
	if( SPDR == 5 ){REL12_on;REL11_off;}

	if( S10 && S16)	{_delay_ms(255);if( S10 && S16 ){REL5_on;REL6_off;REL7_off;}}
	if( S10 && S17)	{_delay_ms(255);if( S10 && S17 ){REL4_off;REL5_on;REL6_off;REL7_off;}}
	if( S10 && S18)	{_delay_ms(255);if( S10 && S18 ){REL4_off;REL6_off;REL7_on;}}

//	if( S11 && S18)	{_delay_ms(255);if( S11 && S18 ){REL6_on;REL7_on;}}



	if( S16 && S18)	{_delay_ms(255);if( S16 && S18 ){REL4_on;}}
	if( S16 && S17)	{_delay_ms(255);if( S16 && S17 ){REL4_off;}}
	if( S16 && S13)	{_delay_ms(255);if( S16 && S13 ){REL5_off;}}


	if( S11  && S15 ) 	{_delay_ms(255);if( S11  && S15 ){REL1_off;REL9_on;}}
	if( S11  && S13 ) 	{_delay_ms(255);if( S11  && S13 ){REL1_on;REL9_on;}}
	if( S11  && S16 ) 	{_delay_ms(255);if( S11  && S16 ){REL1_on;REL9_off;REL5_on;REL7_off;REL6_on;}}
	if( S11  && S17 ) 	{_delay_ms(255);if( S11  && S17 ){REL1_on;REL9_off;REL5_on;REL7_off;REL6_on;}}
	if( S11  && S18 ) 	{_delay_ms(255);if( S11  && S18 ){REL9_off;REL7_on;REL6_on;}}


	if( S17 && S13)	{_delay_ms(255);if( S17 && S13 ){REL5_off;}}

	if( S12 )	REL13_on; else REL13_off;

 



  }
  return 0;                         
}

/*
Rel8 Lauenstein Einfahrt von Altenberg
*/


/*
	if( S01 )	REL1_on; else REL1_off;
	if( S02 )	REL2_on; else REL2_off;
	if( S03 )	REL3_on; else REL3_off;
	if( S04 )	REL4_on; else REL4_off;
	if( S05 )	REL5_on; else REL5_off;
	if( S06 )	REL6_on; else REL6_off;
	if( S07 )	REL7_on; else REL7_off;
	if( S07 )	REL8_on; else REL8_off;
*/





/*
    warten();
    REL2_on;   	  //Bit setzen
    warten();
    REL3_on;   	  //Bit setzen
    warten();
    REL4_on;   	  //Bit setzen
    warten();
    REL5_on;   	  //Bit setzen
    warten();
    REL6_on;   	  //Bit setzen
    warten();
    REL7_on;   	  //Bit setzen
    warten();
	*/
