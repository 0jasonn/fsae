#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/comm.h"

// Functions in this file (module com, original names from the debug build): frame_ack (frame_ack())

#include "engine/com_work.h"
#include "engine/key_ring.h"
extern u16 data_02134cd0[];
extern u16 data_02134cf0[];
extern u16 data_02134d10[];

// frame_ack (0x02028944): a frame is acknowledged when no table entry of the players selected by byte 3 (bits 0..3) is
// 0xc000 at the index data_0212c538 - 2. Wireless play answers with 2 at +8 unless the manager says the frame is done.
void frame_ack(void) {
    void *manager;
    void *knife;
    u8 flags;
    u8 ready;
    u32 index;

    manager = func_020909c8();
    knife = KnifeApp_getInstance();
    index = (data_0212c538 - 2) & 0xf;
    flags = comWork.status;
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
            comWork.result = 2;
            return;
        }
        MIi_CpuCopy16(&comWork.next, &comWork.send, sizeof(ComPacket));
        return;
    }
    if (Knife_Comm_WirelessManager_getFrameFlag(manager) == 0) {
        comWork.result = 2;
        return;
    }
    MIi_CpuCopy16(&comWork.next, &comWork.send, sizeof(ComPacket));
}
