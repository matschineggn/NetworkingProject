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

void initSetup(void);

int currentState;

int main(void)
{
	initSetup();

	currentState = IDLE;

	switch(currentState)
		{
			case IDLE:			// Idle State
				idle();
			break;

			case BUSY:			// Busy State
				busy();
			break;

			case COLLISION:		// Collision State
				collision();
			break;

			default:
				currentState = IDLE;
			break;
		}

}

void initSetup(void)
{
	// pin INT1 (PD3) has pin change interrupt
	DDRD 	|= (1<<2);	// PD3(input), PD2(output)
	PORTD 	|= (1<<2);	// PD3(low)  , PD2(high)

	DDRB	|= (1<<2)|(1<<1)|(1<<0);	// PB2,PB1,PB0 (outputs)
	PORTD	&= (0b11111000);			// PB2-0 (all low)	USE FOR LEDs
}

