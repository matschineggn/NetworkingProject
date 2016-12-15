/*
 * Test_File.c
 *
 *  Created on: Dec 11, 2016
 *      Author: matsc
 */

#include <avr/io.h>
#include <MSOE_I2C/delay.h>
#include <MSOE/bit.c>
#include <avr/interrupt.h>

#include "states.h"
#include "interrupts.h"
#include "timer.h"
#include "FSM.h"

void pinSetup(void);
//void stateCheck(void);

int Tb = 215; 	// period in micro second (400us = 0.4ms) (Using 215 to obtain proper threshold)
// I think that Tb needs to be around half the 400us because it is acting like the sample frequency
// which needs to be twice the fastest frequency, or half 400us.

//int currentState;			// declared in "FSM.h"
//int nextState;			// declared in "FSM.h"
//int initRxLine;				// declared in "FSM.h"
//int RxLine;				// declared in "interrupts.h"
//int whileEscape;			// declared in "interrupts.h"
//int count;				// declared in "timer.h"

int main(void)
{
	pinSetup();
	interruptSetup();

	initRxLine = PIND & (0x04);

	if(initRxLine == 4)
	{
		currentState = IDLE;
	}
	else
	{
		currentState = COLLISION;
	}

	while(1)
	{
		switch(currentState)
		{
			case IDLE:			// Idle State
				idle();
				FSM(Tb);
			break;

			case BUSY:			// Busy State
				busy();
				FSM(Tb);
			break;

			case COLLISION:		// Collision State
				collision();
				FSM(Tb);
			break;

			default:
				currentState = IDLE;
			break;
		}
	}
}

void pinSetup(void)
{
	// pin INT0 (PD2) has pin change interrupt
	DDRD 	= (0x00)|(1<<3);	// PD3(output), PD2(input) (INT0)
	PORTD 	= (0x00)|(1<<3);	// PD3(high)  , PD2(low) (INT0)

	DDRB	= DDRB  | (0x07);	// PB2,PB1,PB0 (outputs)
	PORTB	= PORTB & (0xF8);	// PB2-0 (all low)	USE FOR LEDs
}












