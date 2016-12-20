/*
 * states.h
 *
 *  Created on: Dec 12, 2016
 *      Author: matschineggn
 */

#ifndef STATES_H_
#define STATES_H_

#include <avr/io.h>
//#include <MSOE_I2C/delay.h>
#include <MSOE/bit.c>
#include <avr/interrupt.h>

#include "interrupts.h"
#include "timer.h"
#include "FSM.h"
#include "delay.h"

/**
 * States of the state machine
 */
typedef uint8_t STATE;
enum STATE {IDLE, BUSY, COLLISION};

/********************************************************************************
 * Function name: idle
 * Operation:
 * Inputs: None
 * Returns: None
 * Alters: None
 * Implemented: 12/12/16
 * Edited:
 *********************************************************************************/
void idle(void);

void idleLED(void);

/********************************************************************************
 * Function name: busy
 * Operation:
 * Inputs: None
 * Returns: None
 * Alters: None
 * Implemented: 12/12/16
 * Edited:
 *********************************************************************************/
void busy(void);

void busyLED(void);

/********************************************************************************
 * Function name: collision
 * Operation:
 * Inputs: None
 * Returns: None
 * Alters: None
 * Implemented: 12/12/16
 * Edited:
 *********************************************************************************/
void collision(void);

void collisionLED(void);

#endif /* STATES_H_ */
