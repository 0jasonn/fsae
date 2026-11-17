#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/fumi_api.h"
#include "actor/object/cellcalls.h"

typedef struct Vars_Set03Move {
    /* 00 */ u8 unk_00[0x76];
    /* 76 */ u16 cellPlain; // cell of the switch without the grid origin
    /* 78 */ u16 cellEvent; // result of func_0208367c
    /* 7a */ u16 cellKind;  // GetCellKind of the cell when the switch was placed
    /* 7c */ u16 cell;      // cell of the switch with the grid origin
    /* 7e */ u8 event;      // result of func_02083d4c
    /* 7f */ u8 countdown;  // turns down while the switch is off
} Vars_Set03Move;

extern const u32 flagBits[]; // area flag bit per type
extern u32 em12_typeMasks[]; // one mask per area

// Cell of player k (its entity, 3 pixels below the feet).
#define SET03_PLAYER_CELL(k) ((playerWork[k].entity->x.HALF.HI >> 4) | (((playerWork[k].entity->y.HALF.HI + 3) >> 4) << 6))

// Clears the player bit when that player is busy (statusFlags & 0x90) or stands on another cell than the switch.
#define SET03_PRUNE_PLAYER(k, bit, keep) \
    if ((flags & (bit)) != 0) { \
        if ((pl[k].statusFlags & 0x90) != 0 || VARS(Vars_Set03Move, e)->cellPlain != SET03_PLAYER_CELL(k)) { \
            flags &= (keep); \
        } \
    }

// set03_wait (0x0205b15c): waits for a player on the switch (fumiCheck bit per player), ignoring busy players
// (statusFlags & 0x90) and players standing on another cell. Once pressed it sets the type's area flag, plays
// sound 0x12 and rewrites the cell: type2 0 uses the permanent pressed tile 0x14b and removes the object, others
// 0x149 with action 2 (and type2 as countdown unless it is 1). A recorded event cell is then re-applied.
void set03_wait(Entity *e) {
    int flags = fumiCheck(e);
    PlayerData *pl;
    if (flags == 0) {
        return;
    }
    pl = playerWork;
    SET03_PRUNE_PLAYER(0, 1, 254)
    SET03_PRUNE_PLAYER(1, 2, 253)
    SET03_PRUNE_PLAYER(2, 4, 251)
    SET03_PRUNE_PLAYER(3, 8, 247)
    if (flags == 0) {
        return;
    }
    em12_typeMasks[e->areaIndex] |= flagBits[e->type];
    func_02085f98(e, 0x12);
    if (e->type2 != 0) {
        e->action = 2;
        RewCell(0x149, VARS(Vars_Set03Move, e)->cell, e->layer);
        if (e->type2 != 1) {
            VARS(Vars_Set03Move, e)->countdown = e->type2;
        }
    } else {
        RewCell(0x14b, VARS(Vars_Set03Move, e)->cell, e->layer);
        PutObjWork(e);
    }
    if (VARS(Vars_Set03Move, e)->cellEvent == 0xffff) {
        return;
    }
    func_0208366c(VARS(Vars_Set03Move, e)->cellEvent, VARS(Vars_Set03Move, e)->cell, e->layer);
    func_0208365c(VARS(Vars_Set03Move, e)->event, VARS(Vars_Set03Move, e)->cell, e->layer);
}

// set03_move (0x0205b348): the switch stays pressed while a pressing player (fumiCheck2 bit per player) stands on it
// and is not busy; once nobody does, it goes to action 3.
void set03_move(Entity *e) {
    int flags = fumiCheck2(e);
    PlayerData *pl = playerWork;
    SET03_PRUNE_PLAYER(0, 1, 254)
    SET03_PRUNE_PLAYER(1, 2, 253)
    SET03_PRUNE_PLAYER(2, 4, 251)
    SET03_PRUNE_PLAYER(3, 8, 247)
    if (flags == 0) {
        e->action = 3;
    }
}

// set03_swoff (0x0205b480): checks the cell of the switch. While it still shows the pressed/off tiles (0x149, 0x148
// or the original kind) the switch turns off: at once for type2 1, else after countdown turns. Otherwise it was
// changed from outside and goes to action 2. Turning off clears the type's area flag and rewrites the cell.
void set03_swoff(Entity *e) {
    int cell = GetCellKind(VARS(Vars_Set03Move, e)->cell, e->layer);
    if (cell != 0x149 && cell != 0x148 && cell != VARS(Vars_Set03Move, e)->cellKind) {
        e->action = 2;
        VARS(Vars_Set03Move, e)->cellEvent = func_0208367c(VARS(Vars_Set03Move, e)->cell, e->layer);
        VARS(Vars_Set03Move, e)->event = func_02083d4c(VARS(Vars_Set03Move, e)->cell, e->layer);
        return;
    }
    if (e->type2 != 1) {
        VARS(Vars_Set03Move, e)->countdown--;
        if (VARS(Vars_Set03Move, e)->countdown == 0) {
            e->action = 1;
        }
    } else {
        e->action = 1;
    }
    if (e->type2 != 1) {
        if (VARS(Vars_Set03Move, e)->countdown != 0) {
            return;
        }
        em12_typeMasks[e->areaIndex] &= ~flagBits[e->type];
        RewCell(0x148, VARS(Vars_Set03Move, e)->cell, e->layer);
        func_02085f98(e, 0x148 + 0xf1);
    } else {
        em12_typeMasks[e->areaIndex] &= ~flagBits[e->type];
        RewCell(0x148, VARS(Vars_Set03Move, e)->cell, e->layer);
        func_02085f98(e, 0x148 + 0xf1);
    }
}
