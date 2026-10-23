#include "engine/functions.h"
#include "global.h"
#include "object/option.h"

// Option panel screen, fifth unit (module option). Address -> name:
//   0x0205c9c8 option_nop (renamed from option_nop), 0x0205c9cc optionGuide
//   (option_dialog at 0x0205c84c is in scratch/agentF/nonmatching; langCursor at 0x0205c7b0 too)

// Per-slot dialog position {x, y} and animation bounds; the slot is data_021349c0[NP_SLOT_B] or NP_PANEL_STATE
extern const u16 data_020d8a8c[][2];
extern const u8 data_020d8a74[];
extern s8 data_021350f7[]; // 0x50 bytes per slot, first byte signed

// No-op action slot
ARM void option_nop(void) {
}

ARM void optionGuide(Entity *e) {
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
        slot = data_021349c0[NP_PANEL_STATE];
        e->y.HALF.HI = data_020d8a8c[slot][1] + 0x10;
        if (data_021349c0[0x24] == 2) {
            e->spriteSettings.b0 = 2;
        }
        return;
    }
    if (data_021349c0[NP_PHASE] != 0 || data_021349c0[0x24] != 0) {
        return;
    }
    slot = data_021349c0[NP_PANEL_STATE];
    if (slot >= 3) {
        return;
    }
    if (data_021350f7[slot * 0x50] <= 0) {
        return;
    }
    e->y.HALF.HI = data_020d8a74[slot];
    e->spriteSettings.b0 = 2;
}
