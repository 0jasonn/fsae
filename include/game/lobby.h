#ifndef WIP_F_LOBBY_H
#define WIP_F_LOBBY_H

// Lobby of the multiplayer screens (wireless group, colour choice, dialogs). The lobby state is the block that the
// pointer at +4 of data_02181860 leads to (see exchange_savedata.cpp). Only the fields that the F round 16 files use
// are named here.

#include "types.h"

// Four 32-bit entries in rodata (also copied to the stack by the functions that index them)
typedef struct U32Table4 {
    u32 v[4];
} U32Table4;

// Four signed 32-bit entries in rodata
typedef struct S32Table4 {
    s32 v[4];
} S32Table4;

// Lobby state block (the pointer at +4 of data_02181860). Only the fields the F round 16 files use are named.
typedef struct LobbyState {
    u8 unk_00[0x28];
    s8 phase;                 // 0x28: lobby phase (8 when the connection is done)
    u8 unk_29;
    s16 timer;                // 0x2a: counts down in update_change_filesel, set to 2 by connectCheck
    u8 unk_2c[0x2e - 0x2c];
    u16 recvBits;             // 0x2e: one nibble per player, see lobby_setRecvParam
    u16 recvBits2;            // 0x30: second receive word, latched by lobby_latchRecvBits
    u8 unk_32[0x34 - 0x32];
    u8 *objects;              // 0x34: UI objects of the lobby (+0x58, +0x108 and +0x160 are used by update_colcancel_req_wait)
    u8 unk_38;
    s8 unk_39;                // 0x39: stage mode, switched on by update_change_stage
    s8 isParent;              // 0x3a: nonzero when the device is the wireless parent
    u8 playerCount;           // 0x3b: number of players in the group
    u8 unk_3c[0x9c - 0x3c];
    u16 unk_9c;               // 0x9c: set to 0x8007 by update_change_filesel
    u8 unk_9e[0xa4 - 0x9e];
    s8 unk_a4;                // 0xa4: signed, read as a flag by connectCheck
    u8 unk_a5;
    u8 unk_a6;
    u8 unk_a7;
    u8 unk_a8[0xb0 - 0xa8];
    void *unk_b0;             // 0xb0: blocks freed by subTask_lobby_end
    void *unk_b4;             // 0xb4
    void *unk_b8;             // 0xb8
} LobbyState;

extern u8 data_02181860[];   // lobby block pointer at +4 (LobbyState *)
extern u8 data_0217d23c[];   // lobby flags at +0xd0 and +0xd1
extern u8 data_0217d348[];   // pointer to the table of the received data blocks (stride 0x14)

extern u8 pauseDialogWindow[];   // pauseDialogWindow, the selection dialog of the lobby
extern u8 pauseDialogBuffer[];   // pauseDialogBuffer, screen block of the selection dialog (0x600 bytes)
extern u8 data_0212c9a8[];   // exchange state, the key block of the four players (stride 0x34) at +0x7a
extern u8 data_0212c584[];   // previous key state of the four players (u16 each)
extern u8 data_0212c58c[];   // new keys of the four players (u16 each), also the key state of the machine
extern u8 data_0212c514[];   // key state of the machine (u16)

extern u8 data_0212c5ac[];   // stage change block, the word at +0xc is set to -1 by update_change_stage
extern u8 data_0217a258[];   // OBJInfo block freed by subTask_lobby_end
extern u8 data_02126a48[];   // vtable of the lobby message object (lobby_msgObj_init)
extern "C" void Heap_VirtualFree(void *heap, void *block); // frees a block of a heap

extern const s32 data_020ded8c[2]; // start position of the link object (x, y in pixels)

extern const U32Table4 data_020ded94; // shift per player index: 0 0 4 8
extern const U32Table4 data_020deda4; // shift per player index: 0 0 4 8
extern const S32Table4 data_020dedb4; // 0 0 2 4
extern const U32Table4 data_020dedc4; // 6 7 8 9

// Sends a block of the screen data to the VBlank transfer queue (original subTaskSendScr(short, void*, unsigned long,
// unsigned long))
void subTaskSendScr(s16 index, void *data, u32 offset, u32 size);
extern "C" u32 addOamUiObj(void *oamBuffer, u32 size, void *obj);
extern "C" void subTask_init_bg3(int a, int b, int c);
void OpeningTaskPrepareFinalize(void);

// Received parameter of a player (nibble of the 0x474 word of the wireless block)
extern "C" s32 getReciveParam(s32 index);

#endif
