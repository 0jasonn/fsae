#include "engine/functions.h"
#include "sdk/wm/wm_work.h"
#include "game/agent.h"
#include "knife/comm/wm_work.h"
#include "sdk/wm/wm_startmp.h"
#include "global.h"
#include "types.h"

// Starts multiplayer mode after validating its callback buffers (0x0201ff40).
extern "C" s32 func_0201ff40(void *callback, void *recvBuf, u16 recvBufSize, void *sendBuf, u16 sendBufSize, void *param) {
    u32 command[16];
    u8 *state;
    s32 status;

    state = *(u8 **)((u8 *)WMi_GetWorkPointer() + 4);
    status = WMi_CheckStateEx(2, 7, 8);
    if (status != 0) {
        return status;
    }

    DC_InvalidateRange(state + 0x188, 2);
    DC_InvalidateRange(state + 0xc6, 2);
    if (*(u16 *)(state + 0x188) != 0 && *(u16 *)(state + 0xc6) != 1) {
        return 3;
    }

    DC_InvalidateRange(state + 0xc, 4);
    if (*(u32 *)(state + 0xc) == 1) {
        return 3;
    }
    if (((u32)recvBufSize & 0x3f) != 0) {
        return 6;
    }

    {
        s32 checkedSendSize = sendBufSize;

        if ((checkedSendSize & 0x1f) != 0) {
            return 6;
        }
        DC_InvalidateRange(state + 0x9c, 2);
        if (*(u16 *)(state + 0x9c) == 0) {
            if ((s32)recvBufSize < (s32)WM_GetMPReceiveBufferSize()) {
                return 6;
            }
            if ((s32)checkedSendSize < (s32)WM_GetMPSendBufferSize()) {
                return 6;
            }
        }
    }

    WMi_SetCallbackTable(0xe, callback);
    OSi_CpuClear32(0, command, 0x40);
    ((u16 *)command)[0] = 0xe;
    command[1] = (u32)recvBuf;
    command[2] = (u32)recvBufSize >> 1;
    command[3] = (u32)sendBuf;
    command[4] = sendBufSize;
    OSi_CpuClear32(0, &command[5], 0x1c);
    MIi_CpuCopy32(param, &command[12], 0x10);

    status = WMi_SendCommandDirect((u16 *)command, 0x40);
    if (status == 0) {
        status = 2;
    }
    return status;
}
