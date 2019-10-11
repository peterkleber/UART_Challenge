/*
 * UART_cnfg.h
 *
 *  Created on: Oct 11, 2019
 *      Author: PeterKleber
 */

#ifndef UART_CNFG_H_
#define UART_CNFG_H_

#include "std_types.h"

typedef enum {
	NO_Parity, Even, Odd
} Prity_t;

typedef struct {
	uint16 Baudrate;

	uint8 No_of_stop_bits;

	Prity_t Parity;
	uint8 No_of_parity_bits;

	uint8 No_of_data_bits;

} UART_cnfg_t;

extern UART_cnfg_t UART_cnfg_struct;

#endif /* UART_CNFG_H_ */
