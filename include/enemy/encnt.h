#ifndef WIP_B_ENCNT_H
#define WIP_B_ENCNT_H

#include "engine/player.h"

// Encounter state (data_02134b48), used by the encnt_* functions at 0x02043760 and their helpers.
typedef struct EncntState {
    /* 00 */ u8 count;             // number of spawn slots filled so far
    /* 01 */ u8 kind;              // bits 12-15 of the table entry
    /* 02 */ u8 unk_02[2];
    /* 04 */ u8 posA;              // low byte of the first table halfword
    /* 05 */ u8 posB;              // low byte of the second table halfword
    /* 06 */ u8 limit;             // bits 8-10 of the second table halfword
    /* 07 */ u8 timerReload;       // 3 or 4, copied to timer
    /* 08 */ u16 timer;
    /* 0a */ u8 unk_0a[6];
    /* 10 */ Entity *entity;       // player entity picked by encnt_move
    /* 14 */ const u16 *table;     // pair table indexed by slot
    /* 18 */ u8 unk_18[0x44];
    /* 5c */ u16 timerBase;        // centre of the random timer set by nextset
    /* 5e */ u8 unk_5e[8];
    /* 66 */ u8 timerRange;        // size of the random spread for timerBase
} EncntState;
extern EncntState data_02134b48;

// One record per spawn slot (data_02134b60).
typedef struct ENCNT_ { // original name ENCNT_
    u16 x;
    u16 y;
    u8 angle;
    u8 unk_05;                  // set when the slot is taken
    u8 unk_06;                  // set once the slot has been initialised
    u8 unk_07;
} EncntEntry;
extern EncntEntry data_02134b60[];

// Node of the circular lists in data_0212c6b0: next at +4, tag and subtag at +8 and +9 (Entity unk_08/unk_09).
typedef struct EncntNode {
    u8 unk_00[4];
    struct EncntNode *next;
    u8 tag;
    u8 subtag;
} EncntNode;

typedef struct EncntListHead {  // 8-byte head; the list runs through next
    u8 unk_00[4];
    EncntNode *next;
} EncntListHead;
extern EncntListHead data_0212c6b0[];
extern EncntListHead data_0212c6f0[];

// Fields that encnt_setem writes on the spawned entity (beyond the Entity common part).
typedef struct EncntSpawnVars {
    u8 unk_00[0x6c];
    u16 unk_6c;                 // 0x4b0 on every spawn
    u8 unk_6e[2];
    u8 unk_70;                  // posA
    u8 unk_71;                  // posB
} EncntSpawnVars;
#define SPAWNV(e) VARS(EncntSpawnVars, e)

extern u8 data_021348ec[];
extern u8 data_021348e0;
extern u16 data_0212c540;
extern u16 data_0212c584[4];

typedef struct AreaRect {
    u16 x;
    u16 y;
} AreaRect;
extern AreaRect data_0213492c[];
extern const u8 data_020f279c[];

typedef void (*EncntPosFunc)(EncntEntry *entry, u16 index);
extern const EncntPosFunc data_020d4150[];

extern const s16 data_020d7e58[];       // direction table, 8 steps per direction, quarter-wave offset at +0x40
extern const u8 data_0215afa4[];        // 64x64 occupancy grid
extern const u8 data_02165fa8[];        // second 64x64 grid
extern u8 data_02158fa0[];              // neighbour grid, read at cell + offset + 0x2004
extern u8 data_02163fa4[];              // neighbour grid, same layout
extern const s16 data_020cf91c[];       // four cell offsets for the neighbour test
extern const s8 data_020d4170[];        // step table, x and y per entry

typedef struct GridOrigin {
    u8 unk_00[0x18];
    u16 x;                              // +18
    u16 y;                              // +1a
} GridOrigin;
extern GridOrigin data_0212c648;

extern u8 data_0212c500;
extern void (*const data_020f29fc[])(void);


void housha0(EncntEntry *e, u16 index);
void housha0att(EncntEntry *e, u16 index);
void nopos(EncntEntry *e, u16 index);
void plbackinit(EncntEntry *e, u16 index);
void plfrontinit(EncntEntry *e, u16 index);

#endif
