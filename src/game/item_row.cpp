#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/item_row_api.h"

// Functions in this file (names given here; the ROM has no symbols for them):
//   ItemRow_layout -> ItemRow_layout (0x020b6cc4)

// One entry of the row: 8 bytes in the table at +0x34 of ItemRow
typedef struct ItemRowEntry {
    s16 minX;      // 0x00: candidate for the maximum of the row
    s16 width;     // 0x02: added to the running sum
    u8 unk_04[4];
} ItemRowEntry;

typedef struct ItemRow {
    u8 unk_00[0x20];
    s32 active;            // 0x20: layout only runs when this is nonzero
    s16 maxX;              // 0x24: largest minX of the entries
    s16 sumX;              // 0x26: running sum of the widths and gaps
    u8 unk_28[0x2e - 0x28];
    s16 gap;               // 0x2e: added between entries (not before the first)
    u8 unk_30[0x34 - 0x30];
    ItemRowEntry *entries; // 0x34
    u16 count;             // 0x38
} ItemRow;

// ItemRow_layout(self, arg, pos) (0x020b6cc4): copies pos and passes it to Pane_setOffset, then computes the largest
// minX and the total width of the entries with the gap between them
void ItemRow_layout(void *selfv, s32 arg, s16 *pos) {
    ItemRow *self = (ItemRow *)selfv;
    s16 copy[2];
    s32 i;

    if (self->active == 0) {
        return;
    }
    copy[0] = pos[0];
    copy[1] = pos[1];
    Pane_setOffset(self, arg, copy);
    self->maxX = 0;
    self->sumX = 0;
    for (i = 0; i < self->count; i++) {
        s16 candidate = self->entries[i].minX;
        s16 current = self->maxX;

        self->maxX = (current < candidate) ? candidate : current;
        if (i > 0) {
            self->sumX = self->sumX + self->gap;
        }
        self->sumX = self->sumX + self->entries[i].width;
    }
}
