/*
 * FSM.h
 *
 *  Created on: Dec 14, 2016
 *      Author: matsc
 */

#ifndef FSM_H_
#define FSM_H_

#include <avr/io.h>
//#include <MSOE_I2C/delay.h>
#include <MSOE/bit.c>
#include <avr/interrupt.h>

#include "states.h"
#include "interrupts.h"
#include "timer.h"
#include "delay.h"

int currentState;
int nextState;
int initRxLine;

//int Tb;

/********************************************************************************
 * Function name: FSM
 * Operation:
 * Inputs: None
 * Returns: None
 * Alters: None
 * Implemented: 12/14/16
 * Edited:
 *********************************************************************************/

void FSM(int Tb);

#endif /* FSM_H_ */
