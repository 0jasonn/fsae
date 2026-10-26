#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// ctrl_leaf: functions Ctrl_noopA (0x020bc1fc), Ctrl_lookupEntry (0x020bc51c), Ctrl_getFlagAdValue (0x020bc574) and
// Table_getEntry58 (0x020bc260), provisional names. Each function is in its own unit (the addresses are not contiguous).

typedef struct CtrlLeafFlags {
    u8 unk_00[0xad];
    u8 flagAd;         // 0xad
} CtrlLeafFlags;

extern "C" s32 Ctrl_getFlagAdValue(CtrlLeafFlags *self);
ARM s32 Ctrl_getFlagAdValue(CtrlLeafFlags *self) {
    s32 value = 0x94;
    if (self->flagAd != 0) {
        value = 0;
    }
    return value;
}
