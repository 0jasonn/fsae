#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "actor/object/k_misc.h"
#include "actor/object/k_yousei.h"
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

extern u8 data_021036a8[]; // (mask, shift) pairs: bit field of GameSlot::fieldBits that belongs to each stage group

// Raises the clear key level of the current stage group (GameState::unk_01 < 5) in every player's field bits to at least
// `level`.
void ClearKeyUpdate(u8 level) {
    u8 mask;
    u8 shift;
    u8 value;
    u8 i;

    if (gameState.unk_01 >= 5) {
        return;
    }
    shift = data_021036a8[gameState.unk_01 * 2 + 1];
    mask = data_021036a8[gameState.unk_01 * 2];
    value = level << shift;
    for (i = 0; i < gameState.playerCount; i++) {
        u8 bits = gameState.slots[i].fieldBits;
        if ((bits & mask) < value) {
            gameState.slots[i].fieldBits = (bits & ~mask) | value;
        }
    }
}
