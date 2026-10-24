#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"
#include "game/g_game_start.h"

// Functions in this file (original names from the debug build):
//   subTask_game_start_reload (0x020c70ac). subTask_game_start_init_vram (0x020c70c8) is parked in scratch/agentG/nonmatching.

extern u8 data_0217d23c[];

// subTask_game_start_reload (0x020c70ac): sets the state bytes of the subtask (1 and 2)
ARM void subTask_game_start_reload(void) {
    data_0217d23c[0xd0] = 1;
    data_0217d23c[0xd1] = 2;
}
