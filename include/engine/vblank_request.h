#ifndef ENGINE_VBLANK_REQUEST_H
#define ENGINE_VBLANK_REQUEST_H

#include "types.h"

// Frame handshake with VBlankIntr (two separate bss bytes; dsd has a symbol every 4 bytes around them).
// data_0212c4c8 is the double-buffer index (0 or 1) of the frame being built: the command queue half in data_0212ccb0
// (0x100 bytes each), the circle/triangle span bank in data_021352a0 (0x180 bytes each) and the scroll-changed flag in
// data_021348f4 are selected by it, and VBlankIntr uploads the other half (index ^ 1). DispReset clears it.
// data_0212c4e0 is nonzero when a finished frame waits for VBlankIntr's transfers; VBlankIntr clears it afterwards.
extern u8 data_0212c4c8; // 0x0212c4c8
extern u8 data_0212c4e0; // 0x0212c4e0

#endif
