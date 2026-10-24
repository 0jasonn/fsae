#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build, or provisional names for func_ addresses):
//   subTask_staffroll_start_finale (0x020ae2b8), PM_GetExitFactor (0x020ae2e4),
//   subTask_staffroll_setupObj (0x020ae2f4): subTask_staffroll_setupObj, registers the object with the task helper

extern "C" {
s32 PM_GetExitFactor(void);
void func_0200c868(void *obj, u32 a, u32 b, void *fn);
void Knife_Message_RenderTarget_dtor_RenderTarget_0a2dd4(void *self);
}

extern u8 data_02180da8[];
extern u8 data_02180fe0[];
extern u8 data_0217d23c[];

// subTask_staffroll_start_finale (0x020ae2b8): sets the flag byte and the sub display control
ARM void subTask_staffroll_start_finale(void) {
    u32 *reg;

    data_02180da8[1] = 1;
    reg = (u32 *)0x04001000;
    *reg = (*reg & ~0x1f00) | 0x1000;
}

// PM_GetExitFactor (0x020ae2e4): returns the value at offset 0x14 of the screen state
ARM s32 PM_GetExitFactor(void) {
    return *(s32 *)(data_02180da8 + 0x14);
}

// subTask_staffroll_setupObj (0x020ae2f4): registers the object of this screen with the task helper
ARM void subTask_staffroll_setupObj(void) {
    func_0200c868(data_02180fe0, 0x10, 0x68, (void *)Knife_Message_RenderTarget_dtor_RenderTarget_0a2dd4);
}
