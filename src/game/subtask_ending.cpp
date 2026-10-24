#include "engine/functions.h"
#include "global.h"
#include "game/g_game_start.h"

// Functions in this file (original names from the debug build):
//   subTask_ending_init (0x020c8c60), subTask_ending_end (0x020c8cc4), subTask_ending_stub (empty stub)

// subTask_ending_init() (0x020c8c60): starts the ending subtask: the VRAM and object setup, the sub screen
// display control, and the fade in
ARM void subTask_ending_init(void) {
    u8 *app;
    u32 zero;

    subTask_init_vram(1);
    subTask_init_obj(0x2b, 0x2a, -1, -1);
    zero = 0;
    subTask_setupBuffer(zero);
    func_020a3778(4);
    app = (u8 *)KnifeApp_getInstance();
    *(u32 *)(app + 0x10) = zero;
    *(u32 *)(app + 0x14) = zero;
    *(u32 *)0x04001000 = (*(u32 *)0x04001000 & ~0x1f00) | 0x1000;
    eff_fade_in_init(0x1000);
}

// subTask_ending_end() (0x020c8cc4): frees the subtask slots and the object info block, then fades out
ARM void subTask_ending_end(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        subTask_free_slot(i);
    }
    subTask_free_objinfo((OBJInfo *)data_0217a258);
    eff_fade_out_init(0x1000);
}

// subTask_ending_stub (0x020c8cf8): empty stub
extern "C" void subTask_ending_stub(void);
ARM void subTask_ending_stub(void) {
}
