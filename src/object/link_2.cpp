#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/objdecls.h"
#include "object/objdecls_d.h"

// Link actor, second unit (module link). Address -> name:
//   0x02072c70 link_kenfuri (original name, dispatches on e->subAction)
//   0x02072c8c kenfuri_init (original name)
//   0x02072d7c kenfuri_walk0 (original name)
//   0x02072ddc kenfuri_walk1 (original name)
//   0x02072e44 kenfuri_kenfuri (original name)
//   0x02072ef4 kenfuri_wait (original name)
//   0x02072f5c kenfuri_bunshin (original name)
//   0x02072fc8 kenfuri_wait2 is in scratch/agentD/nonmatching (near miss)

extern const EntityFunc kenfuri_subActions[]; // indexed by e->subAction
extern s32 data_02134924; // game flag word

ARM void link_kenfuri(Entity *e) {
    kenfuri_subActions[e->subAction](e);
}

ARM void kenfuri_init(Entity *e) {
    if (e->type == 0) {
        e->subAction++;
        e->direction = 0x1e;
        e->speed = 0x140;
        e->animationState = 0;
        e->timer = 0x1e;
        data_0212ceb0[e->type].unk_08 = 4;
    } else {
        e->subAction = 4;
        e->animationState = 4;
        data_0212ceb0[e->type].unk_08 = 0x1b1;
        e->spriteSettings.b30 = data_0212ceb0[0].entity->spriteSettings.b30;
        e->spriteSettings.b14 = data_0212ceb0[0].entity->spriteSettings.b14;
        e->spriteSettings.b0 = 0;
    }
    e->unk_5e.b0 = 3 - e->type;
    e->unk_2e = 3;
    e->unk_5e.b2 = 1;
}

ARM void kenfuri_walk0(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    func_02085934(e, e->unk_1b);
    MoveDir(e);
    if (e->y.HALF.HI >= 0xe2) {
        return;
    }
    e->y.HALF.HI = 0xe2;
    e->direction = 0x18;
    e->animationState = 6;
    e->subAction++;
}

ARM void kenfuri_walk1(Entity *e) {
    func_02085934(e, e->unk_1b);
    MoveDir(e);
    if (e->x.HALF.HI >= 0x80) {
        return;
    }
    e->x.HALF.HI = 0x80;
    e->animationState = 4;
    data_0212ceb0[e->type].unk_08 = 0;
    e->timer = 0x3c;
    e->subAction++;
}

ARM void kenfuri_kenfuri(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        if (e->timer != 0) {
            return;
        }
        data_0212ceb0[e->type].unk_08 = 0x1b1;
        SoundReq(0x228);
        data_02134924 |= 2;
        return;
    }
    if ((e->frame & 0x80) == 0) {
        func_02085934(e, e->unk_1b);
        return;
    }
    SoundReq(0x80040008);
    SoundReq(0x20);
    data_02134924 |= 4;
    e->subAction++;
}

ARM void kenfuri_wait(Entity *e) {
    if (e->type != 0) {
        if ((e->frame & 0x80) == 0) {
            func_02085934(e, e->unk_1b);
        }
        e->x.HALF.HI = data_0212ceb0[0].entity->x.HALF.HI;
        e->y.HALF.HI = data_0212ceb0[0].entity->y.HALF.HI;
    }
    if (data_02134924 & 8) {
        e->subAction++;
    }
}

ARM void kenfuri_bunshin(Entity *e) {
    e->spriteSettings.b0 = 1;
    ObjAnimMoveLine(e);
    if ((data_02134924 & 0x10) == 0) {
        return;
    }
    data_0212ceb0[e->type].unk_08 = 0;
    e->subAction++;
    e->spriteSettings.b0 = 1;
}
