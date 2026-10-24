#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   selectionDialog::stop (0x020a20e0), close (0x020a2108), setVisible (0x020a2138)

extern "C" BOOL Knife_Message_selectionDialog_isModal(const void *a);
extern "C" void Knife_Message_MessageSelect_init(void *self);
extern "C" void Knife_Message_selectionDialog_dispFrame(void *self);
extern "C" void Knife_Message_selectionDialog_clearFrame(void *self);
extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" void MI_CpuFill(void *dst, u32 value, u32 size);
extern "C" void Knife_Message_selectionDialog_dispMessage(void *self);
extern "C" BOOL Knife_Message_selectionDialog_update_move(void *self);
extern "C" void SoundReq(u32 sound);
extern u8 pauseDialogBuffer[];

// Selection dialog (Knife::Message::selectionDialog). Only the fields the functions matched so far use are named.
typedef struct KnifeSelectDialog {
    u8 unk_00[0x06];
    u8 result;          // 0x06: the choice, returned by getResult while the state is 6
    u8 visible;         // 0x07: 1 while the dialog is shown
    u8 unk_08[0x28 - 0x08];
    u8 msgScrn[0x38];   // 0x28: copy of the message screen info
    u8 unk_60[0x64 - 0x60];
    u16 unk_64;
    s8 visibleRequest; // 0x66: requested visibility (setVisible)
    s8 state;           // 0x67: 0 idle, 6 finished, others while open or closing
    u8 unk_68;
    u8 unk_69;
    u8 unk_6a;
    u8 unk_6b[0x70 - 0x6b];
    s16 unk_70;
    s16 unk_72;
    s16 timer;          // 0x74: animation time, 0x1000 when complete
    s16 speed;          // 0x76
    u32 unk_78;
} KnifeSelectDialog;

// selectionDialog::stop() (0x020a20e0): clears the frame and the state when the dialog is shown
extern "C" void Knife_Message_selectionDialog_stop(void *a);
ARM void Knife_Message_selectionDialog_stop(void *a) {
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
extern "C" void Knife_Message_selectionDialog_close(void *a);
ARM void Knife_Message_selectionDialog_close(void *a) {
    KnifeSelectDialog *self = (KnifeSelectDialog *)a;

    if (Knife_Message_selectionDialog_isModal(self)) {
        self->state = 5;
        if (self->visibleRequest != 0) {
            SoundReq(0x44);
        }
    }
}

// selectionDialog::setVisible(bool) (0x020a2138): stores the request and the visible flag
extern "C" void Knife_Message_selectionDialog_setVisible(void *a, s32 visible);
ARM void Knife_Message_selectionDialog_setVisible(void *a, s32 visible) {
    KnifeSelectDialog *self = (KnifeSelectDialog *)a;

    self->visibleRequest = visible;
    self->visible = self->visibleRequest != 0;
}
