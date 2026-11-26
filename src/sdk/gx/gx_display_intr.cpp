#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/gx.h"

// DISPSTAT (0x04000004) helpers; the interrupt toggles return the previous enable bit.

void GX_SetVCountEqVal(u32 line) {
    volatile u16 *reg = (volatile u16 *)0x4000004;
    *reg = (u16)((*reg & 0x3f) | (((u32)line << 24) >> 16) | ((s32)(line & 0x100) >> 1));
}

BOOL GX_HBlankIntr(BOOL enable) {
    volatile u16 *reg = (volatile u16 *)0x4000004;
    BOOL previous = *reg & 0x10;
    if (enable) {
        *reg |= 0x10;
    } else {
        *reg &= ~0x10;
    }
    return previous;
}

BOOL GX_VBlankIntr(BOOL enable) {
    volatile u16 *reg = (volatile u16 *)0x4000004;
    BOOL previous = *reg & 0x8;
    if (enable) {
        *reg |= 0x8;
    } else {
        *reg &= ~0x8;
    }
    return previous;
}
