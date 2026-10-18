#include "enemy/enemy_020347dc.h"
#include "global.h"

ARM void func_02035ba4(Entity *e) {
    if (V(e)->unk_70 == NULL) {
        return;
    }
    if (func_0208de54(func_0208da4c()) == 0) {
        return;
    }
    V(e)->unk_70->spriteSettings.b20 = data_020d119f[e->spriteSettings.b16][Random() % (data_0212c7c8.unk_0 - 1)];
    V(e)->unk_70->spriteSettings.b16 = V(e)->unk_70->spriteSettings.b20;
}

ARM void func_02035c3c(Entity *e) {
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

ARM void func_02035c98(Entity *e) {
    Entity *other = V(e)->unk_70;
    e->unk_3f = 0x40;
    e->hitbox = data_020d119c;
    if (other != NULL) {
        other->unk_3c &= 0x7f;
        InitAnimationForceUpdate(V(e)->unk_70, 7);
    }
    InitAnimationForceUpdate(e, 6);
}

ARM void func_02035ce8(Entity *e) {
    V(e)->unk_6e &= 0x3f;
    e->spriteSettings.b20 = e->parent->spriteSettings.b16;
    e->spriteSettings.b16 = e->spriteSettings.b20;
    if (V(e)->unk_70 != NULL) {
        V(e)->unk_70->spriteSettings.b0 = 0;
    }
    InitAnimationForceUpdate(e, 3);
}

ARM BOOL func_02035d50(Entity *e) {
    Entity *a;
    Entity *b;
    Entity *c;
    Entity *d;
    if ((a = func_0204bcc8()) != NULL && (b = func_0204bd00()) != NULL && (c = func_0204bd00()) != NULL &&
        (d = func_0204bd00()) != NULL) {
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
        CopyPosition(e, a);
        CopyPosition(e, b);
        CopyPosition(e, c);
        CopyPosition(e, d);
        func_0204c178(4, a);
        func_0204c178(4, b);
        func_0204c178(4, c);
        func_0204c178(4, d);
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

ARM void func_02035f18(Entity *e) {
    *V(e)->unk_74 = NULL;
    VCT(e->parent)->unk_7c--;
    Entity *fx = CreateFx(0xf, 1, 0);
    if (fx != NULL) {
        CopyPosition(e, fx);
    }
    func_0203614c(e);
    e->action = 0x19;
    e->spriteSettings.b0 = 0;
    e->unk_3c &= 0x7f;
    e->health = 0;
    if (V(e)->unk_70 != NULL) {
        DeleteEntity(V(e)->unk_70);
    }
}

ARM void func_02035f9c(Entity *e) {
    Entity *proj = CreateProjectile(0xe);
    if (proj == NULL) {
        return;
    }
    proj->direction = e->animationState << 2;
    PositionRelative(e, proj, data_020f2686[e->animationState * 2] << 16, data_020f2686[e->animationState * 2 + 1] << 16);
    EnqueueSFX(0xa5);
}

