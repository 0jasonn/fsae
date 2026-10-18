#include "Unknown/Entity.h"
#include "global.h"

extern const EntityFunc data_020d0828[];
extern const EntityFunc data_020d0840[];
extern const u8 data_020d07c4[];
extern const u8 data_020d0798[];
extern const s8 data_020d07a0[];
extern const EntityFunc data_020d089c[];
extern const u8 data_020d0894[];

typedef struct UnkStruct_0212c540 {
    u16 unk_0;
    u16 unk_2;
} UnkStruct_0212c540;
extern UnkStruct_0212c540 data_0212c540;

ARM void func_020301f0(Entity *e) {
    EnemyFunctionHandler(e, data_020d0828);
}

ARM void func_02030204(Entity *e) {
    data_020d0840[e->action](e);
}

ARM void func_02030220(Entity *e) {
    switch (e->contactFlags & 0x7f) {
        case 0:
            if (e->action == 3) {
                e->timer = 1;
            }
            break;
        case 1:
        case 2:
        case 3:
        case 0x16:
        case 0x18:
        case 0x19:
        case 0x1a:
            if (e->action < 6) {
                e->action = 6;
                e->zVelocity = 0x18000;
                e->speed = 0xc0;
                e->direction = e->unk_3e;
                e->unk_42 = 0;
                e->unk_3f = 0x2f;
                InitAnimationForceUpdate(e, 9);
            }
            break;
    }
    GenericKnockback(e, data_020d0828);
}

ARM void func_020302f8(Entity *e) {
    e->action = 1;
    e->timer = 1;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 5;
    e->hitbox = data_020d07c4;
    e->direction = Random() & 0x18;
    InitAnimationForceUpdate(e, e->animationState = e->direction >> 3);
}

ARM void func_02030354(Entity *e) {
    if (func_02084ac8(e, 0xc) & 0x80) {
        e->action = 2;
        e->timer = 0x1e;
        e->child = func_02084f18();
        e->direction = GetFacingDirection(e, e->child);
        InitAnimationForceUpdate(e, 8);
    } else {
        if (--e->timer == 0) {
            e->timer = data_020d0798[Random() & 3];
            if (Random() & 0x1f) {
                e->direction = Random() & 0x18;
            } else {
                e->direction = (GetFacingDirection(e, func_02045eb4()) + 4) & 0x18;
            }
            if ((e->direction >> 3) != e->animationState) {
                InitAnimationForceUpdate(e, e->animationState = e->direction >> 3);
            }
        }
        if (func_020847a0(e) == 0) {
            e->timer = 1;
        }
    }
    UpdateAnimationSingleFrame(e);
}

ARM void func_02030444(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 3;
    e->timer = 0x78;
    e->speed = 0x1c0;
    InitAnimationForceUpdate(e, 8);
}

ARM void func_0203048c(Entity *e) {
    if (func_020847c8(e) == 0) {
        e->timer = 1;
    }
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        if ((e->timer & 7) == 0) {
            func_02086200(e, GetFacingDirection(e, e->child));
        }
        return;
    }
    e->action = 4;
    e->timer = 0x10;
    InitAnimationForceUpdate(e, e->animationState + 4);
}

ARM void func_0203050c(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action = 1;
    e->timer = 1;
    e->speed = 0x80;
    InitAnimationForceUpdate(e, e->animationState);
}

ARM void func_02030544(Entity *e) {
    if (UpdateGravity(e, 0x1800) == 0) {
        e->action = 1;
        e->timer = 1;
    }
}

ARM void func_02030568(Entity *e) {
    func_020847c8(e);
    switch (func_02086044(e, 0x1800)) {
        case 0:
            e->action = 7;
            e->timer = 0x96;
        case 1:
            EnqueueSFX(0x31);
            break;
    }
}

ARM void func_020305b0(Entity *e) {
    if (--e->timer != 0) {
        if (e->timer >= 0x3c) {
            return;
        }
        if ((e->timer & 1) == 0) {
            return;
        }
        e->x.HALF.HI += data_020d07a0[(e->timer >> 1) & 3];
        return;
    }
    e->action = 5;
    e->zVelocity = 0x10000;
    e->speed = 0x80;
    e->unk_3f = 0x2e;
    InitAnimationForceUpdate(e, e->animationState);
    EnqueueSFX(0x31);
}

ARM void func_02030630(Entity *e) {
    if (data_0212c540.unk_2 > 1) {
        func_02084700(e);
    }
    data_020d089c[e->action](e);
}

ARM void func_0203066c(Entity *e) {
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 5;
    e->hitbox = data_020d0894;
    InitAnimationForceUpdate(e, 0);
}

ARM void func_020306a8(Entity *e) {
    u32 result = func_02084ac8(e, 0xa);
    if (result & 0x80) {
        e->action = 2;
        e->speed = 0x40;
        e->direction = result & 0x18;
        InitAnimationForceUpdate(e, 1);
        return;
    }
    if (e->contactFlags < 1 || e->contactFlags > 3) {
        return;
    }
    e->action = 2;
    e->speed = 0x40;
    e->direction ^= 0x10;
    InitAnimationForceUpdate(e, 1);
}

ARM void func_02030728(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (func_020847a0(e) != 0) {
        if (e->speed < 0x110) {
            e->speed += 8;
        }
        return;
    }
    e->action = 3;
    InitAnimationForceUpdate(e, 2);
}

ARM void func_02030770(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->action = 1;
    }
}
