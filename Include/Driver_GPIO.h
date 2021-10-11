#ifndef MYGPIO_H
#define MYGPIO_H

#include "stm32f10x.h"

typedef struct
{
	GPIO_TypeDef *GPIO;
	char GPIO_Pin;
	char GPIO_Conf;
} MyGPIO_Struct_TypeDef;

#define In_Floating 0b0100
#define In_PullDown 0b1000
#define In_Analog 0b1100
#define Out_Ppull 0b0001
#define Out_OD 0b0101
#define AltOut_Ppull 0b1001
#define AltOut_OD 0b1101

void MyGPIO_Init(MyGPIO_Struct_TypeDef *GPIOStructPtr);
int MyGPIO_Read(GPIO_TypeDef *GPIO, char GPIO_Pin);
void MyGPIO_Set(GPIO_TypeDef *GPIO, char GPIO_Pin);
void MyGPIO_Reset(GPIO_TypeDef *GPIO, char GPIO_Pin);
void MyGPIO_Toggle(GPIO_TypeDef *GPIO, char GPIO_Pin);

#endif
