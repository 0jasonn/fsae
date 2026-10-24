#include "engine/functions.h"
#include "global.h"
#include "game/g_game_start.h"

// Functions in this file (original names from the debug build):
//   TerminateInfoInfoTask (0x020c8998)

// TerminateInfoInfoTask() (0x020c8998): calls the terminate handler for the state byte at data_0212c500
ARM void TerminateInfoInfoTask(void) {
    data_0212720c[data_0212c500[0]]();
}
