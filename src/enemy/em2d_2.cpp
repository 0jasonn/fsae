#include "engine/functions.h"
#include "enemy/em2d.h"
#include "global.h"

ARM void differentColSet(Entity *e) {
    if (V(e)->petal == NULL) {
        return;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        return;
    }
    V(e)->petal->spriteSettings.b20 = em2d_petalColors[e->spriteSettings.b16][Random() % (data_0212c7c8.unk_0 - 1)];
    V(e)->petal->spriteSettings.b16 = V(e)->petal->spriteSettings.b20;
}

ARM void openEndSet(Entity *e) {
    Entity *other = V(e)->petal;
    if (other == NULL) {
        return;
    }
    e->unk_3f = 0x3f;
    e->hitbox = em2d_openHitbox;
    other->unk_3c |= 0x80;
    InitAnimationForceUpdate(V(e)->petal, 8);
    V(e)->petal->unk_28 += Random() & 7;
}

ARM void closeInit(Entity *e) {
    Entity *other = V(e)->petal;
    e->unk_3f = 0x40;
    e->hitbox = em2d_closeHitbox;
    if (other != NULL) {
        other->unk_3c &= 0x7f;
        InitAnimationForceUpdate(V(e)->petal, 7);
    }
    InitAnimationForceUpdate(e, 6);
}

ARM void closeEndSet(Entity *e) {
    V(e)->phaseFlags &= 0x3f;
    e->spriteSettings.b20 = e->parent->spriteSettings.b16;
    e->spriteSettings.b16 = e->spriteSettings.b20;
    if (V(e)->petal != NULL) {
        V(e)->petal->spriteSettings.b0 = 0;
    }
    InitAnimationForceUpdate(e, 3);
}

ARM BOOL kukiSet(Entity *e) {
    Entity *partA;
    Entity *partB;
    Entity *partC;
    Entity *partD;
    if ((partA = GetObjWork()) != NULL && (partB = GetObjWork2(partA)) != NULL && (partC = GetObjWork2(partB)) != NULL &&
        (partD = GetObjWork2(partC)) != NULL) {
        partA->unk_08 = 3;
        partB->unk_08 = 3;
        partC->unk_08 = 3;
        partD->unk_08 = 3;
        partA->unk_09 = 0x2d;
        partB->unk_09 = 0x2c;
        partC->unk_09 = 0x2c;
        partD->unk_09 = 0x2c;
        partA->type = 1;
        partB->type = 2;
        partC->type = 2;
        partD->type = 2;
        partB->type2 = (e->type2 << 4) | 3;
        partC->type2 = (e->type2 << 4) | 2;
        partD->type2 = (e->type2 << 4) | 1;
        partA->parent = e;
        partB->parent = e;
        partC->parent = e;
        partD->parent = e;
        partB->child = e;
        partC->child = partB;
        partD->child = partC;
        ObjPosCopy(e, partA);
        ObjPosCopy(e, partB);
        ObjPosCopy(e, partC);
        ObjPosCopy(e, partD);
        RegistObjWork(4, partA);
        RegistObjWork(4, partB);
        RegistObjWork(4, partC);
        RegistObjWork(4, partD);
        V(e)->petal = partA;
        if (e->type2 == 2) {
            partB->timer = 0x1e;
            partC->timer = 0x3c;
            partD->timer = 0x5a;
        } else {
            partB->timer = 0xf;
            partC->timer = 0x1e;
            partD->timer = 0x2d;
        }
        if (VS(e->child)->segmentA == NULL) {
            VS(e->child)->segmentA = partD;
            V(e)->segmentSlot = &VS(e->child)->segmentA;
            return TRUE;
        }
        if (VS(e->child)->segmentB == NULL) {
            VS(e->child)->segmentB = partD;
            V(e)->segmentSlot = &VS(e->child)->segmentB;
            return TRUE;
        } else {
            VS(e->child)->segmentC = partD;
            V(e)->segmentSlot = &VS(e->child)->segmentC;
            return TRUE;
        }
    }
    return FALSE;
}

ARM void flowerDie(Entity *e) {
    *V(e)->segmentSlot = NULL;
    VCT(e->parent)->flowerCount--;
    Entity *fx = GetSetWork(0xf, 1, 0);
    if (fx != NULL) {
        ObjPosCopy(e, fx);
    }
    testiRupeeSet(e);
    e->action = 0x19;
    e->spriteSettings.b0 = 0;
    e->unk_3c &= 0x7f;
    e->health = 0;
    if (V(e)->petal != NULL) {
        PutObjWork(V(e)->petal);
    }
}

ARM void seedSet(Entity *e) {
    Entity *proj = GetTamaWork(0xe);
    if (proj == NULL) {
        return;
    }
    proj->direction = e->animationState << 2;
    ObjPosCopyOfs32(e, proj, em2d_seedOffsets[e->animationState * 2] << 16, em2d_seedOffsets[e->animationState * 2 + 1] << 16);
    EnqueueSFX(0xa5);
}

