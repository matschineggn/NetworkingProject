/*
 * timer.h
 *
 *  Created on: Dec 14, 2016
 *      Author: matsc
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
//#include <MSOE_I2C/delay.h>
#include <MSOE/bit.c>
#include <avr/interrupt.h>

#include "states.h"
#include "interrupts.h"
#include "FSM.h"
#include "delay.h"

int count;
//int Tb;

/********************************************************************************
 * Function name: timer
 * Operation:
 * Inputs: None
 * Returns: None
 * Alters: None
 * Implemented: 12/14/16
 * Edited:
 *********************************************************************************/

void timer(int Tb);

#endif /* TIMER_H_ */
