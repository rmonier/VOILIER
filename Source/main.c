#include "tests.h"
#include "Service_Wheels.h"
//#include "Service_Communication.h"

void Handle_Wheels()
{
	/* RETRIEVE REMOTE CONTROL DATA via USART */
	
	
	
	/* UPDATE WHEELS PARAMETERS */
	
	Wheels_Stop();
	Wheels_Set_Parameters(0.5, 1);
	Wheels_Start();
}

int main()
{
	//test_PWM();
	//test_ADC();
	//test_IMU();
	//test_GPIO_Timer();
	//test_USART();
	//test_Servo();
	
	/* HANDLE THE WHEELS WITH USART DEVICE */
	
	Wheels_Init();
	Handle_Wheels(); // faire looper avec interruption
	
	return 0;
}
