#ifndef WIP_F_RECT_F_H
#define WIP_F_RECT_F_H

// Declarations used by the implementer F units of the rect family (not in engine/functions.h yet).

#include "types.h"

extern "C" void *func_020c2c34(void *heap, s32 size);
extern "C" void RectItem_clear(void *self);
extern "C" void *RectObjLink2_init(void *self);
extern "C" BOOL RectObj_hitTest(void *self, s16 *pos);
extern "C" void *RectObjList_init2(void *self);
extern "C" void *RectObjList_create(void *holder);
extern "C" void RectObjList_setGeometry(void *self, s16 *pos, s16 *size, s32 value);
extern "C" void RectObjList_setItems(void *self, void *holder, void **src, s32 count, s16 *pos, s16 *size);
extern "C" s32 func_020bc200(void *owner, u16 w, s32 x);

extern "C" void func_020b9688(void *self);
extern "C" void func_020b9774(void *self, s32 flag);
extern "C" void Slider_setPosition(void *self, s16 position);
extern "C" s32 Slider_setPositionChecked(void *self, s16 position);

extern "C" void func_020bb080(void *self);
extern "C" void func_020bb148(void *self);
extern "C" void RectSlot2_setFlag(void *self, s32 flag);
extern "C" s32 Slider_setIndex(void *self, s32 value);
extern "C" s32 Slider_setPositionFromIndex(void *self);

extern "C" void func_020bb980(void *self, s32 flag);
extern "C" s32 Ctrl_isReady(void *self);
extern "C" void Menu_AcquirePoolEntry(void *obj, s32 a, s32 b);
extern "C" void Ctrl_setFlagAndUpdate(void *self, s32 value);

extern "C" void *RectObjList_init(void *self);
extern "C" void RectObjLink_init(void *self);
extern "C" void RectObjLink_setGeometry(void *self, s16 *pos, s16 *size, s32 value);

extern "C" void *Fs_GetDirFileOffset(s32 id);
extern "C" s32 ResChunk_OpenKBEC(void *entry, void *owner);
extern "C" s32 Menu_ForwardC2cb4(void *entry, void *owner);
extern "C" s32 ResChunk_OpenRACH(void *entry, void *owner);
extern "C" s32 ResChunk_OpenTTLP(void *entry, void *owner);
extern "C" s32 ResChunk_GetNRCS(void *entry, void *owner);

extern "C" void OS_WaitVBlankIntr(void);
extern "C" void func_020c37c8(void *entry);
extern "C" void func_020c39c4(void *entry);

extern "C" void *Table_getEntry58(u8 *self, s32 index);
extern "C" void ResPlayer_AdvanceAndRefresh(void *entry, s32 value);
extern "C" void ResPlayer_SeekAndRefresh(void *entry, s32 value);
extern "C" void GXx_SetMasterBrightness_(void *reg, s32 value);
extern "C" void G2x_SetBlendAlpha_(void *reg, s32 a, s32 b, s32 c, s32 d);
extern "C" void GX_LoadBGPltt(void *src, s32 offset, s32 size);
extern "C" void GXS_LoadBGPltt(void *src, s32 offset, s32 size);

#endif
