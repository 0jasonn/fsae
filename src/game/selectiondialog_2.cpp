#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   selectionDialog::isModal (0x020a1d08), getResult (0x020a1d20), update_open (0x020a1d34)

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

// selectionDialog::isModal() const (0x020a1d08): true unless the dialog is idle or finished
extern "C" BOOL Knife_Message_selectionDialog_isModal(const void *a);
ARM BOOL Knife_Message_selectionDialog_isModal(const void *a) {
    const KnifeSelectDialog *self = (const KnifeSelectDialog *)a;

    if (self->state == 0 || self->state == 6) {
        return 0;
    }
    return 1;
}

// selectionDialog::getResult() const (0x020a1d20): the choice once the dialog is finished, else 0
extern "C" u8 Knife_Message_selectionDialog_getResult(const void *a);
ARM u8 Knife_Message_selectionDialog_getResult(const void *a) {
    const KnifeSelectDialog *self = (const KnifeSelectDialog *)a;

    if (self->state != 6) {
        return 0;
    }
    return self->result;
}

// selectionDialog::update_open() (0x020a1d34): opens the dialog by 0x200 per frame, returns true when it is fully open
extern "C" BOOL Knife_Message_selectionDialog_update_open(void *a);
ARM BOOL Knife_Message_selectionDialog_update_open(void *a) {
    KnifeSelectDialog *self = (KnifeSelectDialog *)a;

    self->timer += self->speed;
    if (self->timer >= 0x1000) {
        self->timer = 0x1000;
    }
    Knife_Message_selectionDialog_dispFrame(self);
    return self->timer == 0x1000;
}
