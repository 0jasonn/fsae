#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Functions in this file (module cockpit, original names from the debug build):
//   heartAlart, PinchCheck, pinch_bgm_check, kattiUpdate

// Plays the heart alarm (sound 0x25) when the alarm timer is clear and the heart block is at most 0x10.
void heartAlart(void) {
    if ((data_0212c594 & 0x3f) != 0 || frameCounter[0x11] != 0) {
        return;
    }
    if (cockpitState[8] > 0x10) {
        return;
    }
    SoundReq(0x25);
}

// Returns 1 when a player with a low health (1..16) has a value above the counter at state+8.
s32 PinchCheck(void) {
    u8 i;
    s32 result;

    result = 0;
    for (i = 0; i < gameState.playerCount; i++) {
        if (PL_ENTITY(i)->health != 0 && PL_ENTITY(i)->health <= 0x10) {
            if (func_020867cc() > gameState.score) {
                result = 1;
            }
        }
    }
    return result;
}

// Starts or stops the pinch music and the pinch telop, then updates the background music.
void pinch_bgm_check(void) {
    if (PinchCheck() != 0) {
        if (gameState.unk_50[0x1] == 0) {
            gameState.unk_50[0x1] = 1;
            TelopRequest(0x4b4);
            KAKERA_U32(0x10) = (u16)func_020867cc();
        }
    } else {
        gameState.unk_50[0x1] = 0;
    }
    BgmSet();
}

// Copies the katti graphics of the current player's state (bits 2..3 of its base direction byte) to the screen.
typedef struct KattiDirBits {
    u8 b0 : 2;
    u8 kind : 2;
    u8 rest : 4;
} KattiDirBits;

void kattiUpdate(void) {
    u8 kind;

    kind = ((KattiDirBits *)(data_0212c53c + 0x3e))->kind;
    if (cockpitState[7] == kind) {
        return;
    }
    cockpitState[7] = kind;
    func_020845b0(0x6014200, KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), data_020f2530[cockpitState[7]]) + data_020f2524[cockpitState[7]], 0x180);
}
