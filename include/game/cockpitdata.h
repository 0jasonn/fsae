#ifndef WIP_E_DATA_H
#define WIP_E_DATA_H

// Data and helpers shared by the E units (not in functions.h yet).
#include "engine/functions.h"
#include "engine/player.h"

// Game state block (GameState in engine/player.h): byte 0 is the player count, 0x24 a sound/telop flag.
// PlayerData[4], 0x94 bytes each. Field offsets: 0x03+4 flags, 0x28 entity pointer, 0x3c state byte.
// Per-type halfword flags (4 entries).
extern u16 playerKeysPrev[];
// Per-type health (current) and per-type maximum (in hearts) bytes.
// Cockpit tables used by the item code.
extern u8 data_020cf81c[];
extern u32 *data_020f253c[];

// Background music and pinch warning check (cockpit module, defined in cockpit.cpp).
void pinch_bgm_check(void);

// Cockpit block (cockpitState) and the per-type rupee value array.
#include "engine/cockpit_state.h"
extern s32 data_0212c7d4[];
// Heart alarm and pinch state bytes.
#include "engine/frame_counter.h"
// Katti graphics tables.
extern u32 data_020f2530[];
extern u32 data_020f2524[];

// Adds delta to value and clamps to the limit (add_sub, defined in item_2.cpp).
s32 add_sub(s32 value, s32 delta, s32 limit);


// Keys per type, kakera counts per type and the kakera telop block (the per-type kakera timers are cockpitState.kakeraTimer).
#include "engine/telop_request.h"

// Cockpit graphics and object blocks used by the HUD code.
#include "engine/display_state.h"
#include "engine/hud_tile_obj.h"
extern u16 data_020cf810[];

#endif
