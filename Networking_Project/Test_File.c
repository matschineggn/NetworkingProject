/*
 * Test_File.c
 *
 *  Created on: Dec 11, 2016
 *      Author: matsc
 */

#include <avr/io.h>
#include <MSOE_I2C/delay.h>
#include <MSOE_I2C/lcd.h>
#include <MSOE/bit.c>
#include <avr/interrupt.h>

void setup(void);

typedef uint8_t STATE;
enum STATE {RESET, IDLE, BUSY, COLLISION};

int state;
int idle = 1;
int busy = 2;
int collision = 3;

int main(void)
{
	setup();

	switch(state)
		{
			case IDLE:		// Idle State

			break;

			case BUSY:		// Busy State

			break;

			case COLLISION:		// Collision State

			break;
		}

}

void setup(void)
{
	DDRD 	|= (1<<3);	// PD3(output), PD2(input)
	PORTD 	|= (1<<3);	// PD3(high), PD2(low)
}
