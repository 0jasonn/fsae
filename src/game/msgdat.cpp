#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   Knife_MsgReadPtrFromID

// Marks the message data block as read for the given id; always returns 1
ARM void *Knife_MsgReadPtrFromID(void *dat, u16 id) {
    u8 *block;

    block = (u8 *)dat;
    *(u16 *)(block + 2) = id;
    block[0] = 1;
    return (void *)1;
}
