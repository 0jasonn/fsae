#ifndef ENGINE_IRQ_H
#define ENGINE_IRQ_H

#include "engine/entity.h"

typedef struct GlobalBuffer {
    u32 unk_00;
    u8 *block; // 0x04, returned by EL_GetGlobalAdr
} GlobalBuffer;

typedef struct FrameState {
    u16 frameCount;   // 0x00: incremented once per frame by main; blink and pacing code tests its low bits
    u16 transferLock; // 0x02: VBlankIntr skips the screen, display and character transfers while nonzero
    u8 unk_04;        // 0x04: set to 1 by pot_ware, cleared by pot_remove, PlWorkReset and DispReset
    u8 unk_05;        // 0x05: set by stagesel_init, cleared by DispReset
    u8 unk_06[2];
} FrameState;
extern FrameState frameState;  // 0x0212c594

typedef struct HBlankDmaState {
    u8 enabled; // 0x00
    u8 unk_01[3];
    void *src;  // 0x04
    void *dst;  // 0x08
} HBlankDmaState;
extern HBlankDmaState hblankDma;  // 0x0212c59c: the VBlank handler restarts the HBlank DMA from it

typedef struct IrqState {
    u8 unk_00[8];
    void (*handler)(void); // 0x08
} IrqState;

#endif
