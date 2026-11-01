#ifndef WIP_B_COMM_H
#define WIP_B_COMM_H

#include "engine/functions.h"

// Manager pointer getter used by the communication code (called for its side effect in CommUpdateJoy).
void *func_020909c8(void);

// Current communication mode (sync state), signed.
extern s32 data_0212c538;
// Joypad keys per player slot: four 16-entry tables, 0x20 bytes apart (frame_ack.cpp).
extern u16 data_02134cb0[];
// Keys of the communication slots, and the new keys of the slots (cleared when the mode is below 8).
extern u16 data_0212c58c[];

#endif
