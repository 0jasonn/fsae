#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   selectionDialog::update_close (0x020a2268)

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

// selectionDialog::update_close() (0x020a2268): clears the frame buffer, closes the dialog step by step, returns true
// once it is fully closed
extern "C" BOOL Knife_Message_selectionDialog_update_close(void *a);
ARM BOOL Knife_Message_selectionDialog_update_close(void *a) {
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
