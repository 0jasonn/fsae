#include "Unknown/D/Misc_D.h"
#include "global.h"

ARM void PaletteFade_Init(void) {
    s32 copySize;
    void *copySource;
    func_02082c54((void *)PaletteFade_Update);
    data_0216fcf8.fadeLevel = 0xffff;
    func_020152ec();
    copySource = func_0208dde0(func_0208da4c(), &copySize, 0x3b);
    MIi_CpuCopyFast(copySource, data_0216fd04, copySize);
    MIi_CpuCopyFast(copySource, data_02170104, copySize);
    data_0216fcf8.bufferSelect = 1;
    data_0216fcf8.fadeActive = 0;
}
