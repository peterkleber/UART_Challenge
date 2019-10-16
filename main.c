/*
 * main.c
 *
 *  Created on: Oct 11, 2019
 *      Author: PeterKleber
 */

#include <util/delay.h>
#include "UART.h"
#include "LCD.h"

uint8 Rx_Data = 0;
uint8 Prev_Rx_Data = 0;

int main() {

	//Initialize UART
	UART_init();

	LCD_init();
	LCD_clear();

	while (1) {

		UART_recieve(&Rx_Data);
		if (Rx_Data != Prev_Rx_Data) {
			LCD_clear();
			LCD_Write_Integer_Number(Rx_Data);
			Prev_Rx_Data = Rx_Data;
		}
	}

}
