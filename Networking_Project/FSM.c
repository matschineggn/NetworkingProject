/*
 * FSM.c
 *
 *  Created on: Dec 14, 2016
 *      Author: matsc
 */

#include "FSM.h"

void FSM(int Tb)
{
	switch(currentState)
	{
		case IDLE:			// Idle State
			if(initRxLine == 4)		// Receiver input HIGH
			{
				nextState = IDLE;
				initRxLine = PIND & (0x04);
//				timer();
//				initRxLine = RxLine;
			}
			else					// Reciever input LOW
			{
				nextState = BUSY;
				timer(Tb);
			}
		break;

		case BUSY:			// Busy State
			if(count == Tb)
			{
//				if(initRxLine == RxLine)	//CHANGE WITH CODE IN "timer.c"
				if(RxLine == 0)		// timer expired while RxLine LOW
				{
					nextState = COLLISION;
				}
				else				// timer expired while RxLine HIGH
				{
					nextState = IDLE;
				}
				initRxLine = RxLine;
			}
			else
			{
				nextState = BUSY;
				timer(Tb);

			}
		break;

		case COLLISION:		// Collision State
			if(initRxLine == 0)		// Receiver input LOW
			{
				nextState = COLLISION;
				initRxLine = PIND & (0x04);
//				timer();
//				initRxLine = RxLine;
			}
			else					// Reciever input HIGH
			{
				nextState = BUSY;
				timer(Tb);
			}
		break;

		default:
			currentState = IDLE;
		break;
	}

	currentState = nextState;
}

