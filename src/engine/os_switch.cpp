#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/os_switch_api.h"

extern "C" void OS_LoadContext(void *thread);

// Scheduler record at data_0212991c: the switch callback at +0, a busy word at +4, the pointer to the current thread
// (a pointer to a thread pointer) at +8, a ready half-word at +0x1e and the thread switched to at +0x20.
typedef struct ThreadSwitchState {
    void (*callback)(void *from, void *to);
    u32 busy;
    void **current;
    u8 unk_0c[0x12];
    u16 ready;
    void *next;
} ThreadSwitchState;

extern ThreadSwitchState data_0212991c;
extern u32 data_02129938[];

// Os_ThreadSwitch() (0x02017650): switches the thread when the scheduler is not busy and the system is ready. A thread
// that is not in state 2 is saved first (a nonzero save result returns to the saved thread). Then the callbacks at
// +0 of the scheduler record and at data_02129938[3] run with (from, to), and the thread is loaded.
void Os_ThreadSwitch(void) {
    u32 *threadBase;
    u16 ready;
    void *from;
    void *to;

    if (data_0212991c.busy != 0) {
        return;
    }
    ready = data_0212991c.ready;
    threadBase = data_02129938;
    if (ready != 0 || OS_GetProcMode() == 0x12) {
        *(u16 *)threadBase = 1;
        return;
    }
    from = *data_0212991c.current;
    to = OS_SelectThread();
    if (from == to || to == NULL) {
        return;
    }
    if (*(u32 *)((u8 *)from + 0x64) != 2) {
        if (OS_SaveContext(from) != 0) {
            return;
        }
    }
    if (data_0212991c.callback != NULL) {
        data_0212991c.callback(from, to);
    }
    if (threadBase[3] != 0) {
        ((void (*)(void *, void *))threadBase[3])(from, to);
    }
    data_0212991c.next = to;
    OS_LoadContext(to);
}
