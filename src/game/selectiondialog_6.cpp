#include "engine/functions.h"
#include "global.h"
#include "game/selectiondialog_api.h"
#include "game/selectiondialog.h"

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
