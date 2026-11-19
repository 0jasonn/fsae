#include "engine/functions.h"
#include "knife/comm/comm.h"
#include "global.h"
#include "engine/irq.h"  // hblankDma: enabled flag, DMA destination = window register
#include "game/keyclear_api.h"
#include "engine/display_state.h"

// Key and window module: keyClear clears the two key word tables and requests comm mode 5. StopEffectWindow and
// InitCircleWindow drive the circle window through display flags and the window register mirror hblankDma.
//   keyClear (0x0202b54c), CircleWindowHook (CircleWindowHook, empty), EffectWindowHook (EffectWindowHook, empty),
//   StopEffectWindow (0x0202b598), InitCircleWindow (0x0202b5d4)


extern u16 playerKeysPrev[4];
extern u16 playerKeys[4];

extern "C" void keyClear(void);

// keyClear (0x0202b54c)
void keyClear(void) {
    ComRequest(5);
    playerKeysPrev[3] = 0;
    playerKeysPrev[2] = 0;
    playerKeysPrev[1] = 0;
    playerKeysPrev[0] = 0;
    playerKeys[3] = 0;
    playerKeys[2] = 0;
    playerKeys[1] = 0;
    playerKeys[0] = 0;
}

// CircleWindowHook (CircleWindowHook): placeholder with no code in the ROM, called after the circle window starts.
void CircleWindowHook(void) {
}

// EffectWindowHook (EffectWindowHook): placeholder with no code in the ROM, called after the effect window stops.
void EffectWindowHook(void) {
}

// StopEffectWindow (0x0202b598): clears the window bit of the display flags and the window active flag, stops the DMA
// and calls EffectWindowHook.
void StopEffectWindow(void) {
    displayState.displayFlags = displayState.displayFlags & 0xdfff;
    hblankDma.enabled = 0;
    MI_StopDma(0);
    EffectWindowHook();
}

// InitCircleWindow (0x0202b5d4): sets the window bit, the window bounds x and y, the size 0xc0 and the active flag,
// then calls CircleWindowHook.
void InitCircleWindow(u16 x, u16 y) {
    displayState.displayFlags = displayState.displayFlags | 0x2000;
    displayState.winIn = x;
    displayState.winOut = y;
    displayState.win0V = 0xc0;
    hblankDma.enabled = 1;
    hblankDma.dst = (void *)0x04000040;
    CircleWindowHook();
}
