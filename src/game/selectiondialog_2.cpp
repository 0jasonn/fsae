#include "engine/functions.h"
#include "global.h"
#include "game/messageselect_api.h"
#include "game/selectiondialog_api.h"
#include "game/selectiondialog.h"

// Functions in this file (original names from the debug build):
//   selectionDialog::isModal (0x020a1d08), getResult (0x020a1d20), update_open (0x020a1d34)

extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" void SoundReq(u32 sound);
extern u8 pauseDialogBuffer[];

// selectionDialog::isModal() const (0x020a1d08): true unless the dialog is idle or finished
BOOL Knife_Message_selectionDialog_isModal(const void *a) {
    const KnifeSelectDialog *self = (const KnifeSelectDialog *)a;

    if (self->state == 0 || self->state == 6) {
        return 0;
    }
    return 1;
}

// selectionDialog::getResult() const (0x020a1d20): the choice once the dialog is finished, else 0
extern "C" u8 Knife_Message_selectionDialog_getResult(const void *a);
u8 Knife_Message_selectionDialog_getResult(const void *a) {
    const KnifeSelectDialog *self = (const KnifeSelectDialog *)a;

    if (self->state != 6) {
        return 0;
    }
    return self->result;
}

// selectionDialog::update_open() (0x020a1d34): opens the dialog by 0x200 per frame, returns true when it is fully open
BOOL Knife_Message_selectionDialog_update_open(void *a) {
    KnifeSelectDialog *self = (KnifeSelectDialog *)a;

    self->timer += self->speed;
    if (self->timer >= 0x1000) {
        self->timer = 0x1000;
    }
    Knife_Message_selectionDialog_dispFrame(self);
    return self->timer == 0x1000;
}
