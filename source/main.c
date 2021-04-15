/*	Author & Email: Edwin M. Leon Du, eleon029@ucr.edu
 *  	Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab 4  Exercise 3
 *	Exercise Description: Door lock exercise
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_States {SM_Start, SM_Init,  SM_Release1,  SM_Code, SM_Unlocked, SM_Locked} SM_State;

unsigned char TickFunc(unsigned char A0, unsigned char A1, unsigned char A2, unsigned char A7, unsigned char B){
	switch(SM_State){
		case SM_Start:
			SM_State = SM_Init;
			break;

		case SM_Init:
			SM_State = SM_Locked;
			break;
		
		case SM_Release1:
			if(A2){
				SM_State = SM_Release1;
			}
			else if(!A2){
				SM_State = SM_Code;
			}
			else{
				SM_State = SM_Locked;
			}
			break;

/*		case SM_Release2:
			if(A1){
				SM_State = SM_Release2;
			}
			else{
				SM_State = SM_Unlocked;
			}
			break;
*/
		case SM_Code:
			if(A1){
				SM_State = SM_Unlocked;
			}
			else if(!A0 && !A1 && !A2){
				SM_State = SM_Code;
			}
			else{
				SM_State = SM_Locked;
			}
			break;

		case SM_Unlocked: 
                        if(A7){
                                SM_State = SM_Locked;
                        }
                        else{
                                SM_State = SM_Unlocked;
                        }
			break;

		case SM_Locked:
			if(A2){
				SM_State = SM_Release1;
			}	
			else{
				SM_State = SM_Locked;
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
			break;

		case SM_Locked:
			B = 0x00;
			break;

		case SM_Release1:
			break;

//		case SM_Release2:
//			break;

                case SM_Code:
                        break;

		case SM_Unlocked:
			B = (B & 0x00) | 0x01;;
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
    DDRB = 0xFF;	//Configure port C's 8 pins as output
    PORTB = 0x00;	//Initialize PORTC output to 0's

    unsigned char tempA0 = 0x00;	//Temporary variable to hold value of A
    unsigned char tempA1 = 0x00;
    unsigned char tempA2 = 0x00;
    unsigned char tempA7 = 0x00;
    unsigned char tempB = 0x00;

    /* Insert your solution below */
    while(1) {
	//1) Read Input
	if((PINA & 0xFF) == 0x01){
		tempA0 = PINA & 0x01;	
	}
	else if((PINA & 0xFF) == 0x02){
                tempA1 = PINA & 0x02;
        }
	else if((PINA & 0xFF) == 0x04){
                tempA2 = PINA & 0x04;
        }
	else{
                tempA0 = PINA & 0x01;
                tempA1 = PINA & 0x02;
                tempA2 = PINA & 0x04;
                tempA7 = PINA & 0x80;
        }

	//2) Perform Computation
	tempB = TickFunc(tempA0, tempA1, tempA2, tempA7, tempB);

	//3) Write Output
	PORTB = tempB;
    }
    return 0;
}
