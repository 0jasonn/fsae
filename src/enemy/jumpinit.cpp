#include "engine/functions.h"
#include "engine/player.h"
#include "game/knife_message.h"
#include "global.h"
#include "types.h"

// Functions in this file (module jump, the player-aimed jump setup):
//   jumpInit (0x02040be0)

extern const s8 data_020d319c[]; // two direction offsets, picked by the low bit of the timer

// Actor field at 0x64: the player the actor jumps towards
typedef struct Vars_JumpTarget {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *target;
} Vars_JumpTarget;
#define VJT(e) VARS(Vars_JumpTarget, e)

// Starts a jump towards a player: the target is the local player (single play) or the nearest living player
// (wireless), the direction follows the timer, and the jump sound plays.
ARM void jumpInit(Entity *e) {
    s32 dir;
    s32 found;
    s32 i;
    s32 count;
    u8 timer;

    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        VJT(e)->target = data_0212ceb0[Knife_Single_SinglePlay_GetInstance()[0]].entity;
        dir = func_02084fd0(e, VJT(e)->target);
        timer = e->timer;
        e->timer = timer + 1;
        e->direction = (data_020d319c[timer & 1] + dir) & 0x1f;
    } else {
        found = -1;
        if (VJT(e)->target->health == 0) {
            count = data_0212c7c8.unk_0;
            for (i = 0; i < count; i++) {
                if (data_0212ceb0[i].entity->health != 0) {
                    found = i;
                }
            }
            if (found != -1) {
                VJT(e)->target = data_0212ceb0[found].entity;
            }
        }
    }
    dir = func_02084fd0(e, VJT(e)->target);
    timer = e->timer;
    e->timer = timer + 1;
    e->direction = (data_020d319c[timer & 1] + dir) & 0x1f;
    e->zVelocity = 0x1c000;
    EnqueueSFX(0x31);
}
