#include "engine/functions.h"
#include "object/set01.h"
#include "global.h"

// Set01 actor (module set01). Address -> name:
//   0x02058d50 Set01 (original name)
//   0x02058d6c set01_init (original name)
//   0x02058e7c set01_spawnRandom: not matching yet, see scratch/agentF/nonmatching

ARM void Set01(Entity *e) {
    set01_actions[e->action](e);
}

ARM void set01_init(Entity *e) {
    Entity *child;
    if ((e->type2 & 1) != 0) {
        e->action = 2;
        e->timer = 0x1e;
        e->subtimer = 8;
        SoundReq(0x80010000);
        SoundReq(0x2e);
        if (((u32 *)&data_0212c7c8)[7] < 0xe10) {
            VSET01(e)->stageLevel = 3;
            return;
        }
        if (((u32 *)&data_0212c7c8)[7] < 0x2a30) {
            VSET01(e)->stageLevel = 2;
            return;
        }
        if (((u32 *)&data_0212c7c8)[7] < 0x4650) {
            VSET01(e)->stageLevel = 1;
        }
        return;
    }
    e->action = 1;
    e->spriteSettings.b0 = 1;
    if (e->timer != 0xff) {
        e->timer = (u32)e->timer % data_0212c7c8.unk_0; // unsigned divide in the original
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
