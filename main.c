/*
 * main.c
 *
 *  Created on: Oct 11, 2019
 *      Author: HOBA
 */

#include "std_types.h"
#include <util/delay.h>
#include "LCD.h"
#include "DIO.h"
#include "Switch.h"
#include "Timer.h"
#include "ExtInter.h"
#include "UART.h"



//----------------- Section of Constant Macros -------------------------//
#define  SWITCH_ON  1u
#define  SWITCH_OFF 0u
#define  RUNNING    55u
#define  READY		1u
#define  FINISHED	0u
#define SYSTEM_OFF  100u

#define SPEED_TAG	 1
#define DISTANCE_TAG 2
//----------------- Section of Public Global Variables -------------------------//
//static uint16 Counter_Sec=0;
//static uint16 Speed = 0;
static uint16 Current_Distance =0;
static uint16 Total_Distance = 0;
static uint16 Previous_Speed=0;
static uint16 Current_Speed=0;

//----------------- Section of  Global Flags -------------------------//
static uint8 Display_Flag =0;
static uint8 Switch_flag = SYSTEM_OFF;
static uint8 Busy_Flag = 0;
//static uint8 Speed_Change_Flag = 0;

//-------------------  Section of Public_Functions APIs Prototype-------------------------------//
void Second_Count (void);
void Switch_ON (void);
void Switch_OFF (void);
void Display (void);
void UART_Transmit_Data (void);
void UART_Recieve_Data (void);

//---------------------------------------------------------------------------------------------------------------------------------------//

//-------------------  Section of Public_Functions APIs Body Implementation -------------------------------//
void Second_Count (void)
{	
	if(Busy_Flag == 0)
	{
		Busy_Flag = 1;
		
		
		
		Busy_Flag = 0;		
	}
}

void Switch_ON (void)
{	
	if(Busy_Flag == 0)
	{	
		Busy_Flag = 1;				
		Switch_flag = SWITCH_ON;
		Busy_Flag = 0;	
		LCD_4Bits_Clear();
	}
	
	UART_send(READY);
				 
	Switch_flag = RUNNING ;
	
	//UART_Transmit_Data ();	 // Triggering the UART Transmit
}

void Switch_OFF (void)
{
	if(Busy_Flag == 0)
	{	
		Busy_Flag = 1;
		Switch_flag = SWITCH_OFF;
		Display_Flag = 1;
		
		LCD_4Bits_Clear();
		Busy_Flag = 0;
	}		
}

void Display (void)
{
	if(Display_Flag == 1)
	{	
		if(Switch_flag == RUNNING)
		{	
			
			if(Previous_Speed != Current_Speed) 
			{
				LCD_4Bits_Clear();
			}
			
			LCD_4Bits_Print_String(1,1,"Distance=");	// Total letters in Word Distance are 9 letters
			LCD_4Bits_Print_Number(1,10,Current_Distance); 
			Previous_Speed = Current_Speed;
		}
		
		else if(Switch_flag == SWITCH_OFF)
		{
			LCD_4Bits_Print_String(2,1,"Total=");		// Total letters in Word Distance are 6 letters
			LCD_4Bits_Print_Number(2,7,Total_Distance);  
		} 
		
		Display_Flag = 0;
	}

}

void UART_Recieve_Data (void)
{
	if(Busy_Flag == 0)
	{
	
		Busy_Flag = 1;
		uint8 Data_Recieved = 0;
		static uint8 Status_Recieved_TAG = 55;
			
		if(Switch_flag == RUNNING)
		{
			UART_recieve(&Data_Recieved);
			if(Data_Recieved == 'S')
			{
				Status_Recieved_TAG = SPEED_TAG;
			}
			
			else if (Data_Recieved == 'D')
			{
				Status_Recieved_TAG = DISTANCE_TAG;
			}
			else	//Here when the Data_Recieved is a actual Data
			{
				if(Status_Recieved_TAG == SPEED_TAG )
				{
					Current_Speed= Data_Recieved;
				}
				
				else if (Status_Recieved_TAG == DISTANCE_TAG)
				{
					Current_Distance = Data_Recieved;
				}
				
			}
			
			Total_Distance = Total_Distance + Current_Distance;

			Display_Flag = 1;
		}
		
		Busy_Flag=0;
	}
}

/*
void UART_Transmit_Data (void)
{
	if(Busy_Flag == 0)
	{
		PORTD ^= (1<<PD4);	//Test Pin
		Busy_Flag = 1;
		
		if(Switch_flag == SWITCH_ON)
		{
			 UART_send(READY);
		 
			 Switch_flag = RUNNING ;
		}
		
		Busy_Flag = 0;
	}
}
*/


//--------------------------------------------------------------------------------------------------------------------------//

int main() 
{
	uint8  Test_Return = AK;  

	TIMER_init();
	DIO_init();
	UART_init();
	Switch_Init();
	LCD_4Bits_Initialization();
	INTP_vidInit();
		
	Timer1_Set_Callback ( Second_Count );
	
	INTP1_vidSetCallBack(Switch_ON);
	INTP2_vidSetCallBack(Switch_OFF);
	
	UART_Set_Callback_RX(UART_Recieve_Data);
	//UART_Set_Callback_TX(UART_Transmit_Data);
	
	LCD_4Bits_Print_String(2,2,"SYSTEM OFF");	//idle State of the System 
	
	while(1)
	{
		 Display () ;
	}
	
	return 0;

}
