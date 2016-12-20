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
			idle();
			switch(initRxLine)
			{
				case 4:
					nextState = IDLE;
					initRxLine = PIND & (0x04);
				break;

				case 0:
					nextState = BUSY;
					timer(Tb);
				break;
			}
		break;

		case BUSY:			// Busy State
			busy();
			switch(count)
			{
				case 215:
					switch(RxLine)
					{
						case 0:
							nextState = COLLISION;
						break;

						case 4:
							nextState = IDLE;
						break;
					}
				break;

				default:
					nextState = BUSY;
					timer(Tb);
				break;
			}
		break;

		case COLLISION:		// Collision State
			collision();
			switch(initRxLine)
			{
				case 0:
					nextState = COLLISION;
					initRxLine = PIND & (0x04);
				break;

				case 4:
					nextState = BUSY;
					timer(Tb);
				break;
			}
		break;

		default:
			currentState = IDLE;
		break;
	}

	currentState = nextState;
}
