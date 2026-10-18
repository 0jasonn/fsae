#include "Unknown/Boss_02036ca4.hpp"
#include "global.h"

ARM extern "C" void func_02036ca4(Entity *e) {
    if (e->unk_45 == 0 && e->unk_14 < 0x23) {
        e->unk_14 = 0x23;
    }
    data_020d177c[e->unk_14](e);
}

ARM extern "C" void func_02036cdc(Entity *e) {
    e->unk_14 = 1;
    e->unk_17 = 0xb4;
    e->unk_30.HALF.HI = 0x1f8;
    e->unk_34.HALF.HI = 0x188;
    e->unk_38.HALF.HI = -0x70;
    e->unk_1c.b4 = 2;
    e->unk_5e.b2 = 2;
    e->unk_48 = data_020d1438;
    V(e)->unk_7c = func_0208455c();
    e->unk_45 = data_020d1428[data_0212c7c8.unk_3];
    if (func_0208de54(func_0208da4c()) != 0) {
        switch (data_0212c7c8.unk_0) {
            case 2:
                e->unk_45 = e->unk_45 + e->unk_45 / 5;
                break;
            case 3:
                e->unk_45 = 0xff;
                break;
            case 4:
                e->unk_45 = 0xff;
                break;
        }
    }
    e->unk_6a = 1;
    func_0208ae30(e);
    func_020859e0(e, 0);
    func_020547ec();
    func_02076fe0(0x80080000);
    data_0212c7c8.unk_26 = 0xffff;
}

ARM extern "C" void func_02036df4(Entity *e) {
    func_020547ec();
    u8 timer = --e->unk_17;
    if (timer == 0) {
        e->unk_14 = 2;
        e->unk_17 = 0x78;
        e->unk_1c.b0 = 1;
        data_0212c648 = e;
        for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
            data_0212ceb0[i].unk_28->unk_2a = 0;
            func_02076988(data_0212ceb0[i].unk_28, -8, -12);
        }
        return;
    }
    if (e->unk_18 < 0x20) {
        e->unk_18++;
        data_0212c5ac.unk_c = 0xfff0;
        data_0212c5ac.unk_7 = 0;
        func_020463f0((e->unk_18 >> 2) << 4);
        data_0212c5ac.unk_c = -1;
        return;
    }
    if (timer >= 0x96) {
        return;
    }
    if (timer & 0xf) {
        return;
    }
    for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
        if (func_0208455c() & 7) {
            data_0212ceb0[i].unk_28->unk_2a = func_0208455c() & 6;
        }
    }
}

ARM extern "C" void func_02036f54(Entity *e) {
    func_020547ec();
    func_02085980(e);
    func_02060a70(e);
    e->unk_38.WORD += 0x8000;
    if (e->unk_38.HALF.HI != -0x30) {
        return;
    }
    e->unk_14 = 3;
    e->unk_15 = 0;
    e->unk_17 = 8;
    e->unk_1c.b0 = 1;
    func_02049f0c(0x194);
}

ARM extern "C" void func_02036fbc(Entity *e) {
    func_020547ec();
    func_02085980(e);
    func_02060a70(e);
    if (e->unk_17 != 0) {
        e->unk_17--;
        return;
    }
    if (e->unk_15 == 0) {
        if ((data_0217d384 & 0x7f) != 6) {
            return;
        }
        func_02049eb8();
        e->unk_15 = 1;
        return;
    }
    for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
        if (data_0212c584[i] & 0x1000) {
            return;
        }
    }
    e->unk_14 = 5;
    e->unk_17 = 8;
    func_02076fe0(0x1f9);
    data_0212c5ac.unk_7 = 0x16;
    func_020463f0(0x100);
}

ARM extern "C" void func_02037094(Entity *e) {
}

ARM extern "C" void func_02037098(Entity *e) {
    func_02060a70(e);
    func_020547ec();
    if (--e->unk_17 != 0) {
        if (e->unk_17 == 4) {
            func_02021ec4(data_020d70c8, 1);
            data_02134914 = 0;
        }
        return;
    }
    e->unk_14 = 6;
    e->unk_17 = 0x3e;
    func_0204625c(2, 8);
}

ARM extern "C" void func_02037108(Entity *e) {
    func_020547ec();
    func_02085980(e);
    func_02060a70(e);
    if (--e->unk_17 == 0) {
        e->unk_14 = 7;
        e->unk_17 = 0x1e;
    }
}

ARM extern "C" void func_02037148(Entity *e) {
    func_020547ec();
    func_02085980(e);
    func_02060a70(e);
    if (--e->unk_17 != 0) {
        return;
    }
    Entity *child = func_0204bdb8(0xa);
    if (child == NULL) {
        return;
    }
    child->unk_54 = e;
    child->unk_0a = 1;
    e->unk_58 = child;
    e->unk_14 = 8;
}

ARM extern "C" void func_020371a4(Entity *e) {
    func_020547ec();
    func_02085980(e);
    func_02060a70(e);
    if (e->unk_58->unk_29 == 0) {
        return;
    }
    Entity *child = func_0204bdb8(0xb);
    if (child == NULL) {
        return;
    }
    func_0205031c(e, child);
    child->unk_0b = 1;
    child->unk_2b = 0x10;
    e->unk_58 = child;
    e->unk_14 = 9;
}

ARM extern "C" void func_0203720c(Entity *e) {
    func_020547ec();
    func_02085980(e);
    func_02060a70(e);
    if (e->unk_58->unk_38.HALF.HI < -2) {
        return;
    }
    e->unk_14 = 0xa;
    e->unk_17 = 0x24;
    for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
        PlayerData *player = &data_0212ceb0[i];
        player->unk_0c = 0xf;
        player->unk_08 = 0x1af;
        player->unk_38 = 0xb4;
        player->unk_39 = 0;
        player->unk_28->unk_2b = func_02086080(0x1f8, 0x1c0, player->unk_28->unk_30.HALF.HI, player->unk_28->unk_34.HALF.HI);
        player->unk_28->unk_2a = player->unk_28->unk_2b < 0x10 ? 2 : 6;
    }
}

ARM extern "C" void func_020372e4(Entity *e) {
    func_020547ec();
    func_02085980(e);
    func_02060a70(e);
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14 = 0xb;
    e->unk_1c.b14 = 1;
    e->unk_1c.b30 = 1;
    e->unk_5e.b0 = 3;
    for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
        data_0212ceb0[i].unk_28->unk_2b = 0xff;
    }
}

ARM extern "C" void func_02037390(Entity *e) {
    func_020547ec();
    func_02085980(e);
    func_02060a70(e);
    e->unk_38.WORD += 0x8000;
    if (e->unk_38.HALF.HI == -4) {
        e->unk_14 = 0xc;
        e->unk_17 = 0x1e;
        e->unk_2e = 0xc;
    }
}

ARM extern "C" void func_020373d8(Entity *e) {
    func_02085980(e);
    func_02060a70(e);
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14 = 0xd;
    e->unk_0c = 0x100;
    e->unk_17 = 1;
    e->unk_1c.b14 = 2;
    e->unk_1c.b30 = 2;
    e->unk_5e.b0 = 2;
    if (func_0208de54(func_0208da4c()) != 0) {
        data_0212c648 = data_0212ceb0[data_0212c504].unk_28;
    } else {
        data_0212c648 = data_0212ceb0[*func_02093b5c()].unk_28;
    }
    for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
        PlayerData *player = &data_0212ceb0[i];
        player->unk_08 = 0xc;
        player->unk_38 = 1;
        player->unk_02 = 0x41;
        player->unk_28->unk_10 = 0x20000;
    }
    func_02076fe0(0x1af);
    data_0212c618 = 1;
    func_0205396c();
    func_02026720();
}

ARM extern "C" void func_02037528(Entity *e) {
    func_02085980(e);
    if ((u16)(e->unk_30.HALF.HI - 0x1f7) <= 2 && (u16)(e->unk_34.HALF.HI - 0x19f) <= 2) {
        e->unk_30.HALF.HI = 0x1f8;
        e->unk_34.HALF.HI = 0x1a0;
        if (--e->unk_17 != 0) {
            return;
        }
        func_02037f6c(e);
        return;
    }
    e->unk_2b = func_02086080(e->unk_30.HALF.HI, e->unk_34.HALF.HI, 0x1f8, 0x1a0);
    func_0204fd40(e);
    func_02060a70(e);
}

ARM extern "C" void func_020375c8(Entity *e) {
    if (e->unk_29 & 1) {
        if (func_0203808c(e) == 0) {
            return;
        }
        func_02038138(e);
        e->unk_0c = data_020d142c[func_020384b8(e)];
        func_02085980(e);
        return;
    }
    func_02085980(e);
}

ARM extern "C" void func_02037620(Entity *e) {
    func_02085980(e);
    if (V(e)->unk_70 != 0) {
        return;
    }
    V(e)->unk_70 = 3;
    e->unk_14 = 0x10;
    e->unk_17 = 0x3c;
}

ARM extern "C" void func_02037654(Entity *e) {
    func_02085980(e);
    if (V(e)->unk_70 != 0xf) {
        return;
    }
    if (--e->unk_17 != 0) {
        return;
    }
    V(e)->unk_70 = 0;
    e->unk_14 = 0x11;
    e->unk_0c = 0x100;
    func_02038194(e);
    e->unk_1c.b30 = 1;
    e->unk_1c.b14 = e->unk_1c.b30;
}

ARM extern "C" void func_020376c4(Entity *e) {
    if (V(e)->unk_70 == 0) {
        if (func_020381ec(e) == 0) {
            V(e)->unk_70 = 7;
        }
    } else if (V(e)->unk_70 == 4) {
        e->unk_14 = 0x12;
        e->unk_17 = 0x14;
        e->unk_1c.b30 = 2;
        e->unk_1c.b14 = e->unk_1c.b30;
    }
    func_02085980(e);
}

ARM extern "C" void func_02037730(Entity *e) {
    if (--e->unk_17 == 0) {
        e->unk_14 = 0x13;
        e->unk_17 = 0x3c;
        V(e)->unk_70 = 0;
    }
    func_02085980(e);
}

ARM extern "C" void func_02037768(Entity *e) {
    if (V(e)->unk_70 == 3 && --e->unk_17 == 0) {
        V(e)->unk_70 = data_020cf9b8[V(e)->unk_71 + 2];
        e->unk_14 = 0x14;
    }
    func_02085980(e);
}

ARM extern "C" void func_020377b4(Entity *e) {
    func_02085980(e);
    if (V(e)->unk_70 == 0) {
        e->unk_14 = 0x15;
    }
}

ARM extern "C" void func_020377d4(Entity *e) {
    if (--e->unk_18 != 0) {
        func_02038138(e);
        return;
    }
    e->unk_14 = 0x16;
    V(e)->unk_70 = 0xff;
    func_020859e0(e, 4);
}

ARM extern "C" void func_02037810(Entity *e) {
    func_02085980(e);
    if (!(e->unk_29 & 0x80)) {
        return;
    }
    e->unk_14 = 0xd;
    e->unk_17 = 0x3c;
    e->unk_0c = 0x100;
    func_020859e0(e, 0);
}

ARM extern "C" void func_02037850(Entity *e) {
    func_02085980(e);
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14 = 0x18;
    V(e)->unk_70 = 0;
    V(e)->unk_72 = 0x20;
    func_020859e0(e, 3);
    func_02085f80(0xb2);
    e->unk_1c.b30 = 1;
    e->unk_1c.b14 = e->unk_1c.b30;
}

ARM extern "C" void func_020378c0(Entity *e) {
    func_02085980(e);
    if (e->unk_29 & 1) {
        func_020382fc(e);
        e->unk_0b = 0;
        return;
    }
    if (!(e->unk_29 & 0x80)) {
        return;
    }
    e->unk_14 = 0x19;
    e->unk_17 = 0x3c;
    V(e)->unk_6e = 0;
    V(e)->unk_7d = (func_0208455c() & 1) ? 1 : -1;
    func_020859e0(e, 0);
}

ARM extern "C" void func_02037930(Entity *e) {
    func_02085980(e);
    func_02038414(e);
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14 = 0x1a;
    func_020383bc(e);
}

ARM extern "C" void func_0203796c(Entity *e) {
    func_02085980(e);
    func_02038414(e);
    if (func_020381ec(e) != 0 && V(e)->unk_70 == 0) {
        return;
    }
    e->unk_14 = 0x1b;
}

ARM extern "C" void func_020379a8(Entity *e) {
    func_02085980(e);
    func_02038414(e);
    if (V(e)->unk_6e == 0) {
        e->unk_14 = 0x1c;
        e->unk_17 = 0x1e;
    }
}
