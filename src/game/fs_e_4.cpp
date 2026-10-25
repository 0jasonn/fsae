#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   fsCopyFile(unsigned char, unsigned char) (0x020a7370)

extern "C" void fsSaveBegin(void);
extern "C" void fsSaveEnd(void);
extern "C" void fsUpdateStatus(u8 slot);
extern "C" void fsCopyFile(u8 srcSlot, u8 dstSlot);
s32 Knife_writeMediaFlagged(u8 slot, const u32 *data); // C++, defined in backup.cpp

extern u8 data_021350b0[];   // slot block, 0x50 bytes per slot
extern s8 data_021350f7[];   // +0x47 of the slot block (status byte)

// fsCopyFile(unsigned char, unsigned char) (0x020a7370): copies the save slot srcSlot to dstSlot when the source has no
// status, then marks the destination as a copy (status 7) when it already has one
ARM void fsCopyFile(u8 srcSlot, u8 dstSlot) {
    s32 srcOffset;
    s32 dstOffset;

    srcSlot &= 7;
    dstSlot &= 7;
    fsSaveBegin();
    fsUpdateStatus(srcSlot);
    srcOffset = srcSlot * 0x50;
    if (data_021350f7[srcOffset] == 0) {
        Knife_writeMediaFlagged(dstSlot, (const u32 *)(data_021350b0 + srcOffset));
    }
    fsUpdateStatus(dstSlot);
    dstOffset = dstSlot * 0x50;
    if (data_021350f7[dstOffset] != 0) {
        data_021350f7[dstOffset] = 7;
    }
    fsSaveEnd();
}
