#include "Driver_GPIO.h"
#include "Driver_Timer.h"

//Variables globales du Timer associé à la PWM du Servo_Moteur
MyTimer_Struct_TypeDef tim_girouette = {
		TIM4,
		3599,
		399 //PSC_FOR_CLOCK((0.02), tim_servo.ARR) ;
};
MyTimer_Struct_TypeDef *pt_tim_girouette = &tim_girouette;

MyGPIO_Struct_TypeDef phA = { //PB6 <=> Ch1 TIM4
		GPIOB,
		6,
		(char)In_Floating
	};
	
MyGPIO_Struct_TypeDef phB = { //PB7 <=> Ch2 TIM4
		GPIOB,
		7,
		(char)In_Floating
};

MyGPIO_Struct_TypeDef idx = { //PB8 <=> Ch3 TIM4
		GPIOB,
		8,
		(char)In_Floating
};

void MyGirouette_Init(){
	MyGPIO_Init(&phA);
	MyGPIO_Init(&phB);
	MyGPIO_Init(&idx);

	MyTimer_Encoder_Init(pt_tim_girouette);
	


	
}
