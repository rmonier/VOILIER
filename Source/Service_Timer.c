#include "Service_Timer.h"
#include "Driver_Timer.h"

/**
	* Use this ONLY ONE TIME !!! 
	* TODO: Be able to start many interruptions
	*/
void Timer_Start_Interruption(int millisec, void (*callback)())
{
	MyTimer_Struct_TypeDef timer = {
		TIM1,
		35999,
		PSC_FOR_CLOCK(millisec, timer.ARR)
	};
	MyTimer_Struct_TypeDef *pt_timer = &timer;
	
	MyTimer_Base_Init(pt_timer);
	MyTimer_Base_Start(pt_timer);

	MyTimer_ActiveIT(timer.Timer, 8, callback);
}