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

enum SM_States {SM_Start, SM_Init, SM_PressInc, SM_PressDec, SM_Wait1, SM_WaitInc, SM_WaitDec, SM_Reset} SM_State;

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
			SM_State = SM_WaitInc;
			break;
		
		case SM_PressDec:
			SM_State = SM_WaitDec;
			break;

		case SM_WaitInc: 
                        if(A0 && !A1){
                                SM_State = SM_WaitInc;
                        }
			else if(A0 && A1){
				SM_State = SM_Reset;
			}
                        else{
                                SM_State = SM_Wait1;
                        }
			break;

                case SM_WaitDec:
                        if(A1 && !A0){
                                SM_State = SM_WaitDec;
                        }
			else if(A1 && A0){
				SM_State = SM_Reset;
			}
                        else{
                                SM_State = SM_Wait1;
                        }
                        break;

		case SM_Reset:
		/*	if(A0 && A1){
				SM_State = SM_Reset;
			}
			else if(A0 && !A1){
				SM_State = SM_WaitInc;
			}
			else if(A1 && !A0){
				SM_State = SM_WaitDec;
			}
			else{
				SM_State = SM_Wait1;
			}
		*/	
			SM_State = SM_Wait1;	
			break;

		default:
			SM_State = SM_Start;
			break;
	}	
	
	switch(SM_State){
		case SM_Start:
			break;

		case SM_Init:
			C = 0x07;
			break;

		case SM_Wait1:
			break;

		case SM_PressInc:
			if(C < 0x09){
				C = C + 0x01;
			}
			break;

                case SM_PressDec:
                        if(C > 0x00){
                                C = C - 0x01;
                        }
                        break;

		case SM_WaitInc:
			break;

                case SM_WaitDec:
                        break;
		
		case SM_Reset:
			C = 0x00;
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
	if((PINA & 0x03) == 0x01){
		tempA0 = PINA & 0x01;
		if(tempC == 0){
			tempA1 = PINA & 0x02;
		}
	}
        else if((PINA & 0x03) == 0x02){
                tempA1 = PINA & 0x02;
	        if(tempC == 0){
                        tempA0 = PINA & 0x01;
                }
        }
	else{
		tempA0 = PINA & 0x01;
                tempA1 = PINA & 0x02;
	}
	//2) Perform Computation
	tempC = TickFunc(tempA0, tempA1, tempC);

	//3) Write Output
	PORTC = tempC;
    }
    return 0;
}
