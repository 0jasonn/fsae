#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/message.h"

// Functions in this file (original names from the debug build):
//   telopFrame

// Writes the frame tiles of the telop window; type 1 has no top rows, types 2 and 3 add one or two more
ARM void telopFrame(s8 type, u16 *tiles) {
    int i;

    switch (type) {
    case 3:
        tiles[0] = 0x59;
        tiles[1] = 0x5a;
        tiles[0x17] = 0x5d;
        tiles -= 0x20;
        /* fallthrough */
    case 2:
        tiles[0] = 0x57;
        tiles[1] = 0x58;
        tiles[0x17] = 0x5d;
        tiles -= 0x20;
        /* fallthrough */
    case 1:
        break;
    default:
        return;
    }
    tiles[0] = 0x45b;
    for (i = 0; i < 0x16; i++) {
        tiles[i + 1] = 0x5b;
    }
    tiles[0x17] = 0x5c;
}
