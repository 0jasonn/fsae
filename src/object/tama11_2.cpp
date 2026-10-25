#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/tama11.h"
#include "object/tama11_2.h"

// Tama11 actor, second unit (module tama11). Address -> name:
//   0x0207fe14 Tama11 (original name Tama11(OBJ_WORK_*))
//   tama11_init (0x0207fe64) and tama11_move0 (0x0207ff4c) are parked in scratch/agentC/nonmatching

// Entity sprite settings word (0x1c)
#define SPRITE_WORD(e) (*(u32 *)&(e)->spriteSettings)

// Runs the state table entry of the actor; once the parent is gone (health 0) the actor is removed
ARM void Tama11(Entity *e) {
    Entity *parent;

    data_020dcfd4[e->action](e);
    parent = e->parent;
    if (parent == NULL || e->health == 0) {
        return;
    }
    if (parent->health != 0) {
        return;
    }
    HajikeSet(e);
    PutObjWork(e);
}

