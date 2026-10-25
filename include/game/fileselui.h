#ifndef WIP_F_FILESELUI_H
#define WIP_F_FILESELUI_H

// fileSelUIViewCtrl: controller of the file select screen. Holds one UIObject per list entry and the OAM counter.

#include "types.h"
#include "game/uiobject.h"
#include "game/baseduiview.h"
#include "game/subtask.h"

// One of the two slot tables of fileSelUIViewCtrl: four pointers to buffers, freed by finalize
typedef struct FileSelSlot {
    /* 00 */ void *buf00;
    /* 04 */ u8 unk_04[4];
    /* 08 */ void *buf08;
    /* 0c */ u8 unk_0c[4];
    /* 10 */ void *buf10;
    /* 14 */ u8 unk_14[4];
    /* 18 */ void *buf18;
    /* 1c */ u8 unk_1c[4];
} FileSelSlot;

typedef struct FileSelUIViewCtrl {
    /* 000 */ basedUIView base;
    /* 030 */ u8 unk_030[0x3c - 0x30];
    /* 03c */ u8 unk_03c[0x400];
    /* 43c */ UIObject uiObjects[0x60]; // one per file entry, 0x58 bytes each
    /* 253c */ u8 unk_253c; // cleared by fileSelUIViewCtrl_initUIObject, saved by serialize
    /* 253d */ u8 unk_253d; // saved by serialize
    /* 253e */ u8 pendingFlag; // bit 7: a request for func_020827a8, cleared by update
    /* 253f */ u8 unk_253f;
    /* 2540 */ void *unk_2540; // object whose field at 0x1c is released by finalize
    /* 2544 */ void *oamBuffer; // first argument of addOamUiObj, freed by finalize
    /* 2548 */ u8 unk_2548[0x25a8 - 0x2548]; // embedded object, released by subTask_free_objinfo
    /* 25a8 */ u16 oamCount; // number of OAM entries added so far
    /* 25aa */ u8 unk_25aa[2];
    /* 25ac */ FileSelSlot slotsA[4];
    /* 262c */ FileSelSlot slotsB[4];
    /* 26ac */ void *unk_26ac;
    /* 26b0 */ void *unk_26b0;
    /* 26b4 */ void *unk_26b4;
} FileSelUIViewCtrl;

extern "C" {
void MI_CpuFill8(void *dst, u8 value, u32 size);
u32 addOamUiObj(u32 oamBuffer, u32 size, UIObject *obj);
void fileSelUIViewCtrl_initUIObject(FileSelUIViewCtrl *self);
void fileSelUIViewCtrl_clearOamCount(FileSelUIViewCtrl *self);
void fileSelUIViewCtrl_addOamEntry_0ad964(FileSelUIViewCtrl *self, u8 index);
void fileSelUIViewCtrl_initVram(FileSelUIViewCtrl *self);
void fileSelUIViewCtrl_initialize(FileSelUIViewCtrl *self);
void fileSelUIViewCtrl_serialize(FileSelUIViewCtrl *self, u8 **buf);
void fileSelUIViewCtrl_deserialize(FileSelUIViewCtrl *self, u8 **buf);
void fileSelUIViewCtrl_update(FileSelUIViewCtrl *self);
void fileSelUIViewCtrl_addOamEntry_0ad9a4(FileSelUIViewCtrl *self, const void *entries, s32 count);
void fileSelUIViewCtrl_finalize(FileSelUIViewCtrl *self);
void GXS_SetGraphicsMode(u32 mode);
void UIObject_update(UIObject *self);
void Knife_Message_setPendingPtr(u32 a);
extern u8 data_0217a258[];
void func_020c36fc(void *obj, const u32 *attrs, u16 count);
void func_02015084(u32 a);
void fileSelUIViewCtrl_finalize(FileSelUIViewCtrl *self);
void func_02015190(u32 a);
void *G2S_GetBG1ScrPtr(void);
void *G2S_GetBG2ScrPtr(void);
extern u8 data_0217d23c[];
extern u8 data_0217a23c[];
extern u8 data_0217e6f0[]; // the file select controller (FileSelUIViewCtrl)


// Size of an OAM object in pixels, one entry per shape and size (12 entries, the rodata table data_020de998)
typedef struct OamSize {
    u32 w;
    u32 h;
} OamSize;

typedef struct OamSizeTable {
    OamSize entry[12];
} OamSizeTable;

extern const OamSizeTable data_020de998;
}

#endif
