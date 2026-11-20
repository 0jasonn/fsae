#include "engine/functions.h"
#include "game/agent.h"
#include "sdk/wm/wm_startmp.h"

// WM_StartMP (0x020200c0): fills the MP parameter block and starts the MP session.
s32 WM_StartMP(void *callback, void *recvBuf, u16 recvSize, void *sendBuf, u16 sendSize, u16 frequency) {
    u32 param[4];

    OSi_CpuClear32(0, param, 0x10);
    ((u16 *)param)[2] = frequency;
    ((u16 *)param)[3] = frequency;
    param[0] = 3;
    return func_0201ff40(callback, recvBuf, recvSize, sendBuf, sendSize, param);
}
