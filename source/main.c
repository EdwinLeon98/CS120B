/*	Author & Email: Edwin M. Leon Du, eleon029@ucr.edu
 *  	Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: LED lights exercise
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_States {SM_Start, SM_Init, SM_Lit1, SM_Lit2, SM_Wait1, SM_Wait2} SM_State;

unsigned char TickFunc(unsigned char x, unsigned char y){
	switch(SM_State){
		case SM_Start:
			SM_State = SM_Init;
			break;

		case SM_Init:
			SM_State = SM_Wait1;
			break;

		case SM_Lit1:
			if(!x){
				SM_State = SM_Wait1;
			}
			else{
				SM_State = SM_Lit1;
			}
			break;
		
		case SM_Wait1:
			if(!x){
				SM_State = SM_Wait1;
			}
			else{
				SM_State = SM_Lit2;
			}
			break;

		case SM_Lit2:
			if(!x){
				SM_State = SM_Wait2;
			}
			else{
				SM_State = SM_Lit2;
			}
			break;

		case SM_Wait2:
			if(!x){
				SM_State = SM_Wait2;
			}
			else{
				SM_State = SM_Lit1;
			}
			break;

		default:
			SM_State = SM_Start;
			break;
	}	
	
	switch(SM_State){
		case SM_Start:
			break;

		case SM_Init:
			y = (y & 0x00) | 0x01;
			break;

		case SM_Lit1:
			y = (y & 0x00) | 0x01;
			break;

		case SM_Wait1:
			break;
	
		case SM_Lit2:
			y = (y & 0x00) | 0x02;
			break;

		case SM_Wait2:
			break;

		default:
			break; 			
	}

	return y;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;	//Configure port A's 8 pins as input
    PORTA = 0xFF;
    DDRB = 0xFF;	//Configure port B's 8 pins as output
    PORTB = 0x00;	//Initialize PORTB output to 0's

    unsigned char tempA = 0x00;	//Temporary variable to hold value of A
    unsigned char tempB = 0x00;

    /* Insert your solution below */
    while(1) {
	//1) Read Input
	tempA = PINA & 0x01;

	//2) Perform Computation
	tempB = (TickFunc(tempA, tempB) & 0x03);

	//3) Write Output
	PORTB = tempB;
    }
    return 0;
}
