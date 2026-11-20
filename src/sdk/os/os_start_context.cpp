#include "engine/functions.h"
#include "sdk/callees.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_thread.h"
#include "sdk/os/os_thread_exit_api.h"

extern "C" void OS_InitContext(OsThreadRec *context, void (*func)(void), u32 stack);
extern "C" void OS_LoadContext(OsThreadRec *context);
extern "C" void Os_StartContext(OsThreadRec *context, u32 arg);

// Os_StartContext(context, arg) (0x02017970): when the scheduler block has an initial stack, sets the context up on it to
// run OSi_RunThreadExitHook with arg (flag 0x80 in the first word, arg at +4, state 1) and loads it. Without a stack,
// calls the hook directly.
void Os_StartContext(OsThreadRec *context, u32 arg) {
    u32 stack;
    u32 flags;

    stack = data_0212991c.initStack;
    if (stack != 0) {
        OS_InitContext(context, (void (*)(void))OSi_RunThreadExitHook, stack);
        flags = *(u32 *)context | 0x80;
        *(u32 *)context = flags;
        *((u32 *)context + 1) = arg;
        context->state = 1;
        OS_LoadContext(context);
    } else {
        OSi_RunThreadExitHook(arg);
    }
}

// Provisional name. Run the current thread's exit hook once, then release the thread.
void OSi_RunThreadExitHook(u32 arg) {
    OsThreadRec *thread = *data_0212991c.curHolder;
    void (*hook)(u32) = thread->exitHook;

    if (hook != NULL) {
        thread->exitHook = NULL;
        hook(arg);
        OS_DisableInterrupts();
    }
    Os_ExitCurrentThread();
}
