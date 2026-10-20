#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Functions in this file (module cockpit, original names from the debug build):
//   rupeeUpdate, heartUpdate, bg_trans_body, cockpit_bg_trans

// Moves the displayed rupee count towards the counter at state+8 in steps of 1000, 100 or 10.
ARM void rupeeUpdate(void) {
    s32 target;
    s32 diff;
    s32 current;
    u8 value;

    value = data_0212c7c8[0x24] & 0x7f;
    if (data_0212c618[0xd] != value) {
        data_0212c618[0xd] = value;
        data_0212c618[2] = 1;
    }
    target = *(s32 *)(data_0212c7c8 + 8);
    diff = abs_s32(target - *(s32 *)(data_0212c618 + 0x10));
    if (diff == 0) {
        return;
    }
    if (diff > 1000) {
        current = *(s32 *)(data_0212c618 + 0x10);
        if ((u32)current < (u32)target) {
            *(s32 *)(data_0212c618 + 0x10) = current + 1000;
        } else {
            *(s32 *)(data_0212c618 + 0x10) = current - 1000;
        }
    } else if (diff > 100) {
        current = *(s32 *)(data_0212c618 + 0x10);
        if ((u32)current < (u32)target) {
            *(s32 *)(data_0212c618 + 0x10) = current + 100;
        } else {
            *(s32 *)(data_0212c618 + 0x10) = current - 100;
        }
    } else if (diff > 10) {
        current = *(s32 *)(data_0212c618 + 0x10);
        if ((u32)current < (u32)target) {
            *(s32 *)(data_0212c618 + 0x10) = current + 10;
        } else {
            *(s32 *)(data_0212c618 + 0x10) = current - 10;
        }
    } else {
        *(s32 *)(data_0212c618 + 0x10) = target;
    }
    data_0212c618[2] = 1;
}

// Moves the heart display counter (byte 8) one step towards the health of the current player.
ARM void heartUpdate(u16 kind) {
    s32 health;

    if ((*(u16 *)frameCounter & 3) != 0) {
        return;
    }
    data_0212c618[9] = (u8)kind;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0 || (PL_BYTE(0, 0x3c) == 0 && PL_BYTE(1, 0x3c) == 0)) {
        health = (*(Entity **)(data_0212c53c + 0x28))->health;
    } else {
        health = 0;
    }
    if (data_0212c618[8] == health) {
        return;
    }
    data_0212c618[2] = 1;
    if (data_0212c618[8] < health) {
        data_0212c618[8] += 1;
        if ((data_0212c618[8] & 7) == 0) {
            SoundReq(7);
        }
    } else {
        data_0212c618[8] -= 1;
    }
}

// Background of the cockpit: the rupee, heart and kakera parts are drawn again.
ARM void bg_trans_body(void) {
    rupee_disp();
    addrupee_disp();
    heart_disp();
    if (data_0212c618[5] != 0) {
        kakera_disp();
        kinomi_write();
    }
}
