#include "Driver_GPIO.h"

#define REGISTER_SIZE 32
#define BITS_IN_CR_PORT 4
#define PIN_CR(pin) ((pin*BITS_IN_CR_PORT)%REGISTER_SIZE)

/**
	Before calling the init, please fill the struct with the GPIO, the pin and the conf
*/
void MyGPIO_Init(MyGPIO_Struct_TypeDef *GPIOStructPtr)
{
	// Activation Clock du GPIO
	switch((int)GPIOStructPtr->GPIO)
	{
		case (int)GPIOA:
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // (0x01 << 2)
			break;
		case (int)GPIOB:
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // (0x01 << 3)
			break;
		case (int)GPIOC:
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // (0x01 << 4)
			break;
		case (int)GPIOD:
			RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; // (0x01 << 5)
			break;
	}
	
	if(GPIOStructPtr->GPIO_Pin >= 0 && GPIOStructPtr->GPIO_Pin < 8)
	{
		GPIOStructPtr->GPIO->CRL &= ~(0xF << PIN_CR(GPIOStructPtr->GPIO_Pin));
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << PIN_CR(GPIOStructPtr->GPIO_Pin));
	}
	else if(GPIOStructPtr->GPIO_Pin >= 8 && GPIOStructPtr->GPIO_Pin < 16)
	{
		GPIOStructPtr->GPIO->CRH &= ~(0xF << PIN_CR(GPIOStructPtr->GPIO_Pin));
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << PIN_CR(GPIOStructPtr->GPIO_Pin));
	}
}

int MyGPIO_Read(GPIO_TypeDef *GPIO, char GPIO_Pin)
{
	return (int)((GPIO->IDR & (0x1 << GPIO_Pin)) >> GPIO_Pin);
}

void MyGPIO_Set(GPIO_TypeDef *GPIO, char GPIO_Pin)
{
	GPIO->ODR |= (1 << GPIO_Pin);
}

void MyGPIO_Reset(GPIO_TypeDef *GPIO, char GPIO_Pin)
{
	GPIO->ODR &= (0 << GPIO_Pin);
}

void MyGPIO_Toggle(GPIO_TypeDef *GPIO, char GPIO_Pin)
{
	GPIO->ODR ^= (1 << GPIO_Pin); // XOR pour toggle
}
