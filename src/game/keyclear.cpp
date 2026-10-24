#include "engine/functions.h"
#include "game/comm.h"
#include "global.h"

// Key and window module: keyClear clears the two key word tables and requests comm mode 5. StopEffectWindow and
// InitCircleWindow drive the circle window through display flags and the window register mirror hblankDma.
//   keyClear (0x0202b54c), CircleWindowHook (CircleWindowHook, empty), EffectWindowHook (EffectWindowHook, empty),
//   StopEffectWindow (0x0202b598), InitCircleWindow (0x0202b5d4)

// Window state block hblankDma: an active flag at +0 and the window register address at +8.
typedef struct WindowState {
    u8 active;
    u8 unk_01[7];
    u32 windowReg;
} WindowState;

// Display shadow block (data_0212c75c): display flags at +0, window values at +0x5c, +0x60 and +0x62.
typedef struct WindowDisplay {
    u16 displayFlags;
    u8 unk_02[0x5a];
    u16 unk_5c;
    u8 unk_5e[2];
    u16 unk_60;
    u16 unk_62;
} WindowDisplay;

extern u16 data_0212c584[4];
extern u16 data_0212c58c[4];
extern WindowState hblankDma;
extern WindowDisplay data_0212c75c;

extern "C" void keyClear(void);
extern "C" void CircleWindowHook(void);
extern "C" void EffectWindowHook(void);

// keyClear (0x0202b54c)
ARM void keyClear(void) {
    ComRequest(5);
    data_0212c584[3] = 0;
    data_0212c584[2] = 0;
    data_0212c584[1] = 0;
    data_0212c584[0] = 0;
    data_0212c58c[3] = 0;
    data_0212c58c[2] = 0;
    data_0212c58c[1] = 0;
    data_0212c58c[0] = 0;
}

// CircleWindowHook (CircleWindowHook): placeholder with no code in the ROM, called after the circle window starts.
ARM void CircleWindowHook(void) {
}

// EffectWindowHook (EffectWindowHook): placeholder with no code in the ROM, called after the effect window stops.
ARM void EffectWindowHook(void) {
}

// StopEffectWindow (0x0202b598): clears the window bit of the display flags and the window active flag, stops the DMA
// and calls EffectWindowHook.
ARM void StopEffectWindow(void) {
    data_0212c75c.displayFlags = data_0212c75c.displayFlags & 0xdfff;
    hblankDma.active = 0;
    MI_StopDma(0);
    EffectWindowHook();
}

// InitCircleWindow (0x0202b5d4): sets the window bit, the window bounds x and y, the size 0xc0 and the active flag,
// then calls CircleWindowHook.
ARM void InitCircleWindow(u16 x, u16 y) {
    data_0212c75c.displayFlags = data_0212c75c.displayFlags | 0x2000;
    data_0212c75c.unk_60 = x;
    data_0212c75c.unk_62 = y;
    data_0212c75c.unk_5c = 0xc0;
    hblankDma.active = 1;
    hblankDma.windowReg = 0x04000040;
    CircleWindowHook();
}
