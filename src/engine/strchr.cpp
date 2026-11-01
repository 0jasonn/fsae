#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/strchr_api.h"

// Finds the first byte equal to value in a NUL-terminated string. A zero value finds the terminator; otherwise NULL
// is returned when the byte is not present.
u8 *Str_FindChar(const u8 *str, s32 value) {
    u8 wanted;
    u8 byte;

    wanted = (u8)value;
    byte = *str++;
    if (byte != 0) {
        do {
            if (byte == wanted) {
                return (u8 *)(str - 1);
            }
            byte = *str++;
        } while (byte != 0);
    }
    return (wanted != 0) ? NULL : (u8 *)(str - 1);
}
