#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

extern u8 data_0212c560[];
extern "C" void func_020c34d0(void *oam);
extern "C" void func_020c35a4(void *oam, s32 a, s32 b, s32 c);
struct NNSG2dOamManagerInstance;

// _get_subtask_data_size_lang(long) (0x0209b748): size of entry index in the table at data_0212c560.
ARM s32 _get_subtask_data_size_lang(s32 index) {
    s32 *table = *(s32 **)data_0212c560;

    return table[index + 1] - table[index];
}

// InitOamManager(NNSG2dOamManagerInstance*) (0x0209b768)
ARM void InitOamManager(NNSG2dOamManagerInstance *manager) {
    func_020c34d0(manager);
    func_020c35a4(manager, 4, 0x7c, 1);
}
