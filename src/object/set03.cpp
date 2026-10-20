#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/objdecls_f.h"

// Set03 actor (module set03). Address -> name:
//   0x0205b0bc Set03 (original name), dispatches on e->action through set03_actions
//   0x0205b0d8 set03_init (original name)
//   set03_wait, set03_move, set03_swoff: scratch/agentF/nonmatching/set03_wait.c, set03_move.c, set03_swoff.c

// data_0212c648 as read by set03_init: grid origin of the map cells.
typedef struct Set03GridOrigin {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 originX;
    /* 1a */ u16 originY;
} Set03GridOrigin;

typedef struct Vars_Set03 {
    /* 00 */ u8 unk_00[0x76];
    /* 76 */ u16 cellPlain;  // cell of the actor without the grid origin
    /* 78 */ u16 cellEvent;  // result of func_0208367c
    /* 7a */ u16 cellKind;   // result of func_02083ca8 for the cell
    /* 7c */ u16 cell;       // cell of the actor with the grid origin
    /* 7e */ u8 event;       // argument of func_0208365c
    /* 7f */ u8 countdown;   // turns down while the switch is off
} Vars_Set03;

extern const EntityFunc set03_actions[]; // set03_actions, indexed by e->action
extern const u8 data_020d8a5c[];          // hitbox of the switch
extern const u32 flagBits[];             // flagBits, indexed by e->type
extern u32 em12_typeMasks[];
extern Set03GridOrigin data_0212c648;

// Cell of player k (its entity, 3 pixels below the feet).
#define SET03_PLAYER_CELL(k) ((((data_0212ceb0[k].entity->y.HALF.HI + 3) >> 4) << 6) | (data_0212ceb0[k].entity->x.HALF.HI >> 4))

// Clears the player bit when that player is busy (statusFlags & 0x90) or stands on another cell than the actor.
#define SET03_PRUNE_PLAYER(k, bit, keep)                                                        if ((flags & (bit)) != 0) {                                                                     if ((data_0212ceb0[k].statusFlags & 0x90) != 0 ||                                               VARS(Vars_Set03, e)->cellPlain != SET03_PLAYER_CELL(k)) {                                   flags &= (keep);                                                                        }                                                                                       }

ARM void Set03(Entity *e) {
    set03_actions[e->action](e);
}

ARM void set03_init(Entity *e) {
    e->action++;
    e->statusFlags = 0;
    e->hitbox = data_020d8a5c;
    VARS(Vars_Set03, e)->cell = ((e->x.HALF.HI - data_0212c648.originX) >> 4) | (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6);
    VARS(Vars_Set03, e)->cellKind = func_02083ca8(VARS(Vars_Set03, e)->cell, e->layer);
    VARS(Vars_Set03, e)->cellPlain = (e->x.HALF.HI >> 4) | (((e->y.HALF.HI) >> 4) << 6);
}
