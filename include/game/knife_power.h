#ifndef WIP_G_KNIFE_POWER_H
#define WIP_G_KNIFE_POWER_H

#include "types.h"

namespace Knife {

// Knife::PowerManager (0x0c bytes plus the vtable pointer): keeps the screen power and sleep-lock state of the
// game. The vtable (data_021271c4) has two slots, the complete and the deleting destructor.
class PowerManager {
public:
    PowerManager(void);
    virtual ~PowerManager(void);
    void initialize(void);
    void finalize(void);
    s32 isActive(void);
    void update(void);
    void lockSleep(void);
    void unlockSleep(void);

    /* 04 */ u8 active; // set to 1 by initialize, cleared by finalize
    /* 08 */ s32 sleepLockCount; // raised by lockSleep, lowered by unlockSleep
    /* 0c */ u8 unk_0c; // set to 1 by finalize
    /* 0d */ u8 unk_0d[4]; // cleared by finalize
};

}

#endif
