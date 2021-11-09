#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"

#define ARR_MAX TIM_ARR_ARR
#define PERIODE_CLOCK_SEC(periode_clock_ms) (periode_clock_ms / 1000.0)
#define PSC_FOR_CLOCK(periode_clock_ms, arr) (((SystemCoreClock * PERIODE_CLOCK_SEC(periode_clock_ms)) / (arr + 1.0)) - 1.0) // on met notre valeur en suivant la formule : periode_horloge (s) * (PSC+1) * (ARR+1) = periode_timer

typedef struct
{
	TIM_TypeDef *Timer; // TIM1 � TIM4
	unsigned short ARR; // ~ au + cest grand au - le compteur sera pr�cis (en terme d'erreur), mais au + le temps pourra etre long (max 0xFFFF)
	unsigned short PSC;
} MyTimer_Struct_TypeDef;

/**
	**********************************************************************************************
	* @brief
	* @param	-> Param�tre sous forme d'une structure (son adresse) contenant les
	* 					informations de base
	* @Note 	-> Fonction � lancer syst�matiquement avant d'aller plus en d�tail dans les
	* 				 conf plus fines (PWM, codeur inc...)
	************************************************************************************************
	*/
void MyTimer_Base_Init(MyTimer_Struct_TypeDef *Timer);

#define MyTimer_Base_Start(TimerStruct) (TimerStruct->Timer->CR1 |= TIM_CR1_CEN)
#define MyTimer_Base_Stop(TimerStruct) (TimerStruct->Timer->CR1 &= ~TIM_CR1_CEN)

/**
	**************************************************************************************************
	* @brief
	* @param : - TIM_TypeDef *Timer : Timer concerne
	* - char Prio : de 0 a 15
	* @Note : La fonction MyTimer_Base_Init doit avoir ete lancee au prealable
	**************************************************************************************************
	*/
void MyTimer_ActiveIT(TIM_TypeDef *Timer, char Prio, void (*IT_function)(void));

/**
	* @brief
	* @param 
	* @Note Active le channel sp�cifi� sur Timer le timer sp�cifi�
	* la gestion de la configuration I/O n�est pas faite dans cette fonction
	* ni le r�glage de la p�riode de la PWM (ARR, PSC)
	*/
void MyTimer_PWM(TIM_TypeDef *Timer, char Channel);


void MyTimer_PWM_SetCycle(MyTimer_Struct_TypeDef *Timer, char Channel, float cycle);
void MyTimer_PWM_SetRawCycle(MyTimer_Struct_TypeDef *Timer, char Channel, uint32_t raw_cycle);

void MyTimer_Encoder_Init(MyTimer_Struct_TypeDef *Timer);

#endif
