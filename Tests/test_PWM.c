#include "Driver_Timer.h"

void test_PWM()
{
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
}