/*
 * Weichen_Test.h
 *
 *  Created off: 19.11.2014
 *      Author: joe
 */

#ifndef WEICHEN_TEST_H_
#define WEICHEN_TEST_H_

#define LEDREL0_off (PORTC  |= (1<<0))
#define LEDREL1_off (PORTC  |= (1<<1))
#define LEDREL2_off (PORTC  |= (1<<2))
#define LEDREL3_off (PORTC  |= (1<<3))
#define LEDREL4_off (PORTC  |= (1<<4))
#define LEDREL5_off (PORTC  |= (1<<5))
#define LEDREL6_off (PORTC  |= (1<<6))
#define LEDREL7_off (PORTC  |= (1<<7))

#define LEDREL8_off (PORTA  |= (1<<7))
#define LEDREL9_off (PORTA  |= (1<<6))
#define LEDREL10_off (PORTA |= (1<<5))
#define LEDREL11_off (PORTA |= (1<<4))
#define LEDREL12_off (PORTA |= (1<<3))
#define LEDREL13_off (PORTA |= (1<<2))
#define LEDREL14_off (PORTA |= (1<<1))
#define LEDREL15_off (PORTA |= (1<<0))

#define LEDREL0_on (PORTC &= ~(1<<0))
#define LEDREL1_on (PORTC &= ~(1<<1))
#define LEDREL2_on (PORTC &= ~(1<<2))
#define LEDREL3_on (PORTC &= ~(1<<3))
#define LEDREL4_on (PORTC &= ~(1<<4))
#define LEDREL5_on (PORTC &= ~(1<<5))
#define LEDREL6_on (PORTC &= ~(1<<6))
#define LEDREL7_on (PORTC &= ~(1<<7))

#define LEDREL8_on (PORTA &= ~(1<<7))
#define LEDREL9_on (PORTA &= ~(1<<6))
#define LEDREL10_on (PORTA &= ~(1<<5))
#define LEDREL11_on (PORTA &= ~(1<<4))
#define LEDREL12_on (PORTA &= ~(1<<3))
#define LEDREL13_on (PORTA &= ~(1<<2))
#define LEDREL14_on (PORTA &= ~(1<<1))
#define LEDREL15_on (PORTA &= ~(1<<0))

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






#endif /* WEICHEN_TEST_H_ */
