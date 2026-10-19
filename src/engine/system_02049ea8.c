#include "engine/entity.h"
#include "global.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   Callback_Empty0 -> Callback_Empty0
//   Callback_Empty1 -> Callback_Empty1
//   Callback_Empty2 -> Callback_Empty2
//   Callback_Empty3 -> Callback_Empty3
//   Status_ArmIfEnabled -> Status_ArmIfEnabled
//   Timer_ReleaseHold -> Timer_ReleaseHold
//   Status_ResetWithValue -> Status_ResetWithValue

// Work blocks in the bss, accessed by byte offset
extern u8 data_0217d36c[];
extern u8 data_0217d384[];
extern u8 data_0217d484[];
extern const u8 data_020d7c38[];

extern void MIi_CpuCopy32(const void *src, void *dst, u32 size);

ARM void Callback_Empty0(void) {
}

ARM void Callback_Empty1(void) {
}

ARM void Callback_Empty2(void) {
}

ARM void Callback_Empty3(void) {
}

ARM void Status_ArmIfEnabled(void) {
    u8 value = data_0217d384[0] & 0x7f;
    if (value != 0) {
        data_0217d384[0] = 0x87;
    }
}

ARM void Timer_ReleaseHold(void) {
    u16 flags = *(u16 *)(data_0217d36c + 6);
    if (flags & 0x8000) {
        *(u16 *)(data_0217d36c + 6) = flags & 0x7fff;
    }
    data_0217d484[0xe7] = 1;
}

ARM void Status_ResetWithValue(u16 value) {
    MIi_CpuCopy32(data_020d7c38, data_0217d384, 0x18);
    *(u16 *)(data_0217d384 + 6) = value;
}
