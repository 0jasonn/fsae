#include "engine/functions.h"
#include "global.h"
#include "game/g_game_start.h"

// Functions in this file (original names from the debug build):
//   BootErrorInfoTask (0x020c83b8)
// (disp_A_button, savefile_error_* and terminateInfo_* are not finished yet)

// BootErrorInfoTask() (0x020c83b8): calls the boot error handler for the state byte at data_0212c500
ARM void BootErrorInfoTask(void) {
    data_021271cc[data_0212c500[0]]();
}
