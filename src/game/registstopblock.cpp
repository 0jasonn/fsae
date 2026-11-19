#include "engine/functions.h"
#include "global.h"
#include "game/stopblock.h"

extern STOPBLOCK_WORK_ data_02134f30[];
extern STOPBLOCK_WORK_ data_02134ff0[];
extern STOPBLOCK_WORK_ data_021350b0[];

// RegistStopBlock (0x0204e744): registers a stop block whose key has kind 6 and low byte 0x5c (first table) or 8
// (second table, which starts 0x30 records into the first one); returns 0 when registering failed, else 1.
int RegistStopBlock(u16 *key, u8 kind) {
    u16 word = *key;
    u8 group = (word >> 9) & 0xf;
    u8 low = word & 0x1ff;
    if (group == 6) {
        if (low == 0x5c) {
            if (sbRegistSub(key, kind, data_02134f30, data_02134ff0) != 0) {
                return 0;
            }
        }
        if (low == 8) {
            if (sbRegistSub(key, kind, data_02134f30 + 0x30, data_021350b0) != 0) {
                return 0;
            }
        }
    }
    return 1;
}
