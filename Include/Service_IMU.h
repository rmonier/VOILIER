#ifndef SERVICE_IMU_H
#define SERVICE_IMU_H

#include "lsm9ds1_reg.h"

/** Please note that is MANDATORY: return 0 -> no Error.**/
int32_t platform_write(void *handle, uint8_t Reg, const uint8_t *Bufp, uint16_t len);
int32_t platform_read(void *handle, uint8_t Reg, uint8_t *Bufp, uint16_t len);



#endif
