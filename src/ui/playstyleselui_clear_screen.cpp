#include "engine/functions.h"
#include "knife/message/playstyle_update.h"
#include "knife/subtask/subtask.h"
#include "sdk/os/dc_cache.h"
#include "ui/file_selection_buffers.h"

void playStyleSelUIView_clearScreen(PlayStyleSelUIView *self) {
    FileSelectionTilemap *&bg1 = data_02180d9c.bg1;
    OSi_CpuClear32(0, bg1, sizeof(FileSelectionTilemap));
    DC_FlushRange(bg1, sizeof(FileSelectionTilemap));
    subTaskSendScr(1, bg1, 0, sizeof(FileSelectionTilemap));
    subTaskSendScr(2, bg1, 0, sizeof(FileSelectionTilemap));
}
