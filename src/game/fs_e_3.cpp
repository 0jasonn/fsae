#include "engine/functions.h"
#include "global.h"

// Functions in this file (invented name for fsCreateFile, original names for the rest):
//   fsCreateFile (0x020a7480), fsSaveBegin (0x020a74cc, empty hook), fsSaveEnd (0x020a74d0, empty hook),
//   fsLoadFiles() (0x020a74d4)

extern "C" void fsUpdateStatus(u8 slot);
extern "C" s32 Save4SwordsFile(u8 flags);
extern "C" void fsCreateFile(u8 slot);
extern "C" void fsSaveBegin(void);
extern "C" void fsSaveEnd(void);
extern "C" void fsLoadFiles(void);

extern u8 data_021350dc[];   // +0x2c of the slot block
extern u8 data_021350dd[];   // +0x2d of the slot block

// fsCreateFile(unsigned char) (0x020a7480, invented name): sets the two flags of a slot, writes the file with the 0x80
// bit set and updates the status
ARM void fsCreateFile(u8 slot) {
    s32 offset;

    offset = slot * 0x50;
    data_021350dc[offset] = 1;
    data_021350dd[offset] = 1;
    fsSaveBegin();
    slot |= 0x80;
    Save4SwordsFile(slot);
    fsUpdateStatus(slot);
    fsSaveEnd();
}

// fsSaveBegin() (0x020a74cc): empty hook before a save operation
ARM void fsSaveBegin(void) {
}

// fsSaveEnd() (0x020a74d0): empty hook after a save operation
ARM void fsSaveEnd(void) {
}

// fsLoadFiles() (0x020a74d4): refreshes the status of the three slots
ARM void fsLoadFiles(void) {
    fsSaveBegin();
    fsUpdateStatus(0);
    fsUpdateStatus(1);
    fsUpdateStatus(2);
    fsSaveEnd();
}
