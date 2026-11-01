#include "engine/functions.h"
#include "global.h"
#include "game/e_decls.h"

// Dialog clear block (data_0217e604): a rectangle of tiles in a 0x600-byte screen buffer (32 tiles per row).
// The block is read through the global at each use (the original does not keep the pointer in a local).
typedef struct SubtaskDialogBlock {
    u8 unk_00[4];
    u32 vramSlot;   // 0x04: copied to data_02117e60 by subtask_dialogDelete
    u32 dirty;      // 0x08: nonzero when the screen buffer must be sent
    s8 tileX;       // 0x0c
    s8 tileY;       // 0x0d
    s8 tileWidth;   // 0x0e
    s8 tileHeight;  // 0x0f
    u8 unk_10[0x48 - 0x10];
    u16 *screen;    // 0x48
} SubtaskDialogBlock;

#define DIALOG_BLOCK ((SubtaskDialogBlock *)data_0217e604)

// subtask_dialogDelete (0x020ac308): clears the tiles of the dialog rectangle and sends the screen buffer if dirty
void subtask_dialogDelete(void) {
    u16 *screen = DIALOG_BLOCK->screen;
    u32 y;
    u32 x;

    for (y = 0; y < DIALOG_BLOCK->tileHeight; y++) {
        for (x = 0; x < DIALOG_BLOCK->tileWidth; x++) {
            screen[(DIALOG_BLOCK->tileX + x) + ((DIALOG_BLOCK->tileY + y) << 5)] = 0;
        }
    }
    if (DIALOG_BLOCK->dirty != 0) {
        DC_FlushRange(screen, 0x600);
        subTaskSendScr(0, screen, 0, 0x600);
        DIALOG_BLOCK->dirty = 0;
    }
    *(u32 *)data_02117e60 = DIALOG_BLOCK->vramSlot;
}
