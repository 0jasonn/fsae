#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   fsUpdateStatus (0x020a723c, invented name), clearSaveData(unsigned char) (0x020a72b0), fsFileCount() (0x020a72f0),
//   fsFileCheck(unsigned char) (0x020a7324)

// Save slot table (data_021350b0, 0x50 bytes per slot, 3 slots). The byte arrays below are the fields the file functions
// read, each indexed by slot * 0x50.
extern "C" s32 fsFileCheck(u8 slot);
extern "C" void clearSaveData(u8 slot);
extern "C" u8 fsFileCount(void);

s32 Knife_readMediaFlagged(u8 slot, u32 *block); // C++, defined in savemedia code

extern u8 data_021350b0[];   // slot block; +0x04 unknown, +0x08 u16 size of the saved data
extern u8 data_021350b8[];   // +0x08 of the slot block (u16 read by fsFileCheck)
extern u8 data_021350dc[];   // +0x2c of the slot block (flag set by clearSaveData)
extern u8 data_021350dd[];   // +0x2d of the slot block (flag set by clearSaveData)
extern s8 data_021350f7[];   // +0x47 of the slot block (status byte)

// fsUpdateStatus(unsigned char) (0x020a723c, invented name): reads the file status of a slot into the status byte,
// clearing the slot for the statuses 3, 4, 6 and 8
extern "C" void fsUpdateStatus(u8 slot);
ARM void fsUpdateStatus(u8 slot) {
    s32 status;
    s32 offset;

    slot &= 7;
    offset = slot * 0x50;
    status = Knife_readMediaFlagged(slot, (u32 *)(data_021350b0 + offset));
    switch (status) {
    case 3:
    case 4:
    case 6:
    case 8:
        clearSaveData(slot);
        break;
    }
    data_021350f7[offset] = status;
}

// clearSaveData(unsigned char) (0x020a72b0): clears a slot (masked to 0 to 7) and sets its two flags
ARM void clearSaveData(u8 slot) {
    s32 offset;

    slot &= 7;
    offset = slot * 0x50;
    func_02029a50(data_021350b0 + offset, 0x50);
    data_021350dc[offset] = 1;
    data_021350dd[offset] = 1;
}

// fsFileCount() (0x020a72f0): number of saved files (the three slot checks summed, truncated to a byte)
ARM u8 fsFileCount(void) {
    u8 count;

    count = fsFileCheck(0) + fsFileCheck(1);
    return (u8)(count + fsFileCheck(2));
}

// fsFileCheck(unsigned char) (0x020a7324): 1 when the slot (below 3) holds a file, 0 otherwise
ARM s32 fsFileCheck(u8 slot) {
    s32 offset;
    s8 status;

    if (slot < 3) {
        offset = slot * 0x50;
        status = data_021350f7[offset];
        if (status == 0x80 || status == 0) {
            if (*(u16 *)(data_021350b8 + offset) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
