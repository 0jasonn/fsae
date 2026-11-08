#include "engine/functions.h"
#include "engine/misc.h"
#include "engine/player.h"
#include "global.h"
#include "game/wanwan.h"
#include "actor/object/actor_calls_k.h"

// Wanwan (bow-wow chain) fields past the shared Entity header
typedef struct Vars_Wanwan {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *target; // entity the dog is chasing
    /* 68 */ u16 chaseTimer; // frames left of the chase
    /* 6a */ s16 radius;     // range of the chain link
} Vars_Wanwan;

extern u8 data_0212ceed[];      // playerWork[i].unk_3d, stride 0x94
extern u8 data_0212ced8[];      // playerWork[i].entity, stride 0x94
extern EntityNode data_0212c6d0; // sentinel of the object list

#define WANWAN_V(e) VARS(Vars_Wanwan, e)

// wanwan_move, 0x02081640. Head of the chain (type2 bit 7): wakes up and chases an overlapping entity or player,
// then moves; the other links follow their parent.
void wanwan_move(Entity *e) {
    Entity *end;
    Entity *link;
    Entity *node;
    Entity *player;
    u8 i;
    u32 offset;
    u8 flag = data_0212ceed[e->type * 0x94];
    Entity *owner = *(Entity **)(data_0212ced8 + e->type * 0x94);
    if (flag == 0) {
        PutObjWork(e);
        func_020841b0(e);
        return;
    }
    if ((e->contactFlags & 0x80) && (e->contactFlags & 0x7f) == 0) {
        DropRupees(e->contactedEntity->type, 0xb);
    }
    if (e->type2 & 0x80) {
        e->iframes = 0;
        UpdateAnimationSingleFrame(e);
        if (e->timer-- == 0) {
            e->timer = 0x78;
            end = (Entity *)&data_0212c6d0;
            node = (Entity *)((EntityNode *)end)->next;
            while (node != end) {
                if (node != WANWAN_V(e)->target && func_02085a88(e, node, 0x30, 0x30) != 0 &&
                    (node->statusFlags & 0x80) != 0) {
                    e->direction = GetFacingDirection(e, node);
                    ObjCdirSet(e);
                    InitAnimationForceUpdate(e, (e->animationState >> 1) + 9);
                    e->speed = 0x300;
                    e->subAction = 1;
                    WANWAN_V(e)->target = node;
                    WANWAN_V(e)->chaseTimer = 3;
                    e->statusFlags |= 0x80;
                    EnqueueSFX(0x51);
                    break;
                }
                node = (Entity *)((EntityNode *)node)->next;
            }
            if (e->subAction != 1 && KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
                for (i = 0; i < gameState.playerCount; i++) {
                    if (i != e->type &&
                        (player = *(Entity **)((u8 *)playerWork + (offset = i * 0x94) + 0x28)) != WANWAN_V(e)->target &&
                        func_02085a88(e, player, 0x30, 0x30) != 0) {
                        e->direction = GetFacingDirection(e, *(Entity **)(data_0212ced8 + offset));
                        ObjCdirSet(e);
                        InitAnimationForceUpdate(e, (e->animationState >> 1) + 9);
                        e->speed = 0x300;
                        e->subAction = 1;
                        WANWAN_V(e)->target = *(Entity **)(data_0212ced8 + offset);
                        WANWAN_V(e)->chaseTimer = 3;
                        e->statusFlags |= 0x80;
                        break;
                    }
                }
            }
            if (e->subAction != 1) {
                WANWAN_V(e)->target = NULL;
            }
        }
        if (e->subAction == 1 && (e->contactFlags & 0x80) && e->contactedEntity == WANWAN_V(e)->target) {
            WANWAN_V(e)->target = NULL;
        }
        MoveDir(e);
        link = e;
        if (e->type2 != 0) {
            do {
                wanwan_rangeCk(link->parent, link, WANWAN_V(e)->radius);
                link = link->parent;
            } while (link->type2 != 0);
        }
        if (data_0212ceed[e->type * 0x94] & 2) {
            if (func_02085a88(e, owner, 2, 2) != 0) {
                data_0212ceed[e->type * 0x94] = 0;
            }
        }
        if (UpdateGravity(e, 0x2000) != 0) {
            return;
        }
        e->zVelocity = 0x10000;
        if (e->subAction != 1) {
            e->speed = 0x180;
            e->direction = Random() & 0x9f;
            ObjCdirSet(e);
            InitAnimationForceUpdate(e, (e->animationState >> 1) + 9);
        } else {
            if (WANWAN_V(e)->chaseTimer-- == 0) {
                e->subAction = 0;
                e->statusFlags &= 0x7f;
                return;
            }
            if (WANWAN_V(e)->target != NULL) {
                e->direction = GetFacingDirection(e, WANWAN_V(e)->target);
            }
            ObjCdirSet(e);
            InitAnimationForceUpdate(e, (e->animationState >> 1) + 9);
        }
    } else {
        func_0208ae30(e);
        e->unk_5e.b0 = 1;
        if ((data_0212ceed[e->type * 0x94] & 2) && WANWAN_V(e)->radius != 0) {
            WANWAN_V(e)->radius -= 0x80;
        }
        if (e->type2 != 0) {
            return;
        }
        wanwan_rangeCk(e, e->parent, WANWAN_V(e)->radius);
        link = e;
        if (e->type2 & 0x80) {
            return;
        }
        do {
            wanwan_rangeCk(link->child, link, WANWAN_V(e)->radius);
            link = link->child;
        } while ((link->type2 & 0x80) == 0);
    }
}
