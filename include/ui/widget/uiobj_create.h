#ifndef WIP_D_UIOBJ_CREATE_H
#define WIP_D_UIOBJ_CREATE_H

// Heap-allocated UI objects: the create helpers that allocate a record from the heap of a holder and initialise it.
// The func_ addresses are provisional names from the allocator/initializer call pattern; see scratch/agentD/renames.txt.

#include "types.h"

extern "C" {
void *func_020c2c34(void *heap, s32 size);

void *func_020b8408(void *self);
void *RectObjLink2_initCopy(void *self);
void *RectSlot_init(void *self);
void *CtrlItem_init(void *self);
void *lobby_msgObj_init(void *self);
void *RectSlot3_init(void *self);
void *func_020bbf54(void *self);
void *RectSpan_clear(void *self);

void *UiObj_ba71c_create(void *holder);
void *UiObj_ba748_create(void *holder);
void *UiObj_ba7e0_create(void *holder);
void *UiObj_bcd34_create(void *holder);
void *UiObj_bcd60_create(void *holder);
void *UiObj_bcd8c_create(void *holder);
void *UiObj_bcdb8_create(void *holder);
void *UiObj_bcde4_create(void *holder);
void *UiObj_be128_create(void *holder);
}

#endif
