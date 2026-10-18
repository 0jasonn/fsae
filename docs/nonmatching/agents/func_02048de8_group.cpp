// NONMATCHING (func_02048de8, func_02048ea8, func_02048ee4): not matching. func_02048de8 is 0xbc vs 0xc0 in ROM
// (tail return structure merges the n==0 check into the b!=7 branch), func_02048ea8 uses a different shift/compare
// codegen, func_02048ee4 has register allocation differences.
#include "Unknown/C/State_C.hpp"
#include "global.h"

ARM extern "C" int func_02048de8(void) {
    u8 i = 0;
    u8 n = 0;
    int a = 0xf;
    int b = 0xf;
    int c = 0xf;
    if (data_0212c7c8.unk_0 > 0) {
        do {
            u8 v;
            if (!(data_0212c7c8.unk_28[i].unk_00 & 8)) {
                return 1;
            }
            if (!(data_0212c7c8.unk_28[i].unk_00 & 0x800000)) {
                n = n + 1;
            }
            v = data_0212c7c8.unk_28[i].unk_04[1];
            a &= func_02048ea8(v, 1);
            b &= func_02048ea8(v, 2);
            c &= func_02048ea8(v, 3);
            i = i + 1;
        } while (i < data_0212c7c8.unk_0);
    }
    if (a != 7) {
        return 1;
    }
    if (b != 7) {
        return 2;
    }
    return n == 0 ? 3 : 2;
}

ARM extern "C" int func_02048ea8(int v, int k) {
    int r = 0;
    if ((v & 3) >= k) {
        r |= 1;
    }
    v = (v >> 2) & 0xff;
    if ((v & 3) >= k) {
        r |= 2;
    }
    v = v >> 2;
    if ((v & 3) >= k) {
        r |= 4;
    }
    return r;
}

ARM extern "C" int func_02048ee4(void) {
    u8 i = 0;
    u8 n1 = 0;
    u8 n2 = 0;
    u8 n3 = 0;
    if (data_0212c7c8.unk_0 > 0) {
        do {
            u8 v = data_0212c7c8.unk_28[i].unk_04[1];
            if (func_02048ea8(v, 1) == 7) {
                n1 = n1 + 1;
            }
            if (func_02048ea8(v, 2) == 7) {
                n2 = n2 + 1;
            }
            if (func_02048ea8(v, 3) == 7) {
                n3 = n3 + 1;
            }
            i = i + 1;
        } while (i < data_0212c7c8.unk_0);
    }
    if (n3 == data_0212c7c8.unk_0) {
        return 3;
    }
    if (n2 == data_0212c7c8.unk_0) {
        return 2;
    }
    return n1 == data_0212c7c8.unk_0 ? 1 : 0;
}
