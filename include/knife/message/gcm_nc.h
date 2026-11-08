#ifndef WIP_E_GROUPCREATEUI_MOVE_H
#define WIP_E_GROUPCREATEUI_MOVE_H

// groupCreateUIView move functions (0x020ab6d0 to 0x020aba60, src/wip/E/groupcreateui_move.cpp). Same shape as the
// playStyleSelUIView moves (playstyleselui_move.h): durationFP and the start position of four UIObjects of the
// file select controller block (uiObjects[26] to [29], data_0217f41c, data_0217f474, data_0217f4cc, data_0217f524)
// and the shared list object data_0217f314 (uiObjects[23]).

#include "engine/functions.h"
#include "ui/fileselui.h"
#include "ui/widget/uiobject.h"

extern UIObject data_0217f41c;
extern UIObject data_0217f474;
extern UIObject data_0217f4cc;
extern UIObject data_0217f524;
extern UIObject data_0217f314;

extern s32 data_020de838;    // frames of the move (rodata)
extern s32 data_020de840;    // y offset of the list panel start (rodata)
extern s32 data_020de84c[2]; // list panel position (x, y) in pixels
extern s32 data_020de89c[4]; // group create slide positions: (x, y) of two objects

extern "C" {
void groupCreateUIView_move_in(void);
void groupCreateUIView_move_in_return(void);
void groupCreateUIView_move_out_return(void);
void groupCreateUIView_move_out(void);
}

#endif
