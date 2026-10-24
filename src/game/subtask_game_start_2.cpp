#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"
#include "game/g_game_start.h"

// Functions in this file (original names from the debug build):
//   subTask_game_start_end (0x020c754c)

extern u8 data_0217a258[];

// subTask_game_start_end (0x020c754c): frees the four subtask slots, the object info blocks and the two cell blocks
// of the game start work.
ARM void subTask_game_start_end(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        subTask_free_slot(i);
    }
    subTask_free_objinfo((OBJInfo *)data_0217a258);
    subTask_free_objinfo((OBJInfo *)data_02186fdc);
    func_0208e188(data_02186fdc->cells);
    func_0208e188(data_02186fdc->buffer600);
    func_0209bee4();
}
