#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cellcommon.h"
#include "game/stopblock.h"

// Functions in this file (original names from the debug build):
//   StopBlockPreProcess

// Stop block tables (4-byte records, 0x30 entries each)
extern u8 data_02134f30[];
extern u8 data_02134ff0[];

// Registers the cell of every active stop block and marks it as done
ARM void StopBlockPreProcess(void) {
    STOPBLOCK_WORK_ *block;

    for (block = (STOPBLOCK_WORK_ *)data_02134f30; block < (STOPBLOCK_WORK_ *)data_02134ff0; block++) {
        if (block->state == 0xff) {
            RewCellOne(0x136, block->key & 0xfff, block->key & 0xc000);
            block->key |= 0x2000;
        }
    }
}
