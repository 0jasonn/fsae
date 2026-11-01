#include "engine/functions.h"
#include "global.h"
#include "game/messageselect_api.h"
#include "game/selectiondialog.h"

// Functions in this file (original names from the debug build):
//   func_020a1a1c (0x020a1a1c, C++ symbol _Z13func_020a1a1cPv, declared in functions.h), selectionDialog::initWithMsgScrn (0x020a1a30)

extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" void SoundReq(u32 sound);
extern u8 pauseDialogBuffer[];

// func_020a1a1c (0x020a1a1c, C++ symbol _Z13func_020a1a1cPv, declared in functions.h): clears 0x7c bytes at a
void func_020a1a1c(void *a) {
    MI_CpuFill8(a, 0, 0x7c);
}

// selectionDialog::initWithMsgScrn(KNIFE_MSGSCRN const*) (0x0209a1a30): resets the state and copies the message screen
void Knife_Message_selectionDialog_initWithMsgScrn(void *a, const void *msgScrn) {
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
