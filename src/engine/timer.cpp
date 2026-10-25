#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Snapshot record: value/lastValue/limit are the live counters, mask selects the bits compared against limit.
typedef struct TimerSnapshot {
    u8 unk_00[0x18];
    u32 value;
    u32 lastValue;
    u32 limit;
    u32 snapshot;
    u32 delta;
    u32 mask;
    u8 unk_30[4];
    u32 maskedValue;
} TimerSnapshot;

extern "C" void Timer_Snapshot(TimerSnapshot *rec);

// Copies the previous value into snapshot, computes limit minus the masked value into delta, and saves the
// current value.
ARM void Timer_Snapshot(TimerSnapshot *rec) {
    rec->snapshot = rec->lastValue;
    rec->delta = rec->limit - (rec->value & rec->mask);
    rec->maskedValue = rec->value;
}
