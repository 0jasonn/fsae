#ifndef SDK_SND_SND_COMMAND_H
#define SDK_SND_SND_COMMAND_H

#include "engine/entity.h"
#include "sdk/os/os_mutex.h"

extern OsMutex data_02129d94; // the SND library mutex

// One command record of the ARM9 to ARM7 sound command queue (0x18 bytes, 256 of them in the pool).
typedef struct SndQueuedCommand {
    struct SndQueuedCommand *next; // 0x00
    u32 command;                   // 0x04
    u32 arg[4];                    // 0x08
} SndQueuedCommand;

// State of the command queue (data_02129dac): free list, reserved (being built) list, and the lists already sent to
// the ARM7 and not yet reported back.
typedef struct SndCommandQueue {
    SndQueuedCommand *freeList;    // 0x00
    u32 finishedCount;             // 0x04: number of flushed lists the ARM7 has finished
    SndQueuedCommand *reserveHead; // 0x08
    SndQueuedCommand *reserveTail; // 0x0c
    SndQueuedCommand *freeTail;    // 0x10
    s32 recvIndex;                 // 0x14: next entry of sentLists to take back
    s32 sendIndex;                 // 0x18: next entry of sentLists to fill
    s32 sentCount;                 // 0x1c: lists sent and not yet finished
    u32 sentTag;                   // 0x20: tag of the most recent flush
} SndCommandQueue;

extern SndCommandQueue data_02129dac;
extern SndQueuedCommand *data_02129dd0[9];  // lists sent to the ARM7, a ring of nine
extern SndQueuedCommand data_0212a080[256]; // command pool

// TwlSDK sound library command front end. Every function here queues one command for the ARM7 sound driver.
extern "C" {
void PushCommand_impl(u32 command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);
void SND_StopSeq(s32 playerNo);
void SND_PrepareSeq(s32 playerNo, const void *seqBase, u32 seqOffset, const void *bank);
void SND_StartPreparedSeq(s32 playerNo);
void SND_PauseSeq(s32 playerNo, s32 pause);
void SND_SetPlayerTempoRatio(s32 playerNo, s32 ratio);
void SND_SetPlayerVolume(s32 playerNo, s32 volume);
void SND_SetPlayerChannelPriority(s32 playerNo, s32 priority);
void SND_SetTrackPan(s32 playerNo, u32 trackMask, s32 pan);
void SND_SetTrackAllocatableChannel(s32 playerNo, u32 trackMask, u32 channelMask);
void SND_StartTimer(u32 channelMask, u32 captureMask, u32 alarmMask, u32 flags);
void SND_StopTimer(u32 channelMask, u32 captureMask, u32 alarmMask, u32 flags);
void SND_LockChannel(u32 channelMask, u32 flags);
void SND_UnlockChannel(u32 channelMask, u32 flags);
void SND_SetChannelVolume(u32 channelMask, s32 volume, s32 shift);
void SND_SetChannelPan(u32 channelMask, s32 pan);
void SND_SetupChannelPcm(s32 channel, s32 format, const void *data, s32 loop, s32 loopStart, s32 length, s32 volume,
                         s32 shift, s32 timer, s32 pan);
void SND_InvalidateSeqData(const void *start, const void *end);
void SND_InvalidateBankData(const void *start, const void *end);
void SND_InvalidateWaveData(const void *start, const void *end);
void SND_SetMasterVolume(s32 volume);
void SND_SetOutputSelector(u32 left, u32 right, u32 channel1, u32 channel3);
void SND_SetMasterPan(s32 pan);
void SND_ResetMasterPan(void);
void SND_ReadDriverInfo(void *info);
void SNDi_SetPlayerParam(s32 playerNo, u32 offset, u32 value, u32 size);
void SNDi_SetTrackParam(s32 playerNo, u32 trackMask, u32 offset, u32 value, u32 size);
void SNDi_SetSurroundDecay(s32 decay);
void SND_Init(void);

// Command queue (snd_command.c).
void SND_CommandInit(void);
SndQueuedCommand *SND_RecvCommandReply(u32 flags);
SndQueuedCommand *SND_AllocCommand(u32 flags);
void SND_PushCommand(void *command);
void SND_WaitForCommandProc(u32 tag);
u32 SND_GetCurrentCommandTag(void);
s32 SND_IsFinishedCommandTag(u32 tag);
s32 SND_CountFreeCommand(void);
s32 SND_CountReservedCommand(void);
s32 SND_CountWaitingCommand(void);
void PxiFifoCallback(u32 tag, u32 data, s32 err); // PXI tag 7 receive handler
void InitPXI(void);
void RequestCommandProc(void);
SndQueuedCommand *AllocCommand(void);
BOOL IsCommandAvailable(void);

// Not decompiled yet.
BOOL SND_FlushCommand(u32 flags);
}

#endif
