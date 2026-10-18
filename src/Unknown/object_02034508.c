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
        a->unk_0a = 1;
        b->unk_0a = 1;
        d->unk_0a = 3;
        c->unk_0b = 2;
        d->unk_0b = 2;
        a->unk_54 = e;
        b->unk_54 = e;
        c->unk_54 = e;
        d->unk_54 = e;
        a->unk_58 = d;
        b->unk_58 = d;
        c->unk_58 = d;
        V(a)->unk_75 = 0;
        V(b)->unk_75 = 1;
        V(a)->unk_76 = 0x80;
        V(b)->unk_76 = 0x40;
        V(a)->unk_7c = c;
        V(b)->unk_7c = c;
        func_0205031c(e, a);
        func_0205031c(e, b);
        func_0205031c(e, c);
        func_0205031c(e, d);
        func_0204c178(4, a);
        func_0204c178(4, b);
        func_0204c178(4, c);
        func_0204c178(5, d);
        c->unk_2b = 0x20;
        VCT(e)->unk_7d = 0;
        VCT(e)->unk_7c = 1;
        return TRUE;
    }
    return FALSE;
}

