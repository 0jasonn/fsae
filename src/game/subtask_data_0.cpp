#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

extern u8 data_0212c55c[];

// _get_subtask_data(long) (0x0209b700): entry index of the table at data_0212c55c
ARM s32 _get_subtask_data(s32 index) {
    s32 *table = *(s32 **)data_0212c55c;

    return table[index];
}
