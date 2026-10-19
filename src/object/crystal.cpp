#include "engine/functions.h"
#include "object/crystal.h"
#include "global.h"

// Crystal actor (module crystal). Address -> name:
//   0x020581b8 crystal0 (original name)
//   0x020581d4 cry0_init (original name)
//   0x02058280 set_crystal_child (original name)
//   0x020582e0 cry0_move (original name)
//   0x0205831c crystal1 (original name)
//   0x02058338 cry1_init (original name)
//   0x020583a4 cry1_move (original name)
//   0x020583c8 cry1_plate (original name)

ARM void crystal0(Entity *e) {
    crystal0_actions[e->action](e);
}

ARM void cry0_init(Entity *e) {
    u8 action = e->action;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b14 = 3;
    e->action = action + 1;
    e->spriteSettings.b30 = 3;
    e->spriteSettings.b16 = 8 + ((PlFlagsByte *)&data_0212ceb0[e->type2].unk_3d[0x4e])->b2;
    VCRY(e)->spriteWord = (VCRY(e)->spriteWord & ~0xc00) | 0x400;
    e->x.HALF.HI = TEMPLATE_OF(e->type2)->x.HALF.HI;
    e->y.HALF.HI = TEMPLATE_OF(e->type2)->y.HALF.HI + 0x18;
    VCRY(e)->anchorY = e->y.HALF.HI + 0x20;
    InitAnimationForceUpdate(e, 0);
}

ARM void set_crystal_child(Entity *e) {
    Entity *child;
    if (e->unk_16 != 0) {
        return;
    }
    if (e->y.HALF.HI >= VCRY(e)->anchorY - 0x38) {
        return;
    }
    e->unk_16 = 1;
    child = GetSetWork(0xd, 1, 0);
    if (child == NULL) {
        return;
    }
    child->x.HALF.HI = e->x.HALF.HI;
    child->y.HALF.HI = e->y.HALF.HI + 0x40;
    child->parent = e;
}

ARM void cry0_move(Entity *e) {
    e->x.HALF.HI = TEMPLATE_OF(e->type2)->x.HALF.HI;
    e->y.HALF.HI = TEMPLATE_OF(e->type2)->y.HALF.HI + 0x18;
    set_crystal_child(e);
}

ARM void crystal1(Entity *e) {
    crystal1_actions[e->action](e);
}

ARM void cry1_init(Entity *e) {
    u8 action = e->action;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b14 = 3;
    e->spriteSettings.b30 = 3;
    e->action = action + 1;
    VCRY(e)->spriteWord = (VCRY(e)->spriteWord & ~0xc00) | 0x400;
    e->spriteSettings.b16 = e->parent->spriteSettings.b16;
    VCRY(e)->anchorY = e->y.HALF.HI;
    InitAnimationForceUpdate(e, 1);
}

ARM void cry1_move(Entity *e) {
    e->x.HALF.HI = e->parent->x.HALF.HI;
    e->y.HALF.HI = e->parent->y.HALF.HI + 0x40;
    set_crystal_child(e);
}

ARM void cry1_plate(Entity *e) {
    cry1_plate_actions[e->action](e);
}
