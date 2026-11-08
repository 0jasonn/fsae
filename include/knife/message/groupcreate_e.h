#ifndef WIP_E_GROUPCREATE_E_H
#define WIP_E_GROUPCREATE_E_H

#include "engine/functions.h"
#include "ui/groupcreateui.h"
#include "ui/fileselui.h"
#include "ui/widget/uiobject.h"
#include "knife/subtask/subtask_dialog.h"
#include "game/clamp_api.h"

// The two OAM entry indices per list row of groupCreateUIView_update (rodata data_020de77c): [row][selected ? 0 : 1]
typedef struct GroupCreateOamRows {
    u8 index[2][2];
} GroupCreateOamRows;

// Screen position of the cursor for each choice (rodata data_020de8ac, 8 bytes per choice)
typedef struct GroupCreateCursorPos {
    s32 x;
    s32 y;
} GroupCreateCursorPos;

extern const GroupCreateOamRows data_020de77c;
extern const GroupCreateCursorPos data_020de8ac[];
extern const s32 data_020de854[2]; // position of the wait dialog object (x, y in pixels)

extern u32 opTitleState;
extern u8 effectState[]; // ResultState block (actor/enemy/ending.h): timer u16 at +4, byte at +8, word at +0x24
extern u16 data_0212c510;
extern u8 data_021806f0[];

void MachiukeStart(void);
extern UIObject data_0217f41c;

extern "C" {
void groupCreateUIView_update(GroupCreateUIView *self);
s32 Knife_Comm_WirelessManager_getConnectResult(void *manager);
void func_020ac038(s32 a, s32 b, s32 c, s32 d);
void subtask_dialogDelete(void);
// the move functions get the view as argument (the ROM passes it in r0; groupcreateui_move.h declares them without)
void groupCreateUIView_move_in(GroupCreateUIView *self);
void groupCreateUIView_move_in_return(GroupCreateUIView *self);
void groupCreateUIView_move_out_return(GroupCreateUIView *self);
void groupCreateUIView_move_out(GroupCreateUIView *self);
}

#endif
