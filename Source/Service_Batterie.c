#include "Service_Batterie.h"
#include "Driver_ADC.h"

MyADC_Struct_TypeDef adc = { ADC1 };

void Batterie_Init()
{
	MyADC_Init(&adc, 1);
}

int Batterie_Get_Value()
{	
	int batterie = (int)MyADC_GetValue(&adc); // get the 12 bits value (from 0 to 4095)
	
	// convert in percent
	return (int)(batterie * 4095.0 / 100.0);
}