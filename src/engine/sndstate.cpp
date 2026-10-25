#include "engine/functions.h"
#include "global.h"

extern "C" {
extern u8 *data_021848b0; // sound state pointer (shared with the crypto flag at the same address)
void *func_020c0650(void);
}

extern "C" u32 SndTable_GetWord14(s32 index);
extern "C" s32 SndList_GetEntryCount(void *list);

// SndState_GetBlockWord: returns the word at the offset stored in the block at state+0x98 (0 when that offset is 0).
extern "C" u32 SndState_GetBlockWord(void);
ARM u32 SndState_GetBlockWord(void) {
    u8 *block;
    u8 *word;
    u32 offset;

    block = *(u8 **)(data_021848b0 + 0x98);
    offset = *(u32 *)(block + 8);
    if (offset == 0) {
        word = 0;
    } else {
        word = block + offset;
    }
    if (word == 0) {
        return 0;
    }
    return *(u32 *)word;
}

// SndState_GetEntryCount: the entry count of the list selected by the object from func_020c0650. Returns 0 when there is no
// object or no entry.
extern "C" s32 SndState_GetEntryCount(void);
ARM s32 SndState_GetEntryCount(void) {
    void *obj;
    u32 value;

    obj = func_020c0650();
    if (obj == 0) {
        return 0;
    }
    value = SndTable_GetWord14(*(s32 *)obj);
    if (value == 0) {
        return 0;
    }
    return SndList_GetEntryCount((void *)value);
}

// SndTable_GetWord10: reads the word at +0x10 of entry index of the table at state+0x90 (0 when index is out of range).
extern "C" u32 SndTable_GetWord10(u32 index);
ARM u32 SndTable_GetWord10(u32 index) {
    u8 *table;

    table = *(u8 **)(data_021848b0 + 0x90);
    if (index >= *(u32 *)(table + 8)) {
        return 0;
    }
    return *(u32 *)(table + index * 16 + 0x10);
}
