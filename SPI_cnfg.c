/*
 * SPI_cnfg.c
 *
 *  Created on: Oct 15, 2019
 *      Author: PeterKleber
 */

#include "SPI_cnfg.h"

SPI_Config_t SPI_Config ={
		Master,
		No_Interrupt,
		MSB,
		Clock_Polarity_Low,
		Clock_Phase_High,
		Fosc_4,
};
