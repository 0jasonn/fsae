#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"

extern "C" {
u32 SndTable_GetWord10(u32 index);
s32 func_020c08cc(s32 index, void *payload, u32 size, s32 flag);
void *func_020c0b20(void *record, u32 size, void *callback, void *data, s32 index2);
void DC_StoreRange(void *start, u32 size);
}

// func_020c1014: makes a payload of the table size at index (word at +0x10 of the table entry) in the record. The record
// is the last argument. Returns the payload, or 0 when the size or the record is missing or the payload cannot be set up.
extern "C" void *func_020c1014(s32 index, void *callback, void *data, s32 index2, void *record);
ARM void *func_020c1014(s32 index, void *callback, void *data, s32 index2, void *record) {
    u32 size;
    void *payload;

    size = SndTable_GetWord10(index);
    if (size == 0) {
        return 0;
    }
    if (record == 0) {
        return 0;
    }
    payload = func_020c0b20(record, size + 0x20, callback, data, index2);
    if (payload == 0) {
        return 0;
    }
    if (func_020c08cc(index, payload, size, 0) != (s32)size) {
        return 0;
    }
    DC_StoreRange(payload, size);
    return payload;
}
