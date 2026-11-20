#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// PlWorkClear (0x02054b64): clears the whole player work array (4 * 0x94 bytes) but keeps each player's colour index
// (bits 2..3 of paletteBits).
void PlWorkClear(void) {
    u8 color0 = playerWork[0].paletteBits.color;
    u8 color1 = playerWork[1].paletteBits.color;
    u8 color2 = playerWork[2].paletteBits.color;
    u8 color3 = playerWork[3].paletteBits.color;
    OSi_CpuClear32(0, playerWork, 0x250);
    playerWork[0].paletteBits.color = color0;
    playerWork[1].paletteBits.color = color1;
    playerWork[2].paletteBits.color = color2;
    playerWork[3].paletteBits.color = color3;
}
