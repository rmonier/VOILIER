#ifndef MYCOMMUNICATION_H
#define MYCOMMUNICATION_H

#include "Driver_USART.h"

void Communication_Update_Parameters(short data);
int Communication_Is_Horaire();
float Communication_Get_Speed_Ratio();
void MyCommunication_Init(void (*callback)());
void Communication_Display_Message(char *message);

#endif