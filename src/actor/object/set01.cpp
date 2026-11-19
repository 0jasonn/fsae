#include "engine/functions.h"
#include "actor/object/set01.h"
#include "global.h"

// Set01 actor (module set01). Address -> name:
//   0x02058d50 Set01 (original name)
//   0x02058d6c set01_init (original name)
//   0x02058e7c set01_spawnRandom: not matching yet, see scratch/agentF/nonmatching

void Set01(Entity *e) {
    set01_actions[e->action](e);
}

void set01_init(Entity *e) {
    Entity *child;
    if ((e->type2 & 1) != 0) {
        e->action = 2;
        e->timer = 0x1e;
        e->subtimer = 8;
        SoundReq(0x80010000);
        SoundReq(0x2e);
        if (gameState.frameCount < 0xe10) {
            VSET01(e)->stageLevel = 3;
            return;
        }
        if (gameState.frameCount < 0x2a30) {
            VSET01(e)->stageLevel = 2;
            return;
        }
        if (gameState.frameCount < 0x4650) {
            VSET01(e)->stageLevel = 1;
        }
        return;
    }
    e->action = 1;
    e->spriteSettings.b0 = 1;
    if (e->timer != 0xff) {
        e->timer = (u32)e->timer % gameState.playerCount; // unsigned divide in the original
    }
    InitAnimationForceUpdate(e, 0);
    EnqueueSFX(5);
    if (e->type == 0x12) {
        e->spriteSettings.b0 = 0;
        child = GetSetWork(0x20, 0, 0);
        if (child != NULL) {
            ObjPosCopy(e, child);
        }
    }
}

void set01_spawnRandom(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 0x80) {
        if (e->timer < 4) {
            u8 randomIndex = Random() & 0x1f;
            u8 slot = data_020f26dc[data_020d410c[e->type]][data_0212c81c[e->timer]][randomIndex];
            if (slot != 0xff && e->type2 == 0) {
                Entity *child = GetSetWork(0, slot, 1);
                if (child != NULL) {
                    ObjPosCopy(e, child);
                }
            }
        }
        PutObjWork(e);
    }
}

// Set01 actor, second unit (module set01). Address -> name:
//   0x02058f18 set01_boss (original name)

extern const s8 data_021154f4[]; // (dx, dy) pairs, indexed by subtimer, moved to the child each frame

void set01_boss(Entity *e) {
    Entity *child;

    if (e->timer == 0) {
        child = GetSetWork(0xf, 1, 0x20);
        if (child == NULL) {
            return;
        }
        e->timer = 10;
        e->subtimer--;
        if (e->subtimer == 0) {
            e->action = 3;
            e->timer = 2;
            SoundReq(0x10);
            PutObjWork(e->child);
        }
        ObjPosCopyOfs32(e, child, data_021154f4[e->subtimer * 2] << 16, data_021154f4[e->subtimer * 2 + 1] << 16);
    } else {
        e->timer--;
    }
}
