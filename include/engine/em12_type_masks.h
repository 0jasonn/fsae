#ifndef ENGINE_EM12_TYPE_MASKS_H
#define ENGINE_EM12_TYPE_MASKS_H

#include "types.h"

// Per-area flag words (em12_typeMasks, 0x14 bytes up to data_02134968), indexed by e->areaIndex. Switches, levers and
// spawners set or clear flagBits[type] in their area's word and test ParseTypeBits(type) against it. Word 0 doubles as
// the game flag word of the ending, kenfuri and the set58/set59/set67-69 scenes.
extern u32 em12_typeMasks[5]; // 0x02134954

#endif
