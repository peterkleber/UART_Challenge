/*
 * DIO.c
 *
 *  Created on: Sep 22, 2019
 *      Author: Mohammed
 */

#include "DIO.h"

void DIO_init() {
	DDRC = DDRC & (~(1 << PC4));
	PORTC |= (1 << PC4);

	DDRB = DDRB & (~(1 << PB2));
	PORTB |= (1 << PB2);

	DDRB = DDRB | (1 << PB4);
	PORTB = PORTB | (1 << PB4);
}

uint8 DIO_read(Pin_t Pin) {

	if (Pin == SW0) {
		return (!(PINC & (1 << PC4)));
	}
	else if (Pin == SW1) {
		return (!(PINB & (1 << PB2)));
	}
	else {
		return 0;
	}
}

