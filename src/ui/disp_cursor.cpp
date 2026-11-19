#include "engine/functions.h"
#include "ui/message.h"
#include "engine/cockpit_state.h"

// dispCursor() (0x0204b120): while the message window is open (windowMode 2) and the cursor is drawn (cursorState bit 4),
// writes the cursor tile 0x8f one column left of the bottom right corner of the window into the tile map of the
// current window bank.
void dispCursor(void) {
    u8 bank;
    int pos;
    u16 *tiles;

    if ((messageBox.cursorState & 0x10) == 0) {
        return;
    }
    if (messageBox.windowMode != 2) {
        return;
    }
    bank = cockpitState.bufferIndex;
    pos = (data_0216efe0[bank].width - 2) + ((data_0216efe0[bank].height + 1) << 5);
    tiles = (u16 *)(data_021361a0[bank]);
    tiles += data_0216efe0[bank].tileX + (data_0216efe0[bank].tileY << 5);
    u8 *dst = (u8 *)tiles;
    dst += pos << 1;
    *(u16 *)dst = 0x8f;
}
