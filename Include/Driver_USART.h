#ifndef MYUART_H
#define MYUART_H

#include "stm32f10x.h"

typedef struct
{
	USART_TypeDef *USART;
	int baudRate;
} MyUSART_Struct_TypeDef;

/**
	* Initialisation de l'UART au Baud Rate voulu, exécuter en 1er !!!
	*/
void MyUART_Init(MyUSART_Struct_TypeDef *uart);

/**
	* Initialiser les transmissions
	*/
void MyUART_Transmission_Init(MyUSART_Struct_TypeDef *uart, void (*IT_function)(char));

/** 
	* Envoi d'un message
	*/
void MyUART_Send_Message(MyUSART_Struct_TypeDef *uart, char message[]);

#endif
