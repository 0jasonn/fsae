#include "engine/functions.h"
#include "engine/player.h"
#include "game/scene.h"
#include "engine/misc.h"  // frameCounter.pauseRequest holds the request of the running pause
#include "global.h"

// pause_req_wait (0x02053aec): waits for the request delay (pauseState[2]) of a pause request to run out, then starts
// the pause (pause_start) unless the requesting player is holding the pause key or is down (iframes bit 7). Clears the
// pause request when the pause phase is not 2.
void pause_req_wait(void) {
    pauseState[2]--;
    if (pauseState[2] != 0) {
        return;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
        u8 requester = pauseState[3];
        if (!(playerKeysPrev[requester] & 0x1000)) {
            if ((s8)playerWork[requester].entity->iframes >= 0) {
                pause_start(requester);
            }
        }
    } else {
        if (!(playerKeysPrev[0] & 0x1000) || !(playerKeysPrev[1] & 0x1000)) {
            if ((s8)playerWork[0].entity->iframes >= 0 || (s8)playerWork[1].entity->iframes >= 0) {
                pause_start(0);
            }
        }
    }
    if (pauseState[0] != 2) {
        frameCounter.pauseRequest = 0;
        pauseState[0] = 0;
    }
}
