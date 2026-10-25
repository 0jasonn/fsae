#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   selectionDialog::update (0x020a22cc)

extern "C" BOOL Knife_Message_selectionDialog_update_open(void *self);
extern "C" void Knife_Message_selectionDialog_dispMessage(void *self);
extern "C" BOOL Knife_Message_selectionDialog_update_move(void *self);
extern "C" BOOL Knife_Message_selectionDialog_update_close(void *self);
extern u8 messageRequest[];

// Selection dialog (Knife::Message::selectionDialog). Same layout as the other selectiondialog units.
typedef struct KnifeSelectDialog {
    u8 unk_00[0x06];
    u8 result;          // 0x06: the choice, returned by getResult while the state is 6
    u8 visible;         // 0x07: 1 while the dialog is shown
    u8 unk_08[0x28 - 0x08];
    u8 msgScrn[0x38];   // 0x28: copy of the message screen info
    u8 unk_60[0x64 - 0x60];
    u16 unk_64;
    s8 visibleRequest;  // 0x66: requested visibility (setVisible)
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

// selectionDialog::update() (0x020a22cc): runs the state machine of the dialog, returns true once it has finished
ARM BOOL Knife_Message_selectionDialog_update(void *a) {
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
