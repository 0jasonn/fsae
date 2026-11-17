#ifndef WIP_COMERROR_WORK_H
#define WIP_COMERROR_WORK_H

#include "engine/functions.h"
#include "actor/enemy/commerror.h"

// View of the communication state block (comWork) used by the communication error code (same layout as in
// src/knife/comm/commerror.cpp, which should move it here).
typedef struct ComPlayerSlot {
    u8 tag;          // 00: status code that the player reports
    u8 unk_01[0x33];
} ComPlayerSlot;

typedef struct ComErrorWork {
    u8 unk_00[3];
    u8 readyMask;    // 03
    u8 unk_04[8];
    u16 errorTimer;  // 0c
    u8 holdFlag;     // 0e
    u8 unk_0f[0x78 - 0x0f];
    ComPlayerSlot players[4];
} ComErrorWork;

#define COM_WORK ((ComErrorWork *)comWork)

extern u8 comWork[];
extern u8 data_0212c4d4;
extern u32 opTitleState;

#endif
