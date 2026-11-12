#ifndef ACTOR_OBJECT_SET53_MOVE3_H
#define ACTOR_OBJECT_SET53_MOVE3_H

#include "engine/functions.h"
#include "engine/player.h"
#include "engine/a_decls.h"

// set53 (the rowing boat): fields of the hull. Its child (0x58) is the seat, whose riders sit at 0x64 and 0x68.
typedef struct Vars_Set53Hull {
    /* 00 */ u8 unk_00[0x6c];
    /* 6c */ u32 speed;          // 8.8 pixels per frame, capped at 0x200 by the rowing, slowed by 0x20 per frame
    /* 70 */ u16 savedX;         // position before the last drift
    /* 72 */ u16 savedY;
    /* 74 */ u16 cell;           // cell under the hull; bit 0x4000: a cell to restore when the hull leaves it
    /* 76 */ u8 unk_76[2];
    /* 78 */ u8 savedDirection;  // animation state before the last drift
    /* 79 */ u8 unk_79[3];
    /* 7c */ u32 distance;       // distance rowed since the last rowing sound
} Vars_Set53Hull;

// The seat object riding on the hull
typedef struct Vars_Set53Seat {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *rider0;
    /* 68 */ Entity *rider1;
} Vars_Set53Seat;

extern const s8 data_020db854[];  // (dx, dy) of the cell in front, per animation state
extern const u8 data_020db85c[];  // hitbox while moving diagonally or sideways
extern const u8 data_020db864[];  // hitbox while moving straight up or down

extern "C" {
void FormationBreak(void);
}

// C++ linkage (thumb labels and original names)
void func_02085e08(Entity *e, Entity *player);
int func_02083ccc(Entity *e, s16 x, s16 y);
void set53_nop(Entity *e);

#endif
