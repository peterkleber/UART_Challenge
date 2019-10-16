/*
 * main.c
 *
 *  Created on: Oct 11, 2019
 *      Author: PeterKleber
 */

#include <util/delay.h>
#include "UART.h"
#include "LCD.h"

int main() {

	//Initialize UART
	UART_init();

	LCD_init();
	LCD_clear();
	LCD_Write_Integer_Number(0);

	while (1) {

		static int x = 0;
		UART_send(x);
		LCD_clear();
		LCD_Write_Integer_Number(x);
		_delay_ms(1000);
		x++;

	}

}
