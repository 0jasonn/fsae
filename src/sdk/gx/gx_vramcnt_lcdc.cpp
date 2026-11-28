#include "sdk/gx/gx_vramcnt.h"

// Writes 0x80 (enable) to the VRAMCNT register of every bank selected in mask (bit 0 = bank A ... bit 8 = bank I).
void GX_VRAMCNT_SetLCDC_(u32 mask) {
    if (mask & 0x1) {
        *(volatile u8 *)0x4000240 = 0x80;
    }
    if (mask & 0x2) {
        *(volatile u8 *)0x4000241 = 0x80;
    }
    if (mask & 0x4) {
        *(volatile u8 *)0x4000242 = 0x80;
    }
    if (mask & 0x8) {
        *(volatile u8 *)0x4000243 = 0x80;
    }
    if (mask & 0x10) {
        *(volatile u8 *)0x4000244 = 0x80;
    }
    if (mask & 0x20) {
        *(volatile u8 *)0x4000245 = 0x80;
    }
    if (mask & 0x40) {
        *(volatile u8 *)0x4000246 = 0x80;
    }
    if (mask & 0x80) {
        *(volatile u8 *)0x4000248 = 0x80;
    }
    if (mask & 0x100) {
        *(volatile u8 *)0x4000249 = 0x80;
    }
}
