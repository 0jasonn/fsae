#include "Unknown/Object_02033708.h"
#include "global.h"

ARM BOOL func_02034508(Entity *e) {
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
        CopyPosition(e, a);
        CopyPosition(e, b);
        CopyPosition(e, c);
        CopyPosition(e, d);
        func_0204c178(4, a);
        func_0204c178(4, b);
        func_0204c178(4, c);
        func_0204c178(5, d);
        c->direction = 0x20;
        VCT(e)->unk_7d = 0;
        VCT(e)->unk_7c = 1;
        return TRUE;
    }
    return FALSE;
}

