#ifndef KNIFE_COMM_SINGLE_PLAY_H
#define KNIFE_COMM_SINGLE_PLAY_H

#include "types.h"
#include "engine/player.h"
#include "knife/comm/knife_single_log.h"

// Knife::Single::SinglePlay state (the object the controller, formation and warp functions work on). Offsets from the
// start of the object. Only the fields the D functions read or write are named.
typedef struct SinglePlayWork {
    u8 contNo;               // 0x00: the controlling player (0 or 1)
    u8 contChanging;         // 0x01: nonzero while a controller change is in progress
    u8 formationChanging;    // 0x02
    u8 reqKind;              // 0x03: pending request (1: controller change, 2: formation change)
    u8 reqNo;                // 0x04: pending request number (0xff: none)
    u8 unk_05[2];
    u8 flags07;              // 0x07: bit 0 controller changed, bit 1 controller sound pending, bit 2 formation pending
    u8 unk_08;
    u8 unk_09;
    u8 unk_0a;
    u8 unk_0b;
    u8 unk_0c;
    u8 unk_0d[2];
    u8 unk_0f;
    u8 unk_10[2];
    u8 unk_12;               // 0x12
    u8 unk_13;
    u16 keysOn;              // 0x14: keys CommFrameUpdate ORs into the partner's packet / the local key ring
    u16 keysOff;             // 0x16: keys CommFrameUpdate masks out of the controlled player's keys
    u8 unk_18[0x1a - 0x18];
    u16 unk_1a;              // 0x1a: key mask set by SetContNoDirect
    u8 unk_1c[0x20 - 0x1c];
    u16 unk_20;              // 0x20: set to 0xffff by the initializers
    u16 unk_22;
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u8 unk_2a[0x2c - 0x2a];
    u16 unk_2c;
    u16 unk_2e;
    void *unk_30;            // 0x30
    u8 unk_34[0x34];         // 0x34: the log list (SinglePlayLogList, Initialize at 0x0209a060)
} SinglePlayWork;

extern "C" {
void Knife_Single_SinglePlay_SetContNo(void *self, u8 no); // original Knife::Single::SinglePlay::SetContNo(unsigned char), flat name
void Knife_Single_SinglePlay_SetWarpInfo(void *self, u8 a, u8 b);
void Knife_Single_SinglePlay_ChangeContPlayer(void *self);
void Knife_Single_SinglePlay_ChangeContPlayerDirect(void *self);
void Knife_Single_SinglePlay_ChangeFormationNo(void *self, PlayerData *player0, PlayerData *player1); // original ChangeFormationNo(PL_WORK_*, PL_WORK_*)
void Knife_Single_SinglePlay_InitializeCont(void *self);
void Knife_Single_SinglePlay_InitializeFormation(void *self);
void Knife_Single_SinglePlay_SetContNoDirect(void *self, u8 no);
void Knife_Single_SinglePlay_SetFormationNo(void *self, u8 no);
void Knife_Single_SinglePlay_SetFormationNoDirect(void *self, u8 no);
}

#endif
