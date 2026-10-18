#include "Unknown/Enemy_020347dc.h"
#include "global.h"

ARM void func_02035ba4(Entity *e) {
    if (V(e)->unk_70 == NULL) {
        return;
    }
    if (func_0208de54(func_0208da4c()) == 0) {
        return;
    }
    V(e)->unk_70->unk_1c.b20 = data_020d119f[e->unk_1c.b16][func_0208455c() % (data_0212c7c8.unk_0 - 1)];
    V(e)->unk_70->unk_1c.b16 = V(e)->unk_70->unk_1c.b20;
}

ARM void func_02035c3c(Entity *e) {
    Entity *other = V(e)->unk_70;
    if (other == NULL) {
        return;
    }
    e->unk_3f = 0x3f;
    e->unk_48 = data_020d11a4;
    other->unk_3c |= 0x80;
    func_020859e0(V(e)->unk_70, 8);
    V(e)->unk_70->unk_28 += func_0208455c() & 7;
}

ARM void func_02035c98(Entity *e) {
    Entity *other = V(e)->unk_70;
    e->unk_3f = 0x40;
    e->unk_48 = data_020d119c;
    if (other != NULL) {
        other->unk_3c &= 0x7f;
        func_020859e0(V(e)->unk_70, 7);
    }
    func_020859e0(e, 6);
}

ARM void func_02035ce8(Entity *e) {
    V(e)->unk_6e &= 0x3f;
    e->unk_1c.b20 = e->unk_54->unk_1c.b16;
    e->unk_1c.b16 = e->unk_1c.b20;
    if (V(e)->unk_70 != NULL) {
        V(e)->unk_70->unk_1c.b0 = 0;
    }
    func_020859e0(e, 3);
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
        a->unk_0a = 1;
        b->unk_0a = 2;
        c->unk_0a = 2;
        d->unk_0a = 2;
        b->unk_0b = (e->unk_0b << 4) | 3;
        c->unk_0b = (e->unk_0b << 4) | 2;
        d->unk_0b = (e->unk_0b << 4) | 1;
        a->unk_54 = e;
        b->unk_54 = e;
        c->unk_54 = e;
        d->unk_54 = e;
        b->unk_58 = e;
        c->unk_58 = b;
        d->unk_58 = c;
        func_0205031c(e, a);
        func_0205031c(e, b);
        func_0205031c(e, c);
        func_0205031c(e, d);
        func_0204c178(4, a);
        func_0204c178(4, b);
        func_0204c178(4, c);
        func_0204c178(4, d);
        V(e)->unk_70 = a;
        if (e->unk_0b == 2) {
            b->unk_17 = 0x1e;
            c->unk_17 = 0x3c;
            d->unk_17 = 0x5a;
        } else {
            b->unk_17 = 0xf;
            c->unk_17 = 0x1e;
            d->unk_17 = 0x2d;
        }
        if (VS(e->unk_58)->unk_70 == NULL) {
            VS(e->unk_58)->unk_70 = d;
            V(e)->unk_74 = &VS(e->unk_58)->unk_70;
            return TRUE;
        }
        if (VS(e->unk_58)->unk_74 == NULL) {
            VS(e->unk_58)->unk_74 = d;
            V(e)->unk_74 = &VS(e->unk_58)->unk_74;
            return TRUE;
        } else {
            VS(e->unk_58)->unk_78 = d;
            V(e)->unk_74 = &VS(e->unk_58)->unk_78;
            return TRUE;
        }
    }
    return FALSE;
}

ARM void func_02035f18(Entity *e) {
    *V(e)->unk_74 = NULL;
    VCT(e->unk_54)->unk_7c--;
    Entity *fx = func_02076858(0xf, 1, 0);
    if (fx != NULL) {
        func_0205031c(e, fx);
    }
    func_0203614c(e);
    e->unk_14 = 0x19;
    e->unk_1c.b0 = 0;
    e->unk_3c &= 0x7f;
    e->unk_45 = 0;
    if (V(e)->unk_70 != NULL) {
        func_0204be88(V(e)->unk_70);
    }
}

ARM void func_02035f9c(Entity *e) {
    Entity *proj = func_0204bdb8(0xe);
    if (proj == NULL) {
        return;
    }
    proj->unk_2b = e->unk_2a << 2;
    func_02050390(e, proj, data_020f2686[e->unk_2a * 2] << 16, data_020f2686[e->unk_2a * 2 + 1] << 16);
    func_02085f80(0xa5);
}

