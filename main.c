/*
 * main.c
 *
 *  Created on: Oct 11, 2019
 *      Author: HOBA
 */

#ifndef F_CPU
#define F_CPU   8000000ul
#endif

#include "std_types.h"
#include <util/delay.h>
#include "LCD.h"
#include "DIO.h"
#include "Switch.h"
#include "Timer.h"
#include "ExtInter.h"
#include "Keypad.h"
#include "UART.h"


//----------------- Section of Constant Macros -------------------------//
#define RECIEVED_FLAG 1
#define READY		  1

//----------------- Section of Public Global Variables -------------------------//
static uint16 Counter_Sec=0;
static uint16 Current_Time=0;
static uint8 Speed = 0;
static uint8 Distance = 0;



//----------------- Section of  Global Flags -------------------------//
static uint8 Speed_Change_Flag=0;
static uint8 Display_Flag =0;
//static uint8 Controlling_Flag =0;
static uint8 Busy_Flag = 0;
static uint8 UART_Recieve_Flag=0;


//-------------------  Section of Public_Functions APIs Prototype-------------------------------//
void Second_Count (void);
void Increment_Speed (void);
void Decrement_Speed (void);
void Display (void);
void Calculate_Distance (void);
void UART_Recieve_Data (void);
void UART_Transmit_Data (void);


//---------------------------------------------------------------------------------------------------------------------------------------//

//-------------------  Section of Public_Functions APIs Body Implementation -------------------------------//
void Second_Count (void)
{	
	if(Busy_Flag == 0)
	{
		Busy_Flag = 1;
		Counter_Sec++;
		Display_Flag=1;

		
		Calculate_Distance ();
				
		if(UART_Recieve_Flag == READY)  //initiate the transmission
		{	
				static uint16 Counter_index = 0;
				uint8 Buffer_Send[2]={0,0};	

				Buffer_Send[0]='S';
				Buffer_Send[1]=Speed;
				
				UART_send(Buffer_Send[Counter_index]);
				
				Counter_index++;

				if(Counter_index == 2)
				{
					Counter_index = 0;
				}

				
		}
		
		Busy_Flag = 0;
	
	}
	
}

void Increment_Speed (void)
{		
	if(Busy_Flag == 0)
	{	
		Busy_Flag = 1;
		Speed++;
		Display_Flag = 1;
		Busy_Flag = 0;
		
	}
}

void Decrement_Speed (void)
{
	if(Busy_Flag == 0)
	{
		Busy_Flag = 1;
		
		if ( (Speed == 10) || (Speed == 100) || (Speed == 1000) )
		{			
			LCD_4Bits_Clear();
			LCD_4Bits_Print_String(1,1,"Speed=");
			LCD_4Bits_Print_String(2,1,"Time=");
			LCD_4Bits_Print_String(1,10,"m/sec");
			LCD_4Bits_Print_String(2,12,"sec");
			LCD_4Bits_Print_Number(2,7,Counter_Sec);	
		}
		
		
		if(Speed > 1)
		{
			Speed--;
			Display_Flag = 1;
		}
		else
		{
			Speed = 0;
			Display_Flag = 1;
		}
		
		LCD_4Bits_Print_Number(1,8,Speed);			
		
		Busy_Flag = 0;
				
	}
		
}

void Display (void)
{
	if(Display_Flag == 1)
	{
		LCD_4Bits_Print_Number(1,8,Speed);
		LCD_4Bits_Print_Number(2,7,Counter_Sec);
		Display_Flag = 0;
	}

}

void Calculate_Distance (void)
{
		uint16 Delta_time = 0;
		Delta_time= Counter_Sec - Current_Time;
		Distance = Speed * (Delta_time);

}

void UART_Recieve_Data (void)
{	
	if(Busy_Flag == 0)
	{
		
		Busy_Flag = 1;
		
		uint8 Data_recieved=55;
	
		UART_recieve( & Data_recieved) ;
	
		UART_Recieve_Flag = Data_recieved ;	
		
		Busy_Flag = 0;
	}
}



//--------------------------------------------------------------------------------------------------------------------------//

int main() 
{
	uint8  Test_Return = AK;  
	
	TIMER_init();
	DIO_init();
	LCD_4Bits_Initialization();
	Switch_Init();
	UART_init();
	
	LCD_4Bits_Print_String(1,1,"Speed=");
	
	Timer1_COMP_Set_Callback ( Second_Count );
	
	INTP1_vidSetCallBack(Decrement_Speed);
	INTP2_vidSetCallBack(Increment_Speed);
	
	LCD_4Bits_Print_String(1,1,"Speed=");
	LCD_4Bits_Print_String(2,1,"Time=");
	
	
	 UART_Set_Callback_RX(UART_Recieve_Data);
	
	Speed=KEYPAD_INPUT_Number();
	
	LCD_4Bits_Clear();
	LCD_4Bits_Print_String(1,1,"Speed=");
	LCD_4Bits_Print_String(2,1,"Time=");
	LCD_4Bits_Print_String(1,10,"m/sec");
	LCD_4Bits_Print_String(2,12,"sec");
	LCD_4Bits_Print_Number(1,8,Speed);
	
	INTP_vidInit();

	Time_Delay(TIMER1,1,sec);

	while(1)
	{			
		  Display () ;

	}
	
	
	return 0;

}





//------------------------------------------------------------------------------------------------------------------------//
			/*
			if ( Switch_GetState(SWITCH_MINUS) )
			{
				Busy_Flag = 1;
				
				if ( (Speed == 10) || (Speed == 100) || (Speed == 1000) )
				{
					//LCD_4Bits_Clear();
					LCD_4Bits_Print_String(1,1,"Speed=");
					LCD_4Bits_Print_String(2,1,"Time=");
					LCD_4Bits_Print_String(1,12,"Dis=");
					LCD_4Bits_Print_Number(2,7,Counter_Sec);
					
				}
				
				Speed_Change_Flag=1;
				if(Speed > 1)
				{
					Speed--;
					Display_Flag = 1;
				}
				else
				{
					Speed = 0;
					Display_Flag = 1;
				}
				
				LCD_4Bits_Print_Number(1,8,Speed);
			}
				
			if ( Switch_GetState(SWITCH_PLUS) )
			{
				if(Busy_Flag == 0)
				{
					Busy_Flag = 1;
					Speed_Change_Flag=1;
					Speed++;
					Display_Flag = 1;
					Busy_Flag = 0;
					
				}
				
			}
			*/