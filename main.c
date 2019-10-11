/*
 * main.c
 *
 *  Created on: Oct 11, 2019
 *      Author: PeterKleber
 */

//#include <util/delay.h>
#include "UART.h"
#include "LCD.h"

uint8 Rx_Data = 0 ;

int main(){
	//Initialize UART
	UART_init();

	LCD_init();
    LCD_clear();

	while(1){

		/*UART_send(0b01010101);
		_delay_ms(1000);*/

		UART_recieve(&Rx_Data);
		LCD_clear();
		LCD_displayChar(Rx_Data);

	}
}
