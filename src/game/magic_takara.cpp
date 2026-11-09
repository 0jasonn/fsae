#include "engine/functions.h"
#include "global.h"
#include "game/takara.h"
#include "game/magic_takara.h"

extern TakaraEntry data_02134c30[32];

// Picks one entry of the given kind (handler index 7 in the low 5 bits) at random and marks it with the takara state:
// the picked entry keeps its kind and gets flags 0x10, every other matching entry changes to handler index 1.
void magic_takara(u8 kind) {
    u8 handler;
    TakaraEntry *entry;
    u32 count;
    int pick;
    u8 key;
    u8 i;

    key = kind << 5;
    entry = data_02134c30;
    count = i = 0;
    for (; i < 0x20; i++) {
        handler = entry->handlerIndex;
        if ((handler & 0xe0) == key && (handler & 0x1f) == 7) {
            count++;
        }
        entry++;
    }
    pick = Random() % count;
    entry = data_02134c30;
    for (i = 0; i < 0x20; i++) {
        handler = entry->handlerIndex;
        if ((handler & 0xe0) == key && (handler & 0x1f) == 7) {
            if (0 == pick) {
                entry->handlerIndex = handler & 0xe0;
                entry->flags = 0x10;
            } else {
                entry->handlerIndex = (handler & 0xe0) | 1;
            }
            pick--;
        }
        entry++;
    }
}
