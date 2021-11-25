#include <avr/io.h>

void SPI_MasterInit(void) {
DDRB = (1<<PB3)|(1<<PB5);					//MOSI und SCK als Ausgang, Rest ist Eingang
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);		//Aktivierung des SPI, Master, Taktrate fck/16
}

void SPI_MasterTransmit(char cData) {
SPDR = cData;								//starte Transmission
while(!(SPSR & (1<<SPIF))) {}				//warte, bis Transmission abgeschlossen ist
}

void SPI_SlaveInit(void){
DDRB = (1<<PB4);							//MISO als Ausgang, Rest ist Eingang
SPCR = (1<<SPE);							//Aktivierung des SPI
}

char SPI_SlaveReceive(void) {
while(!(SPSR & (1<<SPIF))) {}				//warte, bis Empfang abgeschlossen ist
return SPDR;								//gib empfangenen Wert zurück
}
