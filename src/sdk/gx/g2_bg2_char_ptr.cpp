#include "engine/functions.h"
#include "sdk/gx/g2.h"

// Character base address of the main BG2; 0 when BG2 is an extended / bitmap layer.
void *G2_GetBG2CharPtr(void) {
    s32 mode = *(volatile u32 *)0x4000000 & 7;
    u32 bgcnt = *(volatile u16 *)0x400000c;
    if (mode < 5 || !(bgcnt & 0x80)) {
        u32 base = (*(volatile u32 *)0x4000000 & 0x7000000) >> 24;
        s32 block = (bgcnt & 0x3c) >> 2;
        return (void *)(0x6000000 + (base << 16) + (block << 14));
    }
    return 0;
}
