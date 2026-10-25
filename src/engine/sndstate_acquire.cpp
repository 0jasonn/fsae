#include "engine/functions.h"
#include "global.h"

extern "C" {
u8 *func_020c05ec(s32 index);
u8 *func_020c0650(s32 index);
s32 func_020c0e50(u16 entryIndex, u32 flags, u32 size, s32 flag, u32 extra);
void *SndBank_AcquireSeqData(s32 index, u32 size, s32 flag);
void *SndBank_AcquireSeqDataB(s32 index, u32 size, s32 flag);
u32 SndTable_GetWord14(s32 index);
}

// func_020c0d6c: looks the index up in the 08 table (returns 2 when there is no entry). A non-zero result of
// func_020c0e50 is returned. Otherwise flag bit 0 selects SndBank_AcquireSeqData (6 when it fails) over the table word
// stored for the entry. The result goes to out when it is not null.
extern "C" s32 func_020c0d6c(s32 index, u32 flags, u32 size, s32 flag, u32 *out);
ARM s32 func_020c0d6c(s32 index, u32 flags, u32 size, s32 flag, u32 *out) {
    u8 *entry;
    s32 status;
    void *result;

    entry = func_020c05ec(index);
    if (entry == 0) {
        return 2;
    }
    status = func_020c0e50(*(u16 *)(entry + 0x4), flags, size, flag, 0);
    if (status != 0) {
        return status;
    }
    if ((flags & 1) != 0) {
        result = SndBank_AcquireSeqData(*(s32 *)entry, size, flag);
        if (result == 0) {
            return 6;
        }
    } else {
        result = (void *)SndTable_GetWord14(*(s32 *)entry);
    }
    if (out != 0) {
        *out = (u32)result;
    }
    return 0;
}

// SndState_AcquireAt0c: the same with the 0c table and flag bit 3, using SndBank_AcquireSeqDataB (7 when it fails).
extern "C" s32 SndState_AcquireAt0c(s32 index, u32 flags, u32 size, s32 flag, u32 *out);
ARM s32 SndState_AcquireAt0c(s32 index, u32 flags, u32 size, s32 flag, u32 *out) {
    u8 *entry;
    void *result;

    entry = func_020c0650(index);
    if (entry == 0) {
        return 3;
    }
    if ((flags & 8) != 0) {
        result = SndBank_AcquireSeqDataB(*(s32 *)entry, size, flag);
        if (result == 0) {
            return 7;
        }
    } else {
        result = (void *)SndTable_GetWord14(*(s32 *)entry);
    }
    if (out != 0) {
        *out = (u32)result;
    }
    return 0;
}
