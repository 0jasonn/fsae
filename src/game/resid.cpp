#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (module resid, original names from the debug build): GetResTranslateID
// (GetResTranslateID(unsigned short, ResIDTranslate const*, long)). Kept under its plain name, because src/engine/vgroup.cpp
// declares it extern "C".

// One entry of a translation table: the id, then the value for game states 1..5
typedef struct ResIDTranslate {
    s16 id;
    u16 value[5];
} ResIDTranslate;

extern u8 data_0212c7c8[];

extern "C" u16 GetResTranslateID(u16 id, const ResIDTranslate *table, s32 count);

// GetResTranslateID (0x02029ab8): the value of the entry with id for the current game state (byte 0x8e of data_0212c7c8),
// or id itself when it is not in the table or the state is not 1..5.
ARM u16 GetResTranslateID(u16 id, const ResIDTranslate *table, s32 count) {
    const ResIDTranslate *entry;
    s32 i;
    u8 state;

    for (i = 0; i < count; i++) {
        entry = &table[i];
        if (id == entry->id) {
            state = data_0212c7c8[0x8e];
            if (state == 1) {
                return entry->value[0];
            }
            if (state == 2) {
                return entry->value[1];
            }
            if (state == 3) {
                return entry->value[2];
            }
            if (state == 4) {
                return entry->value[3];
            }
            if (state == 5) {
                return entry->value[4];
            }
            return id;
        }
    }
    return id;
}
