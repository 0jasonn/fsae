#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"

// Set2b actor (module set2b). Address -> name:
//   0x0205a594 Set2b (original name)

typedef struct Vars_Set2b {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u16 lifeTimer; // 0x258 at start, the actor is removed when it reaches 0
} Vars_Set2b;

void Set2b(Entity *e) {
    Entity *templ = data_0212ceb0[e->type].entity;
    u16 lifeTimer;
    u8 timer;
    u8 subtimer;
    int offset;
    Entity *child;

    if (e->action != 0) {
        lifeTimer = VARS(Vars_Set2b, e)->lifeTimer;
        VARS(Vars_Set2b, e)->lifeTimer = lifeTimer - 1;
        if (lifeTimer != 0) {
            templ->spriteSettings.b0 = 1;
            timer = e->timer;
            e->timer = timer - 1;
            if (timer == 0) {
                templ->spriteSettings.b0 = templ->spriteSettings.b0 ^ 1;
                e->timer = 5;
                if (VARS(Vars_Set2b, e)->lifeTimer < 0x12c) {
                    e->timer = 0xa;
                    if (VARS(Vars_Set2b, e)->lifeTimer < 0xb4) {
                        e->timer = 0x14;
                    }
                }
            }
            subtimer = e->subtimer;
            e->subtimer = subtimer - 1;
            if (subtimer == 0) {
                e->subtimer = 3;
                if (VARS(Vars_Set2b, e)->lifeTimer < 0x12c) {
                    e->subtimer = 0xa;
                    if (VARS(Vars_Set2b, e)->lifeTimer < 0xb4) {
                        e->subtimer = 0x14;
                    }
                }
                child = GetSetWork(0xf, 7, 0);
                if (child != NULL) {
                    offset = Random() & 0xf;
                    if (Random() & 1) {
                        offset = -offset;
                    }
                    child->x.HALF.HI = templ->x.HALF.HI + offset;
                    offset = Random() & 0xf;
                    if (Random() & 1) {
                        offset = -offset;
                    }
                    child->y.HALF.HI = templ->y.HALF.HI + offset;
                }
            }
            data_0212ceb0[e->type].statusFlags |= 2;
            templ->unk_40 = 0xf;
            templ->attackKnockback = 0xc;
        } else {
            templ->spriteSettings.b0 = 1;
            PutObjWork(e);
            return;
        }
    } else {
        e->action++;
        e->timer = 0xa;
        e->subtimer = 0x14;
        VARS(Vars_Set2b, e)->lifeTimer = 0x258;
        return;
    }
}
