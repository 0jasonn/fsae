#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/snd/snd_command.h"

// Command ids understood by the ARM7 sound driver (SND_COMMAND_*).
enum {
    SND_CMD_STOP_SEQ = 1,
    SND_CMD_PREPARE_SEQ = 2,
    SND_CMD_START_PREPARED_SEQ = 3,
    SND_CMD_PAUSE_SEQ = 4,
    SND_CMD_SKIP_SEQ = 5,
    SND_CMD_PLAYER_PARAM = 6,
    SND_CMD_TRACK_PARAM = 7,
    SND_CMD_MUTE_TRACK = 8,
    SND_CMD_ALLOCATABLE_CHANNEL = 9,
    SND_CMD_START_TIMER = 12,
    SND_CMD_STOP_TIMER = 13,
    SND_CMD_SETUP_CHANNEL_PCM = 14,
    SND_CMD_CHANNEL_VOLUME = 20,
    SND_CMD_CHANNEL_PAN = 21,
    SND_CMD_SURROUND_DECAY = 22,
    SND_CMD_MASTER_VOLUME = 23,
    SND_CMD_MASTER_PAN = 24,
    SND_CMD_OUTPUT_SELECTOR = 25,
    SND_CMD_LOCK_CHANNEL = 26,
    SND_CMD_UNLOCK_CHANNEL = 27,
    SND_CMD_INVALIDATE_SEQ = 30,
    SND_CMD_INVALIDATE_BANK = 31,
    SND_CMD_INVALIDATE_WAVE = 32,
    SND_CMD_READ_DRIVER_INFO = 33
};

// One queued command: link, command id and four arguments.
typedef struct SndCommand {
    void *next;
    u32 command;
    u32 arg[4];
} SndCommand;

extern u32 data_02129d90;

// SND_StopSeq(playerNo) (0x0201ab90) ... SNDi_SetSurroundDecay (0x0201af5c): thin wrappers around PushCommand_impl.

void SND_StopSeq(s32 playerNo) {
    PushCommand_impl(SND_CMD_STOP_SEQ, playerNo, 0, 0, 0);
}

void SND_PrepareSeq(s32 playerNo, const void *seqBase, u32 seqOffset, const void *bank) {
    PushCommand_impl(SND_CMD_PREPARE_SEQ, playerNo, (u32)seqBase, seqOffset, (u32)bank);
}

void SND_StartPreparedSeq(s32 playerNo) {
    PushCommand_impl(SND_CMD_START_PREPARED_SEQ, playerNo, 0, 0, 0);
}

void SND_PauseSeq(s32 playerNo, s32 pause) {
    PushCommand_impl(SND_CMD_PAUSE_SEQ, playerNo, pause, 0, 0);
}

void SND_SetPlayerTempoRatio(s32 playerNo, s32 ratio) {
    SNDi_SetPlayerParam(playerNo, 0x1a, ratio, 2);
}

void SND_SetPlayerVolume(s32 playerNo, s32 volume) {
    SNDi_SetPlayerParam(playerNo, 6, volume, 2);
}

void SND_SetPlayerChannelPriority(s32 playerNo, s32 priority) {
    SNDi_SetPlayerParam(playerNo, 4, priority, 1);
}

void SND_SetTrackPan(s32 playerNo, u32 trackMask, s32 pan) {
    SNDi_SetTrackParam(playerNo, trackMask, 9, pan, 1);
}

void SND_SetTrackAllocatableChannel(s32 playerNo, u32 trackMask, u32 channelMask) {
    PushCommand_impl(SND_CMD_ALLOCATABLE_CHANNEL, playerNo, trackMask, channelMask, 0);
}

void SND_StartTimer(u32 channelMask, u32 captureMask, u32 alarmMask, u32 flags) {
    PushCommand_impl(SND_CMD_START_TIMER, channelMask, captureMask, alarmMask, flags);
}

void SND_StopTimer(u32 channelMask, u32 captureMask, u32 alarmMask, u32 flags) {
    s32 alarmNo;
    u32 mask = alarmMask;

    for (alarmNo = 0; alarmNo < 8 && mask != 0; alarmNo++, mask >>= 1) {
        if (mask & 1) {
            SNDi_IncAlarmId(alarmNo);
        }
    }
    PushCommand_impl(SND_CMD_STOP_TIMER, channelMask, captureMask, alarmMask, flags);
}

void SND_LockChannel(u32 channelMask, u32 flags) {
    PushCommand_impl(SND_CMD_LOCK_CHANNEL, channelMask, flags, 0, 0);
}

void SND_UnlockChannel(u32 channelMask, u32 flags) {
    PushCommand_impl(SND_CMD_UNLOCK_CHANNEL, channelMask, flags, 0, 0);
}

void SND_SetChannelVolume(u32 channelMask, s32 volume, s32 shift) {
    PushCommand_impl(SND_CMD_CHANNEL_VOLUME, channelMask, volume, shift, 0);
}

void SND_SetChannelPan(u32 channelMask, s32 pan) {
    PushCommand_impl(SND_CMD_CHANNEL_PAN, channelMask, pan, 0, 0);
}

void SND_SetupChannelPcm(s32 channel, s32 format, const void *data, s32 loop, s32 loopStart, s32 length, s32 volume,
                         s32 shift, s32 timer, s32 pan) {
    PushCommand_impl(SND_CMD_SETUP_CHANNEL_PCM, channel | (timer << 16), (u32)data,
                     length | ((volume << 24) | (shift << 22)),
                     loopStart | (((loop << 26) | (format << 24)) | (pan << 16)));
}

void SND_InvalidateSeqData(const void *start, const void *end) {
    PushCommand_impl(SND_CMD_INVALIDATE_SEQ, (u32)start, (u32)end, 0, 0);
}

void SND_InvalidateBankData(const void *start, const void *end) {
    PushCommand_impl(SND_CMD_INVALIDATE_BANK, (u32)start, (u32)end, 0, 0);
}

void SND_InvalidateWaveData(const void *start, const void *end) {
    PushCommand_impl(SND_CMD_INVALIDATE_WAVE, (u32)start, (u32)end, 0, 0);
}

void SND_SetMasterVolume(s32 volume) {
    PushCommand_impl(SND_CMD_MASTER_VOLUME, volume, 0, 0, 0);
}

void SND_SetOutputSelector(u32 left, u32 right, u32 channel1, u32 channel3) {
    PushCommand_impl(SND_CMD_OUTPUT_SELECTOR, left, right, channel1, channel3);
}

void SND_SetMasterPan(s32 pan) {
    PushCommand_impl(SND_CMD_MASTER_PAN, pan, 0, 0, 0);
}

void SND_ResetMasterPan(void) {
    PushCommand_impl(SND_CMD_MASTER_PAN, -1, 0, 0, 0);
}

void SND_ReadDriverInfo(void *info) {
    PushCommand_impl(SND_CMD_READ_DRIVER_INFO, (u32)info, 0, 0, 0);
}

void SNDi_SetPlayerParam(s32 playerNo, u32 offset, u32 value, u32 size) {
    PushCommand_impl(SND_CMD_PLAYER_PARAM, playerNo, offset, value, size);
}

void SNDi_SetTrackParam(s32 playerNo, u32 trackMask, u32 offset, u32 value, u32 size) {
    PushCommand_impl(SND_CMD_TRACK_PARAM, playerNo | (size << 24), trackMask, offset, value);
}

void SNDi_SetSurroundDecay(s32 decay) {
    PushCommand_impl(SND_CMD_SURROUND_DECAY, decay, 0, 0, 0);
}

// PushCommand_impl(command, arg0..arg3) (0x0201af7c): allocates a command (blocking), fills it and queues it.
void PushCommand_impl(u32 command, u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    SndCommand *cmd = (SndCommand *)SND_AllocCommand(1);

    if (cmd == NULL) {
        return;
    }
    cmd->command = command;
    cmd->arg[0] = arg0;
    cmd->arg[1] = arg1;
    cmd->arg[2] = arg2;
    cmd->arg[3] = arg3;
    SND_PushCommand(cmd);
}

// SND_Init() (0x0201afc0): one-time setup of the command queue and alarms.
void SND_Init(void) {
    if (data_02129d90 != 0) {
        return;
    }
    data_02129d90 = 1;
    OS_InitMutex(&data_02129d94);
    SND_CommandInit();
    SND_AlarmInit();
}
