///*
// * delay.c
// *
// *  Created on: Dec 19, 2016
// *      Author: matsc
// */
//
//#include "delay.h"
//
//void delay_ms(uint16_t ms)
//{
//	uint8_t delayms;
//	uint16_t numberOfLoops;
//
//	// Check boundary conditions and split the delay in
//	// multiple loops, if necessary
//	if(ms <= 12) {
//		numberOfLoops = 1;
//		delayms = ms;
//	} else {
//		numberOfLoops = (uint16_t) ms/12;
//		delayms = 12;
//		// If delay is not a multiple of 12ms, compensate for the remainder
//		if(ms%12 != 0) {
//			delay_ms(ms%12);
//		} // End if
//	} // End if
//
//	for(uint16_t i=0; i<numberOfLoops; i++) {
//
//		// Clear timer
//		TCNT0 = 0x00;
//
//		// Set OCR with delay value
//		OCR0A = (uint8_t) (delayms * CPU_FREQ_MHZ*1000/1024 - 1);
//
//		// Set Clock/1024 from prescaler (19.531 kHz) and start timer
//		TCCR0B |= (1<<CS02|1<<CS00);
//
//		// Delay
//		while((TIFR0 & (1<<OCF0A)) == 0);
//
//		// Stop timer
//		TCCR0B &= ~(1<<CS02|1<<CS01|1<<CS00);
//
//		// Clear compare flag
//		TIFR0 |= (1<<OCF0A);
//
//	} // End for loop
//}
//
//void delay_us(uint16_t us)
//{
//	uint8_t delayus;
//	uint16_t numberOfLoops;
//
//	// Check boundary conditions and split the delay in
//	// multiple loops, if necessary
//	if(us <= 12) {
//		numberOfLoops = 1;
//		delayus = us;
//	} else {
//		numberOfLoops = (uint16_t) us/12;
//		delayus = 12;
//		// If delay is not a multiple of 12us, compensate for the remainder
//		if(us%12 != 0) {
//			delay_us(us%12);
//		} // End if
//	} // End if
//
//	for(uint16_t i=0; i<numberOfLoops; i++) {
//
//		// Clear timer
//		TCNT0 = 0x00;
//
//		// Set OCR with delay value
//		OCR0A = (uint8_t) (delayus * CPU_FREQ_MHZ - 1);
//
//		// Set Clock without prescaler (20 MHz) and start timer
//		TCCR0B |= (1<<CS00);
//
//		// Delay
//		while((TIFR0 & (1<<OCF0A)) == 0);
//
//		// Stop timer
//		TCCR0B &= ~(1<<CS02|1<<CS01|1<<CS00);
//
//		// Clear compare flag
//		TIFR0 |= (1<<OCF0A);
//
//	} // End for loop
//}

#include "delay.h"

//#define CYCLES_PER_US 16				// cpu cycles per microsecond

// delay for ms milli-seconds
// delay times are only half-way accurate if optimization is turned on!
void delay_ms(uint16_t ms)
{
	volatile uint16_t i;

	for(i=ms;i>0;i--)
	{
		delay_us(1000);
	}
}

// delay for us micro-seconds
// delay times are only half-way accurate if optimization is turned on to level 3!
// max value for us is 65535/4*CYCLES_PER_US
// which is app. 17777 for 14.7456MHZ
void delay_us(uint16_t us)
{
	uint16_t _count;
//	_count=us/4*CYCLES_PER_US;
	_count = us/4;//*CYCLES_PER_US;

	asm volatile (
		"1: sbiw %0,1" "\n\t"
		"brne 1b" : "=w" (_count) : "0" (_count)
	);
}
