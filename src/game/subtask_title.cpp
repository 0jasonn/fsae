#include "engine/functions.h"
#include "global.h"
#include "game/subtask_init.h"
#include "game/eff.h"

// subtask title and push start functions, 0x0209c6c0 to 0x0209c88c.

extern u8 data_0217c23c[];
extern u8 data_0212c508;
extern u8 data_0217a23c[];
extern u8 data_0217d23c[];
extern u8 data_0217a258[];

// subTask_empty_0 (0x0209c6c0): empty function, a table entry
extern "C" void subTask_empty_0(void);
ARM void subTask_empty_0(void) {
}

// subTask_empty_1 (0x0209c6c4): empty function, a table entry
extern "C" void subTask_empty_1(void);
ARM void subTask_empty_1(void) {
}

// subTask_nop() (0x0209c6c8)
extern "C" void subTask_nop(void);
ARM void subTask_nop(void) {
    if (*(s32 *)(data_0217c23c + 0xf50) <= 0) {
        func_020827a8(data_0212c508);
    }
}

// subTask_title_init() (0x0209c6f4)
extern "C" void subTask_title_init(void);
ARM void subTask_title_init(void) {
    u8 *app;

    *(s32 *)(data_0217a23c + 0xfc) = 0;
    subTask_init_vram(0);
    subTask_init_bg3(12, 13, 14);
    subTask_setupBuffer(0);
    func_020a3778(0);
    app = (u8 *)KnifeApp_getInstance();
    *(s32 *)(app + 0x10) = 0;
    *(s32 *)(app + 0x14) = 0;
    *(volatile u32 *)0x04001000 = (*(volatile u32 *)0x04001000 & ~0x1f00) | 0x1800;
    eff_cut_in_init();
}

// subTask_title_end() (0x0209c75c)
extern "C" void subTask_title_end(void);
ARM void subTask_title_end(void) {
    func_0209bee4();
    eff_white_out_init(0x1000);
}

// subTask_title() (0x0209c770): counts up to 0x5a, then moves to subtask 2
extern "C" void subTask_title(void);
ARM void subTask_title(void) {
    s32 timer = *(s32 *)(data_0217a23c + 0xfc);

    if (timer <= 0x5a) {
        timer++;
        *(s32 *)(data_0217a23c + 0xfc) = timer;
        return;
    }
    func_020827a8(2);
}

// subTask_push_start_init() (0x0209c79c)
extern "C" void subTask_push_start_init(void);
ARM void subTask_push_start_init(void) {
    u8 *work;
    u8 *app;

    work = *(u8 **)(data_0217d23c + 0x10c);
    *(s32 *)(work + 0x51c) = 0;
    subTask_init_vram(0);
    subTask_init_bg3(15, 16, 17);
    subTask_init_bg2(18, 19, 35);
    subTask_init_bg2_lang(0, 0x2000);
    subTask_init_obj(23, 26, -1, -1);
    subTask_init_obj_lang(1, 0x2000);
    subTask_setupBuffer(0);
    func_020a3778(0x100);
    app = (u8 *)KnifeApp_getInstance();
    *(s32 *)(app + 0x10) = 0;
    *(s32 *)(app + 0x14) = 0;
    *(volatile u32 *)0x04001000 = *(volatile u32 *)0x04001000 & ~0x1f00;
    eff_fade_in_init(0x888);
}

// subTask_push_start_end() (0x0209c84c)
extern "C" void subTask_push_start_end(void);
ARM void subTask_push_start_end(void) {
    u32 i;

    *(volatile u32 *)0x04001000 = *(volatile u32 *)0x04001000 & ~0x1f00;
    for (i = 0; i < 4; i++) {
        subTask_free_slot(i);
    }
    subTask_free_objinfo((OBJInfo *)data_0217a258);
}
