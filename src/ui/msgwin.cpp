#include "engine/functions.h"
#include "ui/message.h"
#include "ui/msgwin.h"
#include "global.h"
#include "types.h"


extern u8 data_021361a0[];

// Draws the frame of the current window slot and copies it into the saved slot
void createWindow(void) {
    u8 slotIndex;
    u16 attr;
    u8 *tiles;
    WindowSlot *slot;

    if (messageBox.sizeStep <= 0) {
        return;
    }
    attr = (u16)((((u32)messageBox.layoutFlags << 24) >> 30) << 12 | 0x88);
    slotIndex = cockpitState[3];
    slot = &data_0216efe0[slotIndex];
    tiles = (u8 *)data_021361a0 + slotIndex * 0x800 + ((slot->tileX + (slot->tileY << 5)) << 1);
    MessageFrameDisp((u16 *)tiles, slot->width, slot->height, attr);
    dispString();
    dispEnqCursor();
    dispCursor();
    slotIndex = cockpitState[3];
    slot = &data_0216efe0[slotIndex];
    {
        WindowSlot *dst = &data_0216eff0[slotIndex];
        *dst = *slot;
    }
    func_02026774();
}
