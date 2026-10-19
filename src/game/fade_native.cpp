#include "engine/functions.h"
#include "enemy/enemycommon.h"
#include "global.h"

// Implementer B, round 6: fade_native_init_0464c0 (0x020464c0), fade_native_init_046538 (0x02046538).
// Both are the native init routines of a fade-table entry; they fill random block lists.

ARM void fade_native_init_0464c0(u8 param) {
    u8 roll = Random();
    if (Random() & 1) {
        RandomBlockSet(nativeInitListA, 0);
    } else {
        RandomBlockSet(nativeInitListB, 0);
    }
    if (roll < 0x55) {
        RandomBlockSet(nativeInitListC, 0);
    } else if (roll < 0xaa) {
        RandomBlockSet(nativeInitListD, 0);
    } else {
        RandomBlockSet(nativeInitListE, 0);
    }
}

ARM void fade_native_init_046538(u8 param) {
    u32 m = Random() % 3;
    switch (m) {
    case 0:
        RandomBlockSet(data_020f3a9e, param);
        RandomBlockSet(data_020f3a94, param);
        break;
    case 1:
        RandomBlockSet(data_020f3a9e, param);
        RandomBlockSet(data_020f3a99, param);
        break;
    case 2:
        RandomBlockSet(data_020f3a94, param);
        RandomBlockSet(data_020f3a99, param);
        break;
    }
    if (Random() & 1) {
        RandomBlockSet(data_020f3a8e, param);
    } else {
        RandomBlockSet(data_020f3a91, param);
    }
}
