#include "engine/functions.h"
#include "global.h"
#include "game/fs_api.h"

// Functions in this file (original names from the debug build):
//   fsDeleteFile(unsigned char) (0x020a73ec)

void DeleteSaveFile(u8 slot); // C++
extern "C" void clearSaveData(u8 slot);

// fsDeleteFile(unsigned char) (0x020a73ec): deletes the file of a slot and clears the slot
void fsDeleteFile(u8 slot) {
    fsSaveBegin();
    DeleteSaveFile(slot);
    clearSaveData(slot);
    fsSaveEnd();
}
