#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"

// FsRom_Command(file, cmd) (0x02012810): cmd 1 gives 4; cmd 7 gives 9 when FSi_IsUnreadableRomOffset says so for the
// file's archive (and the first command word) and 0x101 otherwise;
// cmd 9 and 10 lock the ROM or switch to direct mode with the value and give 0. Other values give 0x102.
extern "C" s32 FsRom_Command(FSFile *file, s32 cmd);

s32 FsRom_Command(FSFile *file, s32 cmd) {
    switch (cmd) {
    case 9:
        CARD_LockRom((u16)data_021297b8.value);
        return 0;
    case 10:
        G3C_Direct1((u16)data_021297b8.value);
        return 0;
    case 7:
        if (FSi_IsUnreadableRomOffset(file->arc, file->command.a.value) != 0) {
            return 9;
        }
        return 0x101;
    case 1:
        return 4;
    default:
        return 0x102;
    }
}
