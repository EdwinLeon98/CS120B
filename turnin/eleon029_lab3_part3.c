/*	Author & Email: Edwin M. Leon Du, eleon029@ucr.edu
 *  	Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab 3  Exercise 3
 *	Exercise Description: Fuel-level sensor extended exercise
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
    unsigned char tempA2 = 0x00;
    unsigned char tempC = 0x00;
    /* Insert your solution below */
    while (1) {
	//1) Read Input
	tempA = PINA & 0x0F;
	tempA2 = PINA & 0x7F;

	//2) Perform Computation
        if(tempA == 0x00){
                tempC = 0x40;
        }	
    	else if(tempA == 0x01 || tempA == 0x02){
		tempC = 0x60;	
	}	
	else if(tempA == 0x03 || tempA == 0x04){
		tempC = 0x70;
	}
        else if(tempA == 0x05 || tempA == 0x06){
                tempC = 0x38;
        }
        else if(tempA == 0x07 || tempA == 0x08 || tempA == 0x09){
                tempC = 0x3C;
        }
        else if(tempA == 0x0A || tempA == 0x0B || tempA == 0x0C){
                tempC = 0x3E;
        }
	else if(tempA == 0x0D || tempA == 0x0E || tempA == 0x0F){
		tempC = 0x3F;
	}
	else{
		//Does nothing
	}

	if((tempA2 & 0x10) && (tempA2 & 0x20) && !(tempA2 & 0x40)){
		tempC = tempC | 0x80;		
	} 

	//3) Write Output
	PORTC = tempC;
    }
    return 0;
}
