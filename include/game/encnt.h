#ifndef GAME_ENCNT_H
#define GAME_ENCNT_H

#include "actor/enemy/encnt.h"

void housha1(EncntEntry *e, u16 index); // original housha1(ENCNT_*, unsigned short), C++ linkage

// Encnt_Reset (0x0204363c, invented name): resets the encounter state for a new map (called by makemap_30).
extern "C" void Encnt_Reset(void);

#endif
