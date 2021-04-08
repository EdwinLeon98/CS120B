/*	Author & Email: Edwin M. Leon Du, eleon029@ucr.edu
 *  	Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab 3  Exercise 5
 *	Exercise Description: Weight sensor, input and output pin combination exercise
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
    DDRD = 0x00;	//Configure port A's 8 pins as input
    PORTD = 0xFF;
    DDRB = 0xFE;        //Configure port B's 8 pins as 7 upper pins output and lower pin input
    PORTB = 0x01;       

    unsigned char tempD = 0x00;
    unsigned char tempInputB = 0x00;
    unsigned char tempOutputB = 0x00;
    unsigned short weight;
    /* Insert your solution below */
    while (1) {
	//1) Read Input
	tempD = PIND & 0xFF;
	tempInputB = PINB & 0x01;
	tempOutputB = 0x00;	
	weight  = 0;

	//2) Perform Computation
	weight = (tempD * 2) + tempInputB;
	
	if(weight >= 70){
		tempOutputB = tempOutputB | 0x02; 
	}	
	else if((weight > 5) && (weight < 70)){
		tempOutputB = tempOutputB | 0x04;
	}
	else{
		//Nothing because there is no passenger
	}

	//3) Write Output
	PORTB = tempOutputB;
    }
    return 0;
}
