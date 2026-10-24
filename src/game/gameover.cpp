#include "engine/functions.h"
#include "global.h"
#include "game/fileselui.h"

// Functions in this file (original names from the debug build):
//   subTask_gameover_init (0x020adb04), subTask_gameover_end (0x020adb68)

// subTask_gameover_init (0x020adb04): starts the game over screen: VRAM and object setup, a clear of the sub display control, then a fade in
ARM void subTask_gameover_init(void) {
    u32 *dispCtrl;
    u32 *reg;
    s32 zero;

    subTask_init_vram(1);
    subTask_init_obj(0x2b, 0x2a, -1, -1);
    zero = 0;
    subTask_setupBuffer(zero);
    func_020a3778(4);
    dispCtrl = (u32 *)KnifeApp_getInstance();
    dispCtrl[4] = zero;
    dispCtrl[5] = zero;
    reg = (u32 *)0x04001000;
    *reg = (*reg & ~0x1f00) | 0x1000;
    eff_fade_in_init(0x2000);
}

// subTask_gameover_end (0x020adb68): releases the four slots and the object, then fades out unless the screen is already done
ARM void subTask_gameover_end(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        subTask_free_slot(i);
    }
    subTask_free_objinfo((OBJInfo *)data_0217a258);
    if (data_0217d23c[0xd0] == 1 && (s8)data_0217d23c[0xd1] == 2) {
        return;
    }
    eff_fade_out_init(0x1000);
}
