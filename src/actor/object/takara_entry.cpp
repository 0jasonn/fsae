#include "engine/functions.h"
#include "global.h"
#include "game/takara.h"

// Map grid origin (mapState): the position of cell 0 in world units
typedef struct MapGridOrigin {
    u8 unk_00[0x18];
    u16 originX; // 18
    u16 originY; // 1a
} MapGridOrigin;

extern TakaraEntry data_02134c30[32];
extern MapGridOrigin mapState;

// Registers e in the first free treasure entry, keyed by its cell (row in bits 6 and up, column below). Returns nothing.
// Address 0x020772f0, original name unknown.
extern "C" void takaraAddEntry(Entity *e, u8 handlerIndex);
void takaraAddEntry(Entity *e, u8 handlerIndex) {
    TakaraEntry *entry;
    int i;

    entry = data_02134c30;
    for (i = 0; i < 32; i++) {
        if (entry->id == 0xffff) {
            entry->id = ((e->x.HALF.HI - mapState.originX) >> 4) | (((e->y.HALF.HI - mapState.originY) >> 4) << 6);
            entry->handlerIndex = handlerIndex;
            entry->flags = 1;
            return;
        }
        entry++;
    }
}
