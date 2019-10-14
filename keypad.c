/*
 * FUCNTIONS_KEYPAD.c
 *  Author: HOBA
 */


#include "Keypad.h"

void KEYPAD_Initialization(void);
unsigned char KEYPAD_Press(void);
unsigned char KEYPAD_Button(unsigned );


void KEYPAD_Initialization(void)
{

		if((N_ROW == 3) && (N_COL == 3) )
		{
			KEYPAD_PORT_DDR |= 0x1C;	//0b00011100  // high significant nibble is input which is indicating to columns and Least significant nibble is output which is indicating to Rows
			KEYPAD_PORT_DDR &= 0x1F;	//0b00011111

			KEYPAD_PORT_OUT |= 0xFC;	//0b11111100  // Write ones to the all pins in the port to activate pull-up resistors in the input nibble
		}

		else if((N_ROW == 4) && (N_COL == 4) )
		{
				KEYPAD_PORT_DDR = 0x0F ;              // high significant nibble is input which is indicating to columns and Least significant nibble is output which is indicating to Rows
				KEYPAD_PORT_OUT= 0xFF;	              // Write ones to the all pins in the port to activate pull-up resistors in the input nibble
		}
}


unsigned char KEYPAD_Press(void)
{
     KEYPAD_Initialization();

	unsigned char row,col, key;

	if((N_ROW == 3) && (N_COL == 3) )
	{
		while(1)
		{
			for(row=0;row<N_ROW;row++)  // rows for the output pins ( LSB of the port)
			{
				KEYPAD_PORT_OUT = (~(0b00000100<<row));			//clear this row pin and set all pins


				for(col=0;col<N_COL;col++) // this loop reads the status of each column in that row.
				{

					if( ! ( KEYPAD_PIN_IN & (0b00100000<<col) ) )		//Column Detected means that there is a single 0 in that row.
					{
						key = KEYPAD_Button ((row*N_COL)+col+1) ;
						return  (key);

					}
				}
			}

		}
	}

	else if((N_ROW == 4) && (N_COL == 4) )
	{
		while(1)
		{

			for(row=0;row<N_ROW;row++)  // rows for the output pins ( LSB of the port)
			{
				KEYPAD_PORT_OUT = (~(0b00000001<<row));			//clear this row pin and set all pins


				for(col=0;col<N_COL;col++) // this loop reads the status of each column in that row.
				{

					if( ! ( KEYPAD_PIN_IN & (0b00010000<<col) ) )		//Column Detected means that there is a single 0 in that row.
					{
						key = KEYPAD_Button ((row*N_COL)+col+1) ;
						return  (key);

					}
				}
			}


		}
	}

}


unsigned char KEYPAD_Button (unsigned button_number)
{
	#if(PRINT_NUMBERS_From_KEYPAD)
	{
		switch(button_number)
		{
			case 1: return 1 ; break;		 // position of (1) is located at top left of the keypad which is corresponding to button no. 7
			case 2: return 2 ; break;
			case 3: return 3 ; break;
			case 4: return 4 ; break;
			case 5: return 5 ; break;
			case 6: return 6 ; break;
			case 7: return 7 ; break;
			case 8: return 8 ; break;
			case 9: return 9 ; break;
			case 10: return -1 ; break;
			case 11: return -1 ; break;
			case 12: return -1 ; break;
			case 13: return -1 ; break;
			case 14: return 0 ; break;
			case 15: return -1; break;
			case 16: return -1 ; break;
			default: return button_number;
		}
	}

	// or to print the numbers in terms of ascii value

	#elif(! PRINT_NUMBERS_From_KEYPAD )
	{

		switch(button_number)
		{
			case 1: return '1' ; break;			 // position of (1) is located at top left of the keypad which is corresponding to button no. 7
			case 2: return '2' ; break;
			case 3: return '3' ; break;
			case 4: return '4' ; break;
			case 5: return '5' ; break;
			case 6: return '6' ; break;
			case 7: return '7' ; break;
			case 8: return '8' ; break;
			case 9: return  '9' ; break;
			case 10: return 'A' ; break;
			case 11: return 'B' ; break;
			case 12: return 'C' ; break;
			case 13: return 'D' ; break;
			case 14: return '0' ; break;
			case 15: return 'E'; break;
			case 16: return 'F' ; break;
			default: return button_number;
		}
	}

	#endif
}

//it's used for Keypad 4x4 like Calculator
/*
unsigned char KEYPAD_Button (unsigned button_number)
{
	#if(PRINT_NUMBERS_From_KEYPAD)
	{
		switch(button_number)
		{
			case 1: return 7 ; break;		 // position of (1) is located at top left of the keypad which is corresponding to button no. 7
			case 2: return 8 ; break;
			case 3: return 9 ; break;
			case 4: return 10 ; break;
			case 5: return 4 ; break;
			case 6: return 5 ; break;
			case 7: return 6 ; break;
			case 8: return 11 ; break;
			case 9: return 1 ; break;
			case 10: return 2 ; break;
			case 11: return 3 ; break;
			case 12: return 12 ; break;
			case 13: return 13 ; break;
			case 14: return 0 ; break;
			case 15: return 14; break;
			case 16: return 15 ; break;
			default: return button_number;
		}
	}

	// or to print the numbers in terms of ascii value

	#elif(! PRINT_NUMBERS_From_KEYPAD )
	{

		switch(button_number)
		{
			case 1: return '7' ; break;			 // position of (1) is located at top left of the keypad which is corresponding to button no. 7
			case 2: return '8' ; break;
			case 3: return '9' ; break;
			case 4: return 'A' ; break;
			case 5: return '4' ; break;
			case 6: return '5' ; break;
			case 7: return '6' ; break;
			case 8: return 'B' ; break;
			case 9: return '1' ; break;
			case 10: return '2' ; break;
			case 11: return '3' ; break;
			case 12: return 'C' ; break;
			case 13: return 'D' ; break;
			case 14: return '0' ; break;
			case 15: return 'E'; break;
			case 16: return 'F' ; break;
			default: return button_number;
		}
	}

	#endif
}
*/


 char *  KEYPAD_INPUT_String(void)
{
	char static String[SIZE+1];
	unsigned char i=0 ;

	for ( i = 0; i<DIGIT_SIZE ; i++)
	{
		do
		{
			String[i]= KEYPAD_Press();
		}while ( String[i] == '+' || String[i] == '-' || String[i] == '*' || String[i] == '/' || String[i] == '=' ) ;

		_delay_ms(500);
	}
	String [i] = '\0' ;

	return String ;
}


short  KEYPAD_INPUT_Number(void)
{
	short Number=0 ;
	 char Digit = 0;
	unsigned char i=0 ;

	for ( i = 0; i < DIGIT_SIZE ; i++)
	{
			do
			{
			Digit = KEYPAD_Press();
			}while (  (KEYPAD_Press() > 9) ||  (KEYPAD_Press() < 0)  ) ;

			 LCD_CHAR_DISP( 1, 9+i ,Digit+'0');
			Number = Number+Digit;

			if(i != DIGIT_SIZE-1)
			{
				Number = Number*10;
			}
			_delay_ms(500);
	}
	return Number ;
}


