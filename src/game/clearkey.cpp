#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "actor/object/k_misc.h"
// key_check (0x02048ea8): bit mask of the two-bit fields of keys (field n -> bit n) that are at least threshold
s32 key_check(u8 keys, u8 threshold) {
    s32 result = 0;
    u8 v = keys;

    if ((v & 3) >= threshold) {
        result |= 1;
    }
    v >>= 2;
    if ((v & 3) >= threshold) {
        result |= 2;
    }
    v >>= 2;
    if ((v & 3) >= threshold) {
        result |= 4;
    }
    return result;
}

u8 ClearKeyCheck(void) {
    u8 i;
    u8 keys;
    u8 cnt1;
    u8 cnt2;
    u8 cnt3;
    cnt1 = cnt2 = cnt3 = i = 0;
    for (i = 0; i < gameState.playerCount; i++) {
        keys = gameState.slots[i].fieldBits;
        if (key_check(keys, 1) == 7) cnt1++;
        if (key_check(keys, 2) == 7) cnt2++;
        if (key_check(keys, 3) == 7) cnt3++;
    }
    if (cnt3 == gameState.playerCount) return 3;
    if (cnt2 == gameState.playerCount) return 2;
    return cnt1 == gameState.playerCount;
}
