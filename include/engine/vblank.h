#ifndef ENGINE_VBLANK_H
#define ENGINE_VBLANK_H

#include "types.h"
#include "engine/irq.h"  // HBlankDmaState hblankDma

typedef volatile u16 vu16;


extern u16 data_0212c594[];     // [1] is nonzero while a screen transfer is being prepared (shared decls disagree on its type)
extern u8 data_0212c4e0;
extern u8 data_0212c4c8;
extern u8 data_021348f4[];
extern u16 *data_02158fa0;      // pointer to the screen block (first word of the layer buffer data_02158fa0)
extern u8 data_0213cfa0[];

#endif
