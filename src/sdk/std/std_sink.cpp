#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/std/std_snprintf_api.h"

// string_put_char(sink, ch) (0x0201db90): writes one character when there is room; the cursor advances either way.
void string_put_char(StdStringSink *sink, char ch) {
    if (sink->remaining != 0) {
        *sink->cursor = ch;
        sink->remaining--;
    }
    sink->cursor++;
}

// string_fill_char(sink, ch, count) (0x0201dbbc): writes ch count times, as far as there is room; the cursor advances
// by the full count.
void string_fill_char(StdStringSink *sink, char ch, s32 count) {
    u32 i;
    u32 length;

    if (count <= 0) {
        return;
    }
    length = sink->remaining;
    if (length > count) {
        length = count;
    }
    for (i = 0; i < length; i++) {
        sink->cursor[i] = ch;
    }
    sink->remaining -= length;
    sink->cursor += count;
}

// string_put_string(sink, str, count) (0x0201dc10): copies count characters of str, as far as there is room; the cursor
// advances by the full count.
void string_put_string(StdStringSink *sink, const char *str, s32 count) {
    u32 i;
    u32 length;

    if (count <= 0) {
        return;
    }
    length = sink->remaining;
    if (length > count) {
        length = count;
    }
    for (i = 0; i < length; i++) {
        sink->cursor[i] = str[i];
    }
    sink->remaining -= length;
    sink->cursor += count;
}
