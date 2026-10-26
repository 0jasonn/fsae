#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// ctrl_wrap: functions Ctrl_updateSlotsA (0x020bc36c), Ctrl_getConst (0x020bc390) and Ctrl_waitVBlank (0x020bc39c),
// provisional names.

// Ctrl_updateSlotsA(self) (0x020bc36c, provisional name): func_020c37c8 and then func_020c39c4 on the record at +0x2c18
extern "C" void Ctrl_updateSlotsA(void *self);
ARM void Ctrl_updateSlotsA(void *self) {
    u8 *base = (u8 *)self;
    func_020c37c8(base + 0x18 + 0x2c00);
    func_020c39c4(base + 0x18 + 0x2c00);
}

// Ctrl_getConst() (0x020bc390, provisional name): the constant 0x100010
extern "C" u32 Ctrl_getConst(void);
ARM u32 Ctrl_getConst(void) {
    return 0x100010;
}

// Ctrl_waitVBlank() (0x020bc39c, provisional name): OS_WaitVBlankIntr
extern "C" void Ctrl_waitVBlank(void);
ARM void Ctrl_waitVBlank(void) {
    OS_WaitVBlankIntr();
}
