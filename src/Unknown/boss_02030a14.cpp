#include "Unknown/Boss_02030a14.hpp"
#include "global.h"

ARM extern "C" void func_02030a14(Entity *e) {
    s8 count = 0;
    Entity *a = func_0204bd80(3);
    if (a != NULL) {
        count++;
        a->unk_3d = 0xf0;
    }
    Entity *b = func_0204bd80(3);
    if (b != NULL) {
        b->unk_30.HALF.HI -= 6;
        b->unk_3d = 0xf0;
        count++;
    }
    func_02045c20(e, a, b);
    if (count == 2) {
        a->unk_54 = b;
        b->unk_54 = a;
    }
    Entity *counter = V(e)->unk_60;
    if (counter != NULL) {
        VARS(Vars_Counter, counter)->unk_62 += count;
    }
    Entity *fx = func_02076858(0xf, 2, 0);
    if (fx != NULL) {
        fx->unk_30.HALF.HI = e->unk_30.HALF.HI - 4;
        fx->unk_34.HALF.HI = e->unk_34.HALF.HI;
        fx->unk_50 = e->unk_50;
    }
    func_0204be88(e);
}

ARM extern "C" void func_02030ae4(int index) {
    data_0212ceb0[index].unk_0c = 6;
    data_0212ceb0[index].unk_38 = 1;
    PlayerData *other = NULL;
    if (data_0212ceb0[index].unk_1e & 0x80) {
        other = V(data_0212ceb0[index].unk_28)->unk_64;
    } else if (data_0212ceb0[index].unk_1e & 0x20) {
        other = (PlayerData *)V(data_0212ceb0[index].unk_28)->unk_60;
    }
    if (other != NULL && other->unk_0c != 6 && other->unk_28->unk_14 != 6) {
        other->unk_0c = 6;
        other->unk_38 = 1;
    }
}

ARM extern "C" void func_02030b70(Entity *e) {
    if (e->unk_0b & 0x80) {
        func_02031cb0(e);
        return;
    }
    if (e->unk_0b & 0x40) {
        data_020d0a7c[e->unk_14](e);
        if (e->unk_17 == 0) {
            return;
        }
        if (e->unk_38.WORD != 0) {
            return;
        }
        if (!(e->unk_41 & 0x80)) {
            return;
        }
        if ((e->unk_41 & 0x7f) != 0x10) {
            return;
        }
        Entity *hitter = e->unk_4c;
        data_0212ceb0[hitter->unk_0a].unk_0c = 6;
        data_0212ceb0[hitter->unk_0a].unk_38 = 1;
        e->unk_3d = 0xfe;
        if (hitter->unk_2a != 2) {
            return;
        }
        e->unk_54->unk_30.WORD = e->unk_30.WORD;
        e->unk_54->unk_34.WORD = e->unk_34.WORD;
        e->unk_54->unk_38.WORD = 0;
        e->unk_54->unk_3c |= 0x80;
        e->unk_54->unk_1c.b0 = 1;
        e->unk_54->unk_0c = 0x200;
        e->unk_54->unk_10 = 0x18000;
        e->unk_54->unk_2b = 8;
        func_020859e0(e->unk_54, 0xe);
        e->unk_54->unk_14 = 6;
        V(e->unk_54)->unk_74 = 0;
        V(e->unk_54)->unk_75 = 0x1e;
        func_02032b78(e->unk_54);
        func_02076fe0(0xa6);
        func_02076fe0(0xa3);
        func_0204be88(e);
        return;
    }
    if (e->unk_0a >= 4) {
        if (e->unk_45 == 0) {
            func_02045ac0(e);
            e->unk_0a = 5;
            return;
        }
    } else {
        if (V(e)->unk_7c != 0) {
            V(e)->unk_7c--;
        }
        if (e->unk_14 != 8 && e->unk_38.WORD == 0 && e->unk_0a != 0 && (e->unk_41 & 0x80) && (e->unk_41 & 0x7f) != 0) {
            if ((e->unk_41 & 0x7f) == 0x10) {
                Entity *hitter = e->unk_4c;
                data_0212ceb0[hitter->unk_0a].unk_0c = 6;
                data_0212ceb0[hitter->unk_0a].unk_38 = 1;
                e->unk_3d = 0xfe;
                if (hitter->unk_2a == 2) {
                    e->unk_1c.b0 = 1;
                    e->unk_0c = 0x200;
                    e->unk_10 = 0x18000;
                    e->unk_2b = 8;
                    func_020859e0(e, (e->unk_0a - 1) * 10 + 4);
                    if (V(e)->unk_75 != 0) {
                        V(e)->unk_74++;
                    } else {
                        V(e)->unk_74 = 0;
                    }
                    V(e)->unk_75 = 0x1e;
                    func_02032b78(e);
                    e->unk_14 = 6;
                    func_02076fe0(0xa6);
                }
                if (e->unk_0a == 3 && e->unk_14 != 2 && e->unk_14 != 6 && e->unk_14 != 7) {
                    func_02076fe0(0xa3);
                }
            } else {
                e->unk_3d = 0xd8;
                func_020859e0(e, (e->unk_0a - 1) * 10 + 5);
                V(e)->unk_72 = e->unk_14;
                e->unk_14 = 5;
            }
        }
    }
    data_020d0dc0[e->unk_14](e);
}

ARM extern "C" void func_02030e90(Entity *e) {
    Entity *child = func_02076858(0x65, 0, 0);
    if (child != NULL) {
        child->unk_54 = e;
    }
    e->unk_1c.b16++;
    e->unk_1c.b20 = e->unk_1c.b16;
    e->unk_14 = 1;
    e->unk_1c.b0 = 1;
    func_020859e0(e, 6);
    e->unk_17 = data_0212c7c8.unk_0 * 3;
    e->unk_18 = 0xb4;
    V(e)->unk_7c = 0x2a30;
    e->unk_0c = 0x300;
    e->unk_2e = 8;
    e->unk_1c.b4 = 3;
    e->unk_5e.b2 = 2;
    e->unk_48 = data_020d0a62;
    e->unk_6a = 1;
    e->unk_3f = 0x48;
    e->unk_58 = data_0212c648;
    data_0212c648 = e;
    func_020266f8();
}

ARM extern "C" void func_02030f8c(Entity *e) {
    if (e->unk_18 != 0) {
        if (e->unk_18 == 0x3c) {
            data_0212c648 = e->unk_58;
        } else if (e->unk_18 == 0x1e) {
            func_02026720();
        }
        func_020547ec();
        e->unk_18--;
    }
    if (!(e->unk_41 & 0x80)) {
        return;
    }
    switch (e->unk_41 & 0x7f) {
        case 0x10:
            func_02030ae4(e->unk_4c->unk_0a);
        case 4:
        case 8:
        case 0xc:
            break;
        default:
            return;
    }
    e->unk_3d = 0xe8;
    if (--e->unk_17 == 0) {
        e->unk_1c.b16 = e->unk_1c.b20 - 1;
        e->unk_1c.b20 = e->unk_1c.b16;
        func_02032ac4(e);
    }
    func_02032e5c(e);
}

ARM extern "C" void func_02031084(Entity *e) {
    func_02085980(e);
    if (e->unk_29 == 0) {
        return;
    }
    if (e->unk_29 & 0x40) {
        func_02076fe0(0xa8);
    }
    func_0204fd40(e);
    s16 dx = e->unk_30.HALF.HI - 0x1f8;
    s16 dy = e->unk_34.HALF.HI - 0x1f8;
    if (dx <= 3 && dx >= -3) {
        e->unk_30.HALF.HI = 0x1f8;
        e->unk_18 |= 1;
    }
    if (dy <= 3 && dy >= -3) {
        e->unk_34.HALF.HI = 0x1f8;
        e->unk_18 |= 2;
    }
    if (e->unk_18 == 3) {
        if (e->unk_17 != 0) {
            e->unk_17--;
            e->unk_2b = 0xff;
            e->unk_10 = 0;
            return;
        }
        if (func_020856cc(e, 0x2000) != 0) {
            return;
        }
        e->unk_14++;
        if (e->unk_0a != 0) {
            func_02076858(0x61, 0, 0);
        } else {
            e->unk_0a = 1;
            func_02032b48(e);
            func_02076fe0(0x19c);
        }
        func_020859e0(e, (e->unk_0a - 1) * 10 + 8);
        func_020329c8(e);
        func_0205747c(0x10, 3);
        return;
    }
    e->unk_2b = func_02086080(e->unk_30.HALF.HI, e->unk_34.HALF.HI, 0x1f8, 0x1f8);
    if (e->unk_10 == 0) {
        return;
    }
    func_020856cc(e, 0x1000);
}
