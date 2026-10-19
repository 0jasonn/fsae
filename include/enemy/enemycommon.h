#ifndef WIP_B_ENEMY_B_H
#define WIP_B_ENEMY_B_H

// Declarations for the enemy init helpers of implementer B (0x020458f8 onwards).

#include "engine/functions.h"

// Enemy init table (enemyInitTable): one 16-byte row per objId, eight u16 fields per row.
//   row[0] 0xffff marks an indirect row, row[1] then selects a row array in enemyInitIndirect.
//   row[0] == 0 ends the row; bit 15 of row[0] / row[1] selects the field layout.
extern const u16 enemyInitTable[];
// Row arrays (enemyInitIndirect), indexed by row[1] of an indirect row; each row is indexed by e->type.
extern const u16 *const enemyInitIndirect[];

extern u16 data_0212c540[];                                 // flag words read by EmDie

// Magnet-style move of an enemy towards the players in range; returns the number of candidate directions
u8 EmMagneMove(Entity *e, u16 a);

// Hit/position test used by EmDivPosSet (dsd name func_02083d18, thumb)
int func_02083d18(Entity *e, int a, int b);

// Data and helpers used by the enemy registration code
extern const u8 data_020d41b0[];                 // boss drop table, 4 bytes per row
extern u8 data_021348e8;                         // registered item count, see ItemRegist
extern u8 data_02134934[];                       // registered item ids
extern u8 data_021348f8[];                       // 4-entry table written by MultiEventSet

typedef struct ParseTypeTable {
    u32 bits[8];
} ParseTypeTable;
extern const ParseTypeTable data_020d42b4;       // copied to the stack by ParseTypeBits

s32 RegistStopBlock(u16 *list, u8 a);
void *func_02025d2c(u8 item);

// Native init lists (rodata) used by the fade_native_init functions
extern const u8 nativeInitListE[];   // nativeInitListE
extern const u8 nativeInitListB[];   // nativeInitListB
extern const u8 nativeInitListD[];   // nativeInitListD
extern const u8 nativeInitListA[];   // nativeInitListA
extern const u8 nativeInitListC[];   // nativeInitListC
extern const u8 data_020f3a8e[];
extern const u8 data_020f3a91[];
extern const u8 data_020f3a94[];
extern const u8 data_020f3a99[];
extern const u8 data_020f3a9e[];

// Spawns a child actor of e at the given position offsets (dsd name ObjPosCopyOfs32)
void ObjPosCopyOfs32(Entity *child, Entity *e, int a, int b);

#endif
