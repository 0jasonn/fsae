#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   func_020a1a1c (0x020a1a1c, C++ symbol _Z13func_020a1a1cPv, declared in functions.h), selectionDialog::initWithMsgScrn (0x020a1a30)

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

// func_020a1a1c (0x020a1a1c, C++ symbol _Z13func_020a1a1cPv, declared in functions.h): clears 0x7c bytes at a
ARM void func_020a1a1c(void *a) {
    MI_CpuFill8(a, 0, 0x7c);
}

// selectionDialog::initWithMsgScrn(KNIFE_MSGSCRN const*) (0x0209a1a30): resets the state and copies the message screen
extern "C" void Knife_Message_selectionDialog_initWithMsgScrn(void *a, const void *msgScrn);
ARM void Knife_Message_selectionDialog_initWithMsgScrn(void *a, const void *msgScrn) {
    KnifeSelectDialog *self = (KnifeSelectDialog *)a;

    self->unk_64 = 0;
    self->state = 2;
    self->unk_70 = 1;
    self->unk_72 = 1;
    self->timer = 0;
    self->speed = 0x200;
    self->unk_78 = 0;
    self->unk_68 = 0;
    self->unk_6a = 0;
    Knife_Message_MessageSelect_init(self);
    MIi_CpuCopy32(msgScrn, self->msgScrn, 0x38);
}
