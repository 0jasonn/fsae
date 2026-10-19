#include "engine/functions.h"
#include "enemy/em2d.h"
#include "global.h"

ARM void differentColSet(Entity *e) {
    if (V(e)->unk_70 == NULL) {
        return;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        return;
    }
    V(e)->unk_70->spriteSettings.b20 = data_020d119f[e->spriteSettings.b16][Random() % (data_0212c7c8.unk_0 - 1)];
    V(e)->unk_70->spriteSettings.b16 = V(e)->unk_70->spriteSettings.b20;
}

ARM void openEndSet(Entity *e) {
    Entity *other = V(e)->unk_70;
    if (other == NULL) {
        return;
    }
    e->unk_3f = 0x3f;
    e->hitbox = data_020d11a4;
    other->unk_3c |= 0x80;
    InitAnimationForceUpdate(V(e)->unk_70, 8);
    V(e)->unk_70->unk_28 += Random() & 7;
}

ARM void closeInit(Entity *e) {
    Entity *other = V(e)->unk_70;
    e->unk_3f = 0x40;
    e->hitbox = data_020d119c;
    if (other != NULL) {
        other->unk_3c &= 0x7f;
        InitAnimationForceUpdate(V(e)->unk_70, 7);
    }
    InitAnimationForceUpdate(e, 6);
}

ARM void closeEndSet(Entity *e) {
    V(e)->unk_6e &= 0x3f;
    e->spriteSettings.b20 = e->parent->spriteSettings.b16;
    e->spriteSettings.b16 = e->spriteSettings.b20;
    if (V(e)->unk_70 != NULL) {
        V(e)->unk_70->spriteSettings.b0 = 0;
    }
    InitAnimationForceUpdate(e, 3);
}

ARM BOOL kukiSet(Entity *e) {
    Entity *a;
    Entity *b;
    Entity *c;
    Entity *d;
    if ((a = GetObjWork()) != NULL && (b = GetObjWork2(a)) != NULL && (c = GetObjWork2(b)) != NULL &&
        (d = GetObjWork2(c)) != NULL) {
        a->unk_08 = 3;
        b->unk_08 = 3;
        c->unk_08 = 3;
        d->unk_08 = 3;
        a->unk_09 = 0x2d;
        b->unk_09 = 0x2c;
        c->unk_09 = 0x2c;
        d->unk_09 = 0x2c;
        a->type = 1;
        b->type = 2;
        c->type = 2;
        d->type = 2;
        b->type2 = (e->type2 << 4) | 3;
        c->type2 = (e->type2 << 4) | 2;
        d->type2 = (e->type2 << 4) | 1;
        a->parent = e;
        b->parent = e;
        c->parent = e;
        d->parent = e;
        b->child = e;
        c->child = b;
        d->child = c;
        ObjPosCopy(e, a);
        ObjPosCopy(e, b);
        ObjPosCopy(e, c);
        ObjPosCopy(e, d);
        RegistObjWork(4, a);
        RegistObjWork(4, b);
        RegistObjWork(4, c);
        RegistObjWork(4, d);
        V(e)->unk_70 = a;
        if (e->type2 == 2) {
            b->timer = 0x1e;
            c->timer = 0x3c;
            d->timer = 0x5a;
        } else {
            b->timer = 0xf;
            c->timer = 0x1e;
            d->timer = 0x2d;
        }
        if (VS(e->child)->unk_70 == NULL) {
            VS(e->child)->unk_70 = d;
            V(e)->unk_74 = &VS(e->child)->unk_70;
            return TRUE;
        }
        if (VS(e->child)->unk_74 == NULL) {
            VS(e->child)->unk_74 = d;
            V(e)->unk_74 = &VS(e->child)->unk_74;
            return TRUE;
        } else {
            VS(e->child)->unk_78 = d;
            V(e)->unk_74 = &VS(e->child)->unk_78;
            return TRUE;
        }
    }
    return FALSE;
}

ARM void flowerDie(Entity *e) {
    *V(e)->unk_74 = NULL;
    VCT(e->parent)->unk_7c--;
    Entity *fx = GetSetWork(0xf, 1, 0);
    if (fx != NULL) {
        ObjPosCopy(e, fx);
    }
    testiRupeeSet(e);
    e->action = 0x19;
    e->spriteSettings.b0 = 0;
    e->unk_3c &= 0x7f;
    e->health = 0;
    if (V(e)->unk_70 != NULL) {
        PutObjWork(V(e)->unk_70);
    }
}

ARM void seedSet(Entity *e) {
    Entity *proj = GetTamaWork(0xe);
    if (proj == NULL) {
        return;
    }
    proj->direction = e->animationState << 2;
    ObjPosCopyOfs32(e, proj, data_020f2686[e->animationState * 2] << 16, data_020f2686[e->animationState * 2 + 1] << 16);
    EnqueueSFX(0xa5);
}

