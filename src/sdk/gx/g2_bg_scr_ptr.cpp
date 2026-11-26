#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/g2.h"

// Screen base address of a background: the main engine adds the DISPCNT screen base, the sub engine uses 0x06200000.

void *G2_GetBG0ScrPtr(void) {
    s32 block = (*(volatile u16 *)0x4000008 & 0x1f00) >> 8;
    u32 base = (*(volatile u32 *)0x4000000 & 0x38000000) >> 27;
    return (void *)(0x6000000 + (base << 16) + (block << 11));
}

void *G2S_GetBG0ScrPtr(void) {
    s32 block = (*(volatile u16 *)0x4001008 & 0x1f00) >> 8;
    return (void *)(0x6200000 + (block << 11));
}

void *G2_GetBG1ScrPtr(void) {
    s32 block = (*(volatile u16 *)0x400000a & 0x1f00) >> 8;
    u32 base = (*(volatile u32 *)0x4000000 & 0x38000000) >> 27;
    return (void *)(0x6000000 + (base << 16) + (block << 11));
}

void *G2S_GetBG1ScrPtr(void) {
    s32 block = (*(volatile u16 *)0x400100a & 0x1f00) >> 8;
    return (void *)(0x6200000 + (block << 11));
}
