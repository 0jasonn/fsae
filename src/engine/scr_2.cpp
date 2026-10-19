#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Scroll and background helpers (module scr). Address -> name:
//   0x02056ef0 scr_init (original name, matches)
//   0x02056f0c ScrollMove (original name, matches)
//   0x02056f30 GetBgBuffAdrs (original name, matches)
//   0x0205747c YureSet (original name, matches)

ARM void YureSet(int a, int b) {
    data_0212c648.yureValue = a;
    data_0212c648.yureMode = b & 3;
}
