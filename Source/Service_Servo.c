#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include <math.h>

//Variables globales du Timer associé à la PWM du Servo_Moteur
MyTimer_Struct_TypeDef tim_servo = {
		TIM3,
		3599,
		399 //PSC_FOR_CLOCK((0.02), tim_servo.ARR) ;
};
MyTimer_Struct_TypeDef *pt_tim_servo = &tim_servo;


void MyServo_Init() //PWM avec une période de 20ms sur TIM3 Ch2, position initiale avec les voiles rangées
{
	MyTimer_Base_Init(&tim_servo); //Lance le Timer 3
	MyTimer_PWM(tim_servo.Timer,2); //Active la PWM associée au Servo Moteur
	
	MyTimer_PWM_SetCycle(pt_tim_servo, 2, 0.1); //Définie une position initiale au Servo Moteur : ici 10% pour des voiles "rangées"
	MyTimer_Base_Start(pt_tim_servo); //Lance la PWM
}



void MyServo_Set(float angle_voile)  //PWM en pas de 0.25 <=> résolution de teta en 4.5°
{
	
	if (angle_voile >= 0 || angle_voile <= 90) { //si la valeur n'est pas valide c'est tant pis
			float teta;
			float pourcent;
			float rest;
		
			//arrondi l'angle_voile en un mutliple de 4.5	
	  	rest = fmod(angle_voile,4.5);
			if ( fmod(angle_voile,4.5) < 2.25 ) {
				teta = angle_voile - fmod(angle_voile,4.5);
			} else {
				teta = angle_voile + 4.5 - fmod(angle_voile,4.5);
			}
			
			//on map le teta à un pourcentage de la PWM : 0° => 10% et 90° => 5°
			pourcent = 0.1 - ((teta/4.5)*0.0025);
			MyTimer_PWM_SetCycle(pt_tim_servo, 2, pourcent); 
	}

}
