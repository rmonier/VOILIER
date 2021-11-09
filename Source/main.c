#include "tests.h"
#include "Service_Wheels.h"
#include "Service_Communication.h"

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

int main()
{	
	/* HANDLE THE WHEELS WITH USART DEVICE */
	
	Wheels_Init();
	MyCommunication_Init(Handle_Wheels);
	
	return 0;
}
