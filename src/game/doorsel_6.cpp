#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/enemy/ending.h"
#include "game/doorsel.h"

extern u16 playerKeys[];

// Button check of the door selection screen: A restarts the selection (state 5 for data_0212c500, effectState flag set),
// B counts the cancel, finishes the Zelda fade, plays 0x3f, starts a fade and sets the telop timer to 60 frames.
void ab_check(void) {
    if (playerKeys[0] & 1) {
        data_0212c500 = 5;
        data_0212c4dc = 0;
        effectState.unk_06[2] = 1;
        return;
    }
    if (playerKeys[0] & 2) {
        data_0212c4dc++;
        ZeldaFadeFinish();
        SoundReq(0x3f);
        FadeSet(3, 8);
        effectState.timer = 0x3c;
    }
}
