#include "engine/string16_copy.h"

u16 *func_0200a3c8(u16 *dst, const u16 *src) {
    u16 *cursor = dst;
    while ((*cursor++ = *src++) != 0) {
    }
    return dst;
}
