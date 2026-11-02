#ifndef WIP_A_FRAME_LOAD_H
#define WIP_A_FRAME_LOAD_H

// Declarations used by src/wip/A/frame_load.cpp (multiplayer frame / room setup).
#include "engine/functions.h"
#include "actor/enemy/demo_loader.h"

// Entry of the frame table returned by frame_select(): the frame record and a flag word for parts_set.
typedef struct FrameEntry {
    FRAME_INFO_ *frame;
    u32 flags;
} FrameEntry;

extern u16 data_0213492c[];   // area origin: [0] and [1] cleared, [2] and [3] hold the frame's start cell * 16
extern u16 data_021355a0;

// Part record returned by parts_select (first word of a frame table entry).
typedef struct PartRecord {
    u16 partId;           // 0x00
    u8 playerCount;       // 0x02: number of players the part is used for
    u8 unk_03;
    const u32 *infoRows;  // 0x04
} PartRecord;

// Entry of the part tables (data_02103d88[unk_01]): the part record and a flag word (bits 30..31: map level,
// bits 0..4 style mask).
typedef struct PartEntry {
    PartRecord *part;
    u32 flags;
} PartEntry;

extern u8 data_021349e8[];          // 0x40 byte order table walked by the part cursor
extern const u16 data_02103d48[];   // per game mode limit for the order table values
extern PartEntry *data_02103d88[];  // per game mode part table

u32 get_maplevel(void);
BOOL historyCheck(void *entry);
BOOL pasthistoryCheck(void *entry);
BOOL checkSingleErrorParts(u8 mode, u16 partId);

extern Entity *data_0212c648;      // entity of the local player
extern u8 localPlayerIndex;
extern u32 em12_typeMasks[];
extern const u8 data_02103e84[];    // 8 byte start layouts, indexed by the low nibble of game state byte 0x4f
extern u8 data_0212c84c[];          // copy of the 8 start slots

extern u32 data_0216f834[];   // 0x20 words, copied to data_0216f8b4
extern u32 data_0216f8b4[];
extern u16 data_0216f820[];   // [1] holds the part id of the part being set

extern "C" {
FrameEntry *frame_select(void);                             // 0x0204dcc4
void MPlayerInit(u8 player, u8 slotA, u8 slotB);               // 0x0204c87c
void MIi_CpuCopy16(const void *src, void *dst, u32 size);
PartRecord *parts_select(FRAME_INFO_ *frame, u32 flags);        // 0x0204d950
void PartsSet(u16 partId, u16 x, u16 y);                    // 0x020571fc
void takara_set(u8 *list, FRAME_INFO_ *frame, u8 flag);     // 0x0204d788
void parts_set(FRAME_INFO_ *frame, u32 flags);              // 0x0204db38
void FrameLoad_Select(void);                                // 0x0204df84
}
void GameState_SetTrackVariant(void);

#endif
