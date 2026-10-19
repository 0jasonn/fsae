#ifndef WIP_E_DECLS_H
#define WIP_E_DECLS_H

// Callees of the E units that functions.h does not declare yet (dsd names, or original names still unlisted).
// The reviewer moves the ones with an original name into functions.h.
#include "engine/functions.h"

Entity *GetSetWork(s32 kind, u8 type); // 0x02076858 (original name GetSetWork); arrow_init passes two arguments
void UpdateIroyuka(void); // original name, C++ (0x0204d3ac)
int func_02083e54(int a); // 0x02083e54, returns a map-cell kind
void func_0208366c(s32 a, u16 b, u16 c); // 0x0208366c

// Bomb module callees (original signatures where listed).
void bombFire(Entity *e); // original bombFire(OBJ_WORK_*)
void bombFlash(Entity *e); // original bombFlash(OBJ_WORK_*)
void BombWallCk(Entity *e); // original BombWallCk(OBJ_WORK_*)
void TaimatuIgnition(Entity *e, u16 kind); // original TaimatuIgnition(OBJ_WORK_*, unsigned short)
void func_02085cf8(Entity *e);
void func_02085d34(Entity *e);

int func_02083ccc(Entity *e, s16 x, s16 y); // 0x02083ccc: cell kind at an offset from the entity

// Boots module callees.
void *zMalloc(u16 size); // original zMalloc(unsigned short)
void zFree(void *p); // original zFree(void*)
void func_020841b0(Entity *e);
void func_0208a224(Entity *e, u32 a, s32 x, s32 y); // 0x0208a224

// Hit module callees.
extern "C" s32 AddHeart(Entity *e, s32 amount); // original name, unmangled

u8 decVital(Entity *e, Entity *t); // 0x020248f0, defined in hit.cpp
void shiledCheck(Entity *e, Entity *t);
void nakamaCheckTgtOnly(Entity *e, Entity *t);
void nakamaCheck(Entity *e, Entity *t);
void setKokin(Entity *e, Entity *t);
void func_02085e08(Entity *e, Entity *t); // 0x02085e08, called with the hit arguments
void SetItemAdd(Entity *e, Entity *tmpl); // original SetItemAdd(OBJ_WORK_*, OBJ_WORK_*)

extern u8 data_0212cece[];
extern u8 data_0212cee6[];
extern u8 data_0212ced6[];
extern u8 data_0212ceca[];
extern u8 data_0212ceba[];
extern u8 data_0212ceb2[];

#endif
