#ifndef GAME_FRAME_LOAD_H
#define GAME_FRAME_LOAD_H

// Multiplayer frame / room setup (frame_load, parts, history and the frame tables).
#include "engine/functions.h"
#include "actor/enemy/demo_loader.h"

// Entry of the frame tables (bgmIndexTable[unk_01], returned by frame_select()): the frame record and a flag word for
// parts_set.
typedef struct FrameEntry {
    /* 00 */ FRAME_INFO_ *frame; // frame->roomNo indexes the per-room tables (bgm variant, vgroups, cell lists, ...)
    /* 04 */ u32 flags;
} FrameEntry;

// Frame tables per game mode (gameState.unk_01): arrays of FrameEntry indexed by gameState.unk_48 (the current frame).
// The symbol keeps its old name bgmIndexTable (0x02103da4); a better name would be frameTables.
extern FrameEntry *const bgmIndexTable[8];
extern FrameEntry *const data_02103d68[];
extern const u16 data_02103d78[];

extern u16 data_0213492c[];   // area origin: [0] and [1] cleared, [2] and [3] hold the frame's start cell * 16
#include "engine/palette_buff.h"

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

extern u8 data_021349e8[0x40];      // 0x40 byte order table walked by the part cursor
extern const u16 data_02103d48[];   // per game mode limit for the order table values
extern PartEntry *data_02103d88[];  // per game mode part table

u8 get_maplevel(void);
int checkSingleErrorFrame(u8 frame, u16 value);
extern u8 data_02134a28[0x40];
BOOL historyCheck(void *entry);
BOOL pasthistoryCheck(void *entry);
BOOL checkSingleErrorParts(u8 mode, u16 partId);

#include "engine/map_state.h"
#include "engine/em12_type_masks.h"
extern const u8 data_02103e84[];    // 8 byte start layouts, indexed by the low nibble of game state byte 0x4f

extern u32 data_0216f834[];   // 0x20 words, copied to data_0216f8b4
extern u32 data_0216f8b4[];
#include "engine/floor_parts_state.h"

// original names with parameter lists (original_names.tsv): C++ linkage, so outside the extern "C" block
FrameEntry *frame_select(void);                             // 0x0204dcc4
PartRecord *parts_select(FRAME_INFO_ *frame, u32 flags);    // 0x0204d950
extern "C" {
void MPlayerInit(u8 player, u8 slotA, u8 slotB);               // 0x0204c87c
void takara_set(u8 *list, FRAME_INFO_ *frame, u8 flag);     // 0x0204d788
void parts_set(FRAME_INFO_ *frame, u32 flags);              // 0x0204db38
void FrameLoad_Select(void);                                // 0x0204df84
}
void GameState_SetTrackVariant(void);

#endif
