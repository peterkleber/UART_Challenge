/*
 * SPI.h
 *
 *  Created on: Oct 15, 2019
 *      Author: PeterKleber
 */

#ifndef SPI_H_
#define SPI_H_

#include"SPI_cnfg.h"
#include"std_types.h"
#include<avr/io.h>
#include <avr/interrupt.h>

Std_Func_t SPI_init();

Std_Func_t SPI_send(const uint8 Data_to_sent);

Std_Func_t SPI_recieve(uint8 *Data_recieved);

#endif /* SPI_H_ */
