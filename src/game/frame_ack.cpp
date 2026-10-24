#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/comm.h"

// Functions in this file (module com, original names from the debug build): frame_ack (frame_ack())

extern "C" void MIi_CpuCopy16(const void *src, void *dst, u32 size);

extern u32 data_0212c538;
extern u8 data_0212c9a8[];   // communication state block (see com.cpp)
extern u8 data_0212c9ec[];
extern u8 data_0212c9b8[];
extern u16 data_02134cb0[];  // four 16-entry key tables, 0x20 bytes apart
extern u16 data_02134cd0[];
extern u16 data_02134cf0[];
extern u16 data_02134d10[];

// frame_ack (0x02028944): a frame is acknowledged when no table entry of the players selected by byte 3 (bits 0..3) is
// 0xc000 at the index data_0212c538 - 2. Wireless play answers with 2 at +8 unless the manager says the frame is done.
ARM void frame_ack(void) {
    void *manager;
    void *knife;
    u8 flags;
    u8 ready;
    u32 index;

    manager = func_020909c8();
    knife = KnifeApp_getInstance();
    index = (data_0212c538 - 2) & 0xf;
    flags = data_0212c9a8[3];
    ready = 1;
    if (flags & 1) {
        if (data_02134cb0[index] == 0xc000) {
            ready = 0;
        }
    }
    if (flags & 2) {
        if (data_02134cd0[index] == 0xc000) {
            ready = 0;
        }
    }
    if (flags & 4) {
        if (data_02134cf0[index] == 0xc000) {
            ready = 0;
        }
    }
    if (flags & 8) {
        if (data_02134d10[index] == 0xc000) {
            ready = 0;
        }
    }
    if (KnifeApp_isWirelessMode(knife) == 0) {
        if (ready != 0) {
            *(u32 *)(data_0212c9a8 + 8) = 2;
            return;
        }
        MIi_CpuCopy16(data_0212c9ec, data_0212c9b8, 0x34);
        return;
    }
    if (func_020921b0(manager) == 0) {
        *(u32 *)(data_0212c9a8 + 8) = 2;
        return;
    }
    MIi_CpuCopy16(data_0212c9ec, data_0212c9b8, 0x34);
}
