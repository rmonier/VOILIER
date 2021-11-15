#include "Service_Communication.h"

static int horaire = 1;
static float speed_ratio = 0.0;

MyUSART_Struct_TypeDef uart = {
	USART1,
	9600
};

void (*callback_com)();

void UART_callback(char character)
{	
	//MyUART_Send_Message("INTERRUPT\n");
	short data = (short)character;
	if (data != 95)	{ // ignore the underscores triggered everytime
		Communication_Update_Parameters(data);
		callback_com();
	}
}

void Communication_Update_Parameters(short data)
{
	if(data > 128) {
		speed_ratio = ((256 - data) * 100.0 / 128.0) / 100.0;
		horaire = 0;
	} else {
		speed_ratio	= (data * 100.0 / 128.0) / 100.0;
		horaire = 1;
	}
}

int Communication_Is_Horaire()
{
	return horaire;
}

float Communication_Get_Speed_Ratio()
{
	return speed_ratio;
}

/**
	* Set a callback to handle each reception of data
	*/
void MyCommunication_Init(void (*callback)())
{
	callback_com = callback;
	MyUART_Init(&uart);
	MyUART_Transmission_Init(&uart, UART_callback);
}

void Communication_Display_Message(char *message)
{
	MyUART_Send_Message(&uart, message);
}
