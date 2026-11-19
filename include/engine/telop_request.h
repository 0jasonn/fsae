#ifndef ENGINE_TELOP_REQUEST_H
#define ENGINE_TELOP_REQUEST_H

#include "types.h"

// Telop request block (telopRequest, 0x18 bytes up to messageRequest). TelopRequest() clears it and stores the text id;
// the caller then fills the numbers shown in the telop. tlpInit copies the whole block into telopBox (+0x0c), so the
// layout matches the request part of KNIFE_MSGSYS (windowPhase, layoutFlags, msgId).
typedef struct TelopWork {
    /* 00 */ u8 active;
    /* 01 */ u8 unk_01;
    /* 02 */ u8 flags; // low nibble = 3 while a request is active, bits 4-5 = bank of (id - 1000) / 100
    /* 03 */ u8 unk_03[3];
    /* 06 */ u16 requestId; // bit 15 is set while the telop is busy
    /* 08 */ u32 params[4]; // numbers shown in the telop text (player number, minutes/seconds, bonus, counts)
} TelopWork;
extern TelopWork telopRequest; // 0x0217d36c

#endif
