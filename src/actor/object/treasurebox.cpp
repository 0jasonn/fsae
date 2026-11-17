#include "engine/functions.h"
#include "actor/object/treasurebox.h"
#include "global.h"

// setupTreasureBox (0x02077368): shuffles the 12 chest slots (128 random swaps), picks two distinct random positions
// of the shuffled list for the special chests, and creates the 12 chest objects (two chests per work type slot).
void setupTreasureBox(void) {
    TreasureOrder order = data_020dc65c;
    int swap;
    for (swap = 0; swap < 0x80; swap++) {
        u32 first = Random() % 12;
        u32 second = Random() % 12;
        if (first != second) {
            u8 held = order.slot[first];
            order.slot[first] = order.slot[second];
            order.slot[second] = held;
        }
    }
    u32 special1 = Random() % 12;
    u32 special2;
    do {
        special2 = Random() % 12;
    } while (special1 == special2);
    u32 slot;
    for (slot = 0; slot < 12; slot++) {
        Entity *chest = GetSetWork(12, (u8)((s32)slot / 2), 1);
        if (chest != NULL) {
            u8 cell = order.slot[slot];
            chest->x.HALF.HI = data_020dc623[cell * 2] << 4;
            chest->y.HALF.HI = data_020dc623[cell * 2 + 1] << 4;
            chest->direction = 0xff;
            chest->layer = 0x4000;
            chest->areaIndex = 0;
            takaraAddEntry(chest, (slot == special1 || slot == special2) ? 8 : 4);
        }
    }
    em12_typeMasks[0] = 0;
}
