#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// ctrl_leaf: functions Ctrl_noopA (0x020bc1fc), Ctrl_lookupEntry (0x020bc51c), Ctrl_getFlagAdValue (0x020bc574) and
// Table_getEntry58 (0x020bc260), provisional names. Each function is in its own unit (the addresses are not contiguous).

// Ctrl_lookupEntry(id) (0x020bc51c, provisional name): the entry of id from Fs_GetDirFileOffset
extern "C" void *Ctrl_lookupEntry(s32 id);
ARM void *Ctrl_lookupEntry(s32 id) {
    return Fs_GetDirFileOffset(id);
}

// Ctrl_getFlagAdValue(self) (0x020bc574, provisional name): 0x94 while the flag byte at +0xad is zero, otherwise 0
