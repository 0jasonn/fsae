#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/snd/snd_alarm.h"

// SND_AlarmInit() (0x0201b700): clears the handler, argument and id of all eight alarm slots.
void SND_AlarmInit(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        data_0212b880[i].handler = NULL;
        data_0212b880[i].arg = NULL;
        data_0212b880[i].id = 0;
    }
}

// SNDi_IncAlarmId(alarmNo) (0x0201b738): bumps the generation id of an alarm slot so stale notifications are ignored.
void SNDi_IncAlarmId(s32 alarmNo) {
    SndAlarmSlot *slot = &data_0212b880[alarmNo];

    slot->id++;
}

// SNDi_CallAlarmHandler(alarm) (0x0201b758): the low byte of the word picks the slot and the next byte must equal the
// slot's current id; then the slot's handler is called with its argument.
void SNDi_CallAlarmHandler(s32 alarm) {
    SndAlarmSlot *slot = &data_0212b880[alarm & 0xff];

    if (((alarm >> 8) & 0xff) != slot->id) {
        return;
    }
    if (slot->handler == NULL) {
        return;
    }
    slot->handler(slot->arg);
}
