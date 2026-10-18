#include "Unknown/C/State_C.h"
#include "global.h"

extern const u8 data_021036a8[];

ARM void func_02048fa0(u32 a) {
    u8 i;
    u8 idx = data_0212c7c8.unk_1;
    u32 val;
    u32 mask;
    if (idx >= 5) {
        return;
    }
    val = (a << data_021036a8[idx * 2 + 1]) & 0xff;
    mask = data_021036a8[idx * 2];
    if (data_0212c7c8.unk_0 == 0) {
        return;
    }
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        u8 b = data_0212c7c8.unk_28[i].unk_05;
        if ((b & mask) < val) {
            data_0212c7c8.unk_28[i].unk_05 = (b & ~mask) | val;
        }
    }
}

ARM int func_02049020(void) {
    switch (data_0212c7c8.unk_6) {
        case 1:
            if (data_0212c7c8.unk_8 >= 0x3e8) {
                return 1;
            }
        case 2:
            if (data_0212c7c8.unk_8 >= 0xbb8) {
                return 2;
            }
        case 3:
            if (data_0212c7c8.unk_8 >= 0x1388) {
                return 3;
            }
    }
    return 0;
}

ARM BOOL func_02049098(Entity *e) {
    return (data_0212c7f0[e->type].unk_0 & 2) != 0;
}

ARM BOOL func_020490b8(Entity *e) {
    return (data_0212c7f0[e->type].unk_0 & 1) != 0;
}
