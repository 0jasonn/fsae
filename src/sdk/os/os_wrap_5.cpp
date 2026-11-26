#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_event.h"

// Os_WaitEventExWrap(event, pattern, mode) (0x02019e84): OS_WaitEventEx without clearing any bits.
u32 Os_WaitEventExWrap(OsEvent *event, u32 pattern, u32 mode) {
    return OS_WaitEventEx(event, pattern, mode, 0);
}
