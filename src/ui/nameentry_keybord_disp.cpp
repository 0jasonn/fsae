#include "knife/subtask/subtask.h"
#include "sdk/os/dc_cache.h"
#include "ui/nameentry_align.h"

void nameEntryUIView_keybord_disp(void *self) {
    u32 i;

    for (i = 6; i < 0x47; i++) {
        nameEntryUIView_alignCenter(self, i, 0xe);
    }
    for (i = 0; i < 0x47; i++) {
        Knife_Message_RedrawText(i, 0);
    }

    FileSelectionTilemap *&bg1 = data_02180d9c.bg1;
    DC_FlushRange(bg1, sizeof(FileSelectionTilemap));
    subTaskSendScr(1, bg1, 0, sizeof(FileSelectionTilemap));
}
