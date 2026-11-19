#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "game/yousei.h"
#include "game/b_extra.h"
#include "engine/display_state.h"

// Yousei demo fade, 0x02081f14 to 0x02082054.
//   yousei_fade (0x02081f14): step 0 counts effectState.timer down, then starts the fade and moves to step 1;
//   step 1 waits for ZeldaFadeFlagGet, bumps the demo step, sets every player to state 3 and finishes the fade.
//   yousei_msgFinishWait (0x02082008): 1 while any player's message window (bit 12 of playerKeysPrev) is open.

extern u8 data_0212c4dc; // demo sub-step
extern u8 data_0212c500; // demo step
#include "engine/effect_state.h"
extern u16 playerKeysPrev[];

// yousei_fade (0x02081f14)
void yousei_fade(void) {
    u8 i;

    switch (data_0212c4dc) {
    case 0:
        effectState.timer = effectState.timer - 1;
        if (effectState.timer != 0) {
            return;
        }
        displayState.blendCnt = 0x3f40;
        displayState.blendAlpha = 0x70c;
        ZeldaFadeSet(NULL, 1);
        displayState.displayFlags = displayState.displayFlags | 0x1700;
        data_0212c4dc = data_0212c4dc + 1;
        return;
    case 1:
        if (ZeldaFadeFlagGet() == 0) {
            return;
        }
        data_0212c500 = data_0212c500 + 1;
        data_0212c4dc = 0;
        for (i = 0; i < gameState.playerCount; i++) {
            playerWork[i].state = 3;
        }
        ZeldaFadeFinish();
        return;
    }
}

// yousei_msgFinishWait (0x02082008)
int yousei_msgFinishWait(void) {
    u8 i;

    for (i = 0; i < gameState.playerCount; i++) {
        if (playerKeysPrev[i] & 0x1000) {
            return 1;
        }
    }
    return 0;
}
