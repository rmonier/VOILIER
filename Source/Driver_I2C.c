#include "Driver_I2C.h"

void MyI2C_Init(MyI2C_Struct_TypeDef *I2C)
{
	// Activation clock I2C
	switch((int)I2C->I2C)
	{
		case (int)I2C1:
			// Clock
			RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
			break;
		case (int)I2C2: // NE PAS UTILISER CAR CONFLIT AVEC USART !!!
			//RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
			break;
	}
	
	// Active I2C
	I2C->I2C->CR1 |= I2C_CR1_PE;
	I2C->I2C->CR2 |= I2C_CR2_FREQ_1;
	// TODO:
	//I2C->I2C->CCR |= clock;
	//I2C->I2C->OAR1 |= addr;
}