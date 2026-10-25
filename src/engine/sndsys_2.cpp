#include "engine/functions.h"
#include "global.h"

extern "C" {
void SND_StopTimer(u32 mask, u32 a, u32 b, u32 c);
u32 SND_GetCurrentCommandTag(void);
void SND_FlushCommand(u32 mode);
void SND_WaitForCommandProc(u32 tag);
s32 SND_RecvCommandReply(u32 tag);
s32 SND_IsFinishedCommandTag(u32 tag);
void SND_ReadDriverInfo(void *buffer);
s32 SND_ReadChannelInfo(void *table, s32 index, void *entry);
void SNDi_SetSurroundDecay(s32 decay);
void SndSlot_ReleaseAll(s32 arg);
void DC_InvalidateRange(void *start, u32 size);
void func_020c0350(void);
void func_020c1a38(s32 value);
}

// Sound driver state at data_02181964 (the same object as SndSysState in sndsys.cpp).
typedef struct SndDriverBufferState {
    /* 00 */ s8 bufferIndex; // which of the two driver buffers is current (negative is treated as 1)
    /* 01 */ u8 unk_01[3];
    /* 04 */ s32 initialized; // nonzero until the first swap
    /* 08 */ u32 commandTag; // tag of the last command queued by this module
} SndDriverBufferState;

extern "C" SndDriverBufferState data_02181964;
extern "C" u8 data_021819a0[]; // the two driver buffers, 0x11e0 bytes each

extern "C" void SndSys_StopActiveTimer(void);

#define SND_DRIVER_BUFFER_SIZE 0x11e0

// SndSys_StopAll: releases the slots, clears the surround decay and the timer, then flushes the commands and waits for
// the last one.
extern "C" void SndSys_StopAll(void);
ARM void SndSys_StopAll(void) {
    u32 tag;

    SndSlot_ReleaseAll(0);
    func_020c1a38(0);
    func_020c0350();
    SNDi_SetSurroundDecay(0);
    SND_StopTimer(0xffff, 0xffff, 0xffff, 0);
    tag = SND_GetCurrentCommandTag();
    SND_FlushCommand(1);
    SND_WaitForCommandProc(tag);
}

// SndSys_SwapDriverBuffer: swaps the driver buffer once the last queued command has finished. The first call only reads the
// current buffer and records its tag. Returns 1 when the buffers were swapped.
extern "C" s32 SndSys_SwapDriverBuffer(void);
ARM s32 SndSys_SwapDriverBuffer(void) {
    if (data_02181964.initialized == 0) {
        while (SND_RecvCommandReply(0) != 0) {
        }
        if (SND_IsFinishedCommandTag(data_02181964.commandTag) == 0) {
            return 0;
        }
        if (data_02181964.bufferIndex < 0) {
            data_02181964.bufferIndex = 1;
        }
        SND_ReadDriverInfo(data_021819a0 + data_02181964.bufferIndex * SND_DRIVER_BUFFER_SIZE);
        data_02181964.commandTag = SND_GetCurrentCommandTag();
        if (data_02181964.bufferIndex == 0) {
            data_02181964.bufferIndex = 1;
        } else {
            data_02181964.bufferIndex = 0;
        }
        DC_InvalidateRange(data_021819a0 + data_02181964.bufferIndex * SND_DRIVER_BUFFER_SIZE, SND_DRIVER_BUFFER_SIZE);
        SND_FlushCommand(0);
        return 1;
    }
    SND_ReadDriverInfo(data_021819a0);
    data_02181964.commandTag = SND_GetCurrentCommandTag();
    data_02181964.initialized = 0;
    return 0;
}

// SndSys_ReadChannelInfoCurrent: reads the channel info from the current driver buffer. Returns 0 when there is no current buffer.
extern "C" s32 SndSys_ReadChannelInfoCurrent(s32 index, void *entry);
ARM s32 SndSys_ReadChannelInfoCurrent(s32 index, void *entry) {
    u8 *table;

    if (data_02181964.bufferIndex < 0) {
        table = 0;
    } else {
        table = data_021819a0 + data_02181964.bufferIndex * SND_DRIVER_BUFFER_SIZE;
    }
    if (table == 0) {
        return 0;
    }
    return SND_ReadChannelInfo(table, index, entry);
}

// SndSys_ExitStopTimer: sound exit callback (A). Runs SndSys_StopActiveTimer, stops the timer, then flushes the commands and waits for
// the last one.
extern "C" void SndSys_ExitStopTimer(void);
ARM void SndSys_ExitStopTimer(void) {
    u32 tag;

    SndSys_StopActiveTimer();
    SND_StopTimer(0, 0, 0, 0);
    tag = SND_GetCurrentCommandTag();
    SND_FlushCommand(1);
    SND_WaitForCommandProc(tag);
}
