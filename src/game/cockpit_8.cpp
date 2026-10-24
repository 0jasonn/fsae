#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/hud.h"

// Functions in this file (module cockpit, original names from the debug build):
//   cockpit_call_check (cockpit_call_check()), cockpit_obj_trans (cockpit_obj_trans(unsigned char))

extern u16 data_0212c58c[]; // flags per player, bit 0x400 set while the player is active
extern u16 data_0212c584[]; // flags per player, bit 0x1000 blocks the call animation
extern u8 data_0212ceb0[];  // PlayerData block, 0x94 bytes per player, state byte at +0x3c
extern u8 data_0212ceec[];  // the same state bytes, a separate symbol at data_0212ceb0 + 0x3c
extern u8 messageRequest[];
extern u8 frameCounter[];
extern u8 data_0212c7c8[];
extern u8 data_0212c4a0[];
extern u8 data_0212c618[];

// cockpit_call_check (0x02027bd0): starts the call animation of the player that asks for it. Single play uses the
// active player of the single play block; wireless play checks every player.
ARM void cockpit_call_check(void) {
    void *knife;
    void *hud;
    u8 *single;
    u8 requestMode;
    s32 i;

    knife = KnifeApp_getInstance();
    single = Knife_Single_SinglePlay_GetInstance();
    hud = (u8 *)knife + 0x1f8;
    if (KnifeApp_isWirelessMode(knife) == 0) {
        if (single[1] == 0) {
            Knife_Hud_HudManager_setActivePlayer(hud, single[0]);
        } else {
            Knife_Hud_HudManager_setActivePlayer(hud, -1);
        }
        if ((data_0212c58c[0] & 0x400) == 0) {
            return;
        }
        requestMode = messageRequest[0] & 0x7f;
        if (requestMode != 0 || frameCounter[0x14] != 0 || frameCounter[0x11] != 0) {
            return;
        }
        if (data_0212ceec[single[0] * 0x94] != 0) {
            return;
        }
        if (Knife_Hud_HudManager_startCallAnim(hud, single[0]) == 0) {
            return;
        }
        SoundReq(0x232);
        return;
    }
    for (i = 0; i < data_0212c7c8[0]; i++) {
        if ((data_0212c58c[i] & 0x400) == 0) {
            continue;
        }
        if ((data_0212c584[i] & 0x1000) == 0 && frameCounter[0x14] == 0 && frameCounter[0x11] == 0 &&
            data_0212ceb0[i * 0x94 + 0x3c] == 0) {
            if (Knife_Hud_HudManager_startCallAnim(hud, i) != 0) {
                SoundReq(0x232);
            }
        }
    }
    Knife_Hud_HudManager_setActivePlayer(hud, 0);
}

// cockpit_obj_trans (0x02027d44): runs the call check, advances the frame counter at data_0212c4a0 + 4 (modulo 0x30) and
// sets the two HUD slots from the item indices, then updates the HUD with mode.
ARM void cockpit_obj_trans(u8 mode) {
    void *knife;
    void *hud;

    knife = KnifeApp_getInstance();
    Knife_Single_SinglePlay_GetInstance();
    cockpit_call_check();
    *(u32 *)(data_0212c4a0 + 4) = (*(u32 *)(data_0212c4a0 + 4) + 1) % 0x30;
    hud = (u8 *)knife + 0x1f8;
    func_0209e788(hud, 0, data_0212c618[0xc]);
    func_0209e788(hud, 1, data_0212c618[0x2c]);
    Knife_Hud_HudManager_update(hud, mode);
}
