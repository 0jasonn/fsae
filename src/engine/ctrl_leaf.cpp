#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// ctrl_leaf: functions Ctrl_noopA (0x020bc1fc), Ctrl_lookupEntry (0x020bc51c), Ctrl_getFlagAdValue (0x020bc574) and
// Table_getEntry58 (0x020bc260), provisional names. Each function is in its own unit (the addresses are not contiguous).

// Ctrl_noopA() (0x020bc1fc, provisional name): does nothing
extern "C" void Ctrl_noopA(void);
ARM void Ctrl_noopA(void) {
}
