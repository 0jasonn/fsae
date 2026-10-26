#include "engine/functions.h"
#include "global.h"
#include "game/fileselui_e.h"

// Functions in this file (plain names from the debug build, C linkage):
//   fileSelUIView_viewWillApper (0x020a761c)

extern u8 data_0217d23c[];
extern u8 data_0217a23c[];

// fileSelUIView::viewWillApper() (0x020a761c): with the lobby flag set, the first child enters; otherwise the saved
// entry is taken from the list, sent, and the top view enters
ARM void fileSelUIView_viewWillApper(FileSelUIView *self) {
    u8 *sendEntry;

    if (data_0217d23c[0xd0] != 0) {
        ((basedUIView *)self->objB)->enter();
        return;
    }
    s32 empty = (self->value48 == 0);

    if (empty) {
        self->flag41 = 0;
    } else {
        self->value48--;
        self->flag41 = (u8)((u32 *)self->block4c)[self->value48];
        sendEntry = *(u8 **)(data_0217a23c + 0xa8);
        subTaskSendBgChar(1, *(void **)(sendEntry + 0x14), 0, *(u32 *)(sendEntry + 0x10));
    }
    self->flag43 = 1;
    fileSelUIView_setupTextRender(self);
    ((basedUIView *)self->base.viewStack[self->base.stackIndex])->enter();
}
