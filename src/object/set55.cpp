#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/objdecls.h"
#include "object/objdecls_d.h"

// Set55 actor (module set55). Address -> name:
//   0x02071f4c Set55 (provisional name; dispatch by e->action, table depends on e->type)
//   0x02071f88 set55_init (original name)
//   0x020720a0 set55_movei (original name)
//   0x02072280 set55_movef (original name)
//   0x02072554 func_02072554 (C++ name in symbols.txt; stores the Set55 entity of a player)

typedef struct Vars_Set55 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u16 lifetime; // set to 0x1e0 by set55_init for type != 0, counts down in set55_movef
} Vars_Set55;
#define V55(e) VARS(Vars_Set55, e)

extern const u8 set55_hitbox[];
extern const EntityFunc set55_actionsTypeN[]; // indexed by e->action, e->type != 0
extern const EntityFunc set55_actionsType0[]; // indexed by e->action, e->type == 0
extern u8 localPlayerIndex;
extern Entity *data_0212c648;
extern const s8 set55_xOffsets[]; // indexed by animationState >> 1
extern u16 data_0212c58c[];

void set55_movef(Entity *e);

ARM void Set55(Entity *e) {
    if (e->type != 0) {
        set55_actionsTypeN[e->action](e);
    } else {
        set55_actionsType0[e->action](e);
    }
}

ARM void set55_init(Entity *e) {
    Entity *child;

    e->action++;
    e->hitbox = set55_hitbox;
    child = e->child;
    e->statusFlags = child->statusFlags | 0x80;
    e->unk_5c = child->unk_5c;
    e->poseId = 1;
    e->unk_40 = 0x3f;
    if (e->type != 0) {
        e->timer = 0x78;
        V55(e)->lifetime = 0x1e0;
        e->spriteSettings.b0 = 1;
        InitAnimationForceUpdate(e, 0);
        set55_movef(e);
        return;
    }
    e->x.WORD = child->x.WORD;
    e->y.WORD = child->y.WORD;
    e->layer = child->layer;
    e->spriteSettings.b14 = child->spriteSettings.b14;
    e->unk_5e.b0 = child->unk_5e.b0;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        return;
    }
    if (localPlayerIndex == e->child->type) {
        data_0212c648 = e;
    }
}

ARM void set55_movei(Entity *e) {
    Entity *child;
    u8 playerIndex;

    child = e->child;
    if (data_0212ceb0[child->type].statusFlags & 0x1000) {
        data_0212ceb0[child->type].statusFlags &= 0xf7ff;
        data_0212c648 = e->child;
        PutObjWork(e);
        return;
    }
    playerIndex = localPlayerIndex;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        playerIndex = *Knife_Single_SinglePlay_GetInstance();
    }
    child = e->child;
    if (data_0212ceb0[child->type].statusFlags & 0x800) {
        if (e->contactFlags & 0x80) {
            switch (e->contactFlags & 0x7f) {
            case 4:
            case 8:
            case 12:
            case 16:
            case 19:
                data_0212ceb0[child->type].statusFlags &= 0xf7ff;
                if (playerIndex == e->child->type) {
                    data_0212c648 = e->child;
                }
                PutObjWork(e);
                return;
            case 0: {
                Entity *contacted;
                Entity *created;

                contacted = e->contactedEntity;
                if ((data_0212ceb0[contacted->type].statusFlags & 0x1881) == 0 &&
                    data_0212ceb0[contacted->type].state == 0 && contacted->action == 1 &&
                    data_0212ceb0[contacted->type].entity->iframes == 0) {
                    created = GetSetWork(0x55, 0, 0);
                    if (created != NULL) {
                        created->child = e->contactedEntity;
                        data_0212ceb0[e->contactedEntity->type].statusFlags |= 0x800;
                        data_0212ceb0[e->contactedEntity->type].state = 0xd;
                    }
                }
                return;
            }
            default:
                return;
            }
        } else {
            e->layer = child->layer;
            return;
        }
    }
    if (playerIndex == child->type) {
        data_0212c648 = child;
    }
    PutObjWork(e);
}

ARM void set55_movef(Entity *e) {
    u8 type;
    Entity *child;

    V55(e)->lifetime--;
    type = e->child->type;
    if ((data_0212ceb0[type].statusFlags & 0x1810) != 0 || V55(e)->lifetime == 0) {
        data_0212ceb0[type].statusFlags &= 0xfbff;
        PutObjWork(e);
        return;
    }
    if (data_0212c58c[type] != 0) {
        e->subtimer++;
    }
    if (e->subtimer > 0x1e) {
        data_0212ceb0[e->child->type].statusFlags &= 0xfbff;
        PutObjWork(e);
        return;
    }
    child = e->child;
    e->x.HALF.HI = child->x.HALF.HI + set55_xOffsets[child->animationState >> 1];
    e->y.HALF.HI = child->y.HALF.HI - 6;
    e->z.WORD = child->z.WORD;
    e->layer = child->layer;
    e->spriteSettings.b14 = child->spriteSettings.b14;
    e->spriteSettings.b30 = child->spriteSettings.b30;
    if ((child->animationState >> 1) != 2) {
        e->unk_5e.b0 = 3;
    } else {
        e->unk_5e.b0 = 1;
        e->y.HALF.HI -= 2;
    }
    if ((e->type & 0x80) == 0 && e->timer-- == 0) {
        AddHeart(e->child, -4);
        e->timer = 0x78;
        e->child->iframes = 0x10;
        func_02085f98(e->child, 0xc3);
    }
    if (data_0212ceb0[e->child->type].statusFlags & 0x400) {
        UpdateAnimationSingleFrame(e);
        if (e->type & 0x80) {
            return;
        }
        if ((e->contactFlags & 0x80) == 0) {
            return;
        }
        switch (e->contactFlags & 0x7f) {
        case 4:
        case 8:
        case 12:
        case 16:
            data_0212ceb0[e->child->type].statusFlags &= 0xfbff;
            PutObjWork(e);
            return;
        case 0:
            if (data_0212ceb0[e->contactedEntity->type].statusFlags & 0x400) {
                return;
            }
            {
                Entity *created = GetSetWork(0x55, 1, 0);
                if (created == NULL) {
                    return;
                }
                created->child = e->contactedEntity;
                data_0212ceb0[e->contactedEntity->type].statusFlags |= 0x400;
            }
            return;
        default:
            return;
        }
    } else {
        PutObjWork(e);
        return;
    }
}

ARM Entity *func_02072554(s32 a) {
    Entity *set;

    set = GetSetWork(0x56, a, 0);
    if (set != NULL) {
        set->spriteSettings.b16 = (a + 7) & 0xf;
        set->spriteSettings.b20 = set->spriteSettings.b16;
        set->unk_20 = a << 5;
        set->animationState = 4;
        set->spriteSettings.b14 = 2;
        data_0212ceb0[a].entity = set;
    }
    return set;
}
