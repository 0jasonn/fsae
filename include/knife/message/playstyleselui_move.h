#ifndef WIP_E_PLAYSTYLESELUI_MOVE_H
#define WIP_E_PLAYSTYLESELUI_MOVE_H

// playStyleSelUIView move functions (0x020aad08 to 0x020ab098, src/wip/E/playstyleselui_move.cpp). Each one sets the
// durationFP and start position of the five UIObjects of the play style list (data_0217f1b4, data_0217f20c,
// data_0217f264, data_0217f2bc and data_0217f314, stride 0x58 inside the file select controller block data_0217e6f0)
// and starts their move with UIObject_movePos.

#include "engine/functions.h"
#include "ui/fileselui.h"
#include "ui/widget/uiobject.h"

extern UIObject data_0217f1b4;
extern UIObject data_0217f20c;
extern UIObject data_0217f264;
extern UIObject data_0217f2bc;
extern UIObject data_0217f314;

extern const s32 data_020de838;    // frames of the move (rodata)
extern const s32 data_020de840;    // y offset of the list panel start (rodata)
extern const s32 data_020de84c[2]; // list panel position (x, y) in pixels
extern const s32 data_020de87c[4]; // play style slide positions: (x, y) of two objects

extern "C" {
void playStyleSelUIView_move_in(void);
void playStyleSelUIView_move_out(void);
void playStyleSelUIView_move_in_return(void);
void playStyleSelUIView_move_out_return(void);
}

#endif
