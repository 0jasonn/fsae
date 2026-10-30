#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// Set35 family (module set35). Address -> name:
//   0x0206b124 set35_move (original name)

extern u16 data_0212c584[];       // per-player flag halfwords, bit 12 tested
extern u8 data_0212c4f4;          // counter compared against 0x70 before the spawn
extern u8 frameCounter[];         // u16 frame counter at 0, read as halfword
extern const s8 data_02115d38[];  // direction jitter table, indexed by Random() & 7
extern u8 data_0212cebf[];        // PlayerData byte 0x0f (0x94 stride)

typedef struct Vars_Set35 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ s32 homeX;      // rest position written back to the actor
    /* 64 */ s32 homeY;
    /* 68 */ s32 cycleCounter; // counts down once per 60 subtimer ticks
    /* 6c */ u32 frameTicks;   // incremented while the actor is active
} Vars_Set35;

ARM void set35_move(Entity *e) {
    Vars_Set35 *v = VARS(Vars_Set35, e);
    Entity *contacted;
    Entity *spawned;
    u8 timerStart;

    if (e->contactFlags & 0x80) {
        if (!(KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0 && e->contactedEntity->objKind == 1 &&
              (data_0212c584[e->contactedEntity->type] & 0x1000) != 0 &&
              data_0212cebf[e->contactedEntity->type * 0x94] == 0)) {
            timerStart = 0x1e;
            e->timer = timerStart;
            contacted = e->contactedEntity;
            contacted->baseDirection = (contacted->baseDirection + data_02115d38[Random() & 7]) & 0x1f;
            e->attackKnockback = (s8)(timerStart - 0x2e - (Random() & 7));
            e->iframes = 0xfc;
            if (!(data_0212c584[e->contactedEntity->type] & 0x1000) && e->type == 1) {
                if (data_0212c4f4 < 0x70) {
                    s32 kind = 1;
                    e->type2 = 1;
                    if (v->frameTicks >= 0x12c) {
                        if (v->frameTicks < 0x1e0) {
                            kind = 2;
                        } else {
                            kind = 3;
                            if (v->frameTicks >= 0x384) {
                                kind = 8;
                            }
                        }
                    }
                    spawned = GetSetWork(0, (u8)kind, 1);
                    if (spawned != 0) {
                        ObjPosCopy(e, spawned);
                        spawned->direction = (Random() & 0x1f) | 0x80;
                    }
                }
            }
            EnqueueSFX(0x8c);
        }
    }

    if (e->type == 1 && e->type2 != 0) {
        e->subtimer--;
        if (e->subtimer == 0) {
            e->subtimer = 0x3c;
            v->cycleCounter = v->cycleCounter - 1;
        }
        v->frameTicks++;
        if (v->cycleCounter == 0) {
            e->type = 0;
            InitAnimationForceUpdate(e, 0);
        }
    }

    if (e->timer != 0) {
        e->timer--;
        if (((u16 *)frameCounter)[0] & 3) {
            return;
        }
        e->x.HALF.HI = v->homeX + (Random() & 3) - 2;
        e->y.HALF.HI = v->homeY + (Random() & 3) - 2;
    } else {
        e->x.HALF.HI = v->homeX;
        e->y.HALF.HI = v->homeY;
    }
}
