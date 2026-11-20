#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/table_entry.h"

// TODO(headers): this declaration of ResPlayer_AdvanceAndRefresh differs from the shared one;
// see the header restructure report.
extern "C" void ResPlayer_AdvanceAndRefresh(void *entry, s32 value);
// TODO(headers): this declaration of ResPlayer_SeekAndRefresh differs from the shared one;
// see the header restructure report.
extern "C" void ResPlayer_SeekAndRefresh(void *entry, s32 value);

// table_set: functions Table_setValueA (0x020bc280) and Table_setValueB (0x020bc2a8), provisional names. Each looks the
// index up with Table_getEntry58 and passes value to its own setter (ResPlayer_AdvanceAndRefresh and ResPlayer_SeekAndRefresh).

// Table_setValueA(self, index, value) (0x020bc280, provisional name): 0 when there is no entry, otherwise sets the
// entry through ResPlayer_AdvanceAndRefresh and returns 1
extern "C" s32 Table_setValueA(u8 *self, s32 index, s32 value);
s32 Table_setValueA(u8 *self, s32 index, s32 value) {
    void *entry;

    entry = Table_getEntry58(self, index);
    if (entry == NULL) {
        return 0;
    }
    ResPlayer_AdvanceAndRefresh(entry, value);
    return 1;
}

// Table_setValueB(self, index, value) (0x020bc2a8, provisional name): the same with ResPlayer_SeekAndRefresh
extern "C" s32 Table_setValueB(u8 *self, s32 index, s32 value);
s32 Table_setValueB(u8 *self, s32 index, s32 value) {
    void *entry;

    entry = Table_getEntry58(self, index);
    if (entry == NULL) {
        return 0;
    }
    ResPlayer_SeekAndRefresh(entry, value);
    return 1;
}
