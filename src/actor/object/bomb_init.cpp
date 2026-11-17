#include "engine/functions.h"
#include "global.h"
#include "actor/object/bomb.h"
#include "actor/object/bomb_init.h"

// Bomb actor setup: starts the fuse (timer 0xf0, or 0xf for the immediate types), sets the hitbox, and spawns the
// helper object that carries the fuse timer.

typedef struct Vars_BombFuse {
    u8 unk_00[0x64];
    u16 fireTimer;
} Vars_BombFuse;

void bomb_init(Entity *e) {
    Entity *child;

    e->spriteSettings.b0 = 1;
    e->action++;
    e->unk_2e = 4;
    if (e->type == 0xff) {
        e->timer = 0xf;
    } else if (e->type == 0xfe) {
        e->timer = 0xf;
        e->type = 0xff;
    } else {
        e->timer = 0xf0;
    }
    e->unk_40 = 0x16;
    e->attackDamage = 8;
    e->attackKnockback = 0xc;
    e->statusFlags = 8;
    e->hitbox = bomb_hitbox;
    e->poseId = 0xb;
    e->unk_20 = 0xce;
    e->spriteSettings.b6 = 3;
    e->spriteSettings.b20 = 1;
    e->spriteSettings.b16 = e->spriteSettings.b20;
    e->unk_1b = 9;
    e->unk_1a = 0;
    InitAnimationForceUpdate(e, 5);
    child = GetObjWork();
    if (child != NULL) {
        child->parent = e;
        child->objId = 4;
        child->objKind = 8;
        VARS(Vars_BombFuse, child)->fireTimer = 1;
        child->type = 0xff;
        RegistObjWork(2, child);
    }
}
