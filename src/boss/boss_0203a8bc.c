#include "boss/boss_02039ed4.h"
#include "global.h"

// Function names (dsd -> name), also in scratch/agentA/renames.txt:
// Boss_SubtimerStep Boss_SubtimerStep, Boss_InitFromParent Boss_InitFromParent, Boss_DeleteIfParentFree Boss_DeleteIfParentFree,
// Boss_UpdateAnimFromDirection Boss_UpdateAnimFromDirection, Boss_UpdateAnimPair Boss_UpdateAnimPair, Boss_LaunchChild Boss_LaunchChild,
// Boss_LaunchChildOnAction4 Boss_LaunchChildOnAction4, Boss_RunStateTable Boss_RunStateTable, Boss_DispatchAction3 Boss_DispatchAction3

ARM void Boss_SubtimerStep(Entity *e) {
    u8 action;
    if (--e->subtimer == 0) {
        action = e->action;
        e->timer = 1;
        e->action = action - 2;
    }
    Boss_UpdateAnimPair(e);
}

ARM void Boss_InitFromParent(Entity *e) {
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

ARM void Boss_DeleteIfParentFree(Entity *e) {
    if (VPW(e->parent)->unk_04 == 0) {
        DeleteEntity(e);
    }
}

ARM void Boss_UpdateAnimFromDirection(Entity *e) {
    u8 anim = func_02045a8c(e->direction);
    if (anim != 0xff && anim != e->animationState) {
        e->animationState = anim;
        InitAnimationForceUpdate(e, anim);
        InitAnimationForceUpdate(e->parent, anim + 3);
    }
}

ARM void Boss_UpdateAnimPair(Entity *e) {
    UpdateAnimationSingleFrame(e);
    UpdateAnimationSingleFrame(e->parent);
}

ARM void Boss_LaunchChild(Entity *e) {
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

ARM void Boss_LaunchChildOnAction4(Entity *e) {
    if (e->action == 4) {
        Boss_LaunchChild(e);
    }
}

ARM void Boss_RunStateTable(Entity *e) {
    EnemyFunctionHandler(e, data_020d1ec8);
}

ARM void Boss_DispatchAction3(Entity *e) {
    data_020d1f48[e->action](e);
}
