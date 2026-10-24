#include "engine/functions.h"
#include "global.h"
#include "game/g_knife_manual.h"

// Functions in this file (original names from the debug build):
//   Knife_CheckIndexed (provisional name, returns the result of func_020c2c34 for a clamped index)

// Knife_CheckIndexed (0x020c806c): the index is clamped to at least 1 and passed to func_020c2c34 on data_02187050
ARM s32 Knife_CheckIndexed(s32 a) {
    s32 id;
    s32 r;

    id = a;
    if (id <= 0) {
        id = 1;
    }
    r = func_020c2c34((MenuChecker *)data_02187050, id);
    if (r == 0) {
        return 0;
    }
    return r;
}
