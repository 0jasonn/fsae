#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/g2.h"

// Character base address of a background, same layout as the screen base helpers.

void *G2_GetBG0CharPtr(void) {
    s32 block = (*(volatile u16 *)0x4000008 & 0x3c) >> 2;
    u32 base = (*(volatile u32 *)0x4000000 & 0x7000000) >> 24;
    return (void *)(0x6000000 + (base << 16) + (block << 14));
}

void *G2S_GetBG0CharPtr(void) {
    s32 block = (*(volatile u16 *)0x4001008 & 0x3c) >> 2;
    return (void *)(0x6200000 + (block << 14));
}

void *G2_GetBG1CharPtr(void) {
    s32 block = (*(volatile u16 *)0x400000a & 0x3c) >> 2;
    u32 base = (*(volatile u32 *)0x4000000 & 0x7000000) >> 24;
    return (void *)(0x6000000 + (base << 16) + (block << 14));
}

void *G2S_GetBG1CharPtr(void) {
    s32 block = (*(volatile u16 *)0x400100a & 0x3c) >> 2;
    return (void *)(0x6200000 + (block << 14));
}
