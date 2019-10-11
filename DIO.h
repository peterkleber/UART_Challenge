/*
 * DIO.h
 *
 *  Created on: Sep 22, 2019
 *      Author: Mohammed
 */

#ifndef DIO_H_
#define DIO_H_

#include <avr/io.h>
#include "std_types.h"

typedef enum {SW0,SW1}Pin_t;

void DIO_init(void);

uint8 DIO_read(Pin_t Pin) ;


#endif /* DIO_H_ */
