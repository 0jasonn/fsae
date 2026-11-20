#ifndef ACTOR_OBJECT_POT_H
#define ACTOR_OBJECT_POT_H

#include "engine/functions.h"
#include "engine/player.h"

#include "engine/map_state.h"

#define MAP_CELL_INDEX(x, y) \
    ((((x) - mapState.originX) >> 4) | ((((y) - mapState.originY) >> 4) << 6))

// The whole sprite settings word (Entity 0x1c), for single-bit updates
#define SPRITE_WORD(e) (*(u32 *)&(e)->spriteSettings)

// Pot fields that live past the shared Entity header (from 0x68)
typedef struct Vars_Pot {
    /* 00 */ u8 unk_00[0x68];
    /* 68 */ u16 savedCell; // BG cell value under the pot, written back when the pot leaves the cell
    /* 6a */ u8 savedCellState; // state byte of that cell, written back with savedCell
    /* 6c */ u8 unk_6c[2];
    /* 6e */ u16 objSize; // GX_GetSizeOfOBJ() taken when the pot is lifted
} Vars_Pot;

extern const u8 pot_hitbox[];         // hitbox of a pot (pot_hitbox)
extern const u8 pot_moveCheckTable[]; // table passed to func_02085890 with the target position (pot_moveCheckTable)
extern const s8 pot_dirOffsets[];     // (dx, dy) pairs for the four directions (pot_dirOffsets)
extern const u8 grass_hitbox[];       // hitbox of a grass throw (grass_hitbox)


void pot_clash(Entity *e, Entity *other);
void throw_holdoff(Entity *e); // 0x0205f0e0 (pot_4.cpp)
extern "C" u16 GX_GetSizeOfOBJ(void);
extern "C" void m4aMusicSetVolume(u16 a, u16 b); // 0x0208d944
void kanaamiRew(Entity *e, u16 index); // 0x0205e758 (set4e_2.cpp)
void set4e_move(Entity *e); // 0x0205e714 (set4e_2.cpp)
#include "engine/display_state.h"
void MultiEventSet(u16 *a, u8 b, u8 c, u8 d); // 0x0204602c, not yet in functions.h
void set5c_event_check(Entity *e);
void zelda_disp(Entity *e);
extern const EntityFunc data_020d9028[]; // set5c update state table indexed by e->action
extern const s16 trigTable[]; // sine table (trigTable)
#include "engine/effect_state.h"
#include "engine/em12_type_masks.h"
extern u16 data_0213492c[]; // per-area offset, read at [area * 2]
extern u16 em12_spawnOffsetY[]; // per-area offset, read at [area * 2]
int func_02083d4c(u16 a, u16 b); // thumb, cell state of the shutter
const u8 *GetInfoAdrs(u8 area, u8 kind);

#endif
