#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   exchange_savedata (0x020b2a5c), is_exchange_savedata_end (0x020b2a90), lobby_noop (0x020b2aac, renamed from
//   lobby_noop), leaveLobby (0x020b2ab0)

extern u8 enemyTypeFlags[];  // 0x20 bytes, cleared by exchange_savedata
extern u8 data_0212c9a8[];  // exchange state: u32 at +8 (1 when the exchange ended), flag byte at +0x0e
extern u8 data_02181860[];  // lobby state, the pointer at +4 leads to the lobby block
extern u8 data_0217d23c[];  // lobby flags at +0xd0 and +0xd1
extern u8 data_0217d23c[];

void ComRequest(unsigned char request);
void MachiukeStop(void);
extern "C" BOOL Knife_Comm_WirelessManager_endParent(void *manager);
extern "C" BOOL Knife_Comm_WirelessManager_disconnect(void *manager);

// exchange_savedata() (0x020b2a5c): clears the exchange buffer and starts the exchange request
extern "C" void exchange_savedata(void);
ARM void exchange_savedata(void) {
    OSi_CpuClear32(0, enemyTypeFlags, 0x20);
    ComRequest(3);
    data_0212c9a8[0x0e] = 1;
}

// is_exchange_savedata_end() (0x020b2a90): TRUE when the exchange has ended
extern "C" BOOL is_exchange_savedata_end(void);
ARM BOOL is_exchange_savedata_end(void) {
    if (*(u32 *)(data_0212c9a8 + 8) == 1) {
        return TRUE;
    }
    return FALSE;
}

// lobby_noop() (0x020b2aac): empty
ARM void lobby_noop(void) {
}

// leaveLobby() (0x020b2ab0): leaves the wireless group (or disconnects) and resets the lobby block
extern "C" void leaveLobby(void);
ARM void leaveLobby(void) {
    void *manager;
    BOOL result;
    s32 i;

    manager = func_020909c8();
    if (*(s8 *)(*(u8 **)(data_02181860 + 4) + 0x3a) == 0) {
        result = Knife_Comm_WirelessManager_endParent(manager);
    } else {
        result = Knife_Comm_WirelessManager_disconnect(manager);
    }
    if (result == 0) {
        return;
    }
    MachiukeStop();
    *(u16 *)(*(u8 **)(data_02181860 + 4) + 0x2a) = 2;
    *(s8 *)(*(u8 **)(data_02181860 + 4) + 0x28) = 8;
    *(u8 *)(*(u8 **)(data_02181860 + 4) + 0x39) = 0;
    data_0217d23c[0xd0] = 1;
    data_0217d23c[0xd1] = 3;
    for (i = 0; i < 0x20; i++) {
        *(u8 *)(*(u8 **)(*(u8 **)(data_02181860 + 4) + 0x34) + (u8)i * 0x58 + 3) = 0;
    }
}
