#ifndef WIP_E_DATA_H
#define WIP_E_DATA_H

// Data and helpers shared by the E units (not in functions.h yet).
#include "engine/functions.h"

// Game state block (UnkStruct_0212c7c8 in engine/player.h): byte 0 is the player count, 0x24 a sound/telop flag.
extern u8 data_0212c7c8[];
// PlayerData[4], 0x94 bytes each. Field offsets: 0x03+4 flags, 0x28 entity pointer, 0x3c state byte.
extern u8 data_0212ceb0[];
// Per-type halfword flags (4 entries).
extern u16 data_0212c584[];
// Per-type health (current) and per-type maximum (in hearts) bytes.
extern u8 data_0212c828[];
extern u8 data_0212c82c[];
// Cockpit tables used by the item code.
extern u8 data_020cf81c[];
extern u32 *data_020f253c[];

// Background music and pinch warning check (cockpit module, defined in cockpit.cpp).
void pinch_bgm_check(void);

// Rupee counter block at data_0212c618 (cockpit side) and the per-type rupee value array.
extern u8 data_0212c618[];
extern s32 data_0212c7d4[];
// Heart alarm and pinch state (frame counter and state bytes).
extern u16 data_0212c594;
extern u8 frameCounter[];
// Current player entity pointer (cockpit), and the katti graphics tables.
extern u8 *data_0212c53c; // current player block (PlayerData-sized entries, read as bytes or as an entity pointer at 0x28)
extern u32 data_020f2530[];
extern u32 data_020f2524[];

// Adds delta to value and clamps to the limit (add_sub, defined in item_2.cpp).
s32 add_sub(s32 value, s32 delta, s32 limit);

// Absolute value (abs_s32, defined later in the E units).
s32 abs_s32(s32 value);

// Keys per type, kakera counts per type, kakera telop/effect block and the per-type kakera timers (u16).
extern u8 data_0212c824[];
extern u8 data_0212c830[];
extern u16 data_0212c63c[];
extern u8 telopRequest[];

#define GS_U8(off) (*(u8 *)(data_0212c7c8 + (off)))
#define GS_S32(off) (*(s32 *)(data_0212c7c8 + (off)))
#define RUPEE_U8(off) (*(u8 *)(data_0212c618 + (off)))
#define RUPEE_U16(off) (*(u16 *)(data_0212c618 + (off)))
#define RUPEE_S32(off) (*(s32 *)(data_0212c618 + (off)))

// Cockpit graphics and object blocks used by the HUD code.
extern u8 data_0212c75c[];
extern u8 data_021361a0[];
extern u8 data_0212c4a0[];
extern u8 data_021369a0[];
extern u16 data_020cf810[];

#define KAKERA_U32(off) (*(u32 *)(telopRequest + (off)))

#define PL_BYTE(i, off) (data_0212ceb0[(i) * 0x94 + (off)])
#define PL_ENTITY(i) (*(Entity **)(data_0212ceb0 + (i) * 0x94 + 0x28))

#endif
