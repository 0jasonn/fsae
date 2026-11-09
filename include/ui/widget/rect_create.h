#ifndef WIP_D_RECT_CREATE_H
#define WIP_D_RECT_CREATE_H

// Declarations for the rect-family create/init helpers matched in src/wip/D/rect_create.cpp.

#include "types.h"

struct RectObjLink3;
extern "C" {
void *func_020c2c34(void *heap, s32 size);
void *RectObjList_init2(void *self);
void *RectObjLink_initCopy(void *self);
void *RectObjLink2_init(void *self);
void *RectObjLink3_init(RectObjLink3 *self);
void *RectSlot2_init(void *self);
}

#endif
