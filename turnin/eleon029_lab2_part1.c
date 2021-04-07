/*	Author & Email: Edwin M. Leon Du, eleon029@ucr.edu
 *  	Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab 2  Exercise 1
 *	Exercise Description: Garage door exercise
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
	tempA = PINA & 0x03;
	
	//2) Perform Computation
	//If PA1PA0 is 00, set PB0 = 0
	if(tempA == 0x00){	//True if PA1PA0 = 00
		tempB = tempB & 0xFE;	//Sets tempB to bbbbbbb0
	}
	else if(tempA == 0x01){
		tempB = (tempB & 0xFE) | 0x01;	//Sets tempB to bbbbbbb1 (clear right most bit, then set to 1)
	}
	else if(tempA == 0x02){
		tempB = tempB & 0xFE;   //Sets tempB to bbbbbbb0
	}
	else if(tempA == 0x03){
		tempB = tempB & 0xFE;   //Sets tempB to bbbbbbb0
	}
	else{
	}
	
	//3) Write Output
	PORTB = tempB;	//Writes port B's 8 pins
    }
    return 0;
}
