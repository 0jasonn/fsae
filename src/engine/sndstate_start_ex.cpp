#include "engine/functions.h"
#include "global.h"

extern "C" void *func_020c0650(void *arg);
extern "C" u32 SndTable_GetWord14(void *table);
extern "C" void *SndList_GetEntry(void *owner, s32 index);
extern "C" BOOL func_020c1970(u8 *self, s32 a1, s32 a2, s32 a3, void *entry, u32 word, void *arg4, s32 arg5);

// SndState_StartEntryEx (provisional name, SndState_StartEntryEx): finds the list entry for arg4 and arg5 and starts it with
// func_020c1970. Negative a1..a3 are replaced by the matching bytes and halfword of the entry (a2 halfword at +4, a1 byte at
// +9, a3 byte at +8). Returns 0 when a lookup fails.
extern "C" BOOL SndState_StartEntryEx(u8 *self, s32 a1, s32 a2, s32 a3, void *arg4, s32 arg5);
ARM BOOL SndState_StartEntryEx(u8 *self, s32 a1, s32 a2, s32 a3, void *arg4, s32 arg5) {
    void *table;
    u32 word;
    void *entry;

    table = func_020c0650(arg4);
    if (table == NULL) {
        return 0;
    }
    word = SndTable_GetWord14(*(void **)table);
    if (word == 0) {
        return 0;
    }
    entry = SndList_GetEntry((void *)word, arg5);
    if (entry == NULL) {
        return 0;
    }
    if (a3 < 0) {
        a3 = *((u8 *)entry + 0x8);
    }
    if (a2 < 0) {
        a2 = *(u16 *)((u8 *)entry + 0x4);
    }
    if (a1 < 0) {
        a1 = *((u8 *)entry + 0x9);
    }
    return func_020c1970(self, a1, a2, a3, entry, word, arg4, arg5);
}
