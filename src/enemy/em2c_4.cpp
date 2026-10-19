#include "engine/functions.h"
#include "enemy/em2c.h"
#include "global.h"

ARM BOOL set3rd(Entity *e) {
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
        a->unk_09 = 0x2c;
        b->unk_09 = 0x2c;
        c->unk_09 = 0x2d;
        d->unk_09 = 0x2c;
        a->type = 1;
        b->type = 1;
        d->type = 3;
        c->type2 = 2;
        d->type2 = 2;
        a->parent = e;
        b->parent = e;
        c->parent = e;
        d->parent = e;
        a->child = d;
        b->child = d;
        c->child = d;
        V(a)->unk_75 = 0;
        V(b)->unk_75 = 1;
        V(a)->unk_76 = 0x80;
        V(b)->unk_76 = 0x40;
        V(a)->unk_7c = c;
        V(b)->unk_7c = c;
        ObjPosCopy(e, a);
        ObjPosCopy(e, b);
        ObjPosCopy(e, c);
        ObjPosCopy(e, d);
        RegistObjWork(4, a);
        RegistObjWork(4, b);
        RegistObjWork(4, c);
        RegistObjWork(5, d);
        c->direction = 0x20;
        VCT(e)->unk_7d = 0;
        VCT(e)->unk_7c = 1;
        return TRUE;
    }
    return FALSE;
}

