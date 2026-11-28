#include "engine/functions.h"
#include "types.h"
#include "sdk/gx/g2.h"

// Character base address of BG2/BG3; 0 when the background is in a mode where it is an extended/bitmap layer.

void *G2S_GetBG2CharPtr(void) {
    s32 mode = *(volatile u32 *)0x4001000 & 7;
    u32 bgcnt = *(volatile u16 *)0x400100c;
    if (mode < 5 || !(bgcnt & 0x80)) {
        s32 block = (bgcnt & 0x3c) >> 2;
        return (void *)(0x6200000 + (block << 14));
    }
    return 0;
}

void *G2_GetBG3CharPtr(void) {
    s32 mode = *(volatile u32 *)0x4000000 & 7;
    u32 bgcnt = *(volatile u16 *)0x400000e;
    if (mode < 3 || (mode < 6 && !(bgcnt & 0x80))) {
        u32 base = (*(volatile u32 *)0x4000000 & 0x7000000) >> 24;
        s32 block = (bgcnt & 0x3c) >> 2;
        return (void *)(0x6000000 + (base << 16) + (block << 14));
    }
    return 0;
}

void *G2S_GetBG3CharPtr(void) {
    s32 mode = *(volatile u32 *)0x4001000 & 7;
    u32 bgcnt = *(volatile u16 *)0x400100e;
    if (mode < 3 || (mode < 6 && !(bgcnt & 0x80))) {
        s32 block = (bgcnt & 0x3c) >> 2;
        return (void *)(0x6200000 + (block << 14));
    }
    return 0;
}
