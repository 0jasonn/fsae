#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"

extern "C" {
u8 *func_020c0650(s32 index);
u32 SndTable_GetWord14(s32 index);
s32 func_020c1970(void *obj, u32 a, u32 b, u32 c, void *entry, void *owner, s32 index, s32 arg);
}

// SndState_StartEntryList: looks the index up in the 0c table (func_020c0650), takes the owner from the table word at
// that entry and the owner's list entry at arg. When all three exist, passes the entry's byte, halfword and byte, the
// entry, the owner, index and arg to func_020c1970. Returns 0 when one of the lookups fails.
extern "C" s32 SndState_StartEntryList(void *obj, s32 index, s32 arg);
ARM s32 SndState_StartEntryList(void *obj, s32 index, s32 arg) {
    u8 *entry;
    void *owner;
    u8 *listEntry;

    entry = func_020c0650(index);
    if (entry == 0) {
        return 0;
    }
    owner = (void *)SndTable_GetWord14(*(s32 *)entry);
    if (owner == 0) {
        return 0;
    }
    listEntry = (u8 *)SndList_GetEntry(owner, arg);
    if (listEntry == 0) {
        return 0;
    }
    return func_020c1970(obj, listEntry[9], *(u16 *)(listEntry + 4), listEntry[8], listEntry, owner, index, arg);
}
