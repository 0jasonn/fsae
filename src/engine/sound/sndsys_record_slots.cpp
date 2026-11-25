#include "engine/sound/sndstate_lookup_api.h"
#include "engine/sound/sndsys_api.h"
#include "engine/sound/sndtable_api.h"

extern "C" {
u8 *func_020c05dc(void);
void SndTable_SetWord4(s32 index, s32 value);
}

// Initialize the 32 slot table entries, and start every configured slot when a record is supplied.
BOOL func_020c1660(void *record) {
    s32 slot;
    u8 *entry;
    s32 i;
    s32 count;

    func_020c05dc();
    slot = 0;
    do {
        entry = SndState_LookupAt18(slot);
        if (entry != 0) {
            SndTable_SetHalf0(slot, entry[0]);
            SndTable_SetWord4(slot, *(u16 *)(entry + 2));
            if (*(u32 *)(entry + 4) != 0 && record != 0) {
                count = entry[0];
                i = 0;
                if (count > 0) {
                    do {
                        if (SndSys_StartSlot(slot, record, *(u32 *)(entry + 4)) == 0) {
                            return 0;
                        }
                        i++;
                    } while (i < entry[0]);
                }
            }
        }
        slot++;
    } while (slot < 0x20);
    return 1;
}
