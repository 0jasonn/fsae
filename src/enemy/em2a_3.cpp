#include "engine/functions.h"
#include "enemy/em2a.h"
#include "global.h"

typedef struct Vars_BossCore {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *corePart0;
    /* 68 */ u8 unk_68[0xc];
    /* 74 */ Entity *corePart1;
    /* 78 */ Entity *corePart2;
    /* 7c */ Entity *corePart3;
} Vars_BossCore;
#define VC(e) VARS(Vars_BossCore, e)

typedef struct Vars_BossPart {
    /* 00 */ u8 unk_00[0x72];
    /* 72 */ u8 slot;
    /* 73 */ u8 pattern;
    /* 74 */ u8 subtimerStart;
} Vars_BossPart;
#define VP(e) VARS(Vars_BossPart, e)

extern const u8 *const em2a_healthTable[];
extern const u8 em2a_debrisItems[][6];
extern const u16 em2a_waitTimes[];
extern u8 localPlayerIndex;


extern const u8 em2a_corePartTypes[][4];
extern const u8 em2a_corePatterns[][4];

ARM void em2a_shadowinit(Entity *e) {
    e->action++;
    e->spriteSettings.b0 = 1;
    Entity *parent = e->parent;
    e->unk_50 = parent->unk_50;
    e->spriteSettings.b16 = parent->spriteSettings.b16;
    e->spriteSettings.b20 = e->spriteSettings.b16;
    e->spriteSettings.b6 = parent->spriteSettings.b6;
    e->unk_20 = parent->unk_20;
    e->x.WORD = parent->x.WORD;
    e->y.WORD = parent->y.WORD;
    if (e->timer == 0) {
        e->unk_3c = 0;
    } else {
        e->unk_2e = 8;
        e->spriteSettings.b4 = 3;
        e->unk_5e.b2 = 2;
    }
    e->hitbox = em2a_hitboxType2;
    shadowmoveset(e);
}

ARM void shadowmoveset(Entity *e) {
    VH(e)->targetX = e->parent->x.HALF.HI + em2a_shadowOffsets[VH(e)->shadowStep * 2];
    VH(e)->targetY = e->parent->y.HALF.HI + em2a_shadowOffsets[VH(e)->shadowStep * 2 + 1];
    e->subtimer = 0;
    e->speed = 0x300;
    e->zVelocity = 0x30000;
    InitAnimationForceUpdate(e, 0xb);
}

ARM void em2a_shadowmove(Entity *e) {
    Entity *parent = e->parent;
    if (parent->action == 6 || parent->action == 2) {
        if (e->timer != 0) {
            parent->x.WORD = e->x.WORD;
            e->parent->y.WORD = e->y.WORD;
        }
        PutObjWork(e);
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (e->frame == 0) {
        MoveDir(e);
        s16 dx = e->x.HALF.HI - VH(e)->targetX;
        s16 dy = e->y.HALF.HI - (s16)VH(e)->targetY;
        if (dx <= 3 && dx >= -3) {
            e->x.HALF.HI = VH(e)->targetX;
            e->subtimer |= 1;
        }
        if (dy <= 3 && dy >= -3) {
            e->y.HALF.HI = VH(e)->targetY;
            e->subtimer |= 2;
        }
        if (e->subtimer == 3) {
            e->direction = 0xff;
            if (UpdateGravity(e, 0x2000) == 0) {
                e->unk_28 = 1;
                if (e->timer != 0) {
                    Entity *fx = GetSetWork(0x60, 0, 0);
                    if (fx != NULL) {
                        fx->unk_1b = 0x81;
                        fx->unk_23 = 0xd;
                        fx->x.HALF.HI = e->x.HALF.HI;
                        fx->y.HALF.HI = e->y.HALF.HI;
                        fx->spriteSettings.b16 = e->spriteSettings.b16 + 1;
                        fx->spriteSettings.b14 = e->spriteSettings.b14;
                        fx->spriteSettings.b30 = e->spriteSettings.b30;
                        fx->spriteSettings.b6 = e->spriteSettings.b6;
                        fx->unk_20 = e->unk_20;
                        fx->unk_5e.b0 = 0;
                    }
                    SoundReq(0xa7);
                }
                V(e->parent)->shadowLandMask |= (u8)(1 << (e->type2 & 0xf));
            }
        } else {
            e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, VH(e)->targetX, (s16)VH(e)->targetY);
            if (e->zVelocity == 0) {
                e->unk_28 = 2;
            } else {
                UpdateGravity(e, 0x1000);
            }
        }
    } else if (e->frame & 0x80) {
        if (V(e->parent)->shadowLandMask == 0) {
            VH(e)->shadowStep = (VH(e)->shadowStep + 1) & 7;
            shadowmoveset(e);
        }
    }
    e->subtimer |= em2a_areaCheck(e);
}

ARM void coreSync(Entity *e) {
    VC(e)->corePart0->unk_21 = e->unk_21 + 0xf;
    VC(e)->corePart1->unk_21 = e->unk_21 + 0x1c;
    VC(e)->corePart2->unk_21 = e->unk_21 + 0x29;
    VC(e)->corePart3->unk_21 = e->unk_21 + 0x36;
}

ARM void coreSet(Entity *e) {
    if ((VC(e)->corePart0 = GetEnemyWork(0x2a)) != NULL) {
        VC(e)->corePart0->parent = e;
        VC(e)->corePart0->type = 1;
        VC(e)->corePart0->timer = 0;
        VP(VC(e)->corePart0)->subtimerStart = 0xf;
        VC(e)->corePart0->subtimer = VP(VC(e)->corePart0)->subtimerStart;
        VC(e)->corePart0->spriteSettings.b6 = e->spriteSettings.b6;
        VC(e)->corePart0->unk_20 = e->unk_20;
    }
    if ((VC(e)->corePart1 = GetEnemyWork(0x2a)) != NULL) {
        VC(e)->corePart1->parent = e;
        VC(e)->corePart1->type = 1;
        VC(e)->corePart1->timer = 1;
        VP(VC(e)->corePart1)->subtimerStart = 0xf;
        VC(e)->corePart1->subtimer = VP(VC(e)->corePart1)->subtimerStart;
        VC(e)->corePart1->spriteSettings.b6 = e->spriteSettings.b6;
        VC(e)->corePart1->unk_20 = e->unk_20;
    }
    if ((VC(e)->corePart2 = GetEnemyWork(0x2a)) != NULL) {
        VC(e)->corePart2->parent = e;
        VC(e)->corePart2->type = 1;
        VC(e)->corePart2->timer = 2;
        VP(VC(e)->corePart2)->subtimerStart = 0xf;
        VC(e)->corePart2->subtimer = VP(VC(e)->corePart2)->subtimerStart;
        VC(e)->corePart2->spriteSettings.b6 = e->spriteSettings.b6;
        VC(e)->corePart2->unk_20 = e->unk_20;
    }
    if ((VC(e)->corePart3 = GetEnemyWork(0x2a)) != NULL) {
        VC(e)->corePart3->parent = e;
        VC(e)->corePart3->type = 1;
        VC(e)->corePart3->timer = 3;
        VP(VC(e)->corePart3)->subtimerStart = 0xf;
        VC(e)->corePart3->subtimer = VP(VC(e)->corePart3)->subtimerStart;
        VC(e)->corePart3->spriteSettings.b6 = e->spriteSettings.b6;
        VC(e)->corePart3->unk_20 = e->unk_20;
    }
    u8 formation = Random() & 0xf;
    VC(e)->corePart0->type2 = em2a_corePartTypes[formation][0] | 0x80;
    VC(e)->corePart1->type2 = em2a_corePartTypes[formation][1] | 0x80;
    VC(e)->corePart2->type2 = em2a_corePartTypes[formation][2] | 0x80;
    VC(e)->corePart3->type2 = em2a_corePartTypes[formation][3] | 0x80;
    u8 rnd = Random() & 3;
    u8 idx = rnd + (data_0212c7c8.unk_0 - 1) * 4;
    VP(VC(e)->corePart0)->pattern = em2a_corePatterns[idx][VC(e)->corePart0->type2 & 0xf];
    VP(VC(e)->corePart1)->pattern = em2a_corePatterns[idx][VC(e)->corePart1->type2 & 0xf];
    VP(VC(e)->corePart2)->pattern = em2a_corePatterns[idx][VC(e)->corePart2->type2 & 0xf];
    VP(VC(e)->corePart3)->pattern = em2a_corePatterns[idx][VC(e)->corePart3->type2 & 0xf];
    SoundReq(0xa3);
}

ARM void shadowSet(Entity *e) {
    u8 i;
    u8 pick = Random() & 3;
    u8 flip = Random() & 1;
    for (i = 0; i < 4; i++) {
        Entity *part = GetEnemyWork(0x2a);
        if (part != NULL) {
            part->type = 1;
            part->type2 = i | 0x40;
            VP(part)->slot = flip + i * 2;
            part->parent = e;
            if (i == pick) {
                part->timer = 0xff;
            } else {
                part->timer = 0;
            }
        }
    }
    SoundReq(0xa1);
}

ARM void nearplcheck(Entity *e) {
    int playerIndex = ObjNearPlCheck(e, 0, 0);
    e->subtimer = playerIndex;
    e->direction = func_02086078(data_0212ceb0[playerIndex].entity, e);
}

ARM void jumpefectSet(Entity *e) {
    if (e->type == 2 && e->spriteSettings.b0 == 0) {
        return;
    }
    Entity *fx = GetSetWork(0x60, 0, 0);
    if (fx != NULL) {
        fx->unk_1b = 0x81;
        fx->unk_23 = (e->type - 1) * 10 + 3;
        fx->x.HALF.HI = e->x.HALF.HI;
        fx->y.HALF.HI = e->y.HALF.HI;
        fx->spriteSettings.b16 = e->spriteSettings.b16 + 1;
        fx->spriteSettings.b14 = e->spriteSettings.b14;
        fx->spriteSettings.b30 = e->spriteSettings.b30;
        fx->spriteSettings.b6 = e->spriteSettings.b6;
        fx->unk_20 = e->unk_20;
        fx->unk_5e.b0 = 0;
    }
    SoundReq(0xa7);
}

ARM void bigjumpinit(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_3f = 0x3d;
    e->unk_3c |= 0x80;
    V(e)->hitWindow = 0;
    e->speed = 0x300;
    e->zVelocity = 0x30000;
    e->action = 2;
    e->timer = 0x20;
    e->subtimer = 0;
    if (e->type > 1) {
        InitAnimationForceUpdate(e, (e->type - 1) * 10 + 2);
    } else {
        InitAnimationForceUpdate(e, 2);
    }
}

ARM void lifeset(Entity *e) {
    e->health = em2a_healthTable[data_0212c7c8.unk_0 - 1][e->type - 1];
}

ARM void em2a_ruppyset(Entity *e) {
    if (V(e)->effectTimer == 0) {
        return;
    }
    if (V(e)->hitLevel >= 5) {
        V(e)->hitLevel = 4;
    }
    for (u8 i = 0; em2a_debrisItems[V(e)->hitLevel][i] != 0xff; i++) {
        Entity *debris = ItemSet(e, em2a_debrisItems[V(e)->hitLevel][i]);
        if (debris != NULL) {
            debris->x.HALF.HI -= 8;
            debris->z.HALF.HI = -0x10;
            debris->direction = ((Random() & 7) + 0x14) | 0x80;
            debris->type2 = 1;
        }
    }
}

ARM void move3Init(Entity *e) {
    V(e)->waitTimer = em2a_waitTimes[Random() & 7];
    e->direction = func_02086078(e, data_0212ceb0[e->timer].entity) & 0x18;
    e->speed = 0x100;
    e->zVelocity = 0x20000;
    InitAnimationForceUpdate(e, (e->type - 1) * 10 + 1);
}

ARM u8 em2a_areaCheck(Entity *e) {
    u8 result = 0;
    if (e->x.HALF.HI < 0x198) {
        e->x.HALF.HI = 0x198;
        result = 1;
    } else if (e->x.HALF.HI > 0x250) {
        if (!(e->type2 & 0x40) && e->z.WORD == 0) {
            bigjumpinit(e);
        }
        if (e->x.HALF.HI > 0x298) {
            e->x.HALF.HI = 0x298;
            result = 1;
        }
    }
    if (e->y.HALF.HI < 0x1a8) {
        e->y.HALF.HI = 0x1a8;
        result |= 2;
    } else if (e->y.HALF.HI > 0x248) {
        e->y.HALF.HI = 0x248;
        result |= 2;
    }
    return result;
}

ARM u8 move3search(Entity *e) {
    u8 i;
    u8 best;
    u16 bestDist = 0xffff;
    best = 0xff;
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        if (e->timer != i) {
            Entity *player = data_0212ceb0[i].entity;
            if (player->x.HALF.HI < 0x250) {
                s16 dx = player->x.HALF.HI - e->x.HALF.HI;
                s16 dy = player->y.HALF.HI - e->y.HALF.HI;
                dx = -dx;
                dy = -dy;
                if (best == 0xff) {
                    bestDist = dy + dx;
                    best = i;
                } else if (bestDist > (u16)(dy + dx)) {
                    bestDist = dy + dx;
                    best = i;
                }
            }
        }
    }
    return best;
}

ARM void flashcheck(Entity *e) {
    if (e->type != 3) {
        return;
    }
    u8 player = localPlayerIndex;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        player = *Knife_Single_SinglePlay_GetInstance();
    }
    if (player == V(e)->flashPlayer) {
        e->spriteSettings.b0 = 1;
    } else {
        e->spriteSettings.b0 = 0;
    }
}

ARM void efectset(Entity *e) {
    for (u8 i = 0; i < 4; i++) {
        Entity *fx = GetSetWork(0xf, 0xd, 0x20);
        if (fx != NULL) {
            ObjPosCopy(e, fx);
            fx->y.HALF.HI -= 0x10;
            fx->speed = (Random() & 0x1f) << 8;
            fx->direction = Random() & 0x1f;
            MoveDir(fx);
        }
    }
}
