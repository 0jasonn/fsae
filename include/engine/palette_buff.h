#ifndef ENGINE_PALETTE_BUFF_H
#define ENGINE_PALETTE_BUFF_H

#include "types.h"

// Main palette buffer (data_021355a0, 0x400 bytes: 0x100 BG colours, then 0x100 OBJ colours, 16 per slot). CgTrans
// uploads the slots selected by data_02134918 to 0x05000000; entry 0 is the backdrop colour; MakeFadeBuff256 fades the
// BG half. The symbols data_02135640 and data_02135840 are entries 0x50 (BG slot 5) and 0x150 (OBJ slot 5).
extern u16 data_021355a0[0x200];

// Translated (faded) copy of the main palette (data_02135da0, 0x400 bytes, same layout), uploaded by CgTrans instead of
// data_021355a0 when data_02134904 selects slots.
extern u16 data_02135da0[0x200];

// Palette upload buffer (data_0216fd04, 0x400 bytes up to data_02170104): opening.cpp fills it and copies it (or
// data_02170104, chosen by paletteFade.bufferSelect) to 0x06896000.
extern u16 data_0216fd04[0x200];

#endif
