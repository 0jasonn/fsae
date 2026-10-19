#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Scroll and background helpers (module scr). Address -> name:
//   0x02056ef0 scr_init (original name, matches)
//   0x02056f0c ScrollMove (original name, matches)
//   0x02056f30 GetBgBuffAdrs (original name, matches)
//   0x0205747c YureSet (original name, matches)

ARM void scr_init(void) {
    data_0212c648.scrollMode = 1;
    data_0212c648.unk_04 = 0;
}

ARM void ScrollMove(void) {
    data_020d85b0[data_0212c648.scrollMode]();
}

ARM int GetBgBuffAdrs(int a) {
    if (((u32)a >> 14) == 2) {
        return (int)data_02163fa4;
    }
    return (int)data_02158fa0;
}
