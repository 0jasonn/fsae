#ifndef WIP_C_SETSPAWN_H
#define WIP_C_SETSPAWN_H

#include "engine/entity.h"

// Original name of AssignObj(void *): C++ linkage (_Z9AssignObjPv). Returns 1 when the pointer lies in the object pool.
int AssignObj(void *obj);

// Spawn tables, used only by setspawn.cpp (renamed in scratch/agentC/renames.txt)
extern const u8 Set_SpawnChanceTable[];   // per table index: spawn chance, compared with Random() & 0xff
extern const u8 Set_Kind11Threshold[];   // per GameState.unk_01: threshold for the kind 0x11 record choice
extern const u8 Set_Kind12Threshold[];   // per GameState.unk_49[4]: threshold for the kind 0x12 record choice
extern const u8 Set_KindRecords[];   // 4-byte record per kind code (3 spawn bytes + pad)
extern const u8 Set_Record11Miss[];   // kind 0x11 record when Random() & 0x1f is at or above the threshold
extern const u8 Set_Record12Miss[];   // kind 0x12 record when Random() & 0x1f is at or above the threshold
extern const u8 Set_Record12Hit[];   // kind 0x12 record when the threshold is at or above the roll
extern const u8 Set_Record11Hit[];   // kind 0x11 record when the threshold is at or above the roll
extern const u8 *const *const *const Set_KindTables[]; // [table index][GameState.unk_01][type class] -> kind table

// Game state and shared spawn counter (declared in other files too)
extern u8 data_0212c4f4;           // spawn limit, children are not spawned while it is 0x70 or more
extern const u8 data_0212c81c[];   // indexed by target type

extern "C" {
void Set_TrySpawnChild(Entity *parent, u8 tableIndex, Entity *target); // 0x0207c408
}

#endif
