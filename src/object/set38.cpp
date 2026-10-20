#include "engine/functions.h"
#include "global.h"
#include "object/set38.h"

// Set38 family (module set38), 0x0206b7d4 .. 0x0206bb34.
// Address -> name: 0x0206b7d4 Set38, 0x0206b7f0 set38_init, 0x0206b900 set38_move, 0x0206ba64 set38_lift,
//   0x0206ba80 heart_throw_init, 0x0206bab8 heart_throw_nop (empty), 0x0206babc heart_throw_throw,
//   0x0206bae4 heart_throw_end, 0x0206bb28 heart_throw_finish (tail call to heart_throw_end), 0x0206bb34 set38_put

ARM void Set38(Entity *e) {
    set38Table[e->action](e);
}

ARM void set38_init(Entity *e) {
    Entity *child;

    if (e->type & 0x80) {
        child = GetSetWork(0x38, 0, 1);
        if (child != NULL) {
            ObjPosCopy(e, child);
            data_02134920 = child;
            e->child = child;
            child->parent = e;
        } else {
            PutObjWork(e);
            return;
        }
        em12_typeMasks[e->areaIndex] |= flagBits[e->type & 0x1f];
    } else {
        if (e->type2 == 0) {
            func_02085fac(e);
        }
    }

    VARS(Vars_Set38, e)->typeMask = flagBits[e->type & 0x1f];
    e->type = (e->type2 != 0);
    if (e->type == 0) {
        e->hitbox = set38Hitbox;
    } else {
        e->spriteSettings.b0 = 1;
        e->timer = 0xf;
        e->unk_1a = 0;
        InitAnimationForceUpdate(e, 1);
    }
    e->action++;
}

ARM void set38_move(Entity *e) {
    Vars_Set38 *v = VARS(Vars_Set38, e);
    Entity *link;

    if (e->type == 0) {
        if (data_02134920 != NULL && e->child == data_02134920) {
            em12_typeMasks[e->areaIndex] |= v->typeMask;
            return;
        }
        em12_typeMasks[e->areaIndex] &= ~v->typeMask;
        if (e->unk_47 == 0) {
            return;
        }
        link = data_0212ceb0[e->unk_47 - 1].entity;
        if (AssignObj(VARS(Vars_Carrier, link)->carried) != 0) {
            if (VARS(Vars_Carrier, link)->carried->child == data_02134920) {
                data_02134920->action = 3;
                data_02134920->timer = 2;
                e->child = data_02134920;
                data_02134920->parent = e;
                func_02085fd0(e);
            }
        }
        data_0212ceb0[e->unk_47 - 1].unk_0a[1] &= 0x7f;
        e->unk_47 = 0;
    } else {
        if (e->timer != 0) {
            e->timer--;
        } else {
            func_02089524(e);
        }
        UpdateAnimationSingleFrame(e);
        if (e->frame & 0x80) {
            InitAnimationForceUpdate(e, 1);
            e->unk_28 = (Random() & 0xf0) + 1;
        }
    }
}

ARM void set38_lift(Entity *e) {
    set38LiftTable[e->subAction](e);
}

ARM void heart_throw_init(Entity *e) {
    e->parent->child = NULL;
    func_02085fac(e->parent);
    InitAnimationForceUpdate(e, 0);
    e->subAction++;
}

ARM void heart_throw_nop(Entity *e) {
}

ARM void heart_throw_throw(Entity *e) {
    if (e->z.HALF.HI == 0) {
        heart_throw_end(e);
    }
    e->parent->timer = 2;
}

ARM void heart_throw_end(Entity *e) {
    if (func_02085c28(e) == 0) {
        EffectSet(e, 0xd, 0);
    }
    e->spriteSettings.b0 = 0;
    e->action = 3;
    e->timer = 0x1e;
}

ARM void heart_throw_finish(Entity *e) {
    heart_throw_end(e);
}

ARM void set38_put(Entity *e) {
    u8 held;
    u8 timer;
    u8 sfxTimer;

    ObjPosCopy(e->parent, e);
    held = 1;
    InitAnimationForceUpdate(e, held);
    if ((data_0212c594 & 1) == 0) {
        held = 0;
    }
    e->spriteSettings.b0 = held;
    timer = e->timer;
    e->timer = timer - 1;
    if (timer != 0) {
        return;
    }
    e->parent->child = e;
    em12_typeMasks[e->parent->areaIndex] |= VARS(Vars_Set38, e->parent)->typeMask;
    func_02085fd0(e->parent);
    e->spriteSettings.b0 = 1;
    e->action = 1;
    e->subAction = 0;
    sfxTimer = 0xf;
    e->timer = sfxTimer;
    EnqueueSFX(0x23c - sfxTimer);
}
