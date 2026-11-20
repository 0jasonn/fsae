#ifndef WIP_WM_MP_H
#define WIP_WM_MP_H

#include "engine/functions.h"

extern "C" {
s32 WM_StartMP(void *callback, void *recvBuf, u16 recvSize, void *sendBuf, u16 sendSize, u16 frequency);
s32 func_0201ff40(void *callback, void *recvBuf, u16 recvBufSize, void *sendBuf, u16 sendBufSize, void *param);
}

#endif
