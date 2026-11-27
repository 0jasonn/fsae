#include "engine/multisio_save.h"
#include "game/fs_api.h"

extern s32 Knife_writeMediaFlagged(u8 slot, const u32 *data);

s32 Save4SwordsFile(u8 flags) {
    u8 saveFlags = flags & 0xc0;
    flags &= 7;
    u8 slot = flags;
    u8 status = 0x21;
    s32 result;
    if (saveFlags == 0) {
        fsSaveBegin();
    }
    data_021350b0[slot].unk_04 = status;
    data_021350b0[slot].status = (s8)(status - 0xa1);
    result = Knife_writeMediaFlagged(slot, (const u32 *)&data_021350b0[slot]);
    if (saveFlags == 0) {
        fsSaveEnd();
    }
    return result;
}
