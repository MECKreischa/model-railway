

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
	
	DDRB = 0b00000000;	//EEEEEEEE
	PORTB =0b11111111;	//PullUP R  an



	DDRA = 0xFF;  //PORTA = Ausgang
	PORTA= 0x00;		//LEDREL aus

	DDRC = 0xFF;  //PORTC = Ausgang
	PORTC= 0x00;		//LEDREL aus
	

}

void warten()
{
_delay_ms(1000);       // 1 sekunde warten
}


void blinkon()
{
	LEDREL0_on;   	  //Bit setzen
    warten();
    LEDREL1_on;   	  //Bit setzen
    warten();
    LEDREL2_on;   	  //Bit setzen
    warten();
    LEDREL3_on;   	  //Bit setzen
    warten();
    LEDREL4_on;   	  //Bit setzen
    warten();
    LEDREL5_on;   	  //Bit setzen
    warten();
    LEDREL6_on;   	  //Bit setzen
    warten();
    LEDREL7_on;   	  //Bit setzen
    warten();
    LEDREL8_on;   	  //Bit setzen
    warten();
    LEDREL9_on;   	  //Bit setzen
    warten();
    LEDREL10_on;   	  //Bit setzen
    warten();
    LEDREL11_on;   	  //Bit setzen
    warten();
    LEDREL12_on;   	  //Bit setzen
    warten();
    LEDREL13_on;   	  //Bit setzen
    warten();
    LEDREL14_on;   	  //Bit setzen
    warten();
    LEDREL15_on;   	  //Bit setzen
    warten();
}

void blinkoff()
{
    LEDREL0_off;   // Bit loeschen
    warten();
    LEDREL1_off;   // Bit loeschen
    warten();
    LEDREL2_off;   // Bit loeschen
    warten();
    LEDREL3_off;   // Bit loeschen
    warten();
    LEDREL4_off;   // Bit loeschen
    warten();
    LEDREL5_off;   // Bit loeschen
    warten();
    LEDREL6_off;   // Bit loeschen
    warten();
    LEDREL7_off;   // Bit loeschen
    warten();
    LEDREL8_off;   // Bit loeschen
    warten();
    LEDREL9_off;   // Bit loeschen
    warten();
    LEDREL10_off;   // Bit loeschen
    warten();
    LEDREL11_off;   // Bit loeschen
    warten();
    LEDREL12_off;   // Bit loeschen
    warten();
    LEDREL13_off;   // Bit loeschen
    warten();
    LEDREL14_off;   // Bit loeschen
    warten();
    LEDREL15_off;   // Bit loeschen

}
 
main(void)
{
init();


while (1)
{



for (int l=0; l<2;l++)
{
PORTA = 0xFF;
warten();
PORTA= 0x00;
warten();
PORTC = 0xFF;
warten();
PORTC= 0x00;
warten();
}
PORTC=0xFF;
PORTA=0xFF;
blinkon();
warten();
blinkoff();
warten();
PORTC=0x00;
PORTA=0x00;

  }
  return 0;                         
}
