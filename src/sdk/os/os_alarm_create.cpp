#include "global.h"
#include "types.h"
#include "sdk/os/os_alarm.h"

void OS_CreateAlarm(OsAlarm *alarm) {
    alarm->handler = NULL;
    alarm->tag = 0;
}
