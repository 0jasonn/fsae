#ifndef KNIFE_COMM_WXC_H
#define KNIFE_COMM_WXC_H

#include "engine/functions.h"

// Comm state block (shared with lobby.h / multiplay.h, byte-array view kept as declared there).
#include "engine/com_work.h"

extern "C" {
s32 WXC_GetStateCode(void);
}

#endif
