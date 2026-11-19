#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"
#include "engine/irq.h"

// Functions in this file (module cockpit, original names from the debug build):
//   heartAlart, PinchCheck, pinch_bgm_check, kattiUpdate

// Plays the heart alarm (sound 0x25) when the alarm timer is clear and the heart block is at most 0x10.
void heartAlart(void) {
    if ((frameState.frameCount & 0x3f) != 0 || frameCounter.pauseRequest != 0) {
        return;
    }
    if (cockpitState.hearts > 0x10) {
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
        if (playerWork[i].entity->health != 0 && playerWork[i].entity->health <= 0x10) {
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
            telopRequest.params[2] = (u16)func_020867cc();
        }
    } else {
        gameState.unk_50[0x1] = 0;
    }
    BgmSet();
}

// Copies the katti graphics of the current player's state (nutBits.b2 of the current player) to the screen.

void kattiUpdate(void) {
    u8 kind;

    kind = data_0212c53c->nutBits.b2;
    if (cockpitState.kattiKind == kind) {
        return;
    }
    cockpitState.kattiKind = kind;
    func_020845b0(0x6014200, KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), data_020f2530[cockpitState.kattiKind]) + data_020f2524[cockpitState.kattiKind], 0x180);
}
