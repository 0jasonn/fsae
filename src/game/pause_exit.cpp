#include "engine/functions.h"
#include "game/scene.h"
#include "engine/misc.h"  // frameCounter.pauseRequest holds the request of the running pause
#include "global.h"

// pause_exit (0x0205420c): waits for the exit choice of the pause dialog. CommJoyCheck of the three keys (0xd0, 0xe0,
// 0x70) selects option 1, 2 or 3 in pauseState[1]; when the delay (pauseState[2]) runs out the chosen option plays its
// sound and starts a white-out (1, 2) or fade-out (3) and advances the pause phase by the option number. Without a
// choice the pause request is cleared.
void pause_exit(void) {
    u8 fadeSpeed;
    if (CommJoyCheck(0xd0)) {
        pauseState[1] = 1;
    }
    if (CommJoyCheck(0xe0)) {
        pauseState[1] = 2;
    }
    if (CommJoyCheck(0x70)) {
        pauseState[1] = 3;
    }
    keyDisable();
    if (--pauseState[2] != 0) {
        return;
    }
    if (pauseState[1] != 0) {
        SoundReq(0x80040000);
        if (pauseState[1] == 1) {
            fadeSpeed = 8;
            FadeSet(3, fadeSpeed);
            eff_white_out_init(fadeSpeed + 0x880);
            pauseState[0] += 1;
        } else if (pauseState[1] == 2) {
            fadeSpeed = 8;
            FadeSet(3, fadeSpeed);
            eff_white_out_init(fadeSpeed + 0x880);
            pauseState[0] += 2;
        } else if (pauseState[1] == 3) {
            fadeSpeed = 8;
            FadeSet(1, fadeSpeed);
            eff_fade_out_init(fadeSpeed + 0x880);
            pauseState[0] += 3;
        }
    } else {
        frameCounter.pauseRequest = 0;
        pauseState[0] = 0;
        pauseState[0xe] = 0;
    }
}
