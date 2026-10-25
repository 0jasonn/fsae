#include "engine/functions.h"
#include "engine/callees.h"
#include "global.h"
#include "types.h"
#include "engine/os_thread.h"

extern "C" void OSi_InsertLinkToQueue(OsThreadRec *thread, OsThreadRec *queue);
extern "C" void func_02017650(void);
extern "C" void Os_LinkThreadAndFlush(OsThreadRec *thread);

// Os_LinkThreadAndFlush(thread) (0x02017a5c): with interrupts off, links thread to the current thread's queue (when thread
// is not NULL) and clears the state word of the current thread, then runs func_02017650 and restores the interrupts.
ARM void Os_LinkThreadAndFlush(OsThreadRec *thread) {
    u32 state;
    OsThreadRec *current;

    state = OS_DisableInterrupts();
    current = *data_0212991c.curHolder;
    if (thread != NULL) {
        current->link = thread;
        OSi_InsertLinkToQueue(thread, current);
    }
    current->state = 0;
    func_02017650();
    OS_RestoreInterrupts(state);
}
