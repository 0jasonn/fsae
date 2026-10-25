#include "engine/functions.h"
#include "global.h"
#include "game/subtask_a.h"

// Character code to tile number helpers for the subtask text, 0x0209aeb8 and 0x0209af98. Both map 'a' to 'f' (0x61..0x66)
// to c + 3 and ' ' to 0, '-' to 0x55. The digits map to c - 0x1a (subtask_char_tile_num) or c + 0x26 (the _alt variant).

// subtask_char_tile_num (0x0209aeb8)
extern "C" u32 subtask_char_tile_num(u32 c);
ARM u32 subtask_char_tile_num(u32 c) {
    switch (c) {
    case 0x20:
        return 0;
    case 0x2d:
        return 0x55;
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
        return c - 0x1a;
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x66:
        return c + 3;
    default:
        return c;
    }
}

// subtask_char_tile_num_alt (0x0209af98)
extern "C" u32 subtask_char_tile_num_alt(u32 c);
ARM u32 subtask_char_tile_num_alt(u32 c) {
    switch (c) {
    case 0x20:
        return 0;
    case 0x2d:
        return 0x55;
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
        return c + 0x26;
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x66:
        return c + 3;
    default:
        return c;
    }
}
