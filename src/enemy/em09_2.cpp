#include "engine/functions.h"
#include "enemy/em09.h"
#include "global.h"

// Function names (dsd -> name), also in scratch/agentA/renames.txt:
// em09_wait2 em09_wait2, em09_type2_init em09_type2_init, em09_type2_move em09_type2_move,
// em09_seqSet em09_seqSet, seqMove seqMove, kuttsukiReset kuttsukiReset,
// em09_kuttsuki_reset em09_kuttsuki_reset, Boss_RunStateTable Boss_RunStateTable, em10_normal em10_normal

ARM void em09_wait2(Entity *e) {
    u8 action;
    if (--e->subtimer == 0) {
        action = e->action;
        e->timer = 1;
        e->action = action - 2;
    }
    seqMove(e);
}

ARM void em09_type2_init(Entity *e) {
    Tbl3 table;
    e->spriteSettings.b20 = data_020d1d90[e->type];
    e->spriteSettings.b16 = e->spriteSettings.b20;
    if (*((u8 *)&data_0212c7c8 + 0x8e) == 2) {
        table = *(Tbl3 *)data_020d1d88;
        e->spriteSettings.b20 = table.v[e->type];
        e->spriteSettings.b16 = e->spriteSettings.b20;
    }
    e->unk_2e = 0;
    e->unk_20 = VBT(e->parent)->unk_7e;
    e->spriteSettings.b6 = (VBT(e->parent)->unk_7e & 0xff00) >> 8;
    e->unk_1b = 0x2c;
    e->action++;
}

ARM void em09_type2_move(Entity *e) {
    if (VPW(e->parent)->unk_04 == 0) {
        PutObjWork(e);
    }
}

ARM void em09_seqSet(Entity *e) {
    u8 anim = EmCharDir2(e->direction);
    if (anim != 0xff && anim != e->animationState) {
        e->animationState = anim;
        InitAnimationForceUpdate(e, anim);
        InitAnimationForceUpdate(e->parent, anim + 3);
    }
}

ARM void seqMove(Entity *e) {
    UpdateAnimationSingleFrame(e);
    UpdateAnimationSingleFrame(e->parent);
}

ARM void kuttsukiReset(Entity *e) {
    data_0212ceb0[e->child->type].unk_02 = 0x41;
    data_0212ceb0[e->child->type].unk_0a[0] = 0;
    data_0212ceb0[e->child->type].unk_36 &= 0xffef;
    e->child->zVelocity = 0x18000;
    e->child->unk_3c |= 0x80;
    e->child->iframes = 0xdc;
    e->child->z.HALF.HI = 0;
    e->child->unk_2e = VBT(e)->unk_78;
    e->child->direction = e->child->animationState << 2;
    e->unk_5c = 0x21ff;
    e->action++;
    e->subtimer = 0x3c;
    if (e->iframes == 0) {
        e->iframes = 0xf4;
    }
}

ARM void em09_kuttsuki_reset(Entity *e) {
    if (e->action == 4) {
        kuttsukiReset(e);
    }
}

ARM void Boss_RunStateTable(Entity *e) {
    EnemyFunctionHandler(e, data_020d1ec8);
}

ARM void em10_normal(Entity *e) {
    data_020d1f48[e->action](e);
}
