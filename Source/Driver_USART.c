#include "Driver_USART.h"
#include "Driver_GPIO.h"

USART_TypeDef * UART;
void (*USART_function_callback)(char);


void MyUART_Init(USART_TypeDef * uart, int rate /*rien (UART fixé) ou UART au choix de l'user, Bd rate voulu en int*/)
{	
	UART = uart;
	MyGPIO_Struct_TypeDef TX, RX;
	//Activation et gonfiguration GPIO
	switch((int)UART)
	{
		case (int)USART1:
			TX.GPIO = GPIOA;
			TX.GPIO_Conf = AltOut_Ppull;
			TX.GPIO_Pin = 9;
			RX.GPIO = GPIOA;
			RX.GPIO_Conf = In_Floating;
			RX.GPIO_Pin = 10;
			NVIC_EnableIRQ(USART1_IRQn);
			NVIC_SetPriority(USART1_IRQn, 8);
			break;
		case (int)USART2:
			TX.GPIO = GPIOA;
			TX.GPIO_Conf = AltOut_Ppull;
			TX.GPIO_Pin = 2;
			RX.GPIO = GPIOA;
			RX.GPIO_Conf = In_Floating;
			RX.GPIO_Pin = 3;
			NVIC_EnableIRQ(USART2_IRQn);
			NVIC_SetPriority(USART2_IRQn, 8);
			break;
		case (int)USART3:
			TX.GPIO = GPIOB;
			TX.GPIO_Conf = AltOut_Ppull;
			TX.GPIO_Pin = 10;
			RX.GPIO = GPIOB;
			RX.GPIO_Conf = In_Floating;
			RX.GPIO_Pin = 11;
			NVIC_EnableIRQ(USART3_IRQn);
			NVIC_SetPriority(USART3_IRQn, 8);		
			break;
	}
	MyGPIO_Init(&TX); MyGPIO_Init(&RX);

	//Activation clock USART
	switch((int)UART)
	{
		case (int)USART1:
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
			break;
		case (int)USART2:
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
			break;
		case (int)USART3:
			RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
			break;
	}

	//Activation de l'UART
	UART->CR1 |= USART_CR1_UE;
	
	//Longueur mot (ici 8 bits)
	UART->CR1 &=~USART_CR1_M;
	
	//Nombre de stop bits à 1
	UART->CR2 &=~USART_CR2_STOP;
	
	//Baud Rate de 9600 Bd 
	//Clock en Hz/ Bd rate voulu
	switch((int)UART)
	{
		case (int)USART1:
			UART->BRR = SystemCoreClock/rate; //72MHz
			break;
		default:
			UART->BRR = (SystemCoreClock/2)/rate; //36MHz
			break;
	}
}

void MyUART_Transmission_Init(void (*IT_function)(char))
{
	USART_function_callback = IT_function;
	//Active l'uart pour émission/Réception
	UART->CR1 |= USART_CR1_RE;
	UART->CR1 |= USART_CR1_TE;

	//Active l'interrupt quand le buffer de réception se remplit
	
	UART->CR1 |= USART_CR1_RXNEIE;
}

static void SendChar(char character)
{
	while(!(UART->SR & USART_SR_TXE));
	UART->DR = character;
	}


void MyUART_Send_Message(char message[])
{
	int i=0;
	do
	{SendChar(message[i]); i++;	
	}while (message[i]!='\0');
}

void USART1_IRQHandler(void)
{		if (UART->SR & USART_SR_RXNE){
			UART->SR &= ~USART_SR_RXNE; // on reset le callback
		}
			
			(*USART_function_callback)(UART->DR);
}

void USART2_IRQHandler(void)
{		if (UART->SR & USART_SR_RXNE){
			UART->SR &= ~USART_SR_RXNE; // on reset le callback
		}
			(*USART_function_callback)(UART->DR);
}

void USART3_IRQHandler(void)
{		if (UART->SR & USART_SR_RXNE){
			UART->SR &= ~USART_SR_RXNE; // on reset le callback
		}
     //appeler une fonction qui utilise un char comme handler
			(*USART_function_callback)(UART->DR);
}
