/*	Author: eleon029
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
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
    DDRB = 0xFF;	//Configure port B's 8 pins as output
    PORTB = 0x00;	//Initialize PORTB output to 0's

    unsigned char tempA = 0x00;	//Temporary variable to hold value of A
    unsigned char tempB = 0x00;	//Temporary variable to hold value of B

    /* Insert your solution below */
    while (1) {
	//1) Read Input
	tempA = PINA & 0x01;
	
	//2) Perform Computation
	//If PA0 is 1, set PB1PB0 = 01, else 10
	if(tempA == 0x01){	//True if PA0 is 1
		tempB = (tempB & 0xFC) | 0x01;	//Sets tempB to bbbbbb01 (clear right most 2 bits, then set to 01)
	}
	else{
		tempB = (tempB & 0xFC) | 0x02;	//Sets tempB to bbbbbb10 (clear right most 2 bits, then set to 10)
	}
	
	//3) Write Output
	PORTB = tempB;	//Writes port B's 8 pins
    }
    return 0;
}
