#include "Service_Communication.h"

int horaire = 1;
int speed_ratio = 0;

void UART_callback(char character)
{	
	MyUART_Send_Message("INTERRUPT\n");
	short data = (short)character;
	Communication_Update_Parameters(data); // 0 => entre 0 et 256 via get_data
}

void Communication_Update_Parameters(short data)
{
	int speed = data - 128;
	
	if(speed < 0) {
		speed_ratio = -(data * 100 / 256);
		horaire = 0;
	} else {
		speed_ratio	= (data * 100 / 256);
		horaire = 1;
	}
}

int Communication_Is_Horaire()
{
	return horaire;
}

int Communication_Get_Speed_Ration()
{
	return speed_ratio;
}

void MyCommunication_Init(USART_TypeDef * uart, int rate)
{
	MyUART_Init(uart, rate);
	MyUART_Transmission_Init(UART_callback);
}
