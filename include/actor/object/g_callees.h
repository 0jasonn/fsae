#ifndef WIP_G_CALLEES_H
#define WIP_G_CALLEES_H

#include "engine/functions.h"

// Callees used by the G files that engine/functions.h does not declare yet (plain symbols in symbols.txt are extern "C").
extern "C" void func_020841b0(Entity *e); // thumb label, no original name
extern "C" void func_02084228(Entity *e); // thumb label, no original name
extern "C" void func_02083f60(Entity *e, Entity *other); // thumb, no original name
extern "C" void yukaCheck(Entity *e);     // original yukaCheck(OBJ_WORK_*)
extern "C" void rc_yukaMove(Entity *e);   // original yukaMove(OBJ_WORK_*)
extern "C" int rc_yukaPlMoveCheck(PlayerData *player); // original yukaPlMoveCheck(PL_WORK_*)
extern "C" void ue_bgcheck(Entity *e);
extern "C" void shita_bgcheck(Entity *e);
extern "C" void migi_bgcheck(Entity *e);
extern "C" void hidari_bgcheck(Entity *e);
int func_02083ccc(Entity *e, s16 x, s16 y); // C++ symbol _Z13func_02083cccP9OBJ_WORK_ss
extern "C" void hidari_writecell(Entity *e);   // original writecell(OBJ_WORK_*)
extern "C" void hidari_rewritecell(Entity *e); // original rewritecell(OBJ_WORK_*)
extern "C" int cellcheck(Entity *e);           // original cellcheck(OBJ_WORK_*)

extern "C" void func_0208365c(u32 a, u16 index, u16 layer); // thumb, no original name

extern "C" void func_02084200(Entity *e);

extern "C" void ido_yukaMove(Entity *e);   // original yukaMove(OBJ_WORK_*)
extern "C" void ido_getNextInfo(Entity *e); // original getNextInfo(OBJ_WORK_*)

void TaimatuIgnition(Entity *e, u16 a); // original TaimatuIgnition(OBJ_WORK_*, unsigned short)

#endif
