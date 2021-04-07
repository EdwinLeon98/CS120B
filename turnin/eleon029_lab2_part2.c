/*	Author & Email: Edwin M. Leon Du, eleon029@ucr.edu
 *  	Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab 2  Exercise 2
 *	Exercise Description: Parking sensor exercise
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
    DDRC = 0xFF;	//Configure port C's 8 pins as output
    PORTC = 0x00;	//Initialize PORTC output to 0's

    unsigned char tempA = 0x00;	//Temporary variable to hold value of A
    unsigned char cntavail = 0x00; //Counter for avaiable spaces
    /* Insert your solution below */
    while (1) {
	//1) Read Input
	tempA = PINA & 0x0F;
	cntavail = 0x04;

	//2) Perform Computation
	//If PA0 is 1, decrement cntavail
	if(tempA & 0x01){	
		cntavail = cntavail - 1;
	}
	//If PA1 is 1, decrement cntavail
	if(tempA & 0x02){       
                cntavail = cntavail - 1;
        }
	//If PA2 is 1, decrement cntavail
	if(tempA & 0x04){       
                cntavail = cntavail - 1;
        }
	//If PA3 is 1, decrement cntavail
	if(tempA & 0x08){      
                cntavail = cntavail - 1;
        }

	//3) Write Output
	PORTC = cntavail;
    }
    return 0;
}
