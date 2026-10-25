#include "engine/functions.h"
#include "global.h"

// Treasure chest table (module takara), 32 entries: id (cell key), handler index (low 5 bits) and flags.
typedef struct TakaraEntry {
    u16 id;          // 00, 0xffff marks a free entry
    u8 handlerIndex; // 02, low 5 bits index data_02116800
    u8 flags;        // 03, 1 once the entry is in use
} TakaraEntry;

// Map grid origin (data_0212c648): the position of cell 0 in world units
typedef struct MapGridOrigin {
    u8 unk_00[0x18];
    u16 originX; // 18
    u16 originY; // 1a
} MapGridOrigin;

extern TakaraEntry data_02134c30[32];
extern MapGridOrigin data_0212c648;

// Registers e in the first free treasure entry, keyed by its cell (row in bits 6 and up, column below). Returns nothing.
// Address 0x020772f0, original name unknown.
extern "C" void takaraAddEntry(Entity *e, u8 handlerIndex);
ARM void takaraAddEntry(Entity *e, u8 handlerIndex) {
    TakaraEntry *entry;
    int i;

    entry = data_02134c30;
    for (i = 0; i < 32; i++) {
        if (entry->id == 0xffff) {
            entry->id = ((e->x.HALF.HI - data_0212c648.originX) >> 4) | (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6);
            entry->handlerIndex = handlerIndex;
            entry->flags = 1;
            return;
        }
        entry++;
    }
}
