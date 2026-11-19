#include "engine/functions.h"
#include "ui/msgwin_decls.h"
#include "global.h"

// deleteWindow (0x0204a778): clears the tile rows of the current telop slot from its first row down, and the tile
// rectangle of the message slot, then asks for a map refresh.
void deleteWindow(void) {
    int col;
    u16 *tiles;
    int row;
    u8 slotIndex = cockpitState.bufferIndex;
    WindowSlot *slot = &data_0216f010[slotIndex];
    if (slot->active != 0) {
        slot->active = 0;
        int firstRow = slot->tileY;
        tiles = (u16 *)(data_021361a0[slotIndex] + firstRow * 0x40);
        row = 0x18 - firstRow;
        do {
            for (col = 0; col < 0x18; col++) {
                tiles[col] = 0;
            }
            tiles += 0x20;
            row--;
        } while (row > 0);
        func_02026774();
    }
    slotIndex = cockpitState.bufferIndex;
    slot = &data_0216eff0[slotIndex];
    if (slot->active != 0) {
        slot->active = 0;
        tiles = (u16 *)(data_021361a0[slotIndex] + ((slot->tileX + slot->tileY * 0x20) << 1));
        row = slot->height + 2;
        do {
            for (col = 0; col < slot->width + 2; col++) {
                tiles[col] = 0;
            }
            tiles += 0x20;
            row--;
        } while (row > 0);
        CockpitRecovery(slot->tileY, slot->height);
        func_02026774();
    }
}
