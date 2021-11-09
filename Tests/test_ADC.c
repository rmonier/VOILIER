#include "Driver_ADC.h"
	
void test_ADC()
{
	/* TESTS ADC *********************************/
	
	MyADC_Struct_TypeDef adc = { ADC1 };
	
	MyADC_Init(&adc, 1);
	
	uint16_t adc_val = MyADC_GetValue(&adc);
	
	/*********************************************/
}