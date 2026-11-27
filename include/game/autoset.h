#ifndef GAME_AUTOSET_H
#define GAME_AUTOSET_H

#include "types.h"

// Auto-placed objects (AutoSet, 0x02023940): each table lists the map cell kinds that spawn an object when the room is
// built. A cellKind of 0xffff ends a table.
typedef struct AutoSetEntry {
    /* 00 */ u16 cellKind;  // cell kind that spawns the object
    /* 02 */ u16 objKind;
    /* 04 */ u16 objId;
    /* 06 */ u16 typeWord;  // low byte: type, high byte: type2
} AutoSetEntry;

extern const AutoSetEntry data_020cd744[]; // cells of the first layer (GetCellKind key 0x8000)
extern const AutoSetEntry data_020cd798[]; // cells of the second layer (key 0x4000)
extern const u8 data_020d7c60[];           // object work list of each object kind (also used by objwork.cpp)

#endif
