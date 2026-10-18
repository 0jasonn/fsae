#include "Unknown/Boss_02036ca4.hpp"
#include "global.h"

ARM extern "C" void func_02037a6c(Entity *e) {
    func_02085980(e);
    if (--e->unk_17 != 0) {
        return;
    }
    if (--e->unk_18 != 0) {
        e->unk_14 = 0x17;
        e->unk_17 = 0x3c;
    } else {
        e->unk_14 = 0xd;
        e->unk_17 = 0x3c;
        e->unk_0c = 0x100;
        func_020859e0(e, 0);
    }
    e->unk_1c.b30 = 2;
    e->unk_1c.b14 = e->unk_1c.b30;
}

ARM extern "C" void func_02037af8(Entity *e) {
    func_02085980(e);
    if (--e->unk_17 == 0) {
        e->unk_14 = 0x1f;
        e->unk_0c = 0x100;
    }
}

ARM extern "C" void func_02037b28(Entity *e) {
    func_02085980(e);
    if ((u16)(e->unk_30.HALF.HI - 0x1f7) <= 2 && (u16)(e->unk_34.HALF.HI - 0x1f7) <= 2) {
        e->unk_14 = 0x20;
        e->unk_17 = 0x3c;
        e->unk_30.HALF.HI = 0x1f8;
        e->unk_34.HALF.HI = 0x1f8;
        return;
    }
    e->unk_2b = func_02086080(e->unk_30.HALF.HI, e->unk_34.HALF.HI, 0x1f8, 0x1f8);
    if ((data_0212c5bc & 7) == 0) {
        func_02076a50(e, 1, 1, 0x14);
    }
    func_0204fd40(e);
    func_02060a70(e);
}

ARM extern "C" void func_02037bd8(Entity *e) {
    func_02085980(e);
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14 = 0x21;
    e->unk_17 = 0xd2;
    V(e)->unk_6e = data_020d1440[func_0208455c() & 7];
}

ARM extern "C" void func_02037c24(Entity *e) {
    func_02085980(e);
    if (--e->unk_17 == 0) {
        if (V(e)->unk_6e != 0) {
            V(e)->unk_6e--;
            e->unk_17 = 0xf0;
            return;
        }
        e->unk_14 = 0x22;
        func_02038460(e);
        return;
    }
    if (e->unk_17 != 0x78) {
        return;
    }
    if (V(e)->unk_6e == 0) {
        Entity *child = func_0204bdb8(0xa);
        if (child != NULL) {
            child->unk_0b = 1;
            child->unk_54 = e;
        }
    } else {
        Entity *child = func_0204bdb8(0xa);
        if (child != NULL) {
            child->unk_54 = e;
        }
    }
}

ARM extern "C" void func_02037cb4(Entity *e) {
    func_02085980(e);
    if (e->unk_17 != 0) {
        e->unk_17--;
        return;
    }
    if ((data_0212c5bc & 7) == 0) {
        func_02076a50(e, 1, 1, 0x14);
    }
    int result = func_020381ec(e);
    if (result == 0) {
        if (--e->unk_18 != 0) {
            e->unk_14 = 0x20;
            e->unk_17 = 0x3c;
            return;
        }
        e->unk_14 = 0xd;
        e->unk_17 = 0x3c;
        e->unk_0c = 0x100;
        func_020859e0(e, 0);
        return;
    }
    if (result == 2) {
        e->unk_17 = 0x1e;
    }
}

ARM extern "C" void func_02037d68(Entity *e) {
    if (e->unk_3c != 0) {
        e->unk_3c = 0;
        e->unk_17 = 0xb4;
        func_02053958();
        func_020266f8();
        func_02076fe0(0x80010000);
        func_02076fe0(0x2e);
    }
    e->unk_1c.b0 ^= 1;
    if (e->unk_17 != 0) {
        e->unk_17--;
        return;
    }
    u8 count = data_0212c7c8.unk_0;
    for (u32 i = 0; i < count; i++) {
        PlayerData *player = &data_0212ceb0[i];
        if ((player->unk_36 & 1) || player->unk_3c != 0) {
            return;
        }
        if (player->unk_28->unk_45 == 0) {
            return;
        }
    }
    for (u32 i = 0; i < data_0212c7c8.unk_0; i++) {
        PlayerData *player = &data_0212ceb0[i];
        player->unk_28->unk_38.HALF.HI = 0;
        player->unk_28->unk_10 = 0;
        player->unk_28->unk_2b = 0xff;
        player->unk_28->unk_3d = 0x88;
        player->unk_36 &= 0xf3ff;
        func_020899e4(player->unk_28);
    }
    e->unk_14 = 0x24;
    e->unk_17 = 0x20;
    func_020859e0(e, 0);
    func_0204625c(3, 0x10);
    func_02049eb8();
    func_020384f8();
}

ARM extern "C" void func_02037ed8(Entity *e) {
    func_02085980(e);
    e->unk_1c.b0 ^= 1;
    func_020384f8();
    if (e->unk_17 != 0) {
        e->unk_17--;
        return;
    }
    Entity *child = func_02076858(0x69, 0, 0);
    if (child == NULL) {
        return;
    }
    child->unk_54 = e;
    e->unk_14 = 0x25;
    e->unk_1c.b0 = 1;
}

ARM extern "C" void func_02037f54(Entity *e) {
    func_020547ec();
    func_02085980(e);
}
