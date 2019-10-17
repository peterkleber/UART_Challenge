/*
 * KEYPAD_HEADER.h

 *  Author: HOBA
 */


#ifndef KEYPAD_HEADER

#define KEYPAD_HEADER

#ifndef F_CPU
#define F_CPU   8000000ul
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "Timer.h"

// Locate your keypad at which port does it exist
#define KEYPAD_PORT_OUT  PORTC
#define KEYPAD_PORT_DDR  DDRC
#define KEYPAD_PIN_IN   PINC

// Determine your Keypad Dimension
#define N_COL  3
#define N_ROW  3

// Determine your Digit Size for your input
#define DIGIT_SIZE 3

#define SIZE   6
#define YES	   1
#define NO     0

#define TIMEROUT_VALUE 18

// Determine whether you need to return Integer Numbers from keypad or Ascii Value (Characters) from KeyPad
#define PRINT_NUMBERS_From_KEYPAD YES


//----------------------- Section of Public Function Prototype of Keypad API's -----------------// 
short  KEYPAD_INPUT_Number(void); 
char *  KEYPAD_INPUT_String(void);
 


#endif /* KEYPAD_HEADER */
