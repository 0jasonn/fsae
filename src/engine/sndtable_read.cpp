#include "engine/functions.h"
#include "global.h"

extern "C" {
extern u8 *data_021848b0; // sound state pointer
s32 FS_SeekFile(void *file, s32 pos, s32 origin);
s32 FS_ReadFile(void *file, void *dst, s32 size);
}

// SndTable_ReadBlock: reads up to size bytes of the file block of table entry index into payload, starting offset bytes
// into the block. Each read is capped by the state's limit word (size when that is zero) and by what is left of the
// block. Returns the bytes read, or -1 when the index is out of range or a seek fails.
extern "C" s32 SndTable_ReadBlock(s32 index, void *payload, s32 size, s32 offset);
ARM s32 SndTable_ReadBlock(s32 index, void *payload, s32 size, s32 offset) {
    u8 *state;
    u8 *table;
    u8 *entry;
    s32 total;
    s32 limit;
    s32 chunk;
    s32 read;
    u8 *dst;

    state = data_021848b0;
    table = *(u8 **)(state + 0x90);
    if ((u32)index >= *(u32 *)(table + 0x8)) {
        return -1;
    }
    entry = table + 0xc + index * 0x10;
    limit = *(s32 *)(state + 0x9c);
    if (limit == 0) {
        limit = size;
    }
    dst = (u8 *)payload;
    total = 0;
    while (total < size) {
        chunk = size - total;
        if (chunk > limit) {
            chunk = limit;
        }
        if ((u32)chunk > (u32)(*(u32 *)(entry + 0x4) - offset)) {
            chunk = *(u32 *)(entry + 0x4) - offset;
        }
        if (chunk == 0) {
            break;
        }
        if (FS_SeekFile(state + 0x34, *(s32 *)entry + offset, 0) == 0) {
            return -1;
        }
        read = FS_ReadFile(state + 0x34, dst, chunk);
        if (read < 0) {
            return read;
        }
        total += read;
        offset += read;
        dst += read;
    }
    return total;
}
