/*
 * main.c
 *
 *  Created on: Oct 11, 2019
 *      Author: PeterKleber
 */

#include <util/delay.h>
#include "UART.h"
#include "LCD.h"
#include "DIO.h"

uint8 Counter = 0;

uint8 SW0_Status = 0;
uint8 SW1_Status = 0;

int main() {

	//Initialize UART
	UART_init();

	DIO_init();

    LCD_init();
	LCD_clear();

	while (1) {
		// check if the push button is pressed or not
		//if (!(PINC & (1 << PC4))) {
		if (DIO_read(SW0)) {

			_delay_ms(30);
			//second check due to switch de-bouncing
		//	if (!(PINC & (1 << PC4))) {
			if (DIO_read(SW0)) {
				if (SW0_Status == 0) {

					Counter++;

					LCD_clear();
					LCD_Write_Integer_Number(Counter);
					UART_send(Counter + '0');

					SW0_Status = 1;
				}
			}
		} else
			SW0_Status = 0;

		//if (!(PINB & (1 << PB2))) {
			if (DIO_read(SW1)) {
			_delay_ms(30);
			//second check due to switch de-bouncing
			//if (!(PINB & (1 << PB2))) {
			if (DIO_read(SW1)) {
				if (SW1_Status == 0) {

					Counter--;

					LCD_clear();
					LCD_Write_Integer_Number(Counter);
					UART_send(Counter + '0');

					SW1_Status = 1;
				}
			}
		} else
			SW1_Status = 0;
	}

}
