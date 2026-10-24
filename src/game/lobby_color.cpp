#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   isSpaceColorSlot (0x020b2560), isFinishedColorChoiceAllPlayers (0x020b2580)

// Lobby colour state (bss): the pointer at +4 leads to one signed byte per player (0 is free, 1 to 3 are the colours
// taken), the number of players is the byte at +0x3b of that block
extern u8 data_02181860[];

// isSpaceColorSlot(long) (0x020b2560): TRUE when the colour slot is still free
extern "C" BOOL isSpaceColorSlot(s32 slot);
ARM BOOL isSpaceColorSlot(s32 slot) {
    s8 *colors;

    colors = *(s8 **)(data_02181860 + 4);
    if (colors[slot] == 0) {
        return TRUE;
    }
    return FALSE;
}

// isFinishedColorChoiceAllPlayers() (0x020b2580): TRUE when every player has picked a colour
extern "C" BOOL isFinishedColorChoiceAllPlayers(void);
ARM BOOL isFinishedColorChoiceAllPlayers(void) {
    s32 taken;
    u32 i;
    s8 *colors;

    colors = *(s8 **)(data_02181860 + 4);
    taken = 1;
    i = 1;
    while (i < 4) {
        if (colors[i] != 0) {
            taken++;
        }
        i++;
    }
    if (taken == colors[0x3b]) {
        return TRUE;
    }
    return FALSE;
}
