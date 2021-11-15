#include "tests.h"
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

int main()
{
	
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
	
	
	//test_PWM();
	//test_ADC();
	//test_IMU();
	//test_GPIO_Timer();
	//test_USART();
	//test_Servo();
	
	return 0;
}
