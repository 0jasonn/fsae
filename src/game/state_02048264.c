#include "game/state_c.h"
#include "global.h"

extern const u16 data_021037c8[];
extern const u16 data_02103758[];
extern const u16 *const data_021037d8[];
extern const u16 *const data_021037ec[];

ARM BOOL warp_check(void) {
    u8 i;
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        if (!(data_0212ceb0[i].unk_36 & 1)) {
            if (data_0212ceb0[i].unk_28->health != 0) {
                continue;
            }
        }
        return FALSE;
    }
    return (func_020280e0() & 0xf) == data_0212c7c8.unk_6f;
}

ARM void time_bonus(void) {
    u32 t = data_0212c7c8.unk_1c / 60;
    int n = data_0212c7c8.unk_0;
    KnifeApp_getInstance();
    if (KnifeApp_isWirelessMode() == 0) {
        n = 1;
    }
    TelopRequest(0x3ea);
    data_0217d36c.unk_08 = (u16)(t / 60);
    data_0217d36c.unk_0c = (u16)(t % 60);
    data_0217d36c.unk_10 = get_time_bonus();
    data_0217d36c.unk_14 = (u16)n;
}

ARM u16 get_time_bonus(void) {
    u8 i;
    u32 q = data_0212c7c8.unk_1c / 60;
    const u16 *const *values = data_021037d8;
    const u16 *thresholds = data_021037c8;
    if (data_0212c7c8.unk_7[0] == 6) {
        thresholds = data_02103758;
        values = data_021037ec;
    }
    for (i = 0; i < 7; i++) {
        if (q < thresholds[i]) {
            break;
        }
    }
    return values[data_0212c7c8.unk_0][i];
}
