/*	Author & Email: Edwin M. Leon Du, eleon029@ucr.edu
 *  	Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab 3  Exercise 1
 *	Exercise Description: Counting 1's exercise
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
    DDRB = 0x00;        //Configure port B's 8 pins as input
    PORTB = 0xFF;
    DDRC = 0xFF;	//Configure port C's 8 pins as output
    PORTC = 0x00;	//Initialize PORTC output to 0's

    unsigned char tempA = 0x00;	//Temporary variable to hold value of A
    unsigned char tempB = 0x00; //Temporary variable to hold value of B
    unsigned char counter; 	//Counter for 1's in ports A and B
    unsigned char i;
    /* Insert your solution below */
    while (1) {
	//1) Read Input
	tempA = PINA & 0xFF;
	tempB = PINB & 0xFF;
	counter = 0x00;

	//2) Perform Computation
	for(i = 0; i < 8; i++){
		if((tempA >> i) & 0x01){
			counter = counter + 0x01;
		}
		if((tempB >> i) & 0x01){
			counter = counter + 0x01;
		}
	}

	//3) Write Output
	PORTC = counter;
    }
    return 0;
}
