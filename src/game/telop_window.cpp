#include "engine/functions.h"
#include "ui/message.h"
#include "engine/cockpit_state.h"

// telopWindow() (0x0204a93c): draws the pending telop window (frame, then one or two text lines by mode), copies the slot
// to its secondary slot and clears the pending flag.
void telopWindow(void) {
    u8 slotIndex = cockpitState.bufferIndex;
    s8 mode;
    u16 *tiles;

    if (telopWindowSlots[slotIndex].active == 0) {
        return;
    }
    tiles = (u16 *)(data_021361a0[slotIndex] + 0x5c0);
    mode = telopWindowSlots[slotIndex].height;
    telopFrame(mode, tiles);
    tiles += 2;
    switch (mode) {
    case 3:
        telopString(tiles, 1);
        tiles -= 0x20;
    case 2:
        telopString(tiles, 0);
        break;
    }
    slotIndex = cockpitState.bufferIndex;
    ((u32 *)&data_0216f010[slotIndex])[0] = ((u32 *)&telopWindowSlots[slotIndex])[0];
    ((u32 *)&data_0216f010[slotIndex])[1] = ((u32 *)&telopWindowSlots[slotIndex])[1];
    telopWindowSlots[slotIndex].active = 0;
    func_02026774();
}
