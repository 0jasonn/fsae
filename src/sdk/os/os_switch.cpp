#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_switch_api.h"
#include "sdk/os/os_thread.h"

// Os_ThreadSwitch() (0x02017650): switches the thread when the scheduler is not disabled and not inside an interrupt
// handler (otherwise it only flags the reschedule in data_02129938). A thread that is not in state 2 is saved first (a
// nonzero save result returns to the saved thread). Then the scheduler block's callback and the thread system's switch
// callback run with (from, to), and the thread is loaded.
void Os_ThreadSwitch(void) {
    OsThreadInfo *info;
    u16 ready;
    OsThread *from;
    OsThread *to;

    if (data_0212991c.busy != 0) {
        return;
    }
    ready = data_0212991c.ready;
    info = &data_02129938;
    if (ready != 0 || OS_GetProcMode() == 0x12) {
        info->needReschedule = 1;
        return;
    }
    from = *data_0212991c.curHolder;
    to = OS_SelectThread();
    if (from == to || to == NULL) {
        return;
    }
    if (from->state != 2) {
        if (OS_SaveContext(from) != 0) {
            return;
        }
    }
    if (data_0212991c.switchCallback != NULL) {
        data_0212991c.switchCallback(from, to);
    }
    if (info->switchCallback != NULL) {
        info->switchCallback(from, to);
    }
    data_0212991c.current = to;
    OS_LoadContext(to);
}
