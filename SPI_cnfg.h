/*
 * SPI_cnfg.h
 *
 *  Created on: Oct 15, 2019
 *      Author: PeterKleber
 */

#ifndef SPI_CNFG_H_
#define SPI_CNFG_H_

typedef enum {Master,Slave}Mode_t;
typedef enum {Interrupt,No_Interrupt}Interrupt_t;
typedef enum {LSB,MSB}Data_Order_t;
typedef enum {Clock_Polarity_High,Clock_Polarity_Low}Clock_Polarity_t;
typedef enum {Clock_Phase_High,Clock_Phase_Low} Clock_Phase_t;
typedef enum {Fosc_4,Fosc_16,Fosc_64,Fosc_128,Fosc_2,Fosc_8,Fosc_32} Clock_Rate_t;

typedef struct {
	Mode_t mode ;
	Interrupt_t Interrupt_mode;
	Data_Order_t Data_Order;
	Clock_Polarity_t Clock_Polarity;
	Clock_Phase_t Clock_Phase ;
	Clock_Rate_t Clock_Rate ;

}SPI_Config_t;

extern SPI_Config_t SPI_Config;

#endif /* SPI_CNFG_H_ */
