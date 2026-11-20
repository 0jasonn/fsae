#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/commframe_sync.h"
#include "knife/comm/commupdatejoy.h"
#include "engine/data_0212c500.h"
#include "game/keyclear_api.h"
#include "engine/display_state.h"
#include "engine/effect_state.h"

// Functions in this file (module doorsel, third unit; doorsel.cpp and doorsel_2.cpp hold the others):
//   doorsel_shutter (doorsel_shutter())

// The shutter steps are kept in data_0212c4dc: 0 starts the shutter with a 30 frame timer, 1 counts it down and
// closes, 2 runs the shutter frames until the display shadow reaches 0x60, then advances data_0212c500.
// Timer: effectState.timer. Shadow: displayState.bg[1].scrollY.

// doorsel_shutter (0x0202adc8)
void doorsel_shutter(void) {
    u8 step = data_0212c4dc;

    switch (step) {
    case 0:
        effectState.timer = 0x1e;
        data_0212c4dc = step + 1;
        break;
    case 1:
        effectState.timer = effectState.timer - 1;
        if (effectState.timer != 0) {
            return;
        }
        data_0212c4dc = step + 1;
        keyClear();
        effectState.timer = 0;
        SoundReq(0x7c);
        break;
    case 2:
        if (CommFrameSync() == 0) {
            return;
        }
        CommUpdateJoy();
        effectState.timer = effectState.timer + 1;
        if (effectState.timer & 1) {
            displayState.bg[1].scrollY = displayState.bg[1].scrollY + 1;
        }
        if (playerKeys[0] & 1) {
            displayState.bg[1].scrollY = 0x60;
        }
        if (displayState.bg[1].scrollY > 0x60) {
            data_0212c500 = data_0212c500 + 1;
            data_0212c4dc = 0;
            SoundReq(0x7d);
        }
        CommFrameUpdate();
        break;
    }
}
