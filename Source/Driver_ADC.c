#include "Driver_ADC.h"

void MyADC_Init(MyADC_Struct_TypeDef *ADC, int channel)
{
	// Activation Clock de l'ADC
	switch((int)ADC->ADC)
	{
		case (int)ADC1: // on restera ici sur le 1
			RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
			break;
		case (int)ADC2:
			//RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
			break;
	}
	
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; // Réduction fréquence car ADC ne fonctionne pas à 72MHz (donc on divise par 6 pour être large)
	
	// Activation ADC
	ADC->ADC->CR2 |= ADC_CR2_ADON;
	
	if(channel >= 0 && channel <= 15)
	{
		ADC->ADC->SQR1 &= 0x00000000; // Reset de SQR1
		ADC->ADC->SQR1 &= ~ADC_SQR1_L; // config du nombre de conversions avec L, 0000 => 1 conversion
		ADC->ADC->SQR3 |= channel; // on met la channel
		
		MyADC_Calibrate(ADC);
	}
}

void MyADC_Calibrate(MyADC_Struct_TypeDef *ADC)
{
	// Calibration
	ADC->ADC->CR2 |= ADC_CR2_CAL;
	while (ADC->ADC->CR2 & ADC_CR2_CAL);
}

uint16_t MyADC_GetValue(MyADC_Struct_TypeDef *ADC)
{
	// Lancement conversion
  ADC->ADC->CR2 |= ADC_CR2_ADON;
    
	// On attend SR->EOC à 1 => mesure terminée
  while(!(ADC->ADC->SR & ADC_SR_EOC));
    
	// Remise à zéro de EOC
  ADC->ADC->SR &= ~ADC_SR_EOC;
      
	// Lecture en masquant les 4 bits de poid fort 
  return ADC->ADC->DR & ~(0xF << 12);
}