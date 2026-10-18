#include "Unknown/D/Misc_D.h"
#include "global.h"

ARM void func_02050a50(void) {
    s32 size;
    void *p;
    func_02082c54((void *)func_02050924);
    data_0216fcf8.unk_2 = 0xffff;
    func_020152ec();
    p = func_0208dde0(func_0208da4c(), &size, 0x3b);
    MIi_CpuCopyFast(p, data_0216fd04, size);
    MIi_CpuCopyFast(p, data_02170104, size);
    data_0216fcf8.unk_8 = 1;
    data_0216fcf8.unk_0 = 0;
}
