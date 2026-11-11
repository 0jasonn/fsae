#ifndef WIP_E_MODESELUI_MAIN_E_H
#define WIP_E_MODESELUI_MAIN_E_H

#include "engine/functions.h"
#include "ui/modeselui_view.h"
#include "ui/modeselui_api.h"
#include "ui/fileselui_view.h"
#include "ui/fileselui_api.h"
#include "ui/fileselui.h"
#include "ui/widget/uiobject.h"
#include "game/clamp_api.h"
#include "game/fs_api.h"

// Rows of the mode select screen: three pairs (selected, normal) of OAM or UIObject indices (rodata)
typedef struct ModeSelRows {
    u8 pair[3][2];
} ModeSelRows;

// For each of the three items the neighbour reached by the d-pad: [item][up, down, left, right], -1 for none
typedef struct ModeSelNeighbors {
    s8 next[12];
} ModeSelNeighbors;

// Screen position of the cursor for each item (rodata, 8 bytes each)
typedef struct ModeSelCursorPos {
    s32 x;
    s32 y;
} ModeSelCursorPos;

extern const ModeSelRows data_020de798; // oam entry pairs {highlighted, normal}
extern const ModeSelRows data_020de7a0; // UIObject pairs (visibility flag of the item and its label)
extern const ModeSelNeighbors data_020de7d8;
extern const ModeSelCursorPos data_020de8e4[];
extern s32 data_020de834;    // y offset of the slide start (rodata)
extern s32 data_020de840;
extern s32 data_020de844;    // frames of the slides (12)
extern s32 data_020de84c[2]; // list panel position (x, y)
extern s32 data_020de864[2]; // slide position (x, y)
extern UIObject data_0217eb2c[];   // UIObjects of the file select controller
extern UIObject data_0217ec8c;
extern UIObject data_0217eef4;
extern UIObject data_0217f314;
extern u8 data_02180c2d;           // the focused file slot
extern u16 data_0212c510;

extern "C" {
s32 modeSelUIView_updateMain(void *self);
void CARD_LockBackup(void *self); // fileSelUIView::move(2) (symbols.txt still calls it CARD_LockBackup)
void subtask_dialogDelete(void);
void func_020ac038(s32 a, s32 b, s32 c, s32 d);
}

#endif
