#include "Unknown/Boss_02030a14.h"
#include "global.h"

ARM void func_02031304(Entity *e) {
    func_02032e04(e);
    if (e->unk_0a == 2 && V(e)->unk_79 != 0xf) {
        return;
    }
    func_02085980(e);
    if (e->unk_29 == 0) {
        func_0204fd40(e);
        if (func_020856cc(e, 0x2000) == 0) {
            e->unk_28 = 1;
            e->unk_17--;
            e->unk_18--;
            if (e->unk_17 == 0) {
                if (e->unk_0b) {
                    e->unk_2b = (e->unk_2b - 8) & 0x1f;
                } else {
                    e->unk_2b = (e->unk_2b + 8) & 0x1f;
                }
            }
            func_020329c8(e);
            return;
        }
        if (e->unk_10 == 0) {
            e->unk_28 = 1;
        }
        return;
    }
    if (!(e->unk_29 & 0x80)) {
        return;
    }
    if (e->unk_0a == 2) {
        V(e)->unk_79 = 0;
    }
    if (e->unk_18 != 0) {
        if (e->unk_17 == 0) {
            if (V(e)->unk_73) {
                V(e)->unk_73 = 0;
                e->unk_17 = 1;
            } else {
                e->unk_17 = 2;
            }
        }
        e->unk_10 = 0x30000;
        func_020859e0(e, (e->unk_0a - 1) * 10 + 1);
        return;
    }
    e->unk_14 = 0xc;
    e->unk_17 = 0xff;
    if ((e->unk_17 = func_02032d34(e)) == 0xff) {
        func_02032ac4(e);
        return;
    }
    e->unk_18 = data_020d0a42[func_0208455c() & 7];
    func_02032c2c(e);
}

ARM void func_02031498(Entity *e) {
    func_02032e04(e);
    if (e->unk_0a == 2 && V(e)->unk_79 != 0xf) {
        return;
    }
    func_02085980(e);
    if (V(e)->unk_70 != 0) {
        V(e)->unk_70--;
    }
    if (e->unk_29 == 0) {
        func_0204fd40(e);
        if (func_020856cc(e, 0x2000) == 0) {
            e->unk_28 = 1;
            func_020329c8(e);
        } else if (e->unk_10 == 0) {
            e->unk_28 = 1;
        }
    } else if (e->unk_29 & 0x80) {
        if (V(e)->unk_70 != 0) {
            if (e->unk_0a == 2) {
                V(e)->unk_79 = 0;
            }
            func_02032c2c(e);
        } else if (--e->unk_18 != 0) {
            e->unk_14 = 0xd;
            V(e)->unk_70 = 0xb4;
            func_020859e0(e, (e->unk_0a - 1) * 10);
        } else {
            func_02032ac4(e);
        }
    }
    func_02032cac(e);
}

ARM void func_020315ac(Entity *e) {
    func_02032e04(e);
    if (V(e)->unk_70 != 0) {
        if (e->unk_23 != 0) {
            func_020859e0(e, (e->unk_0a - 1) * 10);
        } else {
            func_02085980(e);
        }
        V(e)->unk_70--;
        return;
    }
    e->unk_14 = 0xc;
    if ((e->unk_17 = func_02032d34(e)) == 0xff) {
        func_02032ac4(e);
        return;
    }
    if (e->unk_0a == 2) {
        V(e)->unk_79 = 0;
    }
    func_02032c2c(e);
}

ARM void func_02031650(Entity *e) {
    func_02032e04(e);
    func_02085980(e);
    if (e->unk_29 & 0x80) {
        e->unk_14 = V(e)->unk_72;
    }
}

ARM void func_02031678(Entity *e) {
    func_02085980(e);
    func_0204fd40(e);
    if (e->unk_30.HALF.HI <= 0x184) {
        e->unk_30.HALF.HI = 0x184;
    }
    if (e->unk_34.HALF.HI >= 0x24b) {
        e->unk_34.HALF.HI = 0x24b;
    }
    if (e->unk_34.HALF.HI <= 0x1a3) {
        e->unk_34.HALF.HI = 0x1a3;
    }
    if (e->unk_30.HALF.HI > 0x2a8) {
        e->unk_3d = 0xe0;
        e->unk_3f = 0x48;
        e->unk_30.HALF.HI = 0x2a8;
        func_020859e0(e, (e->unk_0a - 1) * 10 + 6);
        e->unk_14 = 8;
        e->unk_10 = 0;
        e->unk_1c.b16 = e->unk_1c.b20 + 1;
        e->unk_1c.b20 = e->unk_1c.b16;
        V(e)->unk_70 = 0x168;
        func_02076fe0(0xa9);
        return;
    }
    if (func_020856cc(e, 0x2000) != 0) {
        return;
    }
    func_020859e0(e, (e->unk_0a - 1) * 10 + 9);
    e->unk_18 = 0x5a;
    e->unk_14 = 7;
    func_020329c8(e);
}

ARM void func_020317b0(Entity *e) {
    func_02085980(e);
    if (V(e)->unk_75 != 0) {
        V(e)->unk_75--;
    }
    if (e->unk_18-- != 0) {
        return;
    }
    func_02032ac4(e);
}

ARM void func_020317ec(Entity *e) {
    func_020856cc(e, 0x2000);
    if (e->unk_41 & 0x80) {
        switch (e->unk_41 & 0x7f) {
            case 0x10:
                func_02030ae4(e->unk_4c->unk_0a);
            case 4:
            case 8:
            case 0xc:
            case 0x18:
                e->unk_45--;
                e->unk_3d = 0xd0;
                func_02032e5c(e);
                func_02076fe0(0x2d);
                break;
        }
        e->unk_41 = 0;
        if (e->unk_45 == 0) {
            e->unk_0a++;
            func_02081160(e);
            if (data_0212c7c8.unk_6 + 1 == e->unk_0a) {
                e->unk_0a = 4;
            }
            func_02032b48(e);
            if (e->unk_0a < 4) {
                if (e->unk_0a == 2) {
                    func_02027fe8(0x13);
                    func_02081088(e, 8);
                    e->unk_1c.b20 = func_02027ec4(0x15);
                    e->unk_1c.b16 = e->unk_1c.b20;
                    e->unk_1c.b4 = 2;
                    e->unk_48 = data_020d0a72;
                } else {
                    func_02027fe8(0x15);
                    func_02081088(e, 9);
                    e->unk_1c.b20 = func_02027ec4(0x16);
                    e->unk_1c.b16 = e->unk_1c.b20;
                    e->unk_1c.b4 = 0;
                    e->unk_48 = data_020d0a52;
                }
                func_02032ac4(e);
                return;
            }
            func_02027fe8(0x16);
            func_02081088(e, 7);
            e->unk_1c.b20 = func_02027ec4(0x17);
            e->unk_1c.b16 = e->unk_1c.b20;
            e->unk_14 = 0xf;
            e->unk_3c &= 0x7f;
            e->unk_1c.b0 = 0;
            e->unk_38.WORD = 0;
            return;
        }
    }
    V(e)->unk_70--;
    if (V(e)->unk_70 != 0) {
        return;
    }
    e->unk_1c.b16 = e->unk_1c.b20 - 1;
    e->unk_1c.b20 = e->unk_1c.b16;
    func_02032ac4(e);
}

ARM void func_02031a58(Entity *e) {
    e->unk_1c.b0 = 1;
    e->unk_14 = 9;
    func_020859e0(e, 0x1e);
    func_0203263c(e);
    func_020325f8(e);
}

ARM void func_02031a94(Entity *e) {
    e->unk_1c.b0 = 1;
    func_02085980(e);
    if (e->unk_29 & 0x80) {
        e->unk_0c = 0x200;
        e->unk_14 = 0x10;
        e->unk_17 = 0x20;
        e->unk_2b = func_02086080(e->unk_30.HALF.HI, e->unk_34.HALF.HI, 0x1f8, 0x1f8);
        e->unk_48 = data_020d0a4a;
    }
    func_020325f8(e);
}

ARM void func_02031b04(Entity *e) {
    func_02085980(e);
    func_0204fd40(e);
    if (e->unk_17 != 0) {
        e->unk_17--;
    } else {
        e->unk_14 = 0xa;
        e->unk_17 = 0;
    }
    func_020325f8(e);
}

ARM void func_02031b40(Entity *e) {
    if (e->unk_17 != 0) {
        e->unk_17--;
        return;
    }
    e->unk_14 = 0xb;
    e->unk_17 = 0xf0;
    func_020859e0(e, 0x1f);
    func_0203298c(e);
}

ARM void func_02031b80(Entity *e) {
    func_02085980(e);
    if (e->unk_17 != 0) {
        e->unk_17--;
        func_020852ec(e);
        if (e->unk_2c & data_020d0a5a[e->unk_2b >> 3]) {
            u8 target = func_02086078(data_0212ceb0[e->unk_18].unk_28, e);
            if (e->unk_2b != target) {
                e->unk_2b ^= 0x10;
            } else {
                e->unk_2b = (e->unk_2b + 8) & 0x1f;
                if (e->unk_2c & data_020d0a5a[e->unk_2b >> 3]) {
                    e->unk_2b = (e->unk_2b - 0x10) & 0x1f;
                }
            }
        }
    } else {
        e->unk_14 = 0xa;
        e->unk_17 = 0xf0;
        func_020859e0(e, 0x20);
    }
    func_020325f8(e);
}

ARM void func_02031c58(Entity *e) {
    if (e->unk_17-- == 0) {
        e->unk_14 = 0xa;
        e->unk_17 = 0xf0;
        func_020859e0(e, 0x20);
    }
    if (e->unk_23 != 0x20) {
        func_020859e0(e, 0x20);
    }
    func_020325f8(e);
}
