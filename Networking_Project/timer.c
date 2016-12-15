/*
 * timer.c
 *
 *  Created on: Dec 14, 2016
 *      Author: matsc
 */

#include "timer.h"

void timer(int Tb)
{
	whileEscape = 1;
	count = 0;

	interruptEnable();

	while(whileEscape == 1)		// Counter over 0.4ms checking
	{
		if(count < Tb)
		{
			count = count + 1;
			delay_us(1);		// checking in microSec intervals (hopefully)
		}
		else
		{
			interruptDisable();
//			RxLine = initRxLine;	//CHANGE WITH CODE IN "FSM.c"
			RxLine = PIND & (0x04);
			whileEscape = 0;
		}
	}
}
