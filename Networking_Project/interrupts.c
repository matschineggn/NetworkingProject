/*
 * interrupts.c
 *
 *  Created on: Dec 14, 2016
 *      Author: matsc
 */

#include "interrupts.h"

void interruptSetup(void)
{
	EICRA = EICRA | (1<<ISC00);		// any logic change on INT0 (PD2) generates an interrupt request
	sei();							// Enable Global Interrupt
		//	sei() - enables global interrupts
		//	cli() - disables global interrupts
}

void interruptEnable(void)
{
	EIMSK = EIMSK | (1<<INT0);		// will enable the interrupt
}

void interruptDisable(void)
{
	EIMSK = EIMSK & (0xFC);			// will disable the interrupt
}

ISR(INT0_vect)			// Interrupt for INT0 (PD2)
{
	RxLine = PIND & (0x04);		// giving RxIntTrig the value of the Rx line that triggered an interrupt
	whileEscape = 0;			// leaves while loop before 0.4ms expire
	interruptDisable();
}
