#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Work block whose pointer at +0x20 addresses seven words of archive slots.
typedef struct FsWork {
    u8 unk_00[0x20];
    u32 *slots;
} FsWork;

extern "C" void Fs_ResetArchiveSlots(FsWork *self);
extern "C" s32 FS_IsArchiveTableLoaded(void);

// Fs_ResetArchiveSlots(self) (0x02011ffc): checks the archive table, then clears the seven slot words.
ARM void Fs_ResetArchiveSlots(FsWork *self) {
    u32 *slots;

    slots = self->slots;
    FS_IsArchiveTableLoaded();
    slots[0] = 0;
    slots[1] = 0;
    slots[2] = 0;
    slots[3] = 0;
    slots[4] = 0;
    slots[5] = 0;
    slots[6] = 0;
}
