#include "engine/functions.h"
#include "global.h"
#include "ui/message.h"

// Needs the proposed KNIFE_MSGSYS change: `u8 drawFlags` at 0x10 becomes `TelopDrawBits draw` (5-bit position field).

// Moves the telop scroll position by delta (5-bit field at telopBox + 0x10), clamps it to 0x15..0x18 (returns 1 when it was
// clamped) and publishes the position as tileY and height of the telop window slot.
int telopUpdate(s32 delta) {
    u8 slot;
    int result = 0;

    TelopDrawBits *draw = &telopBox.draw;
    draw->pos += (u8)delta;
    if (telopBox.draw.pos <= 0x15) {
        telopBox.draw.pos = 0x15;
        result = 1;
    } else if (telopBox.draw.pos >= 0x18) {
        telopBox.draw.pos = 0x18;
        result = 1;
    }
    slot = cockpitState[3];
    telopWindowSlots[slot].tileY = telopBox.draw.pos;
    telopWindowSlots[slot].height = 0x18 - telopBox.draw.pos;
    telopWindowSlots[slot].active = 1;
    return result;
}
