#include <stdio.h>
#include "tests.h"
#include "Service_Wheels.h"
#include "Service_Communication.h"
#include "Service_Batterie.h"
#include "Service_Timer.h"
#include "Service_Servo.h"
#include "Service_Girouette.h"


int Angle_Voile(int angle_girouette) {
	angle_girouette = angle_girouette / 4;
	if (angle_girouette > 180) {
		angle_girouette = 360 - angle_girouette;
	}
	
	float angle_voile = 0 ;
	
	if (angle_girouette > 45) {
		angle_voile = ((2.0/3.0)*((float)angle_girouette)) - 30.0 ; //map [45;180] dans [0;90]
	}
		
	return (int)angle_voile;
}

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
	sprintf(message, "Batterie : %d%%\n", Batterie_Get_Value());
	Communication_Display_Message(message);
}

int main()
{	
	/* HANDLE THE WHEELS WITH USART DEVICE */
	
	Wheels_Init();
	MyCommunication_Init(Handle_Wheels);
	
	/* HANDLE THE BATTERY */

	/*
	 * Pour exécuter l'analyse de la batterie remplacer le 0 par 1 ci-dessous.
	 * Le code est non activé par défaut car il y a une collision de Timer
	 * entre ce dernier et celui de la Girouette.
	 */
	#if 0
	
	Batterie_Init();
	Handle_Batterie_Display();
	Timer_Start_Interruption(2000, Handle_Batterie_Display);

	#endif
	
	/* HANDLE IMU */
	
	// IMU non traité.
	
	/* HANDLE GIROUETTE */
	
	MyServo_Init();
	MyGirouette_Init();
	int angle_girouette;
	int angle_voile;
	do
	{
		angle_girouette = MyGirouette_Get_Angle();
		angle_voile = Angle_Voile(angle_girouette);
		MyServo_Set(angle_voile);
		
	} while(1);
	
	return 0;
}
