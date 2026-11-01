#include "engine/functions.h"
#include "global.h"
#include "object/protos.h"
#include "object/warphole.h"
#include "engine/player.h"

// Warp hole actor, first unit after warphole_init (module warphole). Address -> name:
//   0x0205dec8 warphole_wait (original name)
//   0x0205df74 warphole_move (original name)
//   (warphole_init at 0x0205de50 is in scratch/agentF/nonmatching; pos_copy at 0x0205e05c is in warphole_2.cpp)

void warphole_wait(Entity *e) {
    u8 *resource;
    u8 kind;

    if (e->timer == 0) {
        if (VGroupLoadWait(e)) {
            return;
        }
        resource = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x9a);
        kind = data_0212c7c8.unk_01;
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

void warphole_move(Entity *e) {
    u8 playerMask;

    UpdateAnimationSingleFrame(e);
    if (data_0212c7c8.unk_6e >= 2) {
        e->action = e->action + 1;
        return;
    }
    playerMask = func_02084110(e);
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0 && playerMask == 3) {
        playerMask = 1;
    }
    if (CountBits(playerMask) == 1) {
        if (e->type2 != data_0212c7c8.phaseFlags) {
            data_0212c7c8.unk_6f = 0;
            data_0212c7c8.phaseFlags = e->type2;
        }
        data_0212c7c8.unk_6f |= playerMask;
        Knife_Single_SinglePlay_SetWarpInfo(Knife_Single_SinglePlay_GetInstance(), data_0212c7c8.unk_6f, data_0212c7c8.phaseFlags);
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

// Warp hole actor, second unit (module warphole). Address -> name:
//   0x0205e05c pos_copy (original name)
//   (warphole_wait2 at 0x0205e078 and warphole_exit at 0x0205e114 are in the next units)

void pos_copy(Entity *src, Entity *dst) {
    dst->x.WORD = src->x.WORD;
    dst->y.WORD = src->y.WORD;
    dst->z.HALF.HI = 0;
}

// Warp hole actor, third unit (module warphole). Address -> name:
//   0x0205e078 warphole_wait2 (original name)
//   (pos_copy at 0x0205e05c is in warphole_2.cpp; warphole_exit at 0x0205e114 is in warphole_3.cpp)

void warphole_wait2(Entity *e) {
    u8 flag;
    Entity *target;

    if (data_0212c7c8.unk_6e >= 3 && data_0212c7c8.phaseFlags == e->type2) {
        flag = 0;
        e->action = e->action + 1;
        e->spriteSettings.b16 = 1;
        InitAnimationForceUpdate(e, flag);
        if ((func_02084110(e) & 1) == 0) {
            flag = 1;
        }
        target = GetSetWork(0x42, flag, 0);
        if (target != NULL) {
            ObjPosCopy(e, target);
        }
    } else {
        UpdateAnimationSingleFrame(e);
    }
    warphole_exit(e);
}

// Warp hole actor, third unit (module warphole). Address -> name:
//   0x0205e114 warphole_exit (original name)

void warphole_exit(Entity *e) {
    int players = func_02084110(e);

    if (players & 1) {
        pos_copy(e, data_0212ceb0[0].entity);
    }
    if (players & 2) {
        pos_copy(e, data_0212ceb0[1].entity);
    }
    if (players & 4) {
        pos_copy(e, data_0212ceb0[2].entity);
    }
    if (players & 8) {
        pos_copy(e, data_0212ceb0[3].entity);
    }
}
