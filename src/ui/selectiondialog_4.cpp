#include "engine/functions.h"
#include "global.h"
#include "ui/messageselect_api.h"
#include "ui/selectiondialog_api.h"
#include "ui/selectiondialog.h"

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

// Functions in this file (original names from the debug build):
//   selectionDialog::update (0x020a22cc)

extern u8 messageRequest[];

// selectionDialog::update() (0x020a22cc): runs the state machine of the dialog, returns true once it has finished
BOOL Knife_Message_selectionDialog_update(void *a) {
    KnifeSelectDialog *self = (KnifeSelectDialog *)a;
    BOOL finished = 0;

    switch (self->state) {
    case 2:
        if (Knife_Message_selectionDialog_update_open(self)) {
            self->state = 3;
        }
        break;
    case 3:
        Knife_Message_selectionDialog_dispMessage(self);
        self->state = 4;
        break;
    case 4:
        if (Knife_Message_selectionDialog_update_move(self)) {
            self->state = 5;
            if (self->visibleRequest != 0) {
                SoundReq(0x44);
            }
        }
        break;
    case 5:
        if (Knife_Message_selectionDialog_update_close(self)) {
            self->state = 6;
        }
        break;
    case 6:
        self->state = 0;
        messageRequest[0] = 0;
        finished = 1;
        break;
    default:
        break;
    }
    return finished;
}
