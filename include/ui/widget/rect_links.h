#ifndef WIP_F_RECT_LINKS_H
#define WIP_F_RECT_LINKS_H

// Declarations used by the implementer F units of the rect family (not in engine/functions.h).

#include "types.h"

extern "C" void *RectObjLink_create(void *holder);
extern "C" s32 func_020bc200(void *owner, u16 w);
extern "C" void RectObjLink_setGeometry(void *self, s16 *pos, s16 *size, s32 value);
extern "C" void RectObjList_setItems(void *self, void *holder, void **src, s32 count, s16 *pos, s16 *size);
extern "C" void RectObjPair_setOffsets(void *self, s32 value);
extern "C" s32 RectObjList_findHit(void **items, s32 count, s16 *pos);
extern "C" void RectObj_updateHitFlag(void *self, s16 *pos);

extern "C" void *func_020b8408(void *self);
extern "C" void *func_020c2c34(void *heap, s32 size);
extern "C" void *RectObjLink_initCopy(void *self);
extern "C" void *RectObjLink2_initCopy(void *self);

extern "C" void func_020b9774(void *self, s32 flag);

#endif
