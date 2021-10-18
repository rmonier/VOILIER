#include "Driver_USART.h"
#include "stm32f10x.h"
				
void MyUART_Init(/*rien (UART fixé) ou UART au choix de l'user, Bd rate voulu en int*/)
{
	//Activation de l'UART
	USART3->CR1 |= USART_CR1_UE;
	
	//Longueur mot (ici 8 bits)
	USART3->CR1 &=~USART_CR1_M;
	
	//Nombre de stop bits
	USART3->CR2 &=~USART_CR2_STOP;
	
	//Baud Rate de 9600 Bd
	USART3->BRR = 3750;
	//Clock en Hz/ Bd rate voulu
}

void MyUART_Send_Message();//message (string ?), longueur message en int 

void MyUART_Receive_Message();
