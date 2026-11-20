#include "engine/functions.h"
#include "global.h"
#include "game/fs_api.h"

// Functions in this file (original names from the debug build):
//   fsCopyFile(unsigned char, unsigned char) (0x020a7370)

s32 Knife_writeMediaFlagged(u8 slot, const u32 *data); // C++, defined in backup.cpp

#include "engine/multisio_save.h"

// fsCopyFile(unsigned char, unsigned char) (0x020a7370): copies the save slot srcSlot to dstSlot when the source has no
// status, then marks the destination as a copy (status 7) when it already has one
void fsCopyFile(u8 srcSlot, u8 dstSlot) {
    srcSlot &= 7;
    dstSlot &= 7;
    fsSaveBegin();
    fsUpdateStatus(srcSlot);
    if (data_021350b0[srcSlot].status == 0) {
        Knife_writeMediaFlagged(dstSlot, (const u32 *)&data_021350b0[srcSlot]);
    }
    fsUpdateStatus(dstSlot);
    if (data_021350b0[dstSlot].status != 0) {
        data_021350b0[dstSlot].status = 7;
    }
    fsSaveEnd();
}
