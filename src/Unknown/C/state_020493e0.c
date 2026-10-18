#include "Unknown/C/State_C.h"
#include "global.h"

ARM BOOL func_020493e0(void) {
    data_0212c7c8.unk_5 = (data_0212c7c8.unk_4 % 3 == 2) ? 0x81 : 0;
    return data_0212c7c8.unk_5 != 0;
}

ARM void func_0204942c(void) {
    u8 old = data_0212c7c8.unk_1;
    u8 v;
    do {
        v = Random() & 3;
        data_0212c7c8.unk_1 = v;
    } while (v == old);
}

ARM BOOL func_02049454(void) {
    int i;
    u8 r;
    if (data_0212c7c8.unk_2 != 0) {
        data_0212c7c8.unk_5 = 0;
        if (data_0212c7c8.unk_4f >= 0xf0) {
            return TRUE;
        }
        if (data_0212c7c8.unk_4f & 0x10) {
            data_0212c7c8.unk_4 = 1;
        }
        if (data_0212c7c8.unk_4f & 0x20) {
            for (i = 0; i < 4; i++) {
                data_0212c7c8.unk_c[i] = 0;
                data_0212c7c8.unk_68[i] = 0;
                data_0212c7c8.unk_58[i] = 9;
                data_0212c7c8.unk_60[i] = 0x28;
            }
            data_0212c7c8.unk_20[4] = 0;
            data_0212c7c8.unk_4 = 0;
            data_0212c7c8.unk_8 = 0;
            func_02054b64();
        }
        if (data_0212c7c8.unk_4f & 0x40) {
            data_0212c7c8.unk_4++;
        }
        return FALSE;
    }
    if (data_0212c7c8.unk_1 >= 5) {
        data_0212c7c8.unk_4++;
        if (data_0212c7c8.unk_4 == 3) {
            return TRUE;
        }
        for (i = 0; i < data_0212c7c8.unk_0; i++) {
            data_0212c7c8.unk_58[i] = 9;
        }
        return FALSE;
    }
    data_0212c7c8.unk_4++;
    switch (data_0212c7c8.unk_3) {
        case 0:
            if (data_0212c7c8.unk_5 != 0) {
                return TRUE;
            }
            func_020493e0();
            return FALSE;
        case 1:
            if (data_0212c7c8.unk_5 != 0) {
                return TRUE;
            }
            func_020493e0();
            if (data_0212c7c8.unk_5 != 0) {
                data_0212c7c8.unk_1 = 2;
            } else {
                func_0204942c();
            }
            return FALSE;
        case 2:
            if (data_0212c7c8.unk_5 != 0 && data_0212c7c8.unk_1 == 2) {
                return TRUE;
            }
            func_0204942c();
            if (func_020493e0() == 0) {
                return FALSE;
            }
            data_0212c7c8.unk_1 = 0xff;
            if (data_0212c7c8.unk_4 == 0xb) {
                data_0212c7c8.unk_1 = 2;
            }
            if (data_0212c7c8.unk_1 == 2) {
                return FALSE;
            }
            do {
                func_0204942c();
                r = data_0212c7c8.unk_1;
            } while (r == 2 || (data_0212c7c8.unk_4e & (1 << r)) != 0);
            data_0212c7c8.unk_4e |= (1 << r);
            return FALSE;
        default:
            return FALSE;
    }
}
