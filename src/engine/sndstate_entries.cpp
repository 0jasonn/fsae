#include "engine/functions.h"
#include "global.h"
#include "engine/sndstate_entries_api.h"

extern "C" u8 *SndState_LookupAt1c(u32 id);
extern "C" s32 func_020c0d6c(u32 word, u32 byte, u32 a1, u32 one, u32 zero);
extern "C" s32 SndState_AcquireAt0c(u32 word, u32 byte, u32 a1, u32 one, u32 zero);
extern "C" s32 func_020c0e50(u32 word, u32 byte, u32 a1, u32 one, u32 zero);

// SndState_RunEntries (provisional name, SndState_RunEntries): walks the entry table of id (count at +0, 8-byte entries from +4)
// and dispatches each entry by its kind byte (0 func_020c0d6c, 1 func_020c0e50, 2 func_020c0f90, 3 SndState_AcquireAt0c). The first
// nonzero result is returned; 1 when the table is missing, 0 when no entry reports one.
s32 SndState_RunEntries(u32 id, u32 a1) {
    u8 *table;
    u8 *entry;
    u32 i;
    s32 result;

    table = SndState_LookupAt1c(id);
    if (table == NULL) {
        return 1;
    }
    i = 0;
    if (i < *(u32 *)table) {
        do {
            entry = table + 4 + i * 8;
            switch (entry[0]) {
            case 0:
                result = func_020c0d6c(*(u32 *)(entry + 4), entry[1], a1, 1, 0);
                if (result != 0) {
                    return result;
                }
                break;
            case 3:
                result = SndState_AcquireAt0c(*(u32 *)(entry + 4), entry[1], a1, 1, 0);
                if (result != 0) {
                    return result;
                }
                break;
            case 1:
                result = func_020c0e50(*(u32 *)(entry + 4), entry[1], a1, 1, 0);
                if (result != 0) {
                    return result;
                }
                break;
            case 2:
                result = func_020c0f90(*(u32 *)(entry + 4), entry[1], a1, 1, 0);
                if (result != 0) {
                    return result;
                }
                break;
            }
            i++;
        } while (i < *(u32 *)table);
    }
    return 0;
}
