#ifndef KNIFE_MESSAGE_PLAYSTYLE_UPDATE_H
#define KNIFE_MESSAGE_PLAYSTYLE_UPDATE_H

#include "engine/functions.h"
#include "ui/playstyleselui.h"
#include "ui/fileselui.h"
#include "ui/widget/uiobject.h"
#include "engine/player.h"
#include "knife/comm/comm.h"

extern UIObject data_0217f1b4;

// The two OAM entry indices per list row of playStyleSelUIView_update (rodata data_020de780): [row][selected ? 0 : 1]
typedef struct PlayStyleOamRows {
    u8 index[2][2];
} PlayStyleOamRows;

// Screen position of the cursor for each choice (rodata data_020de88c, 8 bytes per choice)
typedef struct PlayStyleCursorPos {
    s32 x;
    s32 y;
} PlayStyleCursorPos;

extern const PlayStyleOamRows data_020de780;
extern const PlayStyleCursorPos data_020de88c[];

void MachiukeStart(void);
extern u16 data_0212c510;

extern "C" {
void playStyleSelUIView_clearScreen(PlayStyleSelUIView *self);
void playStyleSelUIView_move_in(PlayStyleSelUIView *self);
void playStyleSelUIView_move_out(PlayStyleSelUIView *self);
void playStyleSelUIView_move_in_return(PlayStyleSelUIView *self);
void playStyleSelUIView_move_out_return(PlayStyleSelUIView *self);
void playStyleSelUIView_update(PlayStyleSelUIView *self);
}

#endif
