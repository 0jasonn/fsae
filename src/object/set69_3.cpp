#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/set69_3.h"

// Set69 actor, third unit (module set69). Address -> name:
//   0x02075ef0 type0_wait5 (original name)
//   0x02076044 type0_suikomi (original name)
//   0x02076094 type0_bgreset (original name)
//   0x020760fc type0_wait6 (original name)
//   0x02076150 type0_down (original name)
//   0x020761b4 type0_sasaru (original name)
//   0x020761e0 type0_wait7 (original name)
//   0x02076220 set69_type1 (original name; dispatches on e->action)
//   0x0207623c rr_type1_init_07623c (dsd name, original type1_init)
//   0x020762f4 rr_type1_wait_0762f4 (dsd name, original type1_wait)
//   0x0207635c type1_suikomare (original name)
//   0x0207649c set69_type2 (original name)
//   0x02076538 set69_type3 (original name)
//   0x020765e0 set69_type4 (original name)

ARM void type0_wait5(Entity *e) {
    Entity *spawn;
    Entity *parent;
    u8 i;

    UpdateAnimationSingleFrame(e);
    if (e->timer != 0) {
        e->timer--;
        if (e->timer != 0) {
            return;
        }
        e->subAction = 0;
        MessageRequest(0x1f4);
        messageRequest[3] = (messageRequest[3] & ~0x1f) | 1;
        messageRequest[4] = (messageRequest[4] & ~0x1f) | 7;
        spawn = GetSetWork(0x68, 0, 0);
        if (spawn != NULL) {
            ObjPosCopyOfs32(e, spawn, 0, -0x240000);
        }
        return;
    }
    if (e->subAction == 0) {
        if ((messageRequest[0] & 0x7f) != 6) {
            return;
        }
        Status_ArmIfEnabled();
        e->subAction = 1;
        return;
    }
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        if (data_0212c584[i] & 0x1000) {
            return;
        }
    }
    spawn = GetSetWork(0x69, 1, 0);
    if (spawn == NULL) {
        e->timer = 1;
        return;
    }
    ObjPosCopyOfs32(e, spawn, 0, 0x300000);
    parent = e->parent;
    e->child = spawn;
    PutObjWork(parent);
    SoundReq(0xb0);
    e->action = 0xc;
}

ARM void type0_suikomi(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->child->health != 0) {
        return;
    }
    e->action = 0xd;
    e->timer = 8;
    SoundReq(0x21f);
    data_0212c5ac[7] = 0x16;
    MakeFadeBuff256(0x100);
}

ARM void type0_bgreset(Entity *e) {
    e->timer--;
    if (e->timer == 5) {
        MapLoad(data_020d70ec, 1);
        em2f_mapFlag = 0;
        return;
    }
    if (e->timer != 0) {
        return;
    }
    e->action = 0xe;
    e->timer = 0x7c;
    FadeSet(2, 4);
}

ARM void type0_wait6(Entity *e) {
    UpdateAnimationSingleFrame(e);
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->action = 0xf;
    e->timer = 0x5a;
    e->speed = 0x400;
    e->direction = 0x10;
    em12_typeMasks[0] = 1;
}

ARM void type0_down(Entity *e) {
    s32 y;

    UpdateAnimationSingleFrame(e);
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    MoveDir(e);
    if (e->y.HALF.HI < 0x1f6) {
        return;
    }
    y = 0x1f8;
    e->y.HALF.HI = y;
    e->action = 0x10;
    InitAnimationForceUpdate(e, 1);
    SoundReq(y + 0x2e);
}

ARM void type0_sasaru(Entity *e) {
    UpdateAnimationSingleFrame(e);
    e->action = 0x11;
    e->timer = 0x78;
    InitAnimationForceUpdate(e, 2);
}

ARM void type0_wait7(Entity *e) {
    UpdateAnimationSingleFrame(e);
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    FadeSet(1, 8);
    Task_Chain(9);
    func_020827a8(0xa);
}

ARM void set69_type1(Entity *e) {
    set69_type1Actions[e->action](e);
}

ARM void rr_type1_init_07623c(Entity *e) {
    Entity *spawn;
    Vars_Set69Type1 *v;

    spawn = GetSetWork(0x69, 2, 0);
    if (spawn == NULL) {
        return;
    }
    spawn->parent = e;
    ObjPosCopy(e, spawn);
    e->action = 1;
    e->timer = 8;
    e->spriteSettings.b0 = 1;
    e->health = 0xff;
    InitAnimationForceUpdate(e, 0);
    func_02085cf8(e);
    v = VARS(Vars_Set69Type1, e);
    v->spriteBits.b8 |= 2;
    v->scaleX = 0x100;
    v->scaleY = 0x100;
    scrollArgs.data[0] = 0x100;
    scrollArgs.data[1] = 0x100;
    scrollArgs.data[2] = 0;
    ObjAffineSet2(&scrollArgs, e);
}

ARM void rr_type1_wait_0762f4(Entity *e) {
    Entity *spawn;
    Vars_Set69Type1 *v;

    UpdateAnimationSingleFrame(e);
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->action = 2;
    e->timer = 0xf0;
    v = VARS(Vars_Set69Type1, e);
    v->suikomareTimer = 0x78;
    spawn = GetSetWork(0x69, 3, 0);
    if (spawn == NULL) {
        return;
    }
    spawn->timer = e->timer;
    spawn->parent = e;
    ObjPosCopy(e, spawn);
}

ARM void type1_suikomare(Entity *e) {
    Vars_Set69Type1 *v;

    v = VARS(Vars_Set69Type1, e);
    if (e->timer != 0) {
        e->timer--;
        if (e->timer == 0) {
            SoundReq(0xb1);
            SoundReq(0x81);
        }
        if (e->timer & 1) {
            e->y.HALF.HI += data_020dc044[(e->timer >> 1) & 1];
        }
        if ((e->timer & 0xf) == 0) {
            v->scaleY--;
        }
        scrollArgs.data[0] = v->scaleX;
        scrollArgs.data[1] = v->scaleY;
        scrollArgs.data[2] = 0;
        ObjAffineSet2(&scrollArgs, e);
        return;
    }
    v->suikomareTimer--;
    if (v->suikomareTimer != 0) {
        if (v->suikomareTimer < 0x1e) {
            e->spriteSettings.b0 ^= 1;
        }
        e->y.WORD -= 0x1999;
        v->scaleY--;
        v->scaleX += 8;
        scrollArgs.data[0] = v->scaleX;
        scrollArgs.data[1] = v->scaleY;
        scrollArgs.data[2] = 0;
        ObjAffineSet2(&scrollArgs, e);
        return;
    }
    func_02085d34(e);
    PutObjWork(e);
}

ARM void set69_type2(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 1;
        InitAnimationForceUpdate(e, 1);
        func_02085cf8(e);
    }
    if (e->parent->health != 0) {
        ObjPosCopyOfs32(e->parent, e, 0, 1);
        scrollArgs.data[0] = VARS(Vars_Set69Type1, e->parent)->scaleX;
        scrollArgs.data[1] = 0x100;
        scrollArgs.data[2] = 0;
        ObjAffineSet2(&scrollArgs, e);
        return;
    }
    func_02085d34(e);
    PutObjWork(e);
}

ARM void set69_type3(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 1;
        e->spriteSettings.b14 = 2;
        e->spriteSettings.b30 = 2;
        e->unk_5e.b0 = 1;
        InitAnimationForceUpdate(e, 2);
    }
    UpdateAnimationSingleFrame(e);
    e->timer--;
    if (e->timer == 0) {
        PutObjWork(e);
        return;
    }
    if (e->timer >= 0xf) {
        return;
    }
    e->spriteSettings.b0 ^= 1;
}

ARM void set69_type4(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 1;
        InitAnimationForceUpdate(e, 3);
    }
    UpdateAnimationSingleFrame(e);
}
