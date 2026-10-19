#include "engine/functions.h"
#include "global.h"
#include "game/map.h"

// Map / collision-cell helpers (module map). Original names from the debug build.
//   isAnkyo, PuyoAnkyo

extern const u16 data_020cd724[];

// Non-zero when the cell at (x, y) is not the 0x43 cell that PuyoAnkyo treats as a blocker.
ARM BOOL isAnkyo(u16 x, u16 y) {
    return func_02083d00(x, y) != 0x43;
}

// Works out which of the four neighbours (left, right, up, down) are blockers and calls RewCellOne with the
// matching entry of data_020cd724. Returns early when the cell itself is a blocker.
ARM void PuyoAnkyo(u16 x, u16 y) {
    int bits;

    if (isAnkyo(x, y)) {
        return;
    }
    bits = isAnkyo((u16)(x - 0x40), y);
    bits |= isAnkyo((u16)(x + 1), y) << 1;
    bits |= isAnkyo((u16)(x + 0x40), y) << 2;
    bits |= isAnkyo((u16)(x - 1), y) << 3;
    RewCellOne(data_020cd724[bits], x, y);
}
