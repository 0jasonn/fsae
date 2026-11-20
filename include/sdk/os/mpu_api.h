#ifndef ENGINE_MPU_API_H
#define ENGINE_MPU_API_H

// Functions defined in src/engine/mpu*.cpp.

#include "engine/entity.h"

extern "C" {
u32 Mpu_GetRegion0(void);
u32 Mpu_GetRegion1(void);
u32 Mpu_GetRegion2(void);
u32 Mpu_GetRegion3(void);
u32 Mpu_GetRegion4(void);
u32 Mpu_GetRegion5(void);
u32 Mpu_GetRegion6(void);
u32 Mpu_GetRegion7(void);
void Mpu_SetRegion0(u32 value);
void Mpu_SetRegion1(u32 value);
void Mpu_SetRegion2(u32 value);
void Mpu_SetRegion3(u32 value);
void Mpu_SetRegion4(u32 value);
void Mpu_SetRegion5(u32 value);
void Mpu_SetRegion6(u32 value);
void Mpu_SetRegion7(u32 value);
}

#endif
