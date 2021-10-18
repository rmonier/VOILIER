#ifndef MYUART_H
#define MYUART_H
#include "stm32f10x.h"


void MyUART_Init(/*rien (UART fixé) ou UART au choix de l'user*/);

void MyUART_Send_Message();//message (string ?), longueur message en int 

void MyUART_Receive_Message();

#endif
