#include "engine/functions.h"
#include "enemy/em2c.h"
#include "global.h"

extern const u8 em2c_pushSpeeds[];
extern const u8 em2c_pushMasks[];
extern const s8 em2c_pushXOffsets[];
extern u16 data_0212c584[];

ARM void type1_appear(Entity *e) {
    if (!(VE(e->parent)->eventFlags & flagBits[VL(V(e)->lockEntity)->lockBitIndex])) {
        return;
    }
    MoveDir(e);
    if (--e->timer == 0) {
        e->action = 3;
        e->speed = 0x20;
        V(e)->homeX = e->x.HALF.HI;
        V(e)->unk_73 = 0;
        V(e)->pushProgress = 0;
    }
    if (em2c_leverTimers[V(e)->side] != 0) {
        em2c_leverTimers[V(e)->side] = 0;
    }
}

ARM void type1_lift(Entity *e) {
    ObjHippariCheck(e);
    if (e->subAction == 5) {
        Entity *player = data_0212ceb0[e->type2].entity;
        if (V(e)->leverState == 0) {
            player->x.HALF.HI = e->x.HALF.HI + em2c_liftOffsets[player->animationState];
            player->y.HALF.HI = e->y.HALF.HI + em2c_liftOffsets[player->animationState + 1];
            V(e)->leverState = 1;
            e->subtimer = 2;
        }
        if (V(e)->side * 2 + 1 == player->animationState >> 1 && player->frame != 0) {
            em2c_leverMove(e);
            if (V(e)->leverState == 1) {
                V(e)->leverState = 2;
                InitAnimationForceUpdate(e->parent, 0x1c);
                EnqueueSFX(0xa4);
            }
        }
    } else {
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0 || em2c_leverTimers[V(e)->side] == 0) {
            e->action = 3;
            V(e)->leverState = 0;
        } else {
            em2c_leverTimers[V(e)->side]--;
            VL(V(e)->lockEntity)->lockFlags |= V(e)->lockBit;
            if (e->parent->action != 6 || (VL(V(e)->lockEntity)->lockFlags & 0xc0) == 0xc0) {
                e->action = 4;
                e->timer = 0x3c;
                e->x.HALF.HI += em2c_liftOffsets[V(e)->side];
                EnqueueSFX(0x12);
                Entity *fx = GetSetWork(0xf, 3, 0x20);
                if (fx != NULL) {
                    ObjPosCopyOfs32(e, fx, em2c_fxXOffsets[V(e)->side] << 16, 0);
                }
                Entity *item = GetSetWork(0, em2c_itemDrops[Random() & 7], 1);
                if (item != NULL) {
                    item->direction = (((V(e)->side ^ 1) << 4) + 8) | 0x80;
                    ObjPosCopyOfs32(e, item, em2c_fxXOffsets[V(e)->side] << 16, 0);
                }
                if (em2c_leverTimers[V(e)->side] != 0) {
                    em2c_leverTimers[V(e)->side] = 0;
                }
            }
        }
        V(e)->leverState = 0;
    }
    func_02085d78(e);
}

ARM void em2c_type1_move(Entity *e) {
    func_02089524(e);
    if (V(e)->pushProgress != 0) {
        e->direction = (V(e)->side << 4) + 8;
        MoveDir(e);
        em2c_setdist(e);
    }
    func_02085d78(e);
}

ARM void em2c_type1_vanish(Entity *e) {
    if (--e->timer == 0) {
        e->action = 5;
        e->spriteSettings.b0 = 0;
        return;
    }
    e->spriteSettings.b0 ^= 1;
}

ARM void em2c_type1_wait_033b38(Entity *e) {
    if (VL(V(e)->lockEntity)->lockValue != 0x10) {
        return;
    }
    e->action = 1;
    e->timer = 0x20;
    e->speed = 0x80;
    e->spriteSettings.b0 = 1;
    e->direction = ((V(e)->side ^ 1) << 4) + 8;
    e->x.HALF.HI = e->parent->x.HALF.HI + em2c_restXOffsets[V(e)->side];
}

ARM void em2c_type2(Entity *e) {
    if (e->parent->health != 0) {
        if (e->action == 0) {
            e->action = 1;
            e->spriteSettings.b0 = 1;
            e->unk_5e.b0 = 1;
            InitAnimationForceUpdate(e, 0x13);
        }
        if (e->type2 >> 4) {
            kukiRangeSet(e, e->child, VL(e->parent)->lockValue);
            return;
        }
        u8 step = e->type2 & 0xf;
        Entity *parent = e->parent;
        e->x.HALF.HI = parent->child->x.HALF.HI + (parent->x.HALF.HI - parent->child->x.HALF.HI) * step / 4;
        e->y.HALF.HI = parent->child->y.HALF.HI + (parent->y.HALF.HI - parent->child->y.HALF.HI) * step / 4;
    } else {
        kukiDieDemoSet(e);
        PutObjWork(e);
    }
}

ARM void em2c_type3(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->unk_5e.b0 = 1;
        return;
    }
    BOOL alive = FALSE;
    if (e->type2 != 0) {
        if (VC(e)->chainA != NULL) {
            kukiMgr(e, VC(e)->chainA);
            alive = TRUE;
        }
        if (VC(e)->chainB != NULL) {
            kukiMgr(e, VC(e)->chainB);
            alive = TRUE;
        }
        if (VC(e)->chainC != NULL) {
            kukiMgr(e, VC(e)->chainC);
            alive = TRUE;
        }
    } else {
        if (VC(e)->chainA != NULL) {
            ObjPosCopyOfs32(VC(e)->chainA->parent, VC(VC(e)->chainA->parent)->chainA, 0, 1);
            alive = TRUE;
        }
        if (VC(e)->chainB != NULL) {
            ObjPosCopyOfs32(VC(e)->chainB->parent, VC(VC(e)->chainB->parent)->chainA, 0, 1);
            alive = TRUE;
        }
        if (VC(e)->chainC != NULL) {
            ObjPosCopyOfs32(VC(e)->chainC->parent, VC(VC(e)->chainC->parent)->chainA, 0, 1);
            alive = TRUE;
        }
    }
    if (!alive) {
        PutObjWork(e);
    }
}

ARM void em2c_type4(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 1;
        e->unk_5e.b0 = 1;
        InitAnimationForceUpdate(e, 0x13);
    }
    if (--e->timer != 0) {
        return;
    }
    Entity *fx = GetSetWork(0xf, 1, 0);
    if (fx != NULL) {
        ObjPosCopy(e, fx);
    }
    PutObjWork(e);
}


ARM void em2c_leverMove(Entity *e) {
    Entity *player = data_0212ceb0[e->type2].entity;
    u8 speed = em2c_pushSpeeds[V(e)->side];
    if (V(e)->pushProgress < 0x30) {
        s16 px = player->x.HALF.HI;
        s16 py = player->y.HALF.HI;
        func_020852f8(player, 0x40, speed);
        if (px == player->x.HALF.HI && py == player->y.HALF.HI) {
            return;
        }
        s16 dist;
        if (V(e)->side != 0) {
            dist = player->x.HALF.HI - px;
        } else {
            dist = px - player->x.HALF.HI;
        }
        func_020852f8(e, dist << 8, speed);
        em2c_setdist(e);
        if (V(e)->pushProgress >= 0x30) {
            V(e)->pushCount = 0;
            if (em2c_leverTimers[V(e)->side] != 0) {
                em2c_leverTimers[V(e)->side] = 0;
            }
            em2c_leverDone = 1;
            return;
        }
        if (--e->subtimer == 0) {
            e->subtimer = 8;
            EnqueueSFX(0x8b);
        }
        return;
    }
    if (em2c_pushMasks[V(e)->side] & data_0212c584[e->type2]) {
        if (V(e)->pushCount < 0xf) {
            V(e)->pushCount++;
            if (em2c_leverTimers[V(e)->side] != 0) {
                em2c_leverTimers[V(e)->side] = 0;
            }
            return;
        }
        VL(V(e)->lockEntity)->lockFlags |= V(e)->lockBit;
        if (e->parent->action == 6 && (VL(V(e)->lockEntity)->lockFlags & 0xc0) != 0xc0) {
            em2c_leverTimers[V(e)->side] = 0x4b0;
            return;
        }
        e->action = 4;
        e->timer = 0x3c;
        e->x.HALF.HI += em2c_pushXOffsets[V(e)->side];
        EnqueueSFX(0x12);
        Entity *fx = GetSetWork(0xf, 3, 0x20);
        if (fx != NULL) {
            ObjPosCopyOfs32(e, fx, em2c_fxXOffsets[V(e)->side] << 16, 0);
        }
        Entity *item = GetSetWork(0, em2c_itemDrops[Random() & 7], 1);
        if (item != NULL) {
            item->direction = (((V(e)->side ^ 1) << 4) + 8) | 0x80;
            ObjPosCopyOfs32(e, item, em2c_fxXOffsets[V(e)->side] << 16, 0);
        }
        return;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        V(e)->pushCount = 0;
        return;
    }
    if (em2c_leverTimers[V(e)->side] != 0) {
        em2c_leverTimers[V(e)->side]--;
    } else {
        V(e)->pushCount = 0;
    }
}
