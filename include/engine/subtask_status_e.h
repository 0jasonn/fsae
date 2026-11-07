#ifndef WIP_E_SUBTASK_STATUS_E_H
#define WIP_E_SUBTASK_STATUS_E_H

#include "engine/functions.h"
#include "engine/fp_pack_api.h"

// Per-player status block filled by GetSubtaskPlayerStatus (0x14 bytes). Same struct as SUBTASK_PLAYER_WORK in
// knife/subtask/subtask.h; this one names the bitfields of the first word (itemFlags there).
typedef struct SUBTASK_PLAYER_WORK {
    u32 linkOk : 1;
    u32 isLocal : 1;
    u32 flag : 2;
    u32 bit4 : 1;
    u32 bit5 : 1;
    u32 bit6 : 1;
    u32 bit7 : 1;
    u32 bit8 : 1;
    u32 field9 : 2;
    u32 field11 : 2;
    u32 field13 : 2;
    u32 unk_04;
    u32 medalValue;
    u32 ruppyValue;
    u32 floatValue;
} SUBTASK_PLAYER_WORK;

// Wireless member record (0x34 bytes each, data_0212ca20); the status bits are packed like the packet word.
typedef struct SubtaskMemberBits {
    u32 b0 : 2;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 1;
    u32 b5 : 1;
    u32 b6 : 1;
    u32 b7 : 2;
    u32 b9 : 2;
    u32 b11 : 2;
    u32 b13 : 10;
    u32 b23 : 7;
    u32 b30 : 2;
} SubtaskMemberBits;

typedef struct SubtaskMember {
    u8 unk_00[0x24];
    SubtaskMemberBits bits; // 24
    u32 w28;
    u32 w2c;
    u32 unk_30;
} SubtaskMember;

typedef struct SubtaskSendEntry {
    u32 word00;
    u8 unk_04;
    u8 b05;
    u16 h06;
    u8 unk_08[0x10];
    u32 w18;
    u8 unk_1c[0x34];
} SubtaskSendEntry;

typedef struct SubtaskSelect {
    u8 unk_00[4];
    u8 index;
} SubtaskSelect;

extern SubtaskMember data_0212ca20[];
extern SubtaskSendEntry data_021350b0[];
extern SubtaskSelect multiSioSelect;
extern u8 localPlayerIndex;

extern "C" {
void GetSubtaskPlayerStatus(int playerIndex, SUBTASK_PLAYER_WORK *status);
u32 func_0200dd38(u32 value);
s32 Knife_Comm_WirelessManager_getLinkLevel(void *manager);
void MI_CpuFill8(void *dst, u8 value, u32 size);
}
s8 subtask_getFlag(u32 index);

#endif
