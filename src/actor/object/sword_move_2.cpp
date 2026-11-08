#include "engine/functions.h"
#include "actor/object/sword_hiddenwall.h"

// isHiddenBombWall, 0x0207b868. Tells whether the bomb wall cell kind is a hidden one (two bit tables: a 64-bit mask
// starting at cell kind 0x43e and a 12-bit mask starting at 0x485).
int isHiddenBombWall(u16 cell) {
    BOOL result = TRUE;
    BOOL first = FALSE;
    u16 index = cell + 0xfbc2;
    if (index <= 0x39) {
        if ((1ULL << index) & 0x0201000400800201ULL) {
            first = TRUE;
        }
    }
    if (!first) {
        BOOL second = FALSE;
        u16 index2 = cell + 0xfb7b;
        if (index2 <= 0xb) {
            if ((1 << index2) & 0x801) {
                second = TRUE;
            }
        }
        if (!second) {
            result = FALSE;
        }
    }
    return result;
}
