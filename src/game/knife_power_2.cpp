#include "engine/functions.h"
#include "global.h"
#include "game/knife_power.h"

// Functions in this file (original names from the debug build):
//   Knife::PowerManager::lockSleep (0x020c8314), Knife::PowerManager::unlockSleep (0x020c8340)

namespace Knife {

// Knife::PowerManager::lockSleep() (0x020c8314): raises the sleep lock count with the interrupt master enable off
ARM void PowerManager::lockSleep(void) {
    u16 ime;

    ime = *(volatile u16 *)0x04000208;
    *(volatile u16 *)0x04000208 = 0;
    sleepLockCount++;
    *(volatile u16 *)0x04000208;
    *(volatile u16 *)0x04000208 = ime;
}

// Knife::PowerManager::unlockSleep() (0x020c8340): lowers the sleep lock count with the interrupt master enable off
ARM void PowerManager::unlockSleep(void) {
    u16 ime;

    ime = *(volatile u16 *)0x04000208;
    *(volatile u16 *)0x04000208 = 0;
    sleepLockCount--;
    *(volatile u16 *)0x04000208;
    *(volatile u16 *)0x04000208 = ime;
}

}
