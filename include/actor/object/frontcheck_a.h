#ifndef WIP_A_FRONTCHECK_A_H
#define WIP_A_FRONTCHECK_A_H

#include "engine/functions.h"
#include "engine/player.h"

// Map scroll position (first fields of mapState at 0x0212c648)
typedef struct MapScroll {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 scrollX;
    /* 1a */ u16 scrollY;
} MapScroll;
extern MapScroll mapState;

typedef struct DirDelta {
    s16 x;
    s16 y;
} DirDelta;

extern const DirDelta data_020cd6c4[];  // pixel offset in front of an actor per direction
extern const s16 cellDeltaTable[];      // cell index step per direction (up, right, down, left)
extern const u16 data_020cd6b0[];       // map words written when a pushed block starts to slide
extern u16 data_0212c510;
extern u8 data_0212ceca[]; // playerWork[0].unk_1a, stride 0x94

// Bit view of PlayerData::paletteBits (0x8b): a = bits 0..1, b = bits 2..3 (palette index), c = bits 4..6, d = bit 7.
typedef struct PalBits {
    u8 a : 2;
    u8 b : 2;
    u8 c : 3;
    u8 d : 1;
} PalBits;

extern "C" {
BOOL TryUsingKey(Entity *e);
void openDoor(Entity *e, PlayerData *player, int bgBuffer);
int FrontCheck(Entity *e, PlayerData *player);
}
u16 func_02083e54(int kind);                                      // class of a cell kind (thumb)
void SetMoveBlockByKind(Entity *e, u8 a, s32 kind, u16 cell);     // 0x0202357c
void TakaraOpen(Entity *e, u16 cell, u16 layer);                  // 0x0207bd00

#endif
