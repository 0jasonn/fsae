#include "engine/functions.h"
#include "engine/callees.h"
#include "global.h"
#include "types.h"
#include "engine/os_thread.h"

extern "C" void OS_InitContext(OsThreadRec *context, void (*func)(void), u32 stack);
extern "C" void OS_LoadContext(OsThreadRec *context);
extern "C" void func_020179c8(u32 arg);
extern "C" void Os_StartContext(OsThreadRec *context, u32 arg);

// Os_StartContext(context, arg) (0x02017970): when the scheduler block has an initial stack, sets the context up on it to
// run func_020179c8 with arg (flag 0x80 in the first word, arg at +4, state 1) and loads it. Without a stack, calls
// func_020179c8 with arg directly.
ARM void Os_StartContext(OsThreadRec *context, u32 arg) {
    u32 stack;
    u32 flags;

    stack = data_0212991c.initStack;
    if (stack != 0) {
        OS_InitContext(context, (void (*)(void))func_020179c8, stack);
        flags = *(u32 *)context | 0x80;
        *(u32 *)context = flags;
        *((u32 *)context + 1) = arg;
        context->state = 1;
        OS_LoadContext(context);
    } else {
        func_020179c8(arg);
    }
}
