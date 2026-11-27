#include "engine/functions.h"
#include "global.h"
#include "engine/misc.h"

// Functions in this file (original names from the debug build): OpeningTaskFinalzie

// OpeningTaskFinalzie() (0x02050ac4): ends the opening task: restores the OBJ VRAM mapping bits of DISPCNT (0x300010)
// that title_init saved at the start of titleDialogBlock, then releases the opening's VRAM and virtual screen.
// The ROM loads the saved word's address before materialising the register address: that only comes out with copy
// propagation off for the local (mwcc otherwise folds `mode` into the expression and schedules the register first).
#pragma push
#pragma opt_propagation off
void OpeningTaskFinalzie(void) {
    u32 mode = titleDialogBlock;

    *(volatile u32 *)0x04000000 = (*(volatile u32 *)0x04000000 & ~0x00300010) | mode;
    func_02082c54(NULL);
    Vram_ResetMainBankA();
    Vram_ResetMainBankB();
    finalizeVirtualScreenData();
}
#pragma pop
