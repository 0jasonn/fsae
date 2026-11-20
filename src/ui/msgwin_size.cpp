#include "engine/functions.h"
#include "ui/message.h"
#include "engine/cockpit_state.h"

// The original re-materialises the address of messageBox for every field access, which only a cast expression does
#define MSG_BOX ((KNIFE_MSGSYS *)&messageBox)

// msgWinSizeChange() (0x0204ab20): grows (mode 1) or shrinks (mode -1) the message window by one step and resizes its
// slot (even width and height, centred on the origin); returns 1 when the limit is reached
int msgWinSizeChange(s32 mode) {
    WindowSlot *slot;
    int limit = 0;
    s8 step;

    MSG_BOX->sizeStep = MSG_BOX->sizeStep + (s8)mode;
    if (MSG_BOX->sizeStep <= 0) {
        MSG_BOX->sizeStep = 0;
        limit = 1;
    } else if (MSG_BOX->sizeStep >= 8) {
        MSG_BOX->sizeStep = 8;
        limit = 1;
    }

    slot = &data_0216efe0[cockpitState.bufferIndex];
    step = MSG_BOX->sizeStep;
    if (step != 0) {
        u32 width = (u32)(step * ((u32)(MSG_BOX->sizeBits << 27) >> 23)) >> 7;
        u8 widthLow;
        u32 height;
        u8 heightLow;

        slot->width = width;
        widthLow = slot->width;
        if (widthLow & 1) {
            slot->width = widthLow + 1;
        }
        slot->tileX = (u8)(((u32)(MSG_BOX->originBits << 27) >> 27) + ((u32)(MSG_BOX->sizeBits << 27) >> 28) -
                           ((u32)slot->width >> 1));
        height = (u32)(step * (((u32)(MSG_BOX->sizeBits << 24) >> 29) << 4)) >> 7;
        slot->height = height;
        heightLow = slot->height;
        if (heightLow & 1) {
            slot->height = heightLow + 1;
        }
        slot->tileY = (u8)(((u32)(MSG_BOX->drawFlags << 27) >> 27) + ((u32)(MSG_BOX->sizeBits << 24) >> 30) -
                           ((u32)slot->height >> 1));
    } else {
        slot->tileY = 0xff;
        slot->tileX = 0xff;
        slot->height = 0xff;
        slot->width = 0xff;
    }
    slot->unk_02 = data_0216efbc[0];
    slot->active = data_0216efbc[0];
    return limit;
}
