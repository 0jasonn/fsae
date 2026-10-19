#ifndef UNKNOWN_D_COMMON_D_H
#define UNKNOWN_D_COMMON_D_H

#include "engine/entity.h"
#include "engine/player.h"

#ifdef __cplusplus
extern "C" {
#endif
s32 _s32_div_f(s32 a, s32 b);
Entity *ObjPosCopy(Entity *src, Entity *dst);
Entity *func_0208ae78(Entity *e);
void *KnifeApp_getInstance(void);
int KnifeApp_isWirelessMode(void *a);
void AddRupee(Entity *e, s32 v);
void DropRupeeDir(s32 i, s32 value, s32 flags);
#ifdef __cplusplus
}
#endif

extern s32 data_0212c7d4[];

#endif
