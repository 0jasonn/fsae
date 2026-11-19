#ifndef ENGINE_MAP_STATE_H
#define ENGINE_MAP_STATE_H

#include "types.h"

struct OBJ_WORK_;

// Map/scroll state (mapState, 0x34 bytes up to irqState; nothing reads or writes past +0x2b). It holds the entity the
// camera follows, the screen shake request, the world position of map cell 0 (a cell index is
// ((x - originX) >> 4) | (((y - originY) >> 4) << 6)), the BG scroll position and the map size.
// dsd also has the symbols data_0212c650 (+0x08), data_0212c65a (+0x12), data_0212c660 (+0x18, originX),
// data_0212c662 (+0x1a, originY) and data_0212c668 (+0x20, scrollX) inside this block.
typedef struct MapState {
    /* 00 */ struct OBJ_WORK_ *target; // entity the camera follows (the local player, or a scene's focus entity; em2a,
                                       // em2e, set55 and set6a set themselves and keep the previous one to restore)
    /* 04 */ u8 unk_04;     // cleared by scr_init
    /* 05 */ u8 yureMode;   // screen shake mode (YureSet: b & 3)
    /* 06 */ u8 scrollMode; // index into the scroll function table data_020d85b0 (ScrollMove); scr_init sets 1
    /* 07 */ u8 unk_07;
    /* 08 */ u8 unk_08;     // bg2StSet sets 0xc
    /* 09 */ u8 unk_09[0x12 - 0x09];
    /* 12 */ s16 unk_12;    // MultiRoomInit sets 0xe; read by AutoSet
    /* 14 */ s16 unk_14;    // cleared by MultiRoomInit
    /* 16 */ u16 yureValue; // screen shake strength (YureSet: a)
    /* 18 */ u16 originX;   // world x of map cell 0 (grid origin used by every cell lookup)
    /* 1a */ u16 originY;   // world y of map cell 0
    /* 1c */ s16 offsetX;   // added to the scroll position for the BG offset (MultiRoomInit clears it)
    /* 1e */ s16 offsetY;
    /* 20 */ s16 scrollX;   // BG scroll position (camera x)
    /* 22 */ s16 scrollY;   // BG scroll position (camera y), copied into BG vertical scroll by the scenes
    /* 24 */ s16 startX;    // scroll position set by ScrPosSet/MultiRoomInit along with scrollX
    /* 26 */ s16 startY;
    /* 28 */ u16 limitX;    // map width in pixels (right edge of the scroll area, 0x3f0 for a multi room)
    /* 2a */ u16 limitY;    // map height in pixels
    /* 2c */ u8 unk_2c[0x34 - 0x2c];
} MapState;
extern MapState mapState; // 0x0212c648

#endif
