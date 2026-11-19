#ifndef GAME_MAGNE_H
#define GAME_MAGNE_H

#include "types.h"

// Per-player data used by the magnet shadow, indexed with stride 0x94 (the PlayerData size)
extern u8 data_0212cebf[]; // playerWork[i].unk_0f: bit 0 keeps the shadow alive, bit 1 selects sprite b16
extern u8 data_0212ced8[]; // playerWork[i].entity
extern u8 data_0212cedc[]; // playerWork[i].weapon (the magnet shadow entity)

#endif
