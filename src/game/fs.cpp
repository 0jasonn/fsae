#include "engine/functions.h"
#include "global.h"
#include "game/fs_api.h"

// Functions in this file (original names from the debug build):
//   fsUpdateStatus (0x020a723c, invented name), clearSaveData(unsigned char) (0x020a72b0), fsFileCount() (0x020a72f0),
//   fsFileCheck(unsigned char) (0x020a7324)

// Save slot table (data_021350b0, 0x50 bytes per slot, 3 slots; MultiSioEntry in engine/multisio_save.h).
extern "C" void clearSaveData(u8 slot);

s32 Knife_readMediaFlagged(u8 slot, u32 *block); // C++, defined in savemedia code

#include "engine/multisio_save.h"

// fsUpdateStatus(unsigned char) (0x020a723c, invented name): reads the file status of a slot into the status byte,
// clearing the slot for the statuses 3, 4, 6 and 8
void fsUpdateStatus(u8 slot) {
    s32 status;

    slot &= 7;
    status = Knife_readMediaFlagged(slot, (u32 *)&data_021350b0[slot]);
    switch (status) {
    case 3:
    case 4:
    case 6:
    case 8:
        clearSaveData(slot);
        break;
    }
    data_021350b0[slot].status = status;
}

// clearSaveData(unsigned char) (0x020a72b0): clears a slot (masked to 0 to 7) and sets its two flags
void clearSaveData(u8 slot) {
    slot &= 7;
    MemClearFast(&data_021350b0[slot], 0x50);
    data_021350b0[slot].unk_2c = 1;
    data_021350b0[slot].unk_2d = 1;
}

// fsFileCount() (0x020a72f0): number of saved files (the three slot checks summed, truncated to a byte)
u8 fsFileCount(void) {
    u8 count;

    count = fsFileCheck(0) + fsFileCheck(1);
    return (u8)(count + fsFileCheck(2));
}

// fsFileCheck(unsigned char) (0x020a7324): 1 when the slot (below 3) holds a file, 0 otherwise
s32 fsFileCheck(u8 slot) {
    s8 status;

    if (slot < 3) {
        status = data_021350b0[slot].status;
        if (status == 0x80 || status == 0) {
            if (data_021350b0[slot].str08[0] != 0) {
                return 1;
            }
        }
    }
    return 0;
}
