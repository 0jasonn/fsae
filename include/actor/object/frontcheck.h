#ifndef ACTOR_OBJECT_FRONTCHECK_H
#define ACTOR_OBJECT_FRONTCHECK_H

#include "engine/functions.h"
#include "engine/player.h"

#include "engine/map_state.h"
#include "engine/bg_buff.h"

typedef struct DirDelta {
    s16 x;
    s16 y;
} DirDelta;

extern const DirDelta data_020cd6c4[];  // pixel offset in front of an actor per direction
extern const s16 cellDeltaTable[];      // cell index step per direction (up, right, down, left)
extern const u16 data_020cd6b0[];       // map words written when a pushed block starts to slide
extern u16 data_0212c510;

extern "C" {
BOOL TryUsingKey(Entity *e);
int FrontCheck(Entity *e, PlayerData *player);
}
void SetMoveBlockByKind(Entity *e, u8 a, s32 kind, u16 cell);     // 0x0202357c
void TakaraOpen(Entity *e, u16 cell, u16 layer);                  // 0x0207bd00

// openDoor (0x0202375c, src/game/opendoor.cpp) has C++ linkage, as in the original openDoor(OBJ_WORK_*, PL_WORK_*, BG_BUFF_*).
void openDoor(Entity *e, PlayerData *player, BG_BUFF_ *bg);

#endif
