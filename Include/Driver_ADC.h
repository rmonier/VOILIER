#ifndef MYADC_H
#define MYADC_H

#include "stm32f10x.h"

typedef struct
{
	ADC_TypeDef *ADC; // ADC1 only
	
} MyADC_Struct_TypeDef;

void MyADC_Init(MyADC_Struct_TypeDef *ADC, int channel);

/**
	* Est utilisée pendant Init
	*/
void MyADC_Calibrate(MyADC_Struct_TypeDef *ADC);

uint16_t MyADC_GetValue(MyADC_Struct_TypeDef *ADC);

#endif
