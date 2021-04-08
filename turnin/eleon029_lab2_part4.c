/*	Author & Email: Edwin M. Leon Du, eleon029@ucr.edu
 *  	Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab 2  Exercise 3
 *	Exercise Description: Parking sensor extended exercise
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
    DDRC = 0x00;        //Configure port C's 8 pins as input
    PORTC = 0xFF;
    DDRD = 0xFF;	//Configure port D's 8 pins as output
    PORTD = 0x00;	//Initialize PORTD output to 0's

    unsigned char tempA = 0x00;	//Temporary variable to hold value of A
    unsigned char tempB = 0x00; //Temporary variable to hold value of B
    unsigned char tempC = 0x00; //Temporary variable to hold value of C
    unsigned char tempD = 0x00; //Temporary variable to hold value of D
    unsigned short sum;
    /* Insert your solution below */
    while (1) {
	//1) Read Input
	tempA = PINA & 0xFF;
	tempB = PINB & 0xFF;
	tempC = PINC & 0xFF;
	sum = 0;

	//2) Perform Computation
	sum = tempA + tempB + tempC;
	tempD = sum >> 2;
	
	if(sum > 140){
		tempD = tempD | 0x01;
	}
	else{
		tempD = tempD & 0xFE;
	}

	if(((tempA - tempC) > 80) || ((tempC - tempA) > 80)){
		tempD = tempD | 0x02;
	}
	else{
		tempD = tempD & 0xFD;
	}

	//3) Write Output
	PORTD = tempD;
    }
    return 0;
}
