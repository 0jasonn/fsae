#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "actor/enemy/comm_check.h"
#include "knife/comm/commupdatejoy.h"

// CommUpdateJoy (0x02029650): copies the keys received for the current communication frame and keeps the keys that
// were pressed this frame (all zero while the frame counter is below 8).
void CommUpdateJoy(void) {
    u32 pressed;
    u16 keys;
    s32 mode;
    u16 player;

    func_020909c8();
    mode = data_0212c538;
    for (player = 0; player < 4; player++) {
        keys = data_02134cb0[((mode - 3) & 0xf) + player * 0x10] & 0x1fff;
        if (mode < 8) {
            pressed = 0;
        } else {
            pressed = keys & ~playerKeysPrev[player];
        }
        playerKeys[player] = pressed;
        playerKeysPrev[player] = keys;
    }
}
