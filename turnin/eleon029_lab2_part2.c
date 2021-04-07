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
    unsigned char cntavail = 0; //Counter for avaiable spaces
    /* Insert your solution below */
    while (1) {
	//1) Read Input
	tempA = PINA & 0x0F;
	cntavail = 4;

	//2) Perform Computation
	if((tempA & 0x01) && (tempA & 0x02) && (tempA & 0x04) && (tempA & 0x08)){	//If all spots are occupied, decrement by 4      
                cntavail = cntavail - 4;
       	}
	else if(((tempA & 0x01) && (tempA & 0x02) && (tempA & 0x04)) || ((tempA & 0x01) && (tempA & 0x02) && (tempA & 0x08)) || ((tempA & 0x01) && (tempA & 0x04) && (tempA & 0x08)) || ((tempA & 0x02) && (tempA & 0x04) && (tempA & 0x08))){	//If 3 spots are occupied, decrement by 3
                cntavail = cntavail - 3;
        }
	else if(((tempA & 0x01) && (tempA & 0x02)) || ((tempA & 0x01) && (tempA & 0x04)) || ((tempA & 0x01) && (tempA & 0x08)) || ((tempA & 0x02) && (tempA & 0x04)) || ((tempA & 0x02) && (tempA & 0x08)) || ((tempA & 0x04) && (tempA & 0x08))){ //If 2 spots are occupied, decrement by 2
                cntavail = cntavail - 2;
        }
	else if((tempA & 0x01) || (tempA & 0x02) || (tempA & 0x04) || (tempA & 0x08)){	//If 1 spots are occupied, decrement by 1
                cntavail = cntavail - 1;
        }
	else{
		//Does nothing cntavail is 4
	}

	//3) Write Output
	PORTC = cntavail;
    }
    return 0;
}
