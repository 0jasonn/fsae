#ifndef SDK_SND_SND_COMMAND_H
#define SDK_SND_SND_COMMAND_H

#include "engine/entity.h"

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
void SND_CommandInit(void);
void SND_AlarmInit(void);
void SNDi_IncAlarmId(s32 alarmNo);
void *SND_AllocCommand(u32 block);
void SND_PushCommand(void *command);
void OS_InitMutex(void *mutex);
}

#endif
