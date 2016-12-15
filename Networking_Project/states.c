/*
 * states.c
 *
 *  Created on: Dec 12, 2016
 *      Author: matschineggn
 */

#include "states.h"

// States

void idle(void)
{
	PORTD |= (1<<2);	// PD2(high) while in idle
	idleLED();
}

void busy(void)
{

	busyLED();
}

void collision(void)
{

	collisionLED();
}

// LED controls

void idleLED(void)
{
	PORTB = (PORTB & (0xF8)) | (1<<2);	// PB2(high) idle LED (green)
}

void busyLED(void)
{
	PORTB = (PORTB & (0xF8)) | (1<<1);	// PB1(high) busy LED (yellow)
}

void collisionLED(void)
{
	PORTB = (PORTB & (0xF8)) | (1<<0);	// PB0(high) collision LED (red)
}
