#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wip_a_decls.h"

// Processes one entry: NULL walks the whole table through Entries_ProcessAll. A finished or mode-less entry fails with
// -1; kind 1 is done; state 1 runs the timer step and retires the entry, the other states settle to 0. A failing timer
// step marks the entry finished and returns -1.
extern "C" s32 Entry_Update(u8 *entry);

ARM s32 Entry_Update(u8 *entry) {
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
