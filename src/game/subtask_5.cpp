#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

// Subtask buffer setup and action dispatch, 0x0209dd44 to 0x0209de18.

extern EntityFunc data_0211c69c[];
extern u32 data_02179a38;
extern u8 data_02179a3c[];
extern "C" void func_02013a38(void *buf, s32 a, s32 size);
extern "C" void func_02013af4(void *buf, s32 a, s32 size);
extern "C" void func_02013bb0(void *buf, s32 a, s32 size);
extern "C" void func_02013d28(void *buf, s32 a, s32 size);

// subTask_setupBuffer (0x0209dd44): clears the 2 KB buffer once, flushes it and runs the variant for mode.
ARM void subTask_setupBuffer(u32 mode) {
    if (data_02179a38 == 0) {
        MIi_CpuClearFast(0, data_02179a3c, 0x800);
        data_02179a38 = 1;
    }
    DC_FlushRange(data_02179a3c, 0x800);
    switch (mode) {
    case 0:
        func_02013a38(data_02179a3c, 0, 0x800);
        break;
    case 1:
        func_02013af4(data_02179a3c, 0, 0x800);
        break;
    case 2:
        func_02013bb0(data_02179a3c, 0, 0x800);
        break;
    case 3:
        func_02013d28(data_02179a3c, 0, 0x800);
        break;
    }
}

// subTask_dispatch (0x0209ddfc): calls the action handler selected by e->action.
ARM void subTask_dispatch(Entity *e) {
    data_0211c69c[e->action](e);
}
