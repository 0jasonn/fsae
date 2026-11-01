#ifndef GAME_TAKARA_H
#define GAME_TAKARA_H

#include "engine/entity.h"

// Treasure chest table (module takara), 32 entries: id (cell key), handler index (low 5 bits) and flags.
typedef struct TakaraEntry {
    u16 id;          // 00, 0xffff marks a free entry
    u8 handlerIndex; // 02, low 5 bits index data_02116800
    u8 flags;        // 03, 1 once the entry is in use
} TakaraEntry;

#endif
