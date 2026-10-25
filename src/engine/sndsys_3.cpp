#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"

extern "C" {
void *func_020c0b20(void *a, void *b, void *callback, s32 c, s32 d);
void *SndHeap_CreateRecord(void *obj, void *arg);
void func_020c0058(void);
extern u8 data_02184304[]; // slot table, 0x24 bytes per slot
}

// Entry created by func_020c0b20. The sub-object at +0x14 is passed to SndHeap_CreateRecord.
typedef struct SndStartEntry {
    /* 00 */ u8 unk_00[8];
    /* 08 */ void *handle; // result of SndHeap_CreateRecord
    /* 0c */ s32 unk_0c;
    /* 10 */ s32 slotIndex;
    /* 14 */ u8 unk_14[4];
} SndStartEntry;

// SndSys_StartSlot: creates an entry (callback func_020c0058), fills in the slot index, takes a handle from
// SndHeap_CreateRecord and registers the entry in slot slotIndex of data_02184304. Returns 1 on success, 0 otherwise.
extern "C" s32 SndSys_StartSlot(s32 slotIndex, void *arg1, void *arg2);
ARM s32 SndSys_StartSlot(s32 slotIndex, void *arg1, void *arg2) {
    SndStartEntry *entry;
    void *handle;

    entry = (SndStartEntry *)func_020c0b20(arg1, (u8 *)arg2 + 0x14, (void *)func_020c0058, 0, 0);
    if (entry == 0) {
        return 0;
    }
    entry->unk_0c = 0;
    entry->slotIndex = slotIndex;
    entry->handle = 0;
    handle = SndHeap_CreateRecord(entry->unk_14, arg2);
    if (handle == 0) {
        return 0;
    }
    entry->handle = handle;
    SndList_Append((SndList *)(data_02184304 + slotIndex * 0x24 + 0xc), (u8 *)entry);
    return 1;
}
