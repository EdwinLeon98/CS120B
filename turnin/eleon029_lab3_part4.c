/*	Author & Email: Edwin M. Leon Du, eleon029@ucr.edu
 *  	Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab 3  Exercise 4
 *	Exercise Description: UpperNibble <-> LowerNibble exercise
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;	//Configure port A's 8 pins as input
    PORTA = 0xFF;
    DDRB = 0xFF;        //Configure port B's 8 pins as output
    PORTB = 0x00;       //Initialize PORTB output to 0's
    DDRC = 0xFF;	//Configure port C's 8 pins as output
    PORTC = 0x00;	//Initialize PORTC output to 0's

    unsigned char tempUpperA = 0x00;	//Temporary variable to hold value of the upper nibble of A
    unsigned char tempLowerA = 0x00;    //Temporary variable to hold value of the lower nibble of A
    unsigned char tempB = 0x00;
    unsigned char tempC = 0x00;

    /* Insert your solution below */
    while (1) {
	//1) Read Input
	tempUpperA = PINA & 0xF0;
	tempLowerA = PINA & 0x0F;

	//2) Perform Computation
	tempB = (tempUpperA >> 4);
	tempC = (tempLowerA << 4);

	//3) Write Output
	PORTB = tempB;
	PORTC = tempC;
    }
    return 0;
}
