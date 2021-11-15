#include "Driver_GPIO.h"
#include "Driver_Timer.h"

//Variables globales du Timer associé à la Girouette
MyTimer_Struct_TypeDef tim_girouette = {
		TIM4,
	  1439, //360*4 car 1/4 de degré de résolution
		3 //il comptera tout les 4 tics d'horloge
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

void Interruption_Encoder(void)
{
	MyTimer_Reset_Counter(pt_tim_girouette);
}


void MyGirouette_Init(){
	MyTimer_Base_Init(&tim_girouette);
	MyGPIO_Init(&phA);
	MyGPIO_Init(&phB);
	MyGPIO_Init(&idx);
	MyTimer_Encoder_Init(pt_tim_girouette,Interruption_Encoder);
}

int MyGirouette_Get_Angle() {
	return (int)MyTimer_Get_Counter(pt_tim_girouette);
}