#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (actor em1d, original names from the debug build; em1d_aimmove and em1d_rndmove are in scratch/agentB/unfinished/em1d_3.cpp until functions.h declares func_020847f8 as int):
//   em1d_buttobi, em1d_init, em1d_getdir

extern "C" Entity *gieniGetAimPl(void);   // original gieniGetAimPl()
extern "C" void func_02084794(Entity *e); // no original name yet
void seqset(Entity *e, int baseAnim);      // original seqset(OBJ_WORK_*, int)
extern const u8 em1d_hitbox[];

// Buttobi: updates the animation frame and, when the entity is flagged and not in action 4, restarts its animation.
ARM void em1d_buttobi(Entity *e) {
    UpdateAnimationSingleFrame(e);
    func_02084794(e);
    if (e->unk_42 != 1) {
        return;
    }
    if (e->action == 4) {
        return;
    }
    InitAnimationForceUpdate(e, e->animationState);
}

// Init: sets the first action, the hitbox and the start height, then starts the animation.
ARM void em1d_init(Entity *e) {
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 4;
    e->hitbox = em1d_hitbox;
    e->z.HALF.HI = -4;
    InitAnimationForceUpdate(e, 0);
}

// Getdir: sets a timer and either starts a chase towards the aim player, facing it, or walks away with a short speed.
ARM void em1d_getdir(Entity *e) {
    func_020847f8(e);
    e->timer = 0xb4;
    if ((Random() & 0xf) < 7) {
        e->action = 2;
        e->speed = 0x100;
        e->child = gieniGetAimPl();
        e->direction = GetFacingDirection(e, e->child);
        seqset(e, 2);
        return;
    }
    e->action = 3;
    e->subtimer = 0x2d;
    e->speed = 0x60;
    seqset(e, 0);
}
