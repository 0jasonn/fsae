#ifndef WIP_F_DECLS_H
#define WIP_F_DECLS_H

// Callees of the F units that engine/functions.h does not declare yet. The reviewer moves the ones with an original
// name into functions.h.
#include "engine/functions.h"

extern "C" void PlStartPosSet(Entity *e); // 0x02054fe4, original name PlStartPosSet (C linkage)
extern "C" int func_02029a44(int a);      // 0x02029a44, returns |a| (no original name yet)
void CalcRanking(void);                   // 0x02055f18, original name CalcRanking()
u32 ranking_getKey(u8 index);             // 0x0205610c, original name ranking_getKey(unsigned char)
int fumiCheck(Entity *e);                   // 0x0205b5bc, original fumiCheck(OBJ_WORK_*)
int fumiCheck2(Entity *e);                  // 0x0205b630, original fumiCheck2(OBJ_WORK_*)
void func_0208366c(s32 a, u16 b, u16 c);    // 0x0208366c (C++ name func_0208366cltt)
u16 func_0208367c(u16 cell, u16 layer);     // 0x0208367c (no original name yet)
void func_0208365c(u8 a, u16 b, u16 c);     // 0x0208365c (no original name yet)
int func_02084110(void);                    // 0x02084110, returns nonzero when an event is pending (callers pass the entity in r0)
void StopEffectWindow(void);                // 0x0202b598, original StopEffectWindow()
void MakeTriangleWindow(s16 a, s16 b, s16 c, s16 d); // 0x0202b828, original MakeTriangleWindow(short, short, short, short)
void InitCircleWindow(u16 a, u16 b);       // 0x0202b5d4, original InitCircleWindow(unsigned short, unsigned short)

#endif
