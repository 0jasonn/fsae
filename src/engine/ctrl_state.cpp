#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// ctrl_state: function Ctrl_setStateValue (0x020bb85c), provisional name.

// State record: the state halfword at +0x9c and the value halfword at +0x9e
typedef struct CtrlState {
    u8 unk_00[0x9c];
    u16 state;         // 0x9c
    s16 value;         // 0x9e
} CtrlState;

// Ctrl_setStateValue(self) (0x020bb85c, provisional name): state 0 sets the value -0x60, state 1 sets 0 and state 2 sets
// -0x30; other states leave it unchanged
extern "C" void Ctrl_setStateValue(CtrlState *self);
ARM void Ctrl_setStateValue(CtrlState *self) {
    switch (self->state) {
    case 0:
        self->value = -0x60;
        break;
    case 1:
        self->value = 0;
        break;
    case 2:
        self->value = -0x30;
        break;
    }
}
