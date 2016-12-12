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

int state;
int idle = 1;
int busy = 2;
int collision = 3;

int main(void)
{
	setup();

	switch(state)
		{
			case 1:		// Idle State

			break;

			case 2:		// Busy State

			break;

			case 3:		// Collision State

			break;
		}

}

void setup(void)
{
	DDRD 	|= (1<<3);	// PD3(output), PD2(input)
	PORTD 	|= (1<<3);	// PD3(high), PD2(low)
}
