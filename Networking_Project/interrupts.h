/*
 * interrupts.h
 *
 *  Created on: Dec 14, 2016
 *      Author: matsc
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <avr/io.h>
//#include <MSOE_I2C/delay.h>
#include <MSOE/bit.c>
#include <avr/interrupt.h>

#include "states.h"
#include "timer.h"
#include "FSM.h"
#include "delay.h"

int whileEscape;
int RxLine;

/********************************************************************************
 * Function name: interruptSetup
 * Operation:
 * Inputs: None
 * Returns: None
 * Alters: None
 * Implemented: 12/14/16
 * Edited:
 *********************************************************************************/

void interruptSetup(void);

/********************************************************************************
 * Function name: interruptEnable
 * Operation:
 * Inputs: None
 * Returns: None
 * Alters: None
 * Implemented: 12/14/16
 * Edited:
 *********************************************************************************/

void interruptEnable(void);

/********************************************************************************
 * Function name: interruptDisable
 * Operation:
 * Inputs: None
 * Returns: None
 * Alters: None
 * Implemented: 12/14/16
 * Edited:
 *********************************************************************************/

void interruptDisable(void);

#endif /* INTERRUPTS_H_ */
