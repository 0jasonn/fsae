#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

extern u8 data_0212c560[];

// _get_subtask_data_lang(long) (0x0209b734): entry index of the table at data_0212c560
ARM s32 _get_subtask_data_lang(s32 index) {
    s32 *table = *(s32 **)data_0212c560;

    return table[index];
}
