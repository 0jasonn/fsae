#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/lobby.h"

// Functions in this file (original names from the debug build):
//   update_change_filesel (0x020b3fcc)

// update_change_filesel() (0x020b3fcc): counts the timer of the lobby down. At 1 the display control register is set
// for the file select, at 0 the phase is set to 4 (parent) and the wait value 0x8007 is stored. Returns 0
extern "C" s32 update_change_filesel(void);
ARM s32 update_change_filesel(void) {
    LobbyState *lobby;

    lobby = *(LobbyState **)(data_02181860 + 4);
    lobby->timer = lobby->timer - 1;
    lobby = *(LobbyState **)(data_02181860 + 4);
    if (lobby->timer == 1) {
        u32 *displayControl = (u32 *)0x04001000;
        *displayControl = (*displayControl & ~0x1f00) | 0x1900;
    } else if (lobby->timer == 0) {
        if (lobby->isParent != 0) {
            data_0217d23c[0xd1] = 4;
        }
        lobby->unk_9c = 0x8007;
    }
    return 0;
}
