#ifndef MYUART_H
#define MYUART_H

#include "stm32f10x.h"

/**
	* Initialisation de l'UART au Baud Rate voulu, exécuter en 1e !!!
	*/
void MyUART_Init(USART_TypeDef * uart, int rate);

/**
	* Initialiser les transmissions
	*/
void MyUART_Transmission_Init(void (*IT_function)(char));

/** 
	* Envoi d'un message
	*/
void MyUART_Send_Message(char message[]);

#endif
