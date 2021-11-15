#include "Driver_Timer.h"
#include "Driver_GPIO.h"

void (*IT_function_callback)(void);

void MyTimer_Base_Init(MyTimer_Struct_TypeDef *Timer)
{
	// Activation Clock du Timer
	switch((int)Timer->Timer)
	{
		case (int)TIM1:
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
			break;
		case (int)TIM2:
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
			break;
		case (int)TIM3:
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
			break;
		case (int)TIM4:
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
			break;
	}
	
	Timer->Timer->CR1 &= 0x0000; // reset timer
	Timer->Timer->PSC &= 0x0000; // reset prescaler
	Timer->Timer->ARR &= 0x0000; // reset autoreload
	
	Timer->Timer->PSC = (uint16_t)Timer->PSC;
	Timer->Timer->ARR = (uint16_t)Timer->ARR;
}

void MyTimer_PWM(TIM_TypeDef *Timer, char Channel)
{
	char GPIO_Pin;
	GPIO_TypeDef *GPIO;
	
	if(Channel >= 1 && Channel <= 4)
	{
		switch((int)Timer) {
			case (int)TIM1:
				Timer->BDTR |= TIM_BDTR_MOE; // spécifique à TIM1, activation PWM
				// choix des pins et GPIO en fonction du channel/timer
				GPIO = GPIOA;
				switch(Channel) {
					case 1: GPIO_Pin = 8; break;
					case 2: GPIO_Pin = 9; break;
					case 3: GPIO_Pin = 10; break;
					case 4: GPIO_Pin = 11; break;
				}
				break;
			case (int)TIM2:
				GPIO = GPIOA;
				switch(Channel) {
					case 1: GPIO_Pin = 0; break;
					case 2: GPIO_Pin = 1; break;
					case 3: GPIO_Pin = 2; break;
					case 4: GPIO_Pin = 3; break;
				}
				break;
			case (int)TIM3:
				switch(Channel) {
					case 1: GPIO_Pin = 6; GPIO = GPIOA; break;
					case 2: GPIO_Pin = 7; GPIO = GPIOA; break;
					case 3: GPIO_Pin = 0; GPIO = GPIOB; break;
					case 4: GPIO_Pin = 1; GPIO = GPIOB; break;
				}
				break;
			case (int)TIM4:
				GPIO = GPIOB;
				switch(Channel) {
					case 1: GPIO_Pin = 6; break;
					case 2: GPIO_Pin = 7; break;
					case 3: GPIO_Pin = 8; break;
					case 4: GPIO_Pin = 9; break;
				}
				break;
		}
		
		// Setup du GPIO associé à la channel du timer
		MyGPIO_Struct_TypeDef pwm = { GPIO, GPIO_Pin, (char)AltOut_Ppull };
		MyGPIO_Init(&pwm);
		
		// Activation des channels
		switch(Channel) {
			case 1:
				Timer->CCER |= TIM_CCER_CC1E; // activation de la channel
				Timer->CCMR1 &= ~TIM_CCMR1_CC1S; // reset (clear) 
				Timer->CCMR1 &= ~TIM_CCMR1_OC1M; // reset mode PWM
				Timer->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // mise en mode PWM 1 (110)
				break;
			case 2:
				Timer->CCER |= TIM_CCER_CC2E;
				Timer->CCMR1 &= ~TIM_CCMR1_CC2S;
				Timer->CCMR1 &= ~TIM_CCMR1_OC2M;
				Timer->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
				break;
			case 3:
				Timer->CCER |= TIM_CCER_CC3E;
				Timer->CCMR2 &= ~TIM_CCMR2_CC3S;
				Timer->CCMR2 &= ~TIM_CCMR2_OC3M;
				Timer->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
				break;
			case 4:
				Timer->CCER |= TIM_CCER_CC4E;
				Timer->CCMR2 &= ~TIM_CCMR2_CC4S;
				Timer->CCMR2 &= ~TIM_CCMR2_OC4M;
				Timer->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
				break;
		}
	}
}

void MyTimer_PWM_SetCycle(MyTimer_Struct_TypeDef *Timer, char Channel, float cycle)
{
	// Configuration du rapport cyclique
	switch(Channel) {
		case 1:
			Timer->Timer->CCR1 &= 0x0000;
			Timer->Timer->CCR1 = (uint32_t)(cycle * Timer->ARR); // calcul du CCR
			break;
		case 2:
			Timer->Timer->CCR2 &= 0x0000;
			Timer->Timer->CCR2 = (uint32_t)(cycle * Timer->ARR); // calcul du CCR
			break;
		case 3:
			Timer->Timer->CCR3 &= 0x0000;
			Timer->Timer->CCR3 = (uint32_t)(cycle * Timer->ARR); // calcul du CCR
			break;
		case 4:
			Timer->Timer->CCR4 &= 0x0000;
			Timer->Timer->CCR4 = (uint32_t)(cycle * Timer->ARR); // calcul du CCR
			break;
	}
}

void MyTimer_PWM_SetRawCycle(MyTimer_Struct_TypeDef *Timer, char Channel, uint32_t raw_cycle)
{
	// Configuration du rapport cyclique
	switch(Channel) {
		case 1:
			Timer->Timer->CCR1 &= 0x0000;
			Timer->Timer->CCR1 = raw_cycle; // calcul du CCR
			break;
		case 2:
			Timer->Timer->CCR2 &= 0x0000;
			Timer->Timer->CCR2 = raw_cycle; // calcul du CCR
			break;
		case 3:
			Timer->Timer->CCR3 &= 0x0000;
			Timer->Timer->CCR3 = raw_cycle; // calcul du CCR
			break;
		case 4:
			Timer->Timer->CCR4 &= 0x0000;
			Timer->Timer->CCR4 = raw_cycle; // calcul du CCR
			break;
	}
}

void MyTimer_ActiveIT(TIM_TypeDef *Timer, char Prio, void (*IT_function)(void))
{
	switch((int)Timer) {
		case (int)TIM1:
			NVIC_EnableIRQ(TIM1_UP_IRQn); // on active l'interruption (coté ARM)
			NVIC_SetPriority(TIM1_UP_IRQn, (uint32_t)Prio);
			break;
		case (int)TIM2:
			NVIC_EnableIRQ(TIM2_IRQn);
			NVIC_SetPriority(TIM2_IRQn, (uint32_t)Prio);
			break;
		case (int)TIM3:
			NVIC_EnableIRQ(TIM3_IRQn);
			NVIC_SetPriority(TIM3_IRQn, (uint32_t)Prio);
			break;
		case (int)TIM4:
			NVIC_EnableIRQ(TIM4_IRQn);
			NVIC_SetPriority(TIM4_IRQn, (uint32_t)Prio);
			break;
	}
	Timer->DIER |= TIM_DIER_UIE; // on active le lien interruption ARM / STM32
	IT_function_callback = IT_function; // on récup la fonction de callback
}

void TIM1_UP_IRQHandler(void)
{
		TIM1->SR &= ~TIM_SR_UIF; // on reset le callback
		if(IT_function_callback != 0)
			(*IT_function_callback)();
}

void TIM2_IRQHandler(void)
{
		TIM2->SR &= ~TIM_SR_UIF;
		if(IT_function_callback != 0)
			(*IT_function_callback)();
}

void TIM3_IRQHandler(void)
{
		TIM3->SR &= ~TIM_SR_UIF;
		if(IT_function_callback != 0)
			(*IT_function_callback)();
}

void TIM4_IRQHandler(void)
{
		TIM3->SR &= ~TIM_SR_UIF;
		if(IT_function_callback != 0)
			(*IT_function_callback)();
}

void MyTimer_Encoder_Init(MyTimer_Struct_TypeDef *Timer, void (*IT_function)(void))
{
	
	Timer->Timer->CCMR1 &= ~TIM_CCMR1_CC1S; // reset (clear) 
	Timer->Timer->CCMR1 |= TIM_CCMR1_CC1S_0; 
	Timer->Timer->CCMR1 &= ~TIM_CCMR1_CC2S;
	Timer->Timer->CCMR1 |= TIM_CCMR1_CC2S_0; 
	
	Timer->Timer->CCMR1 &= ~TIM_CCMR1_IC1F;
	Timer->Timer->CCMR1 &= ~TIM_CCMR1_IC2F;
	
	Timer->Timer->CCER &= ~TIM_CCER_CC1P ;
	Timer->Timer->CCER &= ~TIM_CCER_CC1NP ;
	Timer->Timer->CCER &= ~TIM_CCER_CC2P ;
	Timer->Timer->CCER &= ~TIM_CCER_CC2NP ;

	Timer->Timer->SMCR &= ~TIM_SMCR_SMS ;
	Timer->Timer->SMCR |= TIM_SMCR_SMS_0; //| TIM_SMCR_SMS_1 ;
	
	Timer->Timer->CR1 |= TIM_CR1_CEN ;
	
	//INTERRUPTION QUAND IDX (CH3 du TIM4) PASSE à 1
	RCC->APB2ENR |=	RCC_APB2ENR_AFIOEN; //Alternate function IO clock enable
	AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI8_PB; //Active AFIO du pin PB8 <=> idx
	
	EXTI->IMR |= EXTI_IMR_MR8; //Active Interruption du pin 8
	EXTI->RTSR |= EXTI_RTSR_TR8; //Interruption quand idxpasse de 0 à 1
	EXTI->FTSR &= ~EXTI_FTSR_TR8; //pas d'interruption quand idx passe de 1 à 0
	
	NVIC_EnableIRQ(EXTI9_5_IRQn); // on active l'interruption (coté ARM)
	NVIC_SetPriority(EXTI9_5_IRQn, 1);
	IT_function_callback = IT_function; // on récup la fonction d'interruption
}

void EXTI9_5_IRQHandler(void)
{
	EXTI->PR |= 1; //reset flag
	if(IT_function_callback != 0)
		(*IT_function_callback)();
}

void MyTimer_Reset_Counter(MyTimer_Struct_TypeDef *Timer)
{
	Timer->Timer->CNT &= ~TIM_CNT_CNT;
}


uint16_t MyTimer_Get_Counter(MyTimer_Struct_TypeDef *Timer)
{
	return Timer->Timer->CNT ;
}

