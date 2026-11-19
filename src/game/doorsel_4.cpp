#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/doorsel_4.h"

// Door select screen, selection step (0x0202af70). data_0212c4dc is the sub-step. effectState holds
// the selected entry (selection), the number of entries (entryCount) and the timer.

// doorsel_select (0x0202af70): step 0 sets up the sprite work of the screen, step 1 moves the cursor with left and right
// (wrapping, 3 entries; with 2 entries it toggles) or calls ab_check, step 2 counts the timer down and then returns
// to the task chain.
void doorsel_select(void) {
    EffectState *state = &effectState;
    s32 selection;

    switch (data_0212c4dc) {
    case 0:
        data_0212c4dc = data_0212c4dc + 1;
        if (state->entryCount == 3) {
            displayState.displayFlags = displayState.displayFlags & 0xfdff;
        }
        GetSetWork(0x31, 3, 0);
        GetSetWork(0x31, 3, 2);
        GetSetWork(0x31, 3, 1);
        if (localPlayerIndex != 0) {
            GetSetWork(0x31, 0xe, 0);
        } else {
            GetSetWork(0x31, 0xc, 0);
            GetSetWork(0x31, 0xd, 0);
            GetSetWork(0x31, 0xf, 0);
            GetSetWork(0x31, 0x10, 0);
            GetSetWork(0x31, 0x10, 1);
            GetSetWork(0x31, 0x10, 2);
        }
        keyClear();
        break;
    case 1:
        if (CommFrameSync() == 0) {
            return;
        }
        CommUpdateJoy();
        if (state->entryCount >= 2) {
            if (playerKeys[0] & 0x20) {
                if (state->entryCount == 2) {
                    selection = 2;
                    if (state->selection != 0) {
                        selection = 0;
                    }
                } else {
                    selection = state->selection + 1;
                    if (state->selection >= 2) {
                        selection = 0;
                    }
                }
                state->selection = selection;
                SoundReq(0x3d);
            } else if (playerKeys[0] & 0x10) {
                if (state->entryCount == 2) {
                    selection = 2;
                    if (state->selection != 0) {
                        selection = 0;
                    }
                } else {
                    selection = state->selection - 1;
                    if (state->selection == 0) {
                        selection = 2;
                    }
                }
                state->selection = selection;
                SoundReq(0x3d);
            } else {
                ab_check();
            }
        } else {
            ab_check();
        }
        CommFrameUpdate();
        break;
    case 2:
        if (CommFrameSync() == 0) {
            return;
        }
        CommUpdateJoy();
        state->timer = state->timer - 1;
        if (state->timer == 0) {
            DispReset();
            func_0202809c();
            Task_Chain(5);
            return;
        }
        CommFrameUpdate();
        break;
    }
}
