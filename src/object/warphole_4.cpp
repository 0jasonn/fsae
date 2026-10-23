#include "engine/functions.h"
#include "global.h"
#include "object/protos.h"

// Warp hole actor, first unit after warphole_init (module warphole). Address -> name:
//   0x0205dec8 warphole_wait (original name)
//   0x0205df74 warphole_move (original name)
//   (warphole_init at 0x0205de50 is in scratch/agentF/nonmatching; pos_copy at 0x0205e05c is in warphole_2.cpp)

ARM void warphole_wait(Entity *e) {
    u8 *resource;
    u8 kind;

    if (e->timer == 0) {
        if (VGroupLoadWait(e)) {
            return;
        }
        resource = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x9a);
        kind = data_0212c7c8[1];
        if (kind >= 5) {
            if (kind == 5) {
                func_020845b0(0x6400000 + ((e->unk_53 + 1) << 9), resource + 0x400, 0x100);
            } else if (kind == 6) {
                func_020845b0(0x6400000 + ((e->unk_53 + 1) << 9), resource + 0x500, 0x100);
            }
        } else {
            func_020845b0(0x6400000 + ((e->unk_53 + 1) << 9), resource + (kind << 8), 0x100);
        }
        e->spriteSettings.b0 = 1;
        e->action = e->action + 1;
    } else {
        e->timer--;
    }
}

ARM void warphole_move(Entity *e) {
    u8 playerMask;

    UpdateAnimationSingleFrame(e);
    if (data_0212c7c8[0x6e] >= 2) {
        e->action = e->action + 1;
        return;
    }
    playerMask = func_02084110(e);
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0 && playerMask == 3) {
        playerMask = 1;
    }
    if (CountBits(playerMask) == 1) {
        if (e->type2 != data_0212c7c8[0x4f]) {
            data_0212c7c8[0x6f] = 0;
            data_0212c7c8[0x4f] = e->type2;
        }
        data_0212c7c8[0x6f] |= playerMask;
        Knife_Single_SinglePlay_SetWarpInfo(Knife_Single_SinglePlay_GetInstance(), data_0212c7c8[0x6f], data_0212c7c8[0x4f]);
        if (e->subtimer == 0) {
            EnqueueSFX(0x18);
            e->spriteSettings.b16 = 1;
        }
        e->subtimer = 1;
    } else {
        if (e->subtimer == 1) {
            e->spriteSettings.b16 = 0;
        }
        e->subtimer = 0;
    }
}
