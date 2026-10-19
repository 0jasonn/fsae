#include "engine/functions.h"
#include "game/message.h"
#include "game/msgwin.h"
#include "global.h"
#include "types.h"

// Fields of the message box (data_0217d39c) that game/message.h does not name yet
typedef struct MsgBoxFields {
    /* 00 */ u8 unk_00[0x0e];
    /* 0e */ u8 layoutFlags; // bits 6-7: window slot bank
    /* 0f */ u8 originBits; // low 5 bits: tile origin x of the window
    /* 10 */ u8 drawFlags;
    /* 11 */ u8 sizeBits; // low 5 bits: width step, bits 5-7: height step
    /* 12 */ u8 unk_12[0xe4 - 0x12];
    /* e4 */ u8 cursorFlags; // bit 4: cursor drawn (dispCursor)
    /* e5 */ s8 sizeStep; // window size progress 0..8: msgOpen adds 1, msgClose subtracts 1
} MsgBoxFields;

#define MSG_BOX ((MsgBoxFields *)&data_0217d39c)

extern u8 data_021361a0[];

// Draws the frame of the current window slot and copies it into the saved slot
ARM void createWindow(void) {
    u8 slotIndex;
    u16 attr;
    u8 *tiles;
    WindowSlot *slot;

    if (MSG_BOX->sizeStep <= 0) {
        return;
    }
    attr = (u16)((((u32)MSG_BOX->layoutFlags << 24) >> 30) << 12 | 0x88);
    slotIndex = data_0212c618[3];
    slot = &data_0216efe0[slotIndex];
    tiles = (u8 *)data_021361a0 + slotIndex * 0x800 + ((slot->tileX + (slot->tileY << 5)) << 1);
    MessageFrameDisp((u16 *)tiles, slot->width, slot->height, attr);
    dispString();
    dispEnqCursor();
    dispCursor();
    slotIndex = data_0212c618[3];
    slot = &data_0216efe0[slotIndex];
    {
        WindowSlot *dst = &data_0216eff0[slotIndex];
        *dst = *slot;
    }
    func_02026774();
}
