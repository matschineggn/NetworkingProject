/*
 * Test_File.c
 *
 *  Created on: Dec 11, 2016
 *      Author: matsc
 */

#include <avr/io.h>
//#include <MSOE_I2C/delay.h>
#include <MSOE/bit.c>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "states.h"
#include "interrupts.h"
#include "timer.h"
#include "FSM.h"

#define FOSC 1843200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void pinSetup(void);
//void stateCheck(void);
void transmitter(void);
void Transmit(int);
void USART_Init(unsigned int);
unsigned char USART_Receive(void);
void manchesterOne(void);
void manchesterZero(void);

bool stringComplete = false;  // whether the string is complete
bool enableTx = false;
// reserve 200 bytes for the inputString:
char inputString[80];
char inChar;
float charCon;
int charVect[8];
int manchesterBits[16];
//int msbArray[8];
//int lsbArray[8];
int character;
int charIN;
int intChar;
int transmit;
int maxDecVal;
int twoBits;
int n;
int N;

int Tb = 215; // period in micro second (400us = 0.4ms) (Using 215 to obtain proper threshold)
// I think that Tb needs to be around half the 400us because it is acting like the sample frequency
// which needs to be twice the fastest frequency, or half 400us.

//int currentState;			// declared in "FSM.h"
//int nextState;			// declared in "FSM.h"
//int initRxLine;				// declared in "FSM.h"
//int RxLine;				// declared in "interrupts.h"
//int whileEscape;			// declared in "interrupts.h"
//int count;				// declared in "timer.h"

int main(void)
{
	USART_Init(MYUBRR);

	pinSetup();
	interruptSetup();

	initRxLine = PIND & (0x04);

//	if (initRxLine == 4)
//	{
//		currentState = IDLE;
//	}
//	else
//	{
//		currentState = COLLISION;
//	}

	while (1)
	{

//		FSM(Tb);

		transmitter();

	}
}

void pinSetup(void)
{
	// pin INT0 (PD2) has pin change interrupt
	DDRD = (0x00) | (1 << 3);	// PD3(output), PD2(input) (INT0)
	PORTD = (0x00) | (1 << 3);	// PD3(high)  , PD2(low) (INT0)

	DDRB = DDRB | (0x07);	// PB2,PB1,PB0 (outputs)
	PORTB = PORTB & (0xF8);	// PB2-0 (all low)	USE FOR LEDs
}

void transmitter(void)
{
// 2500 bps = 0.4 ms = 400 us
// 5000 bps = 0.2 ms = 200 us

	stringComplete = false;

//	/* Wait for data to be received */
//	while ( !(UCSR0A & (1<<RXC0)) )	;

	if (UCSR0A && (1 << RXC0))	//if new data, get it
	{
//		N = 0;

		while (stringComplete == false)
		{
			//get the new byte:
			inChar = USART_Receive();
			//add it to the inputString:
			inputString[N] = inChar;

			N = N + 1;			// counts number of characters

			if (inChar == '\r')
			{
				stringComplete = true;
				transmit = 1;
				n = 0;
			}
		}
	}

	while (transmit == 1)
	{
//		for (n=0 ; n==N ; n+1)

		if (inputString[n] != '\0')
		{
			character = inputString[n];
			charIN = character;

			Transmit(charIN);

		}
		else
		{
			//Finish transmitting
			transmit = 0;
		}

	}

}


// Transmit( ) converts character into 16-bit manchester character
void Transmit(int charIN)
{
	charCon = charIN;	// integer saved as float

	// Convert characters to 16-bit array of Manchester code.
	for (n = 0; n < 8; n++)
	{
		twoBits = 2*n;
		maxDecVal = (2 ^ (8 - n));
		if (charCon >= maxDecVal)	// MSB
		{
			manchesterBits[twoBits] = 1;
			manchesterBits[(twoBits+1)]=0;
		}
		else
		{
			manchesterBits[twoBits] = 0;
			manchesterBits[(twoBits+1)]=1;
		}

		if(n == 8)
		{
			enableTx = true;
		}
	}

	while(enableTx == true)
	{
		// Turn on interrupt for timer counter on rising and falling edge to transfer.
		// Timer counter need to be close to 5000 Hz


	}

//	for (n = 0; n < 5; n++)
//	{
//		twoBits = (2*n)+5;			//
//		maxDecVal = (2 ^ (8 - n));
//		if (charCon >= maxDecVal)	// LSB
//		{
//			lsbArray[twoBits] = 1;
//			lsbArray[(twoBits+1)]=0;
//		}
//		else
//		{
//			lsbArray[twoBits] = 0;
//			lsbArray[(twoBits+1)];
//		}
//	}
}

void USART_Init(unsigned int ubrr)
{
// Set Rx as input

	/*Set baud rate */
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;
//Enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

unsigned char USART_Receive(void)
{
///* Wait for data to be received */
//while ( !(UCSR0A & (1<<RXC0)) )	;
	/* Get and return received data from buffer */
	return UDR0;
}

void manchesterOne(void)
{
	//Tx High

	delay_us(200);
	//Tx Low

	delay_us(200);
}

void manchesterZero(void)
{
	//Tx Low

	delay_us(200);
	//Tx High

	delay_us(200);
}

