#include "object/object_02033708.h"
#include "global.h"

void kukiDieDemoSet(Entity *e);
void kukiRangeSet(Entity *e, Entity *other, u16 a);
void kukiMgr(Entity *e, Entity *other);
void ObjPosCopy(Entity *e, Entity *other);
extern const u8 data_020d0eb8[];
extern const u8 data_020d0ebe[];
extern const s8 data_020d0ebc[];
extern u16 data_0212c584[];
void func_020852f8(Entity *e, s32 dist, u8 speed);

ARM void type1_appear(Entity *e) {
    if (!(VE(e->parent)->unk_7d & data_020cf9b8[VL(V(e)->unk_7c)->unk_7e])) {
        return;
    }
    MoveDir(e);
    if (--e->timer == 0) {
        e->action = 3;
        e->speed = 0x20;
        V(e)->unk_70 = e->x.HALF.HI;
        V(e)->unk_73 = 0;
        V(e)->unk_72 = 0;
    }
    if (data_021348b8[V(e)->unk_75] != 0) {
        data_021348b8[V(e)->unk_75] = 0;
    }
}

ARM void type1_lift(Entity *e) {
    ObjHippariCheck(e);
    if (e->subAction == 5) {
        Entity *player = data_0212ceb0[e->type2].entity;
        if (V(e)->unk_74 == 0) {
            player->x.HALF.HI = e->x.HALF.HI + data_020d0f0a[player->animationState];
            player->y.HALF.HI = e->y.HALF.HI + data_020d0f0a[player->animationState + 1];
            V(e)->unk_74 = 1;
            e->subtimer = 2;
        }
        if (V(e)->unk_75 * 2 + 1 == player->animationState >> 1 && player->frame != 0) {
            em2c_leverMove(e);
            if (V(e)->unk_74 == 1) {
                V(e)->unk_74 = 2;
                InitAnimationForceUpdate(e->parent, 0x1c);
                EnqueueSFX(0xa4);
            }
        }
    } else {
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0 || data_021348b8[V(e)->unk_75] == 0) {
            e->action = 3;
            V(e)->unk_74 = 0;
        } else {
            data_021348b8[V(e)->unk_75]--;
            VL(V(e)->unk_7c)->unk_6e |= V(e)->unk_76;
            if (e->parent->action != 6 || (VL(V(e)->unk_7c)->unk_6e & 0xc0) == 0xc0) {
                e->action = 4;
                e->timer = 0x3c;
                e->x.HALF.HI += data_020d0f0a[V(e)->unk_75];
                EnqueueSFX(0x12);
                Entity *fx = GetSetWork(0xf, 3, 0x20);
                if (fx != NULL) {
                    ObjPosCopyOfs32(e, fx, data_020d0ec0[V(e)->unk_75] << 16, 0);
                }
                Entity *item = GetSetWork(0, data_020d0f02[Random() & 7], 1);
                if (item != NULL) {
                    item->direction = (((V(e)->unk_75 ^ 1) << 4) + 8) | 0x80;
                    ObjPosCopyOfs32(e, item, data_020d0ec0[V(e)->unk_75] << 16, 0);
                }
                if (data_021348b8[V(e)->unk_75] != 0) {
                    data_021348b8[V(e)->unk_75] = 0;
                }
            }
        }
        V(e)->unk_74 = 0;
    }
    func_02085d78(e);
}

ARM void em2c_type1_move(Entity *e) {
    func_02089524(e);
    if (V(e)->unk_72 != 0) {
        e->direction = (V(e)->unk_75 << 4) + 8;
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
    if (VL(V(e)->unk_7c)->unk_7c != 0x10) {
        return;
    }
    e->action = 1;
    e->timer = 0x20;
    e->speed = 0x80;
    e->spriteSettings.b0 = 1;
    e->direction = ((V(e)->unk_75 ^ 1) << 4) + 8;
    e->x.HALF.HI = e->parent->x.HALF.HI + data_020d0eba[V(e)->unk_75];
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
            kukiRangeSet(e, e->child, VL(e->parent)->unk_7c);
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
        if (VC(e)->unk_70 != NULL) {
            kukiMgr(e, VC(e)->unk_70);
            alive = TRUE;
        }
        if (VC(e)->unk_74 != NULL) {
            kukiMgr(e, VC(e)->unk_74);
            alive = TRUE;
        }
        if (VC(e)->unk_78 != NULL) {
            kukiMgr(e, VC(e)->unk_78);
            alive = TRUE;
        }
    } else {
        if (VC(e)->unk_70 != NULL) {
            ObjPosCopyOfs32(VC(e)->unk_70->parent, VC(VC(e)->unk_70->parent)->unk_70, 0, 1);
            alive = TRUE;
        }
        if (VC(e)->unk_74 != NULL) {
            ObjPosCopyOfs32(VC(e)->unk_74->parent, VC(VC(e)->unk_74->parent)->unk_70, 0, 1);
            alive = TRUE;
        }
        if (VC(e)->unk_78 != NULL) {
            ObjPosCopyOfs32(VC(e)->unk_78->parent, VC(VC(e)->unk_78->parent)->unk_70, 0, 1);
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
    u8 speed = data_020d0eb8[V(e)->unk_75];
    if (V(e)->unk_72 < 0x30) {
        s16 px = player->x.HALF.HI;
        s16 py = player->y.HALF.HI;
        func_020852f8(player, 0x40, speed);
        if (px == player->x.HALF.HI && py == player->y.HALF.HI) {
            return;
        }
        s16 dist;
        if (V(e)->unk_75 != 0) {
            dist = player->x.HALF.HI - px;
        } else {
            dist = px - player->x.HALF.HI;
        }
        func_020852f8(e, dist << 8, speed);
        em2c_setdist(e);
        if (V(e)->unk_72 >= 0x30) {
            V(e)->unk_77 = 0;
            if (data_021348b8[V(e)->unk_75] != 0) {
                data_021348b8[V(e)->unk_75] = 0;
            }
            data_021348b4 = 1;
            return;
        }
        if (--e->subtimer == 0) {
            e->subtimer = 8;
            EnqueueSFX(0x8b);
        }
        return;
    }
    if (data_020d0ebe[V(e)->unk_75] & data_0212c584[e->type2]) {
        if (V(e)->unk_77 < 0xf) {
            V(e)->unk_77++;
            if (data_021348b8[V(e)->unk_75] != 0) {
                data_021348b8[V(e)->unk_75] = 0;
            }
            return;
        }
        VL(V(e)->unk_7c)->unk_6e |= V(e)->unk_76;
        if (e->parent->action == 6 && (VL(V(e)->unk_7c)->unk_6e & 0xc0) != 0xc0) {
            data_021348b8[V(e)->unk_75] = 0x4b0;
            return;
        }
        e->action = 4;
        e->timer = 0x3c;
        e->x.HALF.HI += data_020d0ebc[V(e)->unk_75];
        EnqueueSFX(0x12);
        Entity *fx = GetSetWork(0xf, 3, 0x20);
        if (fx != NULL) {
            ObjPosCopyOfs32(e, fx, data_020d0ec0[V(e)->unk_75] << 16, 0);
        }
        Entity *item = GetSetWork(0, data_020d0f02[Random() & 7], 1);
        if (item != NULL) {
            item->direction = (((V(e)->unk_75 ^ 1) << 4) + 8) | 0x80;
            ObjPosCopyOfs32(e, item, data_020d0ec0[V(e)->unk_75] << 16, 0);
        }
        return;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        V(e)->unk_77 = 0;
        return;
    }
    if (data_021348b8[V(e)->unk_75] != 0) {
        data_021348b8[V(e)->unk_75]--;
    } else {
        V(e)->unk_77 = 0;
    }
}
