#include "engine/functions.h"
#include "enemy/ending.h"
#include "global.h"

// Implementer B, round 6: FadeInit (0x020461e0), FadeClear (0x02046214), FadeSet (0x0204625c), FadeMain (0x020462c4),
// fade_in (0x020462f4), fade_out (0x0204636c), MakeFadeBuff256 (0x020463f0).

void FadeClear(void);

ARM void FadeInit(void) {
    u32 size = 0x10;
    func_02029a50(&data_0212c5ac, size);
    FadeClear();
    data_0212c5ac.resetValue = size - 0x11;
    data_0212c5ac.fadeRunning = 1;
}

ARM void FadeClear(void) {
    if (data_0212c5ac.fadeRunning == 0) {
        data_0212c75c.unk_66 = 0;
        return;
    }
    em2f_mapFlag = 0xffffffff;
    data_02134910 = 0;
}
