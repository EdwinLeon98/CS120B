/*	Author & Email: Edwin M. Leon Du, eleon029@ucr.edu
 *  	Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: Counter exercise
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_States {SM_Start, SM_Init, SM_PressInc, SM_PressDec, SM_Wait1} SM_State;

unsigned char TickFunc(unsigned char A0, unsigned char A1, unsigned char C){
	switch(SM_State){
		case SM_Start:
			SM_State = SM_Init;
			break;

		case SM_Init:
			SM_State = SM_Wait1;
			break;
		
		case SM_Wait1:
			if(A0 && !A1){
				SM_State = SM_PressInc;
			}
			else if(!A0 && A1){
				SM_State = SM_PressDec;
			}
			else{
				SM_State = SM_Wait1;
			}
			break;

		case SM_PressInc:
			if(A0){
				SM_State = SM_PressInc;
			}
			else{
				SM_State = SM_Wait1;
			}
			break;
		
		case SM_PressDec:
			if(A1){
				SM_State = SM_PressDec;
			}
			else{
				SM_State = SM_Wait1;
			}
			break;

		default:
			SM_State = SM_Start;
			break;
	}	
	
	unsigned char count = 0;	
	switch(SM_State){
		case SM_Start:
			break;

		case SM_Init:
			C = 0x07;
			break;

		case SM_Wait1:
			count = 0;
			break;

		case SM_PressInc:
			if(C < 0x08 && count == 0){
				C = C + 0x01;
				count++;
			}
			break;
	
		case SM_PressDec:
			if(C > 0x00 && count == 0){
				C = C - 0x01;
				count++;
			}
			break;

		default:
			break; 			
	}

	return C;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;	//Configure port A's 8 pins as input
    PORTA = 0xFF;
    DDRC = 0xFF;	//Configure port C's 8 pins as output
    PORTC = 0x00;	//Initialize PORTC output to 0's

    unsigned char tempA0 = 0x00;	//Temporary variable to hold value of A
    unsigned char tempA1 = 0x00;
    unsigned char tempC = 0x00;

    /* Insert your solution below */
    while(1) {
	//1) Read Input
	tempA0 = PINA & 0x01;
	tempA1 = PINA & 0x02;

	//2) Perform Computation
	tempC = (TickFunc(tempA0, tempA1, tempC) & 0x0F);

	//3) Write Output
	PORTC = tempC;
    }
    return 0;
}
