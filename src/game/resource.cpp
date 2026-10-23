#include "engine/functions.h"
#include "global.h"

// Resource control, 0x02082c64 to 0x02082d68: ResourceCtrl runs the callback in data_02171e20[0], calls bgTrans for
// each of the four BG entries that have a flag and a pointer set, then copies the buffer that is not current
// (objAffineSet) to VRAM 0x07000000 when its flag in data_0212c50c is set.

extern "C" void bgTrans(void *bg); // bgTrans, parked (scratch/agentB/nonmatching), unmangled
extern u32 data_02171e20[];
extern u8 data_0212c4c8; // current buffer index
extern u8 data_0212c50c[];
extern u8 objAffineSet[];
extern u8 data_0212c6f0[];
extern u8 data_0212c6f8[];
extern u8 data_0212c704[];
extern u8 data_0212c710[];
extern u8 data_0212c71c[];

// ResourceCtrl (0x02082c64)
ARM void ResourceCtrl(void) {
    void (*callback)(void *);
    s32 other;

    callback = (void (*)(void *))data_02171e20[0];
    if (callback != 0) {
        callback(data_0212c6f0);
    }
    if (*(u16 *)(data_0212c6f0 + 0xe) != 0 && *(u32 *)(data_0212c6f0 + 0x10) != 0) {
        bgTrans(data_0212c6f8);
    }
    if (*(u16 *)(data_0212c6f0 + 0x1a) != 0 && *(u32 *)(data_0212c6f0 + 0x1c) != 0) {
        bgTrans(data_0212c704);
    }
    if (*(u16 *)(data_0212c6f0 + 0x26) != 0 && *(u32 *)(data_0212c6f0 + 0x28) != 0) {
        bgTrans(data_0212c710);
    }
    if (*(u16 *)(data_0212c6f0 + 0x32) != 0 && *(u32 *)(data_0212c6f0 + 0x34) != 0) {
        bgTrans(data_0212c71c);
    }
    other = data_0212c4c8 ^ 1;
    if (data_0212c50c[other] == 0) {
        return;
    }
    if ((*(u16 *)data_0212c6f0 & 0x1000) == 0) {
        return;
    }
    MIi_CpuCopyFast(objAffineSet + (other << 10), (void *)0x7000000, 0x400);
    data_0212c50c[data_0212c4c8 ^ 1] = 0;
}
