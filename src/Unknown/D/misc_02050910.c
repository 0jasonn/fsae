#include "Unknown/D/Misc_D.h"
#include "global.h"

ARM void func_02050910(void) {
    data_0216fcf8.unk_8 = 0;
}

ARM void func_02050924(Entity *e) {
    u16 v = e->x.HALF.LO;
    if (v > 0xc0) {
        v = 0xc0;
    }
    v &= 0xfff8;
    if (data_0216fcf8.unk_2 != v) {
        func_02049c7c(v << 8, v << 8, (0x100 - v) << 8);
        if (v != 0) {
            func_02049c7c(0, 0x10000, v << 8);
        }
        data_0216fcf8.unk_2 = v;
    }
    if (data_0212c5ac.unk_0 != 0 || data_0216fcf8.unk_0 != 0) {
        switch (data_0212c5ac.unk_1) {
            case 0:
            case 2:
            case 4:
            case 5:
                func_02050880(data_0212c5ac.unk_7, data_0212c5ac.unk_8);
                break;
            case 1:
            case 3:
                func_02050880(data_0212c5ac.unk_7, 0x100 - data_0212c5ac.unk_8);
                break;
        }
    }
    data_0216fcf8.unk_0 = data_0212c5ac.unk_0;
    func_020152c8();
    GX_TrySetBankForLCDC(0x20);
    GX_TrySetBankForLCDC(0x40);
    MIi_CpuCopyFast(data_0216fcf8.unk_8 != 0 ? data_0216fd04 : data_02170104, (void *)0x06896000, 0x400);
    func_02014c24(0x60);
}
