#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// PlWorkClear (0x02054b64): clears the whole player work array (4 * 0x94 bytes) but keeps each player's colour index
// (bits 2..3 of paletteBits).
void PlWorkClear(void) {
    u32 color0 = ((u32)playerWork[0].paletteBits << 28) >> 30;
    u32 color1 = ((u32)playerWork[1].paletteBits << 28) >> 30;
    u32 color2 = ((u32)playerWork[2].paletteBits << 28) >> 30;
    u32 color3 = ((u32)playerWork[3].paletteBits << 28) >> 30;
    OSi_CpuClear32(0, playerWork, 0x250);
    playerWork[0].paletteBits = (playerWork[0].paletteBits & ~0xc) | ((color0 << 30) >> 28);
    playerWork[1].paletteBits = (playerWork[1].paletteBits & ~0xc) | ((color1 << 30) >> 28);
    playerWork[2].paletteBits = (playerWork[2].paletteBits & ~0xc) | ((color2 << 30) >> 28);
    playerWork[3].paletteBits = (playerWork[3].paletteBits & ~0xc) | ((color3 << 30) >> 28);
}
