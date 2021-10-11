#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"

void callbackTimer(void)
{
	int test = 0;
	test += 2;
}

int main()
{
	/* TESTS GPIO ********************************/
	
	MyGPIO_Struct_TypeDef led = {
		GPIOA,
		10,
		(char)Out_OD
	};
	
	MyGPIO_Struct_TypeDef button = {
		GPIOA,
		8,
		(char)In_Floating
	};
	
	MyGPIO_Init(&led);
	MyGPIO_Init(&button);
	
	/*********************************************/
	
	/* TESTS TIMER *******************************/
	
	MyTimer_Struct_TypeDef timer = {
		TIM2,
		35999,
		PSC_FOR_CLOCK(2000, timer.ARR)
	};
	MyTimer_Struct_TypeDef *pt_timer = &timer;
	
	MyTimer_Base_Init(pt_timer);
	MvTimer_Base_Start(pt_timer);

	MyTimer_ActiveIT(timer.Timer, 8, callbackTimer);
	
	/*********************************************/
	
	/* TESTS PWM *******************************/
	
	MyTimer_Struct_TypeDef timer_pwm = {
		TIM3,
		35999,
		999 //PSC_FOR_CLOCK((1.0/100000.0)*1000.0, timer_pwm.ARR) // 100kHz en ms donc au final PSC à 999 (ici mis en dur pck petit bug de calcul avec la macro)
	};
	MyTimer_Struct_TypeDef *pt_timer_pwm = &timer_pwm;
	
	MyTimer_Base_Init(pt_timer_pwm);

	MyTimer_PWM(timer_pwm.Timer, 2);
	
	MyTimer_PWM_SetCycle(pt_timer_pwm, 2, 0.2); // 20% sur channel 2
	
	MvTimer_Base_Start(pt_timer_pwm);
	
	/*********************************************/
	
	/* TESTS ADC *********************************/
	
	
	
	/*********************************************/
	
	do
	{
		/* TESTS GPIO ********************************/
		
		// si bouton pc8 appuyé
		if(MyGPIO_Read(button.GPIO, button.GPIO_Pin)) {
			// on allume la LED pc10
			MyGPIO_Set(led.GPIO, led.GPIO_Pin);
		} else {
			// on éteint la LED pc10
			MyGPIO_Reset(led.GPIO, led.GPIO_Pin);
		}
		
		/*********************************************/
		
		/* TESTS TIMER *******************************/
		
		// si bouton pc8 appuyé
		if(MyGPIO_Read(button.GPIO, button.GPIO_Pin)) {
			// on arrete le timer
			MyTimer_Base_Stop(pt_timer);
		}

		/*********************************************/
	}	while(1);
	
	//return 0;
}
