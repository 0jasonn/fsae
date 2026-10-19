#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Save buffer access and NAND helpers. Address -> name (original names):
//   0x02056b40 NAND_CreateDirectory
//   0x02056d00 ReadSaveBufferDword
//   0x02056ddc ProgramSaveBufferDwordEx
// The save buffer is the u16 table at KnifeApp + 0x4b0, four halfwords per dword index.

ARM void ProgramSaveBufferDwordEx(u16 index, u16 *data) {
    u16 base = index * 4;
    u32 i;

    for (i = 0; i < 4; i++) {
        *(u16 *)((u8 *)KnifeApp_getInstance() + 0x4b0 + base * 2 + i * 2) = data[i];
    }
}
