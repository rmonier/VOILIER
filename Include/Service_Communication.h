#ifndef MYCOMMUNICATION_H
#define MYCOMMUNICATION_H

#include "Driver_USART.h"


void Communication_Update_Parameters(short data);

int Communication_Is_Horaire();

int Communication_Get_Speed_Ration();

void MyCommunication_Init(USART_TypeDef * uart, int rate);

#endif