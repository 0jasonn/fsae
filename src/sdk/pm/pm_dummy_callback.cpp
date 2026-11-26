#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pm/pm.h"

// PMi_DummyCallback(result, out) (0x0201c848): stores the result through the argument when one was given.
void PMi_DummyCallback(u32 result, u32 *out) {
    if (out != NULL) {
        *out = result;
    }
}
