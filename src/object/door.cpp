#include "engine/functions.h"
#include "global.h"

// Door helpers (module door). Address -> name:
//   0x02061dc4 DoorTypeCheck, 0x02061e04 doorCheck (original names)

typedef struct Vars_Door {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 cell; // cell index of the door
    /* 7a */ u8 unk_7a[2];
    /* 7c */ u16 foundCell; // cell found by srchDoor, 0xffff when none
    /* 7e */ u16 flags; // bit 0: door type check, bit 1: set by doorCheck when func_02083cdc returns 0x5c
} Vars_Door;

typedef struct SrchEntry {
    u16 first;
    u16 second;
    u16 third;
    u16 fourth;
} SrchEntry;

extern const s16 cellDeltaTable[]; // cell step per kind (x 4 kinds)
extern const SrchEntry data_020d9324[]; // cells to look for, per kind
extern const u8 data_02165fa8[]; // terrain type per cell

int func_02083cdc(Entity *e);

ARM BOOL DoorTypeCheck(Entity *e) {
    s16 offset;

    offset = cellDeltaTable[e->type2 & 3];
    return data_02165fa8[(u16)(VARS(Vars_Door, e)->cell + offset)] != 0x18;
}

ARM void doorCheck(Entity *e) {
    VARS(Vars_Door, e)->flags = VARS(Vars_Door, e)->flags | DoorTypeCheck(e);
    if (e->type2 & 4) {
        return;
    }
    if (func_02083cdc(e) == 0x5c) {
        VARS(Vars_Door, e)->flags = VARS(Vars_Door, e)->flags | 2;
    }
}
