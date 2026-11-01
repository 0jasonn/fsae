#include "engine/functions.h"
#include "global.h"
#include "knife/subtask/subtask.h"

extern u8 data_0212c55c[];

// _get_subtask_data(long) (0x0209b700): entry index of the table at data_0212c55c
s32 _get_subtask_data(s32 index) {
    s32 *table = *(s32 **)data_0212c55c;

    return table[index];
}

// _get_subtask_data_size(long) (0x0209b714): size of entry index in the table at data_0212c55c.
s32 _get_subtask_data_size(s32 index) {
    s32 *table = *(s32 **)data_0212c55c;

    return table[index + 1] - table[index];
}

extern u8 data_0212c560[];

// _get_subtask_data_lang(long) (0x0209b734): entry index of the table at data_0212c560
s32 _get_subtask_data_lang(s32 index) {
    s32 *table = *(s32 **)data_0212c560;

    return table[index];
}

struct NNSG2dOamManagerInstance;

// _get_subtask_data_size_lang(long) (0x0209b748): size of entry index in the table at data_0212c560.
s32 _get_subtask_data_size_lang(s32 index) {
    s32 *table = *(s32 **)data_0212c560;

    return table[index + 1] - table[index];
}

// InitOamManager(NNSG2dOamManagerInstance*) (0x0209b768)
void InitOamManager(NNSG2dOamManagerInstance *manager) {
    func_020c34d0(manager);
    func_020c35a4(manager, 4, 0x7c, 1);
}
