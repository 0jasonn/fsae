#ifndef WIP_B_WXC_H
#define WIP_B_WXC_H

#include "engine/functions.h"

// Comm state block (shared with lobby.h / multiplay.h, byte-array view kept as declared there).
extern u8 comWork[];

extern "C" {
s32 WXC_GetStateCode(void);
}

#endif
