#include "Service_Servo.h"
#include <math.h>

void test_Servo()
{	
	/* TESTS SERVO *********************************/
		
	MyServo_Init();
	float angle_voile = 0;

	/*********************************************/
	
	do
	{
		/* TESTS SERVO *********************************/
	
		MyServo_Set(angle_voile);
		angle_voile = fmod(angle_voile + 4.5,90); //Test les 20 positions sans d�bordement
		int i = 0;
		while (i < 7200000) {i++;} //Sleep pour �tudier le moteur en temps r�el
    
		/*********************************************/
		
	} while(1);
}