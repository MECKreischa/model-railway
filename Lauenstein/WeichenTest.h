/*
 * Weichen_Test.h
 *
 *  Created off: 19.11.2014
 *      Author: joe
 */

#ifndef WEICHEN_TEST_H_
#define WEICHEN_TEST_H_

#define REL10_on (PORTC  |= (1<<0))
#define REL9_on (PORTC  |= (1<<1))
#define REL8_on (PORTC  |= (1<<2))
#define REL7_on (PORTC  |= (1<<3))
#define REL6_on (PORTC  |= (1<<4))
#define REL5_on (PORTC  |= (1<<5))
#define REL4_on (PORTC  |= (1<<6))
#define REL3_on (PORTC  |= (1<<7))

#define REL11_on (PORTA  |= (1<<7))
#define REL12_on (PORTA  |= (1<<6))
#define REL13_on (PORTA |= (1<<5))
#define REL14_on (PORTA |= (1<<4)) // nicht belegt
#define REL15_on (PORTA |= (1<<3)) // geht zu Relais 15 aber durchgekratzt?
#define REL16_on (PORTA |= (1<<2)) // geht zu Relais 16 aber durchgekratzt?
#define REL2_on (PORTA |= (1<<1))
#define REL1_on (PORTA |= (1<<0))

#define REL10_off (PORTC &= ~(1<<0))
#define REL9_off (PORTC &= ~(1<<1))
#define REL8_off (PORTC &= ~(1<<2))
#define REL7_off (PORTC &= ~(1<<3))
#define REL6_off (PORTC &= ~(1<<4))
#define REL5_off (PORTC &= ~(1<<5))
#define REL4_off (PORTC &= ~(1<<6))
#define REL3_off (PORTC &= ~(1<<7))

#define REL11_off (PORTA &= ~(1<<7))
#define REL12_off (PORTA &= ~(1<<6))
#define REL13_off (PORTA &= ~(1<<5))
#define REL14_off (PORTA &= ~(1<<4)) // nicht belegt
#define REL15_off (PORTA &= ~(1<<3)) // geht zu Relais 15 aber durchgekratzt?
#define REL16_off (PORTA &= ~(1<<2)) // geht zu Relais 16 aber durchgekratzt?
#define REL2_off (PORTA &= ~(1<<1))
#define REL1_off (PORTA &= ~(1<<0))


#define S10  !(PIND & 1<<PD0)
#define S07  !(PIND & 1<<PD1)
#define S06  !(PIND & 1<<PD2)
#define S05  !(PIND & 1<<PD3)
#define S04  !(PIND & 1<<PD4)
#define S03  !(PIND & 1<<PD5)
#define S02  !(PIND & 1<<PD6)
#define S01  !(PIND & 1<<PD7)
#define S18  !(PINB & 1<<PB0)
#define S17  !(PINB & 1<<PB1)
#define S16 !(PINB & 1<<PB2)
#define S13 !(PINB & 1<<PB3)
#define S12 !(PINB & 1<<PB2)  // ToDo: from 4 to 2, Einfahrt von Schattenbhf in Hbf auf Digitalgleis
#define S11 !(PINB & 1<<PB2)  // ToDo: from 5 to 2, Hängt an den Klemmen von theoretisch K15
#define S15 !(PINB & 1<<PB2)  // ToDo: from 6 to 2, find new free Port
#define SCK !(PINB & 1<<PB7) // SCK

/*
#define REL15_on (PORTA |= (1<<3))
#define REL16_on (PORTA |= (1<<2))
#define REL15_off (PORTA &= ~(1<<3))
#define REL16_off (PORTA &= ~(1<<2))
*/

/*
#define TASTER0  PD0
#define TASTER1  PD1
#define TASTER2  PD2
#define TASTER3  PD3
#define TASTER4  PD4
#define TASTER5  PD5
#define TASTER6  PD6
#define TASTER7  PD7
#define TASTER8  PB0
#define TASTER9  PB1
#define TASTER10 PB2
#define TASTER11 PB3
#define TASTER12 PB4
*/





#endif /* WEICHEN_TEST_H_ */
