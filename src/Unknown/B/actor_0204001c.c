#include "Unknown/B/Actor_0204001c.h"
#include "global.h"

ARM void func_0204001c(Entity *e) {
    func_02085980(e);
    if (V(e)->unk_64 == NULL) {
        V(e)->unk_64 = func_02084f98(e, 0x58, 0x58);
    }
    if ((e->unk_29 & 0x20) && V(e)->unk_64 != NULL) {
        func_02040334(e);
        return;
    }
    if (e->unk_29 & 0x80) {
        func_02040304(e);
    }
}

ARM void func_0204007c(Entity *e) {
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14 = 5;
    e->unk_17 = 0x78;
    e->unk_18 = 0x1e;
    e->unk_0c = 0x100;
}

ARM void func_020400b4(Entity *e) {
    if (e->unk_18 != 0) {
        e->unk_18--;
    }
    if (e->unk_18 == 0 && func_02040368(e)) {
        e->unk_14 = 6;
        e->unk_0c = 0x280;
        e->unk_2b = (e->unk_2a & 3) << 3;
        func_02040254(e, 0x10);
        e->unk_58->unk_44 = 8;
        return;
    }
    e->unk_58->unk_44 = 4;
    e->unk_2b = func_02084fd0(e, V(e)->unk_64);
    func_02040254(e, 8);
    func_020847a0(e);
    func_02085980(e);
    if (--e->unk_17 == 0) {
        func_020402e0(e);
    }
}

ARM void func_0204017c(Entity *e) {
    func_020852f8(e, 0x40, e->unk_2b ^ 0x10);
    func_02085980(e);
    if (e->unk_29 & 0x20) {
        e->unk_14 = 7;
    }
}

ARM void func_020401b4(Entity *e) {
    func_02085980(e);
    if (e->unk_29 & 0x20) {
        func_020847a0(e);
        func_0204042c(e);
        return;
    }
    if (e->unk_29 & 0x80) {
        func_020402e0(e);
    }
}

ARM void func_020401f4(Entity *e) {
    if (e->unk_58 == NULL) {
        return;
    }
    func_0205031c(e, e->unk_58);
    e->unk_58->unk_48 = data_020d310c[((e->unk_2a & 3) << 2) + (e->unk_29 & 3)];
    e->unk_58->unk_3c = (e->unk_58->unk_3c & 0x7f) | (e->unk_3c & 0x80);
}

ARM void func_02040254(Entity *e, u8 a) {
    u8 d = ((e->unk_2b + 4) & 0x18) >> 3;
    if ((e->unk_2a & 0x1c) == a) {
        if ((e->unk_2b & 7) != 4) {
            if (d == (e->unk_2a & 3)) {
                return;
            }
            func_020859e0(e, e->unk_2a = a + d);
            return;
        }
        if (((d - (e->unk_2a & 3)) & 3) < 2) {
            return;
        }
        func_020859e0(e, e->unk_2a = a + d);
        return;
    }
    func_020859e0(e, e->unk_2a = a + d);
}

ARM void func_020402e0(Entity *e) {
    e->unk_14 = 1;
    e->unk_17 = 0x3c;
    func_020859e0(e, e->unk_2a & 3);
}

ARM void func_02040304(Entity *e) {
    e->unk_14 = 2;
    e->unk_17 = 0xf0;
    e->unk_18 = 1;
    e->unk_0c = 0x80;
    V(e)->unk_64 = NULL;
}

ARM void func_02040334(Entity *e) {
    e->unk_14 = 4;
    e->unk_17 = 0xf;
    e->unk_2b = func_0204fdf0(e, V(e)->unk_64);
    func_02040254(e, 0);
}

ARM BOOL func_02040368(Entity *e) {
    if (func_02084ae8(e, 0xc, V(e)->unk_64) & 0x80) {
        switch (e->unk_2a & 3) {
            case 0:
                if (e->unk_34.HALF.HI - V(e)->unk_64->unk_34.HALF.HI < 0x38) {
                    return TRUE;
                }
                break;
            case 1:
                if (V(e)->unk_64->unk_30.HALF.HI - e->unk_30.HALF.HI < 0x38) {
                    return TRUE;
                }
                break;
            case 2:
                if (V(e)->unk_64->unk_34.HALF.HI - e->unk_34.HALF.HI < 0x38) {
                    return TRUE;
                }
                break;
            case 3:
                if (e->unk_30.HALF.HI - V(e)->unk_64->unk_30.HALF.HI < 0x38) {
                    return TRUE;
                }
                break;
        }
    }
    return FALSE;
}

ARM void func_0204042c(Entity *e) {
    if ((e->unk_28 & 3) != 0) {
        return;
    }
    Entity *other = func_02076858(0xf, 0x11, 0);
    if (other == NULL) {
        return;
    }
    const s8 *p = data_020d2e64 + ((e->unk_2a & 3) * 2);
    func_02050390(e, other, (s32)p[0] << 16, (s32)p[1] << 16);
}

ARM void func_0204048c(Entity *e) {
    func_02084a7c(e, data_020d2fe4);
}

ARM void func_020404a0(Entity *e) {
    data_020d2fb4[e->unk_14](e);
}

ARM void func_020404bc(Entity *e) {
    if (e->unk_14 <= 2) {
        e->unk_14 = 3;
        func_02040254(e, 0xc);
    }
    func_020849f4(e, data_020d2fe4);
}
