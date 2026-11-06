#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "types.h"
#include "knife/app/knife_hud.h"

// Functions in this file (module cockpit, original names from the debug build):
//   cockpit_call_check (cockpit_call_check()), cockpit_obj_trans (cockpit_obj_trans(unsigned char))

extern u16 playerKeys[]; // flags per player, bit 0x400 set while the player is active
extern u16 playerKeysPrev[]; // flags per player, bit 0x1000 blocks the call animation
extern u8 messageRequest[];
extern u8 frameCounter[];
extern u8 data_0212c4a0[];
extern u8 cockpitState[];

// cockpit_call_check (0x02027bd0): starts the call animation of the player that asks for it. Single play uses the
// active player of the single play block; wireless play checks every player.
void cockpit_call_check(void) {
    void *knife;
    Knife::Hud::HudManager *hud;
    u8 *single;
    u8 requestMode;
    s32 i;

    knife = KnifeApp_getInstance();
    single = Knife_Single_SinglePlay_GetInstance();
    hud = (Knife::Hud::HudManager *)((u8 *)knife + 0x1f8);
    if (KnifeApp_isWirelessMode(knife) == 0) {
        if (single[1] == 0) {
            hud->setActivePlayer(single[0]);
        } else {
            hud->setActivePlayer(-1);
        }
        if ((playerKeys[0] & 0x400) == 0) {
            return;
        }
        requestMode = messageRequest[0] & 0x7f;
        if (requestMode != 0 || frameCounter[0x14] != 0 || frameCounter[0x11] != 0) {
            return;
        }
        if (playerWork[single[0]].callState != 0) {
            return;
        }
        if (hud->startCallAnim(single[0]) == 0) {
            return;
        }
        SoundReq(0x232);
        return;
    }
    for (i = 0; i < gameState.playerCount; i++) {
        if ((playerKeys[i] & 0x400) == 0) {
            continue;
        }
        if ((playerKeysPrev[i] & 0x1000) == 0 && frameCounter[0x14] == 0 && frameCounter[0x11] == 0 &&
            playerWork[i].callState == 0) {
            if (hud->startCallAnim(i) != 0) {
                SoundReq(0x232);
            }
        }
    }
    hud->setActivePlayer(0);
}

// cockpit_obj_trans (0x02027d44): runs the call check, advances the frame counter at data_0212c4a0 + 4 (modulo 0x30) and
// sets the two HUD slots from the item indices, then updates the HUD with mode.
void cockpit_obj_trans(u8 mode) {
    void *knife;
    Knife::Hud::HudManager *hud;

    knife = KnifeApp_getInstance();
    Knife_Single_SinglePlay_GetInstance();
    cockpit_call_check();
    *(u32 *)(data_0212c4a0 + 4) = (*(u32 *)(data_0212c4a0 + 4) + 1) % 0x30;
    hud = (Knife::Hud::HudManager *)((u8 *)knife + 0x1f8);
    hud->setField70(0, cockpitState[0xc]);
    hud->setField70(1, cockpitState[0x2c]);
    hud->update(mode);
}
