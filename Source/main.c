#include <math.h>

#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"
#include "Service_Servo.h"
#include "Service_IMU.h"

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
	MyTimer_Base_Start(pt_timer);

	MyTimer_ActiveIT(timer.Timer, 8, callbackTimer);
	
	/*********************************************/
	
	/* TESTS PWM *******************************/
	
	MyTimer_Struct_TypeDef timer_pwm = {
		TIM3,
		9,
		71 //PSC_FOR_CLOCK((1.0/100000.0)*1000.0, timer_pwm.ARR) // 100kHz en ms donc au final PSC à 71 (ici mis en dur pck petit bug de calcul avec la macro)
	};
	MyTimer_Struct_TypeDef *pt_timer_pwm = &timer_pwm;
	
	MyTimer_Base_Init(pt_timer_pwm);

	MyTimer_PWM(timer_pwm.Timer, 2);
	
	MyTimer_PWM_SetCycle(pt_timer_pwm, 2, 0.2); // 20% sur channel 2
	
	MyTimer_Base_Start(pt_timer_pwm);
	
	/*********************************************/
	
	/* TESTS ADC *********************************/
	
	MyADC_Struct_TypeDef adc = { ADC1 };
	
	MyADC_Init(&adc, 1);
	
	uint16_t adc_val = MyADC_GetValue(&adc);
	
	/*********************************************/
	
	/* TESTS SERVO *********************************/
		
	MyServo_Init();
	float angle_voile = 0;
	
		
	/* TESTS SERVICE IMU *********************************/
	
	
	
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
		
		/* TESTS SERVO *********************************/
	
		MyServo_Set(angle_voile);
		angle_voile = fmod(angle_voile + 4.5,90); //Test les 20 positions sans débordement
		int i = 0;
		while (i < 7200000) {i++;} //Sleep pour étudier le moteur en temps réel
    
		/*********************************************/
		
	}	while(1);
	
	//return 0;
}
