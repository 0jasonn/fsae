#ifndef SDK_SND_SND_ALARM_H
#define SDK_SND_SND_ALARM_H

// TwlSDK SND alarms (snd_alarm.c): handlers the ARM7 sound driver triggers through PXI tag 7.
#include "types.h"

// One alarm slot: handler, argument and a generation id (0xc bytes).
typedef struct SndAlarmSlot {
    void (*handler)(void *arg); // 0x00
    void *arg;                  // 0x04
    u8 id;                      // 0x08
} SndAlarmSlot;

extern SndAlarmSlot data_0212b880[8];

extern "C" {
void SND_AlarmInit(void);
void SNDi_IncAlarmId(s32 alarmNo);
void SNDi_CallAlarmHandler(s32 alarm);
}

#endif
