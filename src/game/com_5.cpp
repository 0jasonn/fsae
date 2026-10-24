#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/comm.h"

// Functions in this file (module com, original names from the debug build):
//   com_randomsync (com_randomsync()), com_keysync (com_keysync())

extern u8 data_0212c9a8[]; // communication state block (see com.cpp)
extern u32 data_0212c550;
extern void (*const data_020f2584[])(void); // handler table, indexed by the phase byte 1

// com_randomsync (0x020286d4): when byte 3 is clear, ComFinish(5). Otherwise sends status 0x40 with data_0212c550 at
// +0x14; on a successful send, copies +0x7c into data_0212c550 in wireless play, then ComFinish(1). Always CommErrorCheck(0x40).
ARM void com_randomsync(void) {
    if (data_0212c9a8[3] == 0) {
        ComFinish(5);
        return;
    }
    data_0212c9a8[0x10] = 0x40;
    *(u32 *)(data_0212c9a8 + 0x14) = data_0212c550;
    if (CommStatusSync(0x40) != 0) {
        if (data_0212c9a8[3] & 1) {
            if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
                data_0212c550 = *(u32 *)(data_0212c9a8 + 0x7c);
            }
        }
        ComFinish(1);
    }
    CommErrorCheck(0x40);
}

// com_keysync (0x02028750): calls the handler for the phase byte 1, then CommErrorCheck(0x50).
ARM void com_keysync(void) {
    data_020f2584[data_0212c9a8[1]]();
    CommErrorCheck(0x50);
}
