#ifndef WIP_A_PMI_SEND_H
#define WIP_A_PMI_SEND_H

#include "global.h"
#include "types.h"

// PMi send state at data_0212b920. Fields used by PMi_InitSend (src/wip/A/pmi_init.cpp): ready flag at +0,
// two words at +0x0c and +0x10 copied from 0x02fffc3c, busy flag at +0x30 and a parameter at +0x34.
typedef struct PmiSendState {
    u16 ready;               // 0x00
    u8 unk_02[0x0a];
    u32 unk_0c;              // 0x0c
    u32 unk_10;              // 0x10
    u8 unk_14[0x1c];
    s32 busy;                // 0x30
    u32 param34;             // 0x34
} PmiSendState;

extern PmiSendState data_0212b920;

#endif
