#include "engine/functions.h"
#include "global.h"
#include "game/baseduiview.h"
#include "game/playstyleselui.h"

// Functions in this file (plain names from the debug build, C linkage):
//   playStyleSelUIView_viewWillApper (0x020aac30)

extern u8 data_0217d23c[];
extern u8 data_0217d30c[];
extern u8 data_0217e6f0[];

// playStyleSelUIView viewWillApper (0x020aac30): a pending selection with code 3 or 4 pushes the second view and returns;
// otherwise the pending flag clears, the saved entry is popped (or unk_5e cleared), and the title dialog is shown
ARM void playStyleSelUIView_viewWillApper(PlayStyleSelUIView *self) {
    u8 *pending = data_0217d30c;
    s32 isEmpty;

    if (*pending != 0) {
        s8 codeSigned = (s8)(((s8 *)data_0217d23c)[0xd1] - 3);
        u8 code = (u8)codeSigned;

        if (code <= 1) {
            basedUIView_push_view((basedUIView *)data_0217e6f0, self->secondView);
            return;
        }
        *pending = 0;
    }
    isEmpty = (self->entryCount == 0);
    if (isEmpty) {
        self->unk_5e = 0;
    } else {
        self->unk_5e = 1;
        self->entryCount--;
        self->unk_5d = (u8)self->entries[self->entryCount];
    }
    if (func_02019968() == 0) {
        self->unk_5d = 1;
        knife_title_dialogDisp(0x7ef);
        return;
    }
    knife_title_dialogDisp(0x83b);
}
