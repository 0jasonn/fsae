#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Functions in this file (module cockpit, original names from the debug build):
//   rupeeUpdate, heartUpdate, bg_trans_body, cockpit_bg_trans

// Moves the displayed rupee count towards the counter at state+8 in steps of 1000, 100 or 10.
void rupeeUpdate(void) {
    s32 target;
    s32 diff;
    s32 current;
    u8 value;

    value = gameState.unk_24 & 0x7f;
    if (cockpitState.unk_0d != value) {
        cockpitState.unk_0d = value;
        cockpitState.redraw = 1;
    }
    target = (s32)gameState.score;
    diff = abs_s32(target - cockpitState.rupees);
    if (diff == 0) {
        return;
    }
    if (diff > 1000) {
        current = cockpitState.rupees;
        if ((u32)current < (u32)target) {
            cockpitState.rupees = current + 1000;
        } else {
            cockpitState.rupees = current - 1000;
        }
    } else if (diff > 100) {
        current = cockpitState.rupees;
        if ((u32)current < (u32)target) {
            cockpitState.rupees = current + 100;
        } else {
            cockpitState.rupees = current - 100;
        }
    } else if (diff > 10) {
        current = cockpitState.rupees;
        if ((u32)current < (u32)target) {
            cockpitState.rupees = current + 10;
        } else {
            cockpitState.rupees = current - 10;
        }
    } else {
        cockpitState.rupees = target;
    }
    cockpitState.redraw = 1;
}

// Moves the heart display counter (byte 8) one step towards the health of the current player.
void heartUpdate(u16 kind) {
    s32 health;

    if ((frameCounter.frame & 3) != 0) {
        return;
    }
    cockpitState.heartKind = (u8)kind;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0 || (playerWork[0].callState == 0 && playerWork[1].callState == 0)) {
        health = data_0212c53c->entity->health;
    } else {
        health = 0;
    }
    if (cockpitState.hearts == health) {
        return;
    }
    cockpitState.redraw = 1;
    if (cockpitState.hearts < health) {
        cockpitState.hearts += 1;
        if ((cockpitState.hearts & 7) == 0) {
            SoundReq(7);
        }
    } else {
        cockpitState.hearts -= 1;
    }
}

// Background of the cockpit: the rupee, heart and kakera parts are drawn again.
void bg_trans_body(void) {
    rupee_disp();
    addrupee_disp();
    heart_disp();
    if (cockpitState.mapStep != 0) {
        kakera_disp();
        kinomi_write();
    }
}
