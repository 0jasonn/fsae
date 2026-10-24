#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

extern u8 data_0212c55c[];

// _get_subtask_data_size(long) (0x0209b714): size of entry index in the table at data_0212c55c.
ARM s32 _get_subtask_data_size(s32 index) {
    s32 *table = *(s32 **)data_0212c55c;

    return table[index + 1] - table[index];
}
