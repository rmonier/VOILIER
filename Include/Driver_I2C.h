#ifndef MYI2C_H
#define MYI2C_H

#include "stm32f10x.h"

typedef struct
{
	I2C_TypeDef *I2C;
} MyI2C_Struct_TypeDef;

void MyI2C_Init(MyI2C_Struct_TypeDef *I2C);

#endif
