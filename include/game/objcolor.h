#ifndef GAME_OBJCOLOR_H
#define GAME_OBJCOLOR_H

#include "engine/entity.h"

// One record of the object colour table at set58_bodyState: 16 records of 4 bytes. refCount counts the users of the
// slot, id is the colour id it holds (0xff when empty) and count is the number of slots the colour takes.
typedef struct OC_CTRL_ {
    u8 refCount;
    u8 id;
    u8 count;
    u8 unk_3;
} OC_CTRL_;

#endif
