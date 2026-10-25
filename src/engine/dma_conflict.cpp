#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" void OS_Terminate(void);
extern "C" void Dma_CheckConflict(s32 skip, u32 mode);

// Dma_CheckConflict(skip, mode) (0x02015940): looks at the control words of the three DMA channels (0x040000b8 + 12 * i,
// except channel skip). An enabled channel whose transfer mode is not compatible with mode ends the program. A channel
// in mode 0x8000000 may share mode 0x10000000 and the other way round.
ARM void Dma_CheckConflict(s32 skip, u32 mode) {
    s32 i;
    u32 control;

    for (i = 0; i < 3; i++) {
        if (i == skip) {
            continue;
        }
        control = *(u32 *)(0x040000b8 + i * 12);
        if ((control & 0x80000000) == 0) {
            continue;
        }
        control &= 0x38000000;
        if (control == mode) {
            continue;
        }
        if (control == 0x08000000 && mode == 0x10000000) {
            continue;
        }
        if (control == 0x10000000 && mode == 0x08000000) {
            continue;
        }
        if (control == 0x18000000 || control == 0x20000000 || control == 0x28000000 || control == 0x30000000 ||
            control == 0x38000000 || control == 0x08000000 || control == 0x10000000) {
            OS_Terminate();
        }
    }
}
