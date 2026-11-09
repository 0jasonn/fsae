#include "engine/functions.h"
#include "knife/comm/wirelessmanager.h"
#include "game/agent_a.h"

// WM_EndMP (0x02020260): stops the MP session.
s32 WM_EndMP(void *callback) {
    void *work = func_0201eddc();
    s32 status;

    status = WMi_CheckStateEx(2, 9, 10);
    if (status != 0) {
        return status;
    }
    DC_InvalidateRange(*(u8 **)((u8 *)work + 4) + 0xc, 4);
    if (*(u32 *)(*(u8 **)((u8 *)work + 4) + 0xc) == 0) {
        return 3;
    }
    WMi_SetCallbackTable(0x10, callback);
    status = WMi_SendCommand(0x10, 0);
    if (status == 0) {
        status = 2;
    }
    return status;
}
