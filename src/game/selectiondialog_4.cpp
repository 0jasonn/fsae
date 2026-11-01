#include "engine/functions.h"
#include "global.h"
#include "game/messageselect_api.h"
#include "game/selectiondialog_api.h"
#include "game/selectiondialog.h"

// Functions in this file (original names from the debug build):
//   selectionDialog::update_close (0x020a2268)

extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" void SoundReq(u32 sound);
extern u8 pauseDialogBuffer[];

// selectionDialog::update_close() (0x020a2268): clears the frame buffer, closes the dialog step by step, returns true
// once it is fully closed
BOOL Knife_Message_selectionDialog_update_close(void *a) {
    KnifeSelectDialog *self = (KnifeSelectDialog *)a;

    MI_CpuFill(pauseDialogBuffer, 0, 0x800);
    self->timer = self->timer - self->speed;
    if (self->timer <= 0) {
        Knife_Message_selectionDialog_clearFrame(self);
        self->timer = 0;
    } else {
        Knife_Message_selectionDialog_dispFrame(self);
    }
    return self->timer == 0;
}
