#ifndef ACTOR_ENEMY_ENCNT_H
#define ACTOR_ENEMY_ENCNT_H

#include "engine/player.h"

// One record per spawn slot (encntEntries).
typedef struct ENCNT_ { // original name ENCNT_
    u16 x;
    u16 y;
    u8 angle;
    u8 taken;                   // set when the slot is taken
    u8 initialised;             // set once the slot has been initialised
    u8 unk_07;
} EncntEntry;

// encntState is one object whose slot records start at +0x18 (the symbol encntEntries at 0x02134b60 is that sub-object).
// With the records inside the struct the compiler re-reads limit/kind after each store, as the original does
// (encnt_setinit, encnt_poscheck, encnt_setem).
// One encounter record (data_020f273c, 12 bytes); nextset copies the current one to encntState+0x5c.
typedef struct RecordEntry {
    u16 a;
    u16 b;
    u16 c;
    u16 d;
    u16 e;
    u8 f;
    u8 g;
} RecordEntry;
extern const RecordEntry data_020f273c[8];

// Encounter state (encntState, 0x68 bytes), used by the encnt_* functions at 0x02043760 and their helpers.
typedef struct EncntState {
    /* 00 */ u8 state;             // index into encntStateFuncs, advanced as each phase finishes
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
    /* 18 */ EncntEntry entries[8];
    /* 58 */ const RecordEntry *record; // current record; +0x5c..+0x67 hold a copy of it
    /* 5c */ u16 timerBase;        // record a: centre of the random timer set by nextset
    /* 5e */ u16 recB;
    /* 60 */ u16 recC;
    /* 62 */ u16 recD;
    /* 64 */ u16 recE;
    /* 66 */ u8 timerRange;        // record f: size of the random spread for timerBase
    /* 67 */ u8 recG;
} EncntState;
extern EncntState encntState;
extern void (*const encntStateFuncs[])(void);
extern EncntEntry encntEntries[];   // the same object as encntState.entries (0x02134b60)



#include "engine/obj_list.h"   // object list heads data_0212c6b0

// Fields that encnt_setem writes on the spawned entity (beyond the Entity common part).
typedef struct EncntSpawnVars {
    u8 unk_00[0x6c];
    u16 lifeTime;               // 0x4b0 on every spawn
    u8 unk_6e[2];
    u8 posA;                    // low byte of the first table halfword
    u8 posB;                    // low byte of the second table halfword
} EncntSpawnVars;
#define SPAWNV(e) VARS(EncntSpawnVars, e)

extern u8 encntSharedState[];
extern u8 encntSpawnCount;
#include "engine/data_0212c540.h"
extern u16 playerKeysPrev[4];

typedef struct AreaRect {
    u16 x;
    u16 y;
} AreaRect;
extern AreaRect data_0213492c[];
extern const u8 data_020f279c[];

typedef void (*EncntPosFunc)(EncntEntry *entry, u16 index);
extern const EncntPosFunc encntPosFuncs[];

extern const s16 trigTable[];       // direction table, 8 steps per direction, quarter-wave offset at +0x40
#include "engine/bg_buff.h"           // occupancy grids: data_02158fa0.attr, data_02163fa4.attr
extern const s16 cellDeltaTable[];       // four cell offsets for the neighbour test
extern const s8 data_020d4170[];        // step table, x and y per entry

#include "engine/map_state.h"

extern void (*const endingTasks[])(void);


void housha0(EncntEntry *e, u16 index);
void housha0att(EncntEntry *e, u16 index);
void nopos(EncntEntry *e, u16 index);
void plbackinit(EncntEntry *e, u16 index);
void plfrontinit(EncntEntry *e, u16 index);

#endif
