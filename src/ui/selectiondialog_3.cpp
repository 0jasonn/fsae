#include "engine/functions.h"
#include "global.h"
#include "ui/messageselect_api.h"
#include "ui/selectiondialog_api.h"
#include "ui/selectiondialog.h"

// Functions in this file (original names from the debug build):
//   selectionDialog::stop (0x020a20e0), close (0x020a2108), setVisible (0x020a2138)

extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" void SoundReq(u32 sound);
extern u8 pauseDialogBuffer[];

// selectionDialog::stop() (0x020a20e0): clears the frame and the state when the dialog is shown
void Knife_Message_selectionDialog_stop(void *a) {
    KnifeSelectDialog *self = (KnifeSelectDialog *)a;

    if (self->state == 0) {
        return;
    }
    Knife_Message_selectionDialog_clearFrame(self);
    self->state = 0;
    self->timer = 0;
}

// selectionDialog::close() (0x020a2108): moves the dialog to the closing state (5), and plays the close sound when the
// dialog was modal and is visible
void Knife_Message_selectionDialog_close(void *a) {
    KnifeSelectDialog *self = (KnifeSelectDialog *)a;

    if (Knife_Message_selectionDialog_isModal(self)) {
        self->state = 5;
        if (self->visibleRequest != 0) {
            SoundReq(0x44);
        }
    }
}

// selectionDialog::setVisible(bool) (0x020a2138): stores the request and the visible flag
void Knife_Message_selectionDialog_setVisible(void *a, s32 visible) {
    KnifeSelectDialog *self = (KnifeSelectDialog *)a;

    self->visibleRequest = visible;
    self->visible = self->visibleRequest != 0;
}
