#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

// Subtask wallpaper end and transfer queue entries, 0x0209d9cc to 0x0209da9c.

extern u8 data_0217a258[];
extern SubtaskSendEntry data_0217d1b8[];
extern u8 data_0217d23c[];

// subTask_wall_paper_end (0x0209d9cc)
ARM void subTask_wall_paper_end(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        subTask_free_slot(i);
    }
    func_0209bee4();
    subTask_free_objinfo((OBJInfo *)data_0217a258);
    Knife_Message_CleanupTextRenderer();
    subTaskSendStop();
    if (data_0217d23c[0xd0] == 1 && (s8)data_0217d23c[0xd1] == 2) {
        return;
    }
    eff_fade_out_init(0x1000);
}

// subTask_wallpaper_request (0x0209da28): bumps the frame counter at +0x52c of the object in data_0217d23c + 0x10c
// and redraws the status wallpaper with mode 2.
ARM void subTask_wallpaper_request(void) {
    u8 *state = *(u8 **)(data_0217d23c + 0x10c);

    *(u32 *)(state + 0x52c) += 1;
    subtask_draw_status_wallpaper(0, 2);
}

// subTaskSendStopScr (0x0209da54): clears the single request of index.
ARM void subTaskSendStopScr(s16 index) {
    SubtaskSendEntry *entry = &data_0217d1b8[index];
    entry->size = 0;
    entry->offset = 0;
    entry->data = 0;
}

// subTaskSendScr (0x0209da7c): sets the single request of index.
ARM void subTaskSendScr(s16 index, void *data, u32 offset, u32 size) {
    SubtaskSendEntry *entry = &data_0217d1b8[index];
    entry->size = size;
    entry->offset = offset;
    entry->data = data;
}
