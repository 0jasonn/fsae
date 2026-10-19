#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

typedef struct Vars_02036314 {
    /* 00 */ u8 unk_00[0x6e];
    /* 6e */ u16 unk_6e;
    /* 70 */ u8 mode;
    /* 71 */ u8 fxSpawned;
    /* 72 */ u16 homeX; // home x
    /* 74 */ s32 hideTimer;
    /* 78 */ u8 sparkTimer;
    /* 79 */ u8 displayType;
    /* 7a */ u8 sparkCount;
    /* 7b */ u8 unk_7b;
} Vars_02036314;
#define V(e) VARS(Vars_02036314, e)

extern const EntityFunc em2e_actions[];
extern const u8 em2e_hitbox[];
extern Entity *data_0212c648;
extern s32 em2e_type4Hidden;
extern const u16 em2e_hideTimes[];
extern const u32 em2e_resourceIds[];
extern const u32 em2e_modeMasks[];

typedef struct Vars_Flag {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ s32 spawnFlag;
} Vars_Flag;


ARM void em2e_main(Entity *e) {
    em2e_actions[e->action](e);
    if (!(e->contactFlags & 0x80)) {
        return;
    }
    if (e->contactFlags & 0x7f) {
        return;
    }
    if (data_0212ceb0[e->contactedEntity->type].unk_36 & 0x400) {
        return;
    }
    Entity *obj = GetSetWork(0x55, 1, 0);
    if (obj == NULL) {
        return;
    }
    obj->child = e->contactedEntity;
    data_0212ceb0[e->contactedEntity->type].unk_36 |= 0x400;
}

ARM void em2e_init(Entity *e) {
    e->unk_50 = 0x4000;
    e->spriteSettings.b0 = 1;
    InitAnimationForceUpdate(e, 0);
    e->unk_5e.b2 = 2;
    e->hitbox = em2e_hitbox;
    e->direction = 0xff;
    e->unk_6a = 1;
    gatherInit(e);
    e->subtimer = 0x3c;
    V(e)->unk_7b = 0x1e;
    e->child = data_0212c648;
    data_0212c648 = e;
    CockpitOff();
    em2e_type4Hidden = 0;
    V(e)->unk_6e = 0;
}

ARM void em2e_gatherwait(Entity *e) {
    if (e->type == 0) {
        BindPlayers();
        if (e->subtimer != 0) {
            e->subtimer--;
            return;
        }
    }
    if (e->health == 0) {
        if (data_0212c7c8.unk_6 == e->type) {
            V(e)->displayType = 4;
        } else {
            V(e)->displayType = e->type + 1;
        }
    } else {
        V(e)->displayType = e->type;
    }
    if (V(e)->displayType >= 4) {
        V(e)->displayType = 4;
    }
    if (e->type >= 4) {
        e->type = 4;
    }
    if (e->zVelocity != 0) {
        UpdateAnimationSingleFrame(e);
        UpdateGravity(e, 0x2000);
        MoveDir(e);
        return;
    }
    if (V(e)->sparkTimer != 0) {
        if (--V(e)->sparkTimer % 4 != 0) {
            return;
        }
        Entity *fx = GetTamaWork(0xf);
        if (fx == NULL) {
            return;
        }
        if (Random() & 1) {
            fx->x.HALF.HI = e->x.HALF.HI + (Random() & 0xf);
        } else {
            fx->x.HALF.HI = e->x.HALF.HI - (Random() & 0xf);
        }
        if (Random() & 1) {
            fx->y.HALF.HI = e->y.HALF.HI + (Random() & 0xf);
        } else {
            fx->y.HALF.HI = e->y.HALF.HI - (Random() & 0xf);
        }
        fx->type2 = 4;
        fx->parent = e;
        if ((V(e)->sparkCount++ & 3) == 0) {
            EnqueueSFX(0xbb);
        }
        return;
    }
    if (e->timer != 0) {
        if (e->timer == 0x5a && e->type != 4) {
            EnqueueSFX(0xbc);
        }
        if (--e->timer & 1) {
            InitAnimationForceUpdate(e, 0);
            return;
        }
        int anim = V(e)->displayType;
        if (anim == 4) {
            return;
        }
        InitAnimationForceUpdate(e, anim);
        return;
    }
    if (e->type == 0) {
        data_0212c648 = e->child;
        SoundReq(0x19c);
        CockpitOn();
    }
    e->health = 1;
    e->type = V(e)->displayType;
    int next = V(e)->displayType;
    if (next == 4) {
        InitAnimationForceUpdate(e, 0);
    } else {
        InitAnimationForceUpdate(e, next);
        e->spriteSettings.b4 = 2;
        e->unk_3c |= 0x80;
    }
    atSelect(e);
}

ARM void em2e_sign(Entity *e) {
    UpdateAnimationSingleFrame(e);
    UpdateGravity(e, 0x2000);
    switch (V(e)->mode) {
        case 4:
            if (e->z.WORD != 0) {
                return;
            }
            e->timer -= 10;
            if (e->timer != 0) {
                e->zVelocity = 0x30000;
                return;
            }
            break;
        case 0:
        case 1:
        case 2:
            e->x.HALF.HI = V(e)->homeX + (s8)e->subtimer;
            e->subtimer = -e->subtimer;
            if (--e->timer != 0) {
                return;
            }
            break;
        case 3:
            MoveDir(e);
            e->direction = (e->direction + 1) & 0x1f;
            break;
    }
    e->x.HALF.HI = V(e)->homeX;
    switch (V(e)->mode) {
        case 4:
            for (e->timer = data_0212c7c8.unk_0 << 2; e->timer != 0; e->timer--) {
                int spawnX = ((Random() & 0x1f) << 4) + 0x76;
                int spawnY = ((Random() & 0x1f) << 4) + 0xa8;
                firepostSet(e, spawnX, spawnY);
            }
            atSelect(e);
            return;
        case 0:
            e->direction = Random() & 0x1f;
            e->speed = 0x100;
            e->action = 3;
            e->zVelocity = 0x20000;
            e->timer = 5;
            firepostSet(e, e->x.HALF.HI, e->y.HALF.HI);
            return;
        case 1:
            e->direction = func_02086078(e, data_0212ceb0[func_02085608()].entity);
            e->timer = e->type + 3;
            e->speed = 0x100;
            e->action = 3;
            e->zVelocity = 0x20000;
            return;
        case 2: {
            Entity *fx = GetTamaWork(0xf);
            if (fx != NULL) {
                fx->x.HALF.HI = e->x.HALF.HI;
                fx->y.HALF.HI = e->y.HALF.HI;
                fx->timer = func_02085608();
                fx->parent = e;
                V(e)->fxSpawned = 1;
            }
            atSelect(e);
            return;
        }
        case 3: {
            Entity *fx = GetTamaWork(0xf);
            if (fx != NULL) {
                fx->timer = func_02085608();
                fx->x.HALF.HI = e->x.HALF.HI;
                fx->y.HALF.HI = e->y.HALF.HI;
                fx->type2 = 1;
                fx->parent = e;
            }
            atSelect(e);
            return;
        }
    }
}

ARM void em2e_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    func_020852ec(e);
    if (UpdateGravity(e, 0x2000) != 0) {
        return;
    }
    if (e->type < 4) {
        EnqueueSFX(0xa7);
    }
    if (--e->timer != 0) {
        if (e->type == 4) {
            EnqueueSFX(0x31);
        }
        e->zVelocity = 0x20000;
        if (V(e)->mode == 0) {
            e->direction = Random() & 0x1f;
        } else if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
            e->direction = func_02086078(e, data_0212ceb0[func_02085608()].entity);
        } else {
            e->direction = func_02086078(e, data_0212ceb0[*Knife_Single_SinglePlay_GetInstance()].entity);
        }
        firepostSet(e, e->x.HALF.HI, e->y.HALF.HI);
        return;
    }
    atSelect(e);
}

ARM void em2e_break(Entity *e) {
    if (e->type == 4 && em2e_type4Hidden != 0) {
        e->action = 6;
        return;
    }
    e->spriteSettings.b0 ^= 1;
    e->unk_3c &= 0x7f;
    if (e->subtimer != 0) {
        if (V(e)->hideTimer-- != 0) {
            return;
        }
        V(e)->hideTimer = 5;
        if (e->timer != 0) {
            Entity *fx = GetTamaWork(0xf);
            if (fx != NULL) {
                fx->x.HALF.HI = e->x.HALF.HI;
                fx->y.HALF.HI = e->y.HALF.HI;
                fx->z.HALF.HI = e->z.HALF.HI;
                fx->type = e->type;
                fx->type2 = 3;
                fx->parent = e;
                if (e->timer == e->subtimer) {
                    e->child = fx;
                    fx->health = 0x20;
                    VARS(Vars_Flag, fx)->spawnFlag = 1;
                }
            }
            e->timer--;
            return;
        }
        e->action++;
        V(e)->hideTimer = em2e_hideTimes[e->type - 1];
        if (e->type == 4 && em2e_type4Hidden == 0) {
            V(e)->hideTimer = 0x258;
        }
        e->spriteSettings.b0 = 0;
        if (e->type == 4) {
            em2e_type4Hidden++;
        }
        return;
    }
    e->subtimer = (Random() & 7) + 1;
    V(e)->hideTimer = 5;
}

ARM void em2e_hide(Entity *e) {
    Entity *target = e->child;
    e->x.HALF.HI = target->x.HALF.HI;
    e->y.HALF.HI = target->y.HALF.HI;
    if (target->health == 0) {
        V(e)->hideTimer = 0;
        e->health = 0;
        EnqueueSFX(0xa3);
    }
    if (V(e)->hideTimer-- != 0) {
        return;
    }
    if (e->child->health != 0) {
        em2e_type4Hidden = 0;
    }
    e->spriteSettings.b0 ^= 1;
    InitAnimationForceUpdate(e, 0);
    gatherInit(e);
    e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, 0x1f8, 0x1f8);
}

ARM void em2e_die(Entity *e) {
    EmDie(e);
    e->type = 5;
}

ARM void gatherInit(Entity *e) {
    if (e->health == 0) {
        u8 level = e->type;
        if (level < 3 && level != 0) {
            s32 size;
            void *data = KnifeApp_getZeldaResource_08dde0(KnifeApp_getInstance(), &size, em2e_resourceIds[level - 1]);
            func_020845b0(0x6403000, data, size);
        }
    }
    e->zVelocity = 0x30000;
    e->action = 1;
    e->timer = 0x5a;
    V(e)->sparkTimer = 0x78;
    e->unk_2e = 2;
    e->spriteSettings.b4 = 1;
    V(e)->sparkCount = 0;
}

ARM void atSelect(Entity *e) {
    if (V(e)->mode != 2 && V(e)->fxSpawned == 0) {
        V(e)->mode = 2;
    } else {
        u8 mode;
        do {
            mode = func_02085620(em2e_modeMasks[e->type - 1]);
        } while (V(e)->mode == mode || (mode == 2 && V(e)->fxSpawned != 0));
        V(e)->mode = mode;
    }
    e->timer = 0x1e;
    e->subtimer = 2;
    e->direction = 8;
    e->speed = 0x200;
    e->action = 2;
    V(e)->homeX = e->x.HALF.HI;
}

ARM void firepostSet(Entity *e, u16 x, u16 y) {
    if (Random() & 1) {
        return;
    }
    Entity *fx = GetTamaWork(0xf);
    if (fx != NULL) {
        fx->x.HALF.HI = x;
        fx->y.HALF.HI = y;
        fx->type2 = 2;
        fx->parent = e;
    }
}
