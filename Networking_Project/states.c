/*
 * states.c
 *
 *  Created on: Dec 12, 2016
 *      Author: matschineggn
 */

#include "states.h"


void idle(void)
{
	PORTD |= (1<<2);	// PD2(high) while in idle
	PORTB = (PORTB & (0xF8)) | (1<<2);	// PB2(high) idle LED (blue)
}


void busy(void)
{
	PORTB = (PORTB & (0xF8)) | (1<<1);	// PB1(high) busy LED (green/yellow)
}


void collision(void)
{
	PORTB = (PORTB & (0xF8)) | (1<<0);	// PB0(high) collision LED (red)
}
