#ifndef WIP_K_K_DECLS_H
#define WIP_K_K_DECLS_H

#include "engine/entity.h"

// Callees of the K files that no shared header declares yet (all plain symbols in symbols.txt, so extern "C").
extern "C" {
void ue_bgcheck(Entity *e, void *bgBuffer);     // original ue_bgcheck(OBJ_WORK_*, BG_BUFF_*) (yuka_api.h has a stale 1-argument form)
void shita_bgcheck(Entity *e, void *bgBuffer);  // original shita_bgcheck(OBJ_WORK_*, BG_BUFF_*)
void migi_bgcheck(Entity *e, void *bgBuffer);   // original migi_bgcheck(OBJ_WORK_*, BG_BUFF_*)
void hidari_bgcheck(Entity *e, void *bgBuffer); // original hidari_bgcheck(OBJ_WORK_*, BG_BUFF_*)
void func_0208530c(Entity *e, s32 speed, u8 direction, u16 wallFlags); // thumb, no original name
void func_020841b0(Entity *e);                  // thumb, no original name
void ObjCdirSet(Entity *e);                     // 0x02050280, original ObjCdirSet(OBJ_WORK_*)
void DropRupees(u8 type, u16 amount);           // 0x02050504, original DropRupees(unsigned char, unsigned short)
int func_02085a88(Entity *a, Entity *b, s32 w, s32 h); // thumb, overlap test of two entities
}

#endif
