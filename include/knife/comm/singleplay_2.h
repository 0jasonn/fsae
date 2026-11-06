#ifndef KNIFE_COMM_SINGLEPLAY_2_H
#define KNIFE_COMM_SINGLEPLAY_2_H

#include "types.h"
#include "engine/player.h"
#include "knife/comm/single_play.h"

// SinglePlay work pair (the local object the pause and warp code builds on the stack): the two player pointers, their
// data pointers, entities and position differences. Same layout as SpWorkPair in src/knife/comm/singleplay_work.cpp;
// the reviewer should move it into a shared header.
typedef struct SpWorkPair {
    PlayerData *player0;    // 0x00
    PlayerData *player1;    // 0x04
    void *data0;            // 0x08
    void *data1;            // 0x0c
    Entity *entity0;        // 0x10
    Entity *entity1;        // 0x14
    u16 unk_18;
    u16 unk_1a;
    u16 unk_1c;
    u16 unk_1e;
    u16 unk_20;
    u16 unk_22;
    s16 diffX;              // 0x24
    s16 diffY;              // 0x26
    s16 distX;              // 0x28
    s16 distY;              // 0x2a
    u16 unk_2c;
    u16 unk_2e;
    u16 unk_30;
    u16 unk_32;
    u16 unk_34;
    u16 unk_36;
    u8 unk_38;
    u8 unk_39;
    u8 nearFlag;            // 0x3a
    u8 unk_3b;
    u8 unk_3c;
} SpWorkPair;

// Bit view of PlayerData::paletteBits (0x8b): a = bits 0..1, b = bits 2..3 (palette index), c = bits 4..6, d = bit 7.
typedef struct PalBits {
    u8 a : 2;
    u8 b : 2;
    u8 c : 3;
    u8 d : 1;
} PalBits;

// Rodata block read by the formation code (symbols.txt: data_0211b298); this unit reads the u16 at +0x32.
extern u8 data_0211b298[];

// Table of s16 offset pairs indexed by the animation state (symbols.txt: data_0211b2e4); UpdateTruck reads it.
extern s16 data_0211b2e4[];

// Frame counter block (symbols.txt: frameCounter); this unit reads its byte at +0x13.
extern u8 frameCounter[];

// Functions the SinglePlay update code calls (plain names, original signatures with this as void *).
extern "C" {
void Knife_Single_SinglePlay_SinglePlayWork_Initialize(void *self, u8 contNo, PlayerData *player0, PlayerData *player1);
void Knife_Single_SinglePlay_UpdateWaitPartner(void *self, PlayerData *player0, PlayerData *player1);
void Knife_Single_SinglePlay_UpdatePause(void *self, PlayerData *player0, PlayerData *player1);
BOOL Knife_Single_SinglePlay_UpdateFormationMode2p(void *self, SpWorkPair *pair);
void Knife_Single_SinglePlay_SinglePlayWork_PlayerChange(void *pair);
// SinglePlayLogList::Initialize (0x0209a060), mangled in symbols.txt; this = the log list.
void _ZN5Knife6Single10SinglePlay17SinglePlayLogList10InitializeEv(void *self);
BOOL Knife_Single_SinglePlay_UpdateTruck(void *self, SpWorkPair *pair);
BOOL Knife_Single_SinglePlay_WarpPartner(void *self, PlayerData *player);
BOOL Knife_Single_SinglePlay_WarpPartnerToTarget(void *self, PlayerData *player0, PlayerData *player1, s16 x, s16 y);
void Knife_Single_SinglePlay_SinglePlayLogList_UpdateCurrentLogDistance(void *self, s16 distance);
BOOL Knife_Single_SinglePlay_UpdateStopWarp(void *self, SpWorkPair *pair);
}

#endif
