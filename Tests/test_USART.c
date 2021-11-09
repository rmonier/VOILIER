#include "Driver_USART.h"

#if 0
void UART_callback(char character)
{	
	MyUART_Send_Message("INTERRUPT\n");
	//init servo
	//Utilisation servo
}


void test_USART()
{
	/* TESTS UART *********************************/
	MyUART_Init(USART1, 9600);
	MyUART_Transmission_Init(UART_callback);
	
	/*********************************************/
	
	do
	{
		/* TESTS UART *********************************/
		MyUART_Send_Message("[BUUUUUUG]\n");

	/*********************************************/
		
	}	while(1);
}
#endif