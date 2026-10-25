#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" u16 *Wstr_FindChar(const u16 *str, s32 value);

// Finds the first halfword equal to value in a NUL-terminated string; a zero value finds the terminator. NULL when
// absent.
ARM u16 *Wstr_FindChar(const u16 *str, s32 value) {
    s32 wanted;
    u16 unit;

    wanted = value;
    unit = *str++;
    if (unit != 0) {
        do {
            if (unit == wanted) {
                return (u16 *)(str - 1);
            }
            unit = *str++;
        } while (unit != 0);
    }
    return (wanted != 0) ? NULL : (u16 *)(str - 1);
}
