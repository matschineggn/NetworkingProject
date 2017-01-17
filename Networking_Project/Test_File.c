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
void timerCounterSetup(void);
//void stateCheck(void);
void transmitter(void);
void Transmit(int);
void USART_Init(unsigned int);
unsigned char USART_Receive(void);


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
int interruptCount;
int n;
int N;
int x;	// used in for loops

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
	timerCounterSetup();

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
	DDRD = DDRD | (1<<3) | (1<<1);	// PD3(output), PD2(input) (INT0) , Tx(output), Rx(input)
	PORTD = PORTD | (1 << 3);	// PD3(high)  , PD2(low) (INT0)

	DDRB = DDRB | (0x07);	// PB2,PB1,PB0 (outputs)
	PORTB = PORTB & (0xF8);	// PB2-0 (all low)	USE FOR LEDs
}

void timerCounterSetup(void)
{
//	TCCR0A = (1<<WGM01);		//CTC Mode
	TCCR0B = (1<<CS01);			//Prescaler of 8
	OCR0A = 199;				//Value for 5kHz (199)

//	TIMSK0 = (1<<OCIE0A);		//Enable compare match interrupt for OCR0A
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
		N = 0;	// starts inputString[] at address '0'

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

	if(transmit == 1)
	{
		PORTD = PORTD & (0b11110111);		// Pulls Tx LOW before transmitting
	}

	while (transmit == 1)
	{
		if ((inputString[n] != '\0'))		// | (inputString[n] != '\r'))
		{
			charIN = inputString[n];

			Transmit(charIN);

			n = n+1;	// move to next character
		}
		else
		{
			//Finish transmitting
			transmit = 0;

			PORTD = PORTD | (1<<3);		//Pulls Tx HIGH after transmitting
		}
	}
}


// Transmit( ) converts character into 16-bit manchester character
void Transmit(int charIN)
{
	charCon = charIN;	// integer saved as float

	// Convert characters to 16-bit array of Manchester code.
	for (x = 0; x < 8; x++)
	{
		twoBits = 2*x;
		maxDecVal = (2 ^ (8 - x));
		if (charCon >= maxDecVal)
		{
			// "1" in manchester
			manchesterBits[twoBits] = 1;
			manchesterBits[(twoBits+1)] = 0;
		}
		else
		{
			// "0" in manchester
			manchesterBits[twoBits] = 0;
			manchesterBits[(twoBits+1)] = 1;
		}

		if(n == 8)
		{
			enableTx = true;		// Enable transmission
			interruptCount = 0;		// sets manchester[] array at 0 address
			TCNT0 = (0x00);			// Reset Count Value to '0'
		}
	}

	while(enableTx == true)
	{
		// Turn on interrupt for timer counter '0' on rising and falling edge to transfer.
		// Timer counter needs to be close to 5000 Hz
		TIMSK0 = (1<<OCIE0A);		//Enable compare match interrupt for OCR0A
		TCCR0A = (1<<WGM01);		//Timer 0 "turn ON"
	}

}

void USART_Init(unsigned int ubrr)
{
// Set Rx as input ( Set in pinSetup() )

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

ISR(TIMER0_COMPA_vect)
{
	//Set pin3 equal to manchester[ ] bit value
	if(manchesterBits[interruptCount] >= 1)
	{
		PORTD = PORTD | (1<<3);			//Transmit line pulled "HIGH"
	}
	else
	{
		PORTD = PORTD & (0b11110111);	//Transmit line pulled "LOW"
	}

	TCNT0 = (0x00);			// Reset Count Value to '0'

	interruptCount = interruptCount+1;	//increment to next bit in manchester[ ]

	if(interruptCount == 16)
	{
		enableTx = false;
		TIMSK0 = (0x00);		//Disable compare match interrupt for OCR0A
		TCCR0A = (0x00);		//Timer 0 "turn OFF"
	}
}



