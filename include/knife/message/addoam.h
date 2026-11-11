#ifndef WIP_E_ADDOAM_E_H
#define WIP_E_ADDOAM_E_H

#include "engine/functions.h"
#include "knife/subtask/subtask.h"
#include "ui/widget/uiobject.h"

// Size in pixels of an OAM object for each shape and size (12 entries, the rodata table data_020de998)
typedef struct UiOamSize {
    u32 w;
    u32 h;
} UiOamSize;

typedef struct UiOamSizeTable {
    UiOamSize entry[12];
} UiOamSizeTable;

// attr0 and attr1 of an OAM entry read as one word
typedef struct UiOamWord {
    u32 y : 8;
    u32 attr0Mid : 6;
    u32 shape : 2;
    u32 x : 9;
    u32 attr1Mid : 5;
    u32 size : 2;
} UiOamWord;

extern const UiOamSizeTable data_020de998;
extern u8 data_0217a23c[];

extern "C" {
u32 addOamUiObj(GXOamAttr *oam, u32 size, UIObject *obj);
void OamRing_Push(void *obj, const void *attrs, s32 count);
}

#endif
