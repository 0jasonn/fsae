#include "global.h"
#include "types.h"
#include "sdk/os/os_valarm.h"

void OS_CreateVAlarm(OsVAlarm *alarm) {
    alarm->handler = NULL;
    alarm->tag = 0;
    alarm->finished = 0;
}
