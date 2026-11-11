#ifndef WIP_E_MODESELUI_E_H
#define WIP_E_MODESELUI_E_H

#include "engine/functions.h"
#include "ui/fileselui.h"
#include "ui/modeselui_view.h"
#include "ui/modeselui_api.h"
#include "game/setbg.h"
#include "ui/widget/uiobject.h"

// Six UIObject / OAM indices of the mode select screen (three pairs)
typedef struct ModeSelIndexTable {
    u8 ids[6];
} ModeSelIndexTable;

// Position of an UIObject in whole pixels
typedef struct ModeSelPoint {
    s32 x;
    s32 y;
} ModeSelPoint;

extern const ModeSelIndexTable data_020de788; // oam entry pairs: {highlighted, normal}
extern const ModeSelIndexTable data_020de7c0; // label UIObject pairs
extern const ModeSelPoint data_020de85c;      // off screen position of the two title objects
extern const s32 data_020de848;               // frames of a move (20)
extern const ModeSelPoint data_020de8fc[3];   // targets of the first three label objects
extern const ModeSelPoint data_020de92c[3];   // targets of the other label objects
extern UIObject data_0217eb2c[];              // UIObjects of the file select controller
extern UIObject data_0217fe14;
extern UIObject data_0217fe6c;
extern UIObject data_0217eef4;

// Work block of the subtask screens (pointer at data_0217d348): the BG screen buffer at 0x934
typedef struct ModeSelWork {
    u8 unk_00[0x934];
    u8 *bgBuffer; // 0x934
} ModeSelWork;

extern ModeSelWork *data_0217d348;
extern u8 data_0217a23c[];  // screen resources: palette sources at 0xb0 and 0xd0
extern u8 *data_02180d9c;   // screen buffer of the sub screen BG1
extern u8 *data_02180da0;   // screen buffer of the sub screen BG2

extern "C" {
void modeSelUIView_updateCopyFileselScreen(ModeSelUIView *self);
}
void subtask_redraw_text(s32 index);
void subTaskSendScr(s16 index, void *data, u32 offset, u32 size);

#endif
