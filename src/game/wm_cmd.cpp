#include "engine/functions.h"
#include "knife/comm/wirelessmanager.h"
#include "actor/object/wm_idle2parent.h"
#include "game/agent.h"

// Wireless manager commands, 0x02020df8 .. 0x02020fc8.

// WmGetSharedDataAddress (0x02020df8): returns the address of the slot's data inside the shared
// buffer, skipping the slots below the given index whose mask bit is set.
void *WmGetSharedDataAddress(void *base, u32 mask, void *shared, u32 index) {
    u32 count = MATH_CountPopulation(mask & ((1 << index) - 1));
    u32 size = *(u16 *)((u8 *)base + 0x810);

    return (u8 *)shared + count * size;
}

// WM_SetGameInfo (0x02020e28): copies the game info into the shared block and sends the command.
s32 WM_SetGameInfo(void *callback, void *gameInfo, u16 unk2, u32 unk3, u16 unk4, u8 unk5) {
    s32 status;

    status = WMi_CheckStateEx(2, 7, 9);
    if (status != 0) {
        return status;
    }
    if (gameInfo == NULL) {
        return 6;
    }
    if (unk2 > 0x70) {
        return 6;
    }
    MIi_CpuCopy16(gameInfo, data_0212c420, unk2);
    DC_StoreRange(data_0212c420, unk2);
    WMi_SetCallbackTable(0x18, callback);
    status = WMi_SendCommand(0x18, 5, data_0212c420, unk2, unk3, unk4, unk5);
    if (status == 0) {
        status = 2;
    }
    return status;
}

// WM_MeasureChannel (0x02020eec): measures the wireless channel and reports the result through
// the command buffer.
s32 WM_MeasureChannel(void *callback, u16 unk1, u16 unk2, u16 channel, u16 unk4) {
    u16 data[5];
    s32 status;

    func_0201eddc();
    status = WMi_CheckStateEx(1, 2);
    if (status != 0) {
        return status;
    }
    WMi_SetCallbackTable(0x1e, callback);
    data[0] = 0x1e;
    data[1] = unk1;
    data[2] = unk2;
    data[3] = channel;
    data[4] = unk4;
    status = WMi_SendCommandDirect(data, 0xa);
    if (status == 0) {
        status = 2;
    }
    return status;
}

// WM_SetEntry (0x02020f68): sends the entry command to the wireless module.
u32 WM_SetEntry(void *callback, BOOL flag) {
    s32 status;

    status = WMi_CheckStateEx(2, 7, 9);
    if (status != 0) {
        return status;
    }
    WMi_SetCallbackTable(0x21, callback);
    status = WMi_SendCommand(0x21, 1, flag);
    if (status == 0) {
        status = 2;
    }
    return status;
}

// WM_CheckInitialized (0x02020fbc): thin wrapper around NWMi_CheckInitialized.
s32 WM_CheckInitialized(void) {
    return NWMi_CheckInitialized();
}
