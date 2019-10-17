/*
 * SPI.c
 *
 *  Created on: Oct 15, 2019
 *      Author: PeterKleber
 */

#include "SPI.h"

static void (*SPI_Callback)()= NULL_PTR;

Std_Func_t SPI_init() {

	//SPI Master/Slave mode select
	if (SPI_Config.mode == Master) {

		DDRB = DDRB | (1 << PB4);//SS Pin Direction PB4
		DDRB = DDRB | (1 << PB5);//MOSI Pin Direction PB5
		DDRB = DDRB & ~(1 << PB6);//MISO Pin Direction PB6
		DDRB = DDRB | (1 << PB7);//Sck Pin Direction PB7

		//MSTR bit selects Master SPI mode when written to one, and Slave SPI mode when written logic zero.
		SPCR |= (1 << MSTR);

	} else if (SPI_Config.mode == Slave) {
		// the Slave Select (SS) pin is always input PULLUP
		// MISO becomes an output

		DDRB |= (1 << PB6);    //MISO Pin Direction PB6
		DDRB &= ~(1 << PB5);	   //MOSI Pin Direction PB5
		DDRB &= ~(1 << PB7);    //Sck Pin Direction PB7
		DDRB &= ~(1 << PB4);    //SS Pin Direction PB4
		//	PORTB |= (1 << PB4);      //SS PULLUP
	}

	//Enable SPI
	SPCR |= (1 << SPE);

	//SPI Clock

	switch (SPI_Config.Clock_Rate) {
	case (Fosc_4):
		break;
	case (Fosc_16):
		SPCR |= (1 << SPR0);
		break;
	case (Fosc_64):
		SPCR |= (1 << SPR1);
		break;
	case (Fosc_128):
		SPCR |= (1 << SPR0);
		SPCR |= (1 << SPR1);
		break;
	case (Fosc_2):
		SPSR |= (1 << SPI2X);
		break;
	case (Fosc_8):
		SPSR |= (1 << SPI2X);
		SPCR |= (1 << SPR0);
		break;
	case (Fosc_32):
		SPSR |= (1 << SPI2X);
		SPCR |= (1 << SPR1);
		break;

	}

	//SPI Interrupt mode
	if (SPI_Config.Interrupt_mode == Interrupt) {
		SPCR |= (1 << SPIE);
		SREG |= (1 << 7); //SET IBIT
	}

	//SPI Data order

	if (SPI_Config.Data_Order == LSB) {
		//When the DORD bit is written to one, the LSB of the data word is transmitted first.
		//When the DORD bit is written to zero, the MSB of the data word is transmitted first
		SPCR |= (1 << DORD);
	}

	//SPI Clock Polarity

	if (SPI_Config.Clock_Polarity == Clock_Polarity_High) {
		// this bit is written to one, SCK is high when idle. When CPOL is written to zero, SCK is low when idle
		SPCR |= (1 << CPOL); //Sample on the Trailing edge
	}
//SPI Clock phase
	if (SPI_Config.Clock_Phase == Clock_Phase_Low) {
		// The settings of the Clock Phase bit (CPHA) determine if data is sampled on the leading (first) or
		//trailing (last) edge of SCK.
		SPCR |= (1 << CPHA);
	}

	return OK;

}

Std_Func_t SPI_send(const uint8 Data_to_sent) {

	SPDR = Data_to_sent;
	if (SPI_Config.Interrupt_mode == No_Interrupt) {
		while ((!(SPSR & (1 << SPIF)))) {
		}
	}
	//wait until SPI interrupt flag=1 (data is sent correctly)

	return OK;
}
Std_Func_t SPI_recieve(uint8 *Data_recieved) {
	if (SPI_Config.Interrupt_mode == No_Interrupt) {
		while ((!(SPSR & (1 << SPIF)))) {
		}
	}
	//wait until SPI interrupt flag=1(data is receive correctly)
	*Data_recieved = SPDR;

	return OK;
}

Std_Func_t SPI_Set_Callback(void (*ptr)()) {
	SPI_Callback = ptr ;
	return OK ;
}

ISR(SPI_STC_vect){
	if(SPI_Callback != NULL_PTR){
		SPI_Callback();
	}
}

