#include "engine/functions.h"

// KnifeApp::getZeldaResource (0x0208dde0): returns the data of a resource of the Zelda resource archives and stores its
// size. Ids from 0x1000 use the second archive (data_02171e18), the others the first one (data_02171e08). An archive is
// a table of (offset, size) entries at its start; the offsets are relative to the archive.

typedef struct ZeldaResourceEntry {
    u32 offset;
    u32 size;
} ZeldaResourceEntry;

extern u8 *data_02171e18; // second archive
extern u8 *data_02171e08; // first archive

void *KnifeApp_getZeldaResource_08dde0(void *app, s32 *size, s32 id) {
    u8 *base;
    u32 offset;

    if ((u32)id >= 0x1000) {
        base = data_02171e18;
        offset = ((ZeldaResourceEntry *)base)[id - 0x1000].offset;
        *size = ((ZeldaResourceEntry *)base)[id - 0x1000].size;
        return base + offset;
    }
    base = data_02171e08;
    offset = ((ZeldaResourceEntry *)base)[id].offset;
    *size = ((ZeldaResourceEntry *)base)[id].size;
    return base + offset;
}
