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

enum SM_States { SM_Init, SM_Inc, SM_Dec, SM_Wait1, SM_Wait2, SM_Wait3, SM_Reset} SM_State;

unsigned char TickFunc(unsigned char A0, unsigned char A1, unsigned char B){
	switch(SM_State){
		case SM_Init:
			SM_State = SM_Wait1;;
			break;
		
		case SM_Wait1:
			if(A0 && A1){
				SM_State = SM_Wait1;
			}
			else if(A0 && !A1){
				SM_State = SM_Inc;
			}
			else if(!A0 && A1){
				SM_State = SM_Dec;
			}
			else{
				SM_State = SM_Reset;
			}
			break;

		case SM_Inc:
			SM_State = SM_Wait2;
			break;
		
		case SM_Wait2:
			if(A0 && !A1){
				SM_State = SM_Wait2;
			}
			else if(A1){
				SM_State = SM_Dec;
			}
			else{
				SM_State = SM_Reset;;
			}
			break;

		case SM_Dec:
			SM_State = SM_Wait3;
			break;

		case SM_Wait3:
			if(A1 && !A0){
				SM_State = SM_Wait3;
			}
			else if(A0){
				SM_State = SM_Inc;
			}
			else{
				SM_State = SM_Reset;;
			}
			break;

		case SM_Reset:
			if(A0 || A1){
				SM_State = SM_Wait1;
			}
			else{
				SM_State = SM_Reset;
			}
		default:
			SM_State = SM_Init;
			break;
	}	
	
	switch(SM_State){
		case SM_Init:
			break;

		case SM_Wait1:
			break;

		case SM_Inc:
			if(B < 0x0A){
				B = B + 0x01;
			}
			break;
	
		case SM_Wait2:
			break;

		case SM_Dec:
			if(B > 0x00){
				B = B - 0x01;
			}
			break;

		case SM_Wait3:
			break;

		case SM_Reset:
			B = 0x00;
			break;

		default:
			break; 			
	}

	return B;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;	//Configure port A's 8 pins as input
    PORTA = 0xFF;
    DDRB = 0xFF;	//Configure port B's 8 pins as output
    PORTB = 0x00;	//Initialize PORTB output to 0's

    unsigned char tempA0 = 0x00;	//Temporary variable to hold value of A
    unsigned char tempA1 = 0x00;
    unsigned char tempB = 0x00;

    SM_State = SM_Init;
    tempB = 0x07;
    /* Insert your solution below */
    while(1) {
	//1) Read Input
	tempA0 = PINA & 0x01;
	tempA1 = PINA & 0x02;

	//2) Perform Computation
	tempB = (TickFunc(tempA0, tempA1, tempB) & 0x0F);

	//3) Write Output
	PORTB = tempB;
    }
    return 0;
}
