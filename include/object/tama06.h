#ifndef WIP_C_TAMA06_H
#define WIP_C_TAMA06_H

// Declarations for the Tama06 actor family (src/wip/C/tama06.cpp).
#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"

extern const EntityFunc data_020dce2c[]; // Tama06 state table, indexed by e->type
extern u16 frameCounter; // frame counter used to pick the item of the next type
extern const EntityFunc data_020dce94[]; // Tama06 type0 action table, indexed by e->action
extern const u8 data_020dce1c[]; // hitbox of the Tama06 pieces

// The pieces made by tama06_init: the second and third piece point at the first one.
typedef struct Vars_Tama06Piece {
    /* 00 */ u8 unk_00[0x74];
    /* 74 */ Entity *linkedPiece;
} Vars_Tama06Piece;

// Position record of tama06_move: the target copied from the parent's x/y.
typedef struct Vars_Tama06Move {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ s16 targetX;
    /* 7a */ s16 targetY;
} Vars_Tama06Move;

void tama06_type1_move(Entity *e);
void tama06_type2_move(Entity *e);
void type0PosSet(Entity *e); // original name type0PosSet(OBJ_WORK_*), defined later in this family
void type0AttackPosSet(Entity *e);
void type0PosSetR(Entity *e, u8 a); // original name type0PosSetR(OBJ_WORK_*, unsigned char)
void type0WaitPosSet(Entity *e); // original name type0WaitPosSet(OBJ_WORK_*) // original name type0AttackPosSet(OBJ_WORK_*), defined later in this family

extern const s8 data_020dce24[];
extern const s8 data_020dce54[]; // scale per direction for the type0 position helpers
extern const s16 trigTable[]; // sine/cosine table, 0x40 entries apart (symbols.txt trigTable)
extern const s8 data_020dce0c[]; // (x, y) offsets for type0WaitPosSet, indexed by 2 * animationState
extern const EntityFunc data_020dce04[]; // Tama06 type1 action table, indexed by e->action
extern const EntityFunc data_020dce14[]; // Tama06 type2 action table, indexed by e->action
extern const s8 data_020dce3c[]; // (x, y) offsets for the type 1 pieces while the parent is in action 4
extern const s8 data_020dce74[]; // (x, y) offsets for the type 1 pieces by frame and animation

#endif
