#ifndef WIP_A_DECLS_H
#define WIP_A_DECLS_H

// Callees and data used by the implementer A files (src/wip/A/) that engine/functions.h does not declare yet.
// The reviewer moves the ones with an original name into functions.h.
#include "engine/functions.h"

// Grid origin used to turn a world position into a map cell (data_0212c648, bss). Its u16 pair sits at 0x18 / 0x1a.
typedef struct GridOrigin {
    u8 unk_00[0x18];
    u16 originX; // 0x18
    u16 originY; // 0x1a
} GridOrigin;
extern GridOrigin data_0212c648;

extern u8 data_021180a8[];
extern u8 data_0211857c[];

// Thumb labels without an original name (dsd names kept).
extern "C" int func_020899bc(u16 value, const u8 *table);
extern "C" void func_02086168(Entity *e);
extern "C" void func_020841b0(Entity *e);
extern "C" int func_02089e28(Entity *e, int kind);

// Callees with a mangled original name (C++ linkage).
int func_02083cdc(Entity *e);
int func_02085890(Entity *e, const u8 *table, u16 x, u16 y);
void PlWeaponFireCheck(Entity *e); // original PlWeaponFireCheck(OBJ_WORK_*)

// Unmangled original name.
extern "C" void EffectSet(Entity *e, int kind, int arg);

// Map cell helpers (src/wip/A/map_2.cpp uses them; PuyoAnkyo and RewCellOne are defined in src/game/map.cpp, RewCellOne in src/wip/E).
void RewCellOne(u16 cell, u16 x, u16 y);
void PuyoAnkyo(u16 x, u16 y);

// Game state block (UnkStruct_0212c7c8 in engine/player.h): byte 1 is the mode, byte 0x48 an index.
extern u8 data_0212c7c8[];

// One 8-byte entry of the per-mode tables at bgmIndexTable: the first word points at a byte table (+1 is tested).
typedef struct RewCellEntry {
    u8 *bits;
    u32 unk_04;
} RewCellEntry;
extern RewCellEntry *bgmIndexTable[];

// RewCellBack (unmangled original name) and the map tables it reads.
extern "C" void RewCellBack(int cell, int layer);
extern u8 *data_02171e0c;     // pointer to a byte table indexed by a tile value
extern u16 data_02140fa0[];
extern u16 data_02148fa0[];
extern u8 data_021348f4[];
extern u8 data_0212c4c8[];

// Door and map-block helpers (src/wip/A/frontcheck_2.cpp).
void setmoveblock(Entity *e, u16 cell, u8 mode); // original setmoveblock(OBJ_WORK_*, unsigned short, unsigned char)
extern s16 data_020cd6e4[];                      // x / y offset pairs indexed by (type2 & 3)

// Background buffer (original BG_BUFF_*, only used through pointers here).
struct BG_BUFF_;
typedef struct BG_BUFF_ BG_BUFF_;

// Cockpit block and player blocks (PlayerData[4], 0x94 bytes each; entity pointer at 0x28).
extern u8 data_0212c618[];
extern u8 data_0212ceb0[];
extern u8 data_0212c82c[];
extern u8 *data_0212c53c; // current player block

#endif
