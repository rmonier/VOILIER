#include "Service_Wheels.h"
#include "Driver_Timer.h"
#include "Driver_GPIO.h"

#define TIMER_WHEELS_PWM TIM2
#define CHANNEL_WHEELS_PWM 2

#define GPIO_WHEELS_PWM_DIR GPIOA
#define GPIO_WHEELS_PWM_DIR_PIN 11

MyTimer_Struct_TypeDef timer_wheels = {
	TIMER_WHEELS_PWM,
	225,
	16 //PSC_FOR_CLOCK((1.0/100000.0)*20000.0, timer_pwm.ARR) // 20kHz en ms donc au final PSC à 16 (ici mis en dur pck petit bug de calcul avec la macro)
};
MyTimer_Struct_TypeDef *pt_timer_wheels = &timer_wheels;
	
MyGPIO_Struct_TypeDef direction = {
	GPIO_WHEELS_PWM_DIR,
	GPIO_WHEELS_PWM_DIR_PIN,
	(char)Out_Ppull
};
	
void Wheels_Init()
{
	MyTimer_Base_Init(pt_timer_wheels);
	MyTimer_PWM(pt_timer_wheels->Timer, CHANNEL_WHEELS_PWM); // PA1
	MyGPIO_Init(&direction);	
}

void Wheels_Set_Parameters(float speed_ratio, int isHoraire)
{
	/* PWM DIRECTION */
	
	if(isHoraire) {
			MyGPIO_Set(direction.GPIO, direction.GPIO_Pin);
	} else {
			MyGPIO_Reset(direction.GPIO, direction.GPIO_Pin);
	}
	
	/* PWM TIMER */
	
	if(speed_ratio > 1) speed_ratio = 1;
	else if(speed_ratio < 0) speed_ratio = 0;
	
	MyTimer_PWM_SetCycle(pt_timer_wheels, CHANNEL_WHEELS_PWM, speed_ratio);
}

void Wheels_Start()
{
	MyTimer_Base_Start(pt_timer_wheels);
}

void Wheels_Stop()
{
	MyTimer_Base_Stop(pt_timer_wheels);
}

