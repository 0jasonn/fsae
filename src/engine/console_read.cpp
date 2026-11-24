#include "types.h"

int Stub_0200b120(void);

// Read at most the requested capacity, including a terminating CR or LF in the count.
extern "C" s32 func_0200b12c(void *self, u8 *buffer, u32 *count);
s32 func_0200b12c(void *self, u8 *buffer, u32 *count) {
    u32 index = 0;
    u32 capacity = *count;

    for (; index < capacity; index++) {
        s32 character = Stub_0200b120();
        u32 byte = (u32)character & 0xff;

        buffer[index] = (u8)character;
        if (byte == '\r' || byte == '\n') {
            *count = index + 1;
            break;
        }
    }
    return 0;
}
