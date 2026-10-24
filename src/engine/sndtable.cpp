#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names): the sound table of 0x24-byte records at data_0218431c (halfword at +0),
// data_02184320 (word at +4) and data_02184324 (byte at +8).
//   SndTable_SetByte8 (SndTable_SetByte8), SndTable_SetHalf0 (SndTable_SetHalf0), SndTable_SetWord4 (SndTable_SetWord4)

extern u8 data_0218431c[];
extern u8 data_02184320[];
extern u8 data_02184324[];

// SndTable_SetByte8 (0x020bf7c8): sets the byte at +8 of the record of the index.
extern "C" void SndTable_SetByte8(s32 index, u8 value);
ARM void SndTable_SetByte8(s32 index, u8 value) {
    data_02184324[index * 0x24] = value;
}

// SndTable_SetHalf0 (0x020bf7e0): sets the halfword at +0 of the record of the index (stored as a word).
extern "C" void SndTable_SetHalf0(s32 index, u32 value);
ARM void SndTable_SetHalf0(s32 index, u32 value) {
    *(u32 *)(data_0218431c + index * 0x24) = (u16)value;
}

// SndTable_SetWord4 (0x020bf800): sets the word at +4 of the record of the index.
extern "C" void SndTable_SetWord4(s32 index, s32 value);
ARM void SndTable_SetWord4(s32 index, s32 value) {
    *(s32 *)(data_02184320 + index * 0x24) = value;
}
