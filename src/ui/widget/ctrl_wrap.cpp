#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/rect_f.h"
#include "ui/widget/ctrl_wrap_api.h"

// ctrl_wrap: functions Ctrl_updateSlotsA (0x020bc36c), Ctrl_getConst (0x020bc390) and Ctrl_waitVBlank (0x020bc39c),
// provisional names.

// Ctrl_updateSlotsA(self) (0x020bc36c, provisional name): OamRing_Flush and then OamRing_Clear on the record at +0x2c18
void Ctrl_updateSlotsA(void *self) {
    u8 *base = (u8 *)self;
    OamRing_Flush(base + 0x18 + 0x2c00);
    OamRing_Clear(base + 0x18 + 0x2c00);
}

// Ctrl_getConst() (0x020bc390, provisional name): the constant 0x100010
u32 Ctrl_getConst(void) {
    return 0x100010;
}

// Ctrl_waitVBlank() (0x020bc39c, provisional name): OS_WaitVBlankIntr
void Ctrl_waitVBlank(void) {
    OS_WaitVBlankIntr();
}
