#include <stdio.h>
#include "tests.h"
#include "Service_Wheels.h"
#include "Service_Communication.h"
#include "Service_Batterie.h"
#include "Service_Timer.h"

void Handle_Wheels()
{
	/* RETRIEVE REMOTE CONTROL DATA via USART */
	
	int isHoraire = Communication_Is_Horaire();
	float speed_ratio = Communication_Get_Speed_Ratio();
	
	/* UPDATE WHEELS PARAMETERS */
	
	Wheels_Stop();
	Wheels_Set_Parameters(speed_ratio, isHoraire);
	Wheels_Start();
}

void Handle_Batterie_Display()
{
	/* USE USART DISPLAY TO GET BATTERY IN PERCENT */
	char message[255];
	sprintf(message, "Batterie : %d%%", Batterie_Get_Value());
	Communication_Display_Message(message);
}

int main()
{	
	/* HANDLE THE WHEELS WITH USART DEVICE */
	
	Wheels_Init();
	MyCommunication_Init(Handle_Wheels);
	
	/* HANDLE THE BATTERY */
	
	Batterie_Init();
	Timer_Start_Interruption(2000, Handle_Batterie_Display);
	
	/* HANDLE GIROUETTE */
	
	
	
	/* HANDLE IMU */
	
	
	
	return 0;
}
