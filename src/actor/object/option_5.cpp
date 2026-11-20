#include "engine/functions.h"
#include "global.h"
#include "actor/object/option.h"

// Option panel screen, fifth unit (module option). Address -> name:
//   0x0205c9c8 option_nop (renamed from option_nop), 0x0205c9cc optionGuide
//   (option_dialog at 0x0205c84c is in scratch/agentF/nonmatching; langCursor at 0x0205c7b0 too)

// Per-slot dialog position {x, y} and animation bounds; the slot is effectState.slotB or effectState.panelState
extern const u16 data_020d8a8c[][2];
extern const u8 data_020d8a74[];
#include "engine/multisio_save.h"

// No-op action slot
void option_nop(void) {
}

void optionGuide(Entity *e) {
    u8 slot;

    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b30 = 1;
        if (e->type2 != 0) {
            e->spriteSettings.b16 = 8;
            e->unk_20 = 0xe0;
            InitAnimationForceUpdate(e, 0);
        } else {
            e->spriteSettings.b14 = 3;
            InitAnimationForceUpdate(e, 3);
        }
    }
    UpdateAnimationSingleFrame(e);
    e->spriteSettings.b0 = 0;

    if (e->type2 != 0) {
        slot = effectState.panelState;
        e->y.HALF.HI = data_020d8a8c[slot][1] + 0x10;
        if (effectState.panelMode == 2) {
            e->spriteSettings.b0 = 2;
        }
        return;
    }
    if (effectState.panelPhase != 0 || effectState.panelMode != 0) {
        return;
    }
    slot = effectState.panelState;
    if (slot >= 3) {
        return;
    }
    if (data_021350b0[slot].status <= 0) {
        return;
    }
    e->y.HALF.HI = data_020d8a74[slot];
    e->spriteSettings.b0 = 2;
}
