#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/timer_advance.h"
#include "engine/entry_update_api.h"

// Entry record (0x4c bytes) walked by Entries_ProcessAll and processed by Entry_Update. Its timer fields match
// TimerAdvanceRec.
typedef struct EntryFlagWord {
    u32 unk_b0 : 2;
    u32 kind : 3;            // bits 2..4: kind 1 means done
    u32 unk_b5 : 2;
    u32 mode : 3;            // bits 7..9: must be nonzero
    u32 unk_b10 : 22;
} EntryFlagWord;

typedef struct EntryStateWord {
    u32 state : 3;           // low three bits: the entry state
    u32 unk_b3 : 29;
} EntryStateWord;

typedef struct EntryRec {
    u8 unk_00[4];
    EntryFlagWord flags;     // 0x04
    EntryStateWord stateWord; // 0x08
    u8 unk_0c;
    u8 finished;             // 0x0d: set when the timer step reports an error
    u8 unk_0e[0x0a];
    u32 value;               // 0x18
    u8 unk_1c[0x0c];
    s32 delta;               // 0x28
    u8 unk_2c[0x20];
} EntryRec;

// Processes one entry: NULL walks the whole table through Entries_ProcessAll. A finished or mode-less entry fails with
// -1; kind 1 is done; state 1 runs the timer step and retires the entry, the other states settle to 0. A failing timer
// step marks the entry finished and returns -1.

s32 Entry_Update(u8 *entry) {
    EntryRec *rec;
    s32 timerResult;

    rec = (EntryRec *)entry;
    if (rec == NULL) {
        return Entries_ProcessAll();
    }
    if (rec->finished != 0 || rec->flags.mode == 0) {
        return -1;
    }
    if (rec->flags.kind == 1) {
        return 0;
    }
    if (rec->stateWord.state >= 3) {
        rec->stateWord.state = 2;
    }
    if (rec->stateWord.state == 2) {
        rec->delta = 0;
    }
    if (rec->stateWord.state != 1) {
        rec->stateWord.state = 0;
        return 0;
    }
    timerResult = Timer_Advance((TimerAdvanceRec *)rec, NULL);
    if (timerResult != 0) {
        s32 finishedFlag = 1;
        rec->finished = finishedFlag;
        rec->delta = 0;
        return finishedFlag - 2;
    }
    rec->stateWord.state = 0;
    rec->value = 0;
    rec->delta = 0;
    return 0;
}
