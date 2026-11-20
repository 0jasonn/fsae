#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/timer_advance.h"

extern "C" void _Z13Stub_020056e8v(u32 value, s32 *ptr);
// TODO(headers): this declaration of Timer_Snapshot differs from the shared one; see the header restructure report.
extern "C" void Timer_Snapshot(void *rec);

// Advances a timer record: delta = snapshot - lastValue. When delta is nonzero it is stored, the empty stub is called
// unless flag bit 12 is set, the callback runs and its nonzero result is returned, otherwise delta is added to the live
// value. Timer_Snapshot runs in every path.

s32 Timer_Advance(TimerAdvanceRec *rec, s32 *deltaOut) {
    s32 *out = deltaOut;
    TimerAdvanceRec *timer = rec;
    s32 result;
    s32 delta;

    delta = timer->snapshot - timer->lastValue;
    if (delta != 0) {
        timer->delta = delta;
        if (((timer->flags << 19) >> 31) == 0) {
            _Z13Stub_020056e8v(timer->lastValue, &timer->delta);
        }
        result = timer->callback(timer->owner, timer->lastValue, &timer->delta, timer->callbackArg);
        if (out != NULL) {
            *out = timer->delta;
        }
        if (result != 0) {
            return result;
        }
        timer->value += timer->delta;
    }
    Timer_Snapshot(timer);
    return 0;
}
