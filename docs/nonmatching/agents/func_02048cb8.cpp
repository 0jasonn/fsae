// NONMATCHING: same size (0x130) but the block at 0x02048ce8-0x02048d08 has different register/scheduling
// (the data_0212c7c8 address load and the operand order of the unsigned compare).
#include "Unknown/C/State_C.hpp"
#include "global.h"

ARM extern "C" void func_02048cb8(void) {
    int i;
    if (data_0212c7c8.unk_1[0] == 5) {
        u8 b = data_0212c7c8.unk_48 % 3 + 1;
        u8 old = data_0212c7c8.unk_90;
        u32 x = old & 3;
        if (x < b) {
            data_0212c7c8.unk_90 = (u8)(old & 0xfc) | b;
        }
        if ((data_0212c7c8.unk_90 & 3) != 3 || b != 3) {
            return;
        }
        for (i = 0; i < data_0212c7c8.unk_0; i++) {
            data_0212c7c8.unk_28[i].unk_00 |= 1;
        }
    } else if (data_0212c7c8.unk_1[0] == 6) {
        int b = data_0212c7c8.unk_48 % 3;
        u8 v = data_0212c7c8.unk_90 | (u8)(1 << (b + 4));
        data_0212c7c8.unk_90 = v;
        if (!((v & 0xf0) == 0x70 && b + 1 == 3)) {
            return;
        }
        for (i = 0; i < data_0212c7c8.unk_0; i++) {
            data_0212c7c8.unk_28[i].unk_00 |= 2;
        }
    }
}
