#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Functions in this file (module cockpit, original names from the debug build):
//   heartAlart, PinchCheck, pinch_bgm_check, kattiUpdate

// Plays the heart alarm (sound 0x25) when the alarm timer is clear and the heart block is at most 0x10.
ARM void heartAlart(void) {
    if ((data_0212c594 & 0x3f) != 0 || frameCounter[0x11] != 0) {
        return;
    }
    if (data_0212c618[8] > 0x10) {
        return;
    }
    SoundReq(0x25);
}

// Returns 1 when a player with a low health (1..16) has a value above the counter at state+8.
ARM s32 PinchCheck(void) {
    u8 i;
    s32 result;

    result = 0;
    for (i = 0; i < data_0212c7c8[0]; i++) {
        if (PL_ENTITY(i)->health != 0 && PL_ENTITY(i)->health <= 0x10) {
            if (func_020867cc() > (u32)*(s32 *)(data_0212c7c8 + 8)) {
                result = 1;
            }
        }
    }
    return result;
}

// Starts or stops the pinch music and the pinch telop, then updates the background music.
ARM void pinch_bgm_check(void) {
    if (PinchCheck() != 0) {
        if (data_0212c7c8[0x51] == 0) {
            data_0212c7c8[0x51] = 1;
            TelopRequest(0x4b4);
            KAKERA_U32(0x10) = (u16)func_020867cc();
        }
    } else {
        data_0212c7c8[0x51] = 0;
    }
    BgmSet();
}

// Copies the katti graphics of the current player's state (bits 2..3 of its base direction byte) to the screen.
typedef struct KattiDirBits {
    u8 b0 : 2;
    u8 kind : 2;
    u8 rest : 4;
} KattiDirBits;

ARM void kattiUpdate(void) {
    u8 kind;

    kind = ((KattiDirBits *)(data_0212c53c + 0x3e))->kind;
    if (data_0212c618[7] == kind) {
        return;
    }
    data_0212c618[7] = kind;
    func_020845b0(0x6014200, KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), data_020f2530[data_0212c618[7]]) + data_020f2524[data_0212c618[7]], 0x180);
}
