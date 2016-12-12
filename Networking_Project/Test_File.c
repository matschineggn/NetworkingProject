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

void setup(void);

typedef uint8_t STATE;
enum STATE {IDLE, BUSY, COLLISION};

int currentState;

int main(void)
{
	setup();

	currentState = IDLE;

	switch(currentState)
		{
			case IDLE:			// Idle State

			break;

			case BUSY:			// Busy State

			break;

			case COLLISION:		// Collision State

			break;

			default:
				currentState = IDLE;
			break;
		}

}

void setup(void)
{
	DDRD 	|= (1<<3);	// PD3(output), PD2(input)
	PORTD 	|= (1<<3);	// PD3(high), PD2(low)

	DDRB	|= (1<<2)|(1<<1)|(1<<0);	// PB2,PB1,PB0 (outputs)
	PORTD	&= (0b11111000);			//PB2-0 (all low)	USE FOR LEDs
}

