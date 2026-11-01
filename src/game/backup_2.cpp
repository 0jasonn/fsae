#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"
#include "game/savemedia.h"
#include "game/knife_power.h"
#include "game/backup.h"

// Save media (backup) unit 2. Address -> name:
//   0x020565e8 Knife_fatRead (original name, matches)

s32 Knife_fatRead(u16 slot, _SAVEHEADER *header) {
    s32 result;

    readFromSaveBuffer((u32 *)header, slot, 8);
    result = checkFatData(header);
    switch (result) {
    case 0:
        return 6;
    case 1:
        return 8;
    case 2:
        return 0;
    }
    return result;
}

// Save media unit 10 (module backup). Address -> name:
//   0x0205663c Knife_loadSaveFile (provisional, was Knife_loadSaveFile)

#define SAVE_LOAD_STATE (*(SaveLoadState *)&data_02171d10)

extern u32 data_021152d0; // slot whose file was loaded last
extern const char data_021152d4[]; // file path of slot 1
extern const char data_021152f0[]; // file path of slot 2

s32 Knife_readSaveFile(void *buffer, const char *path);

u32 Knife_loadSaveFile(u32 slot) {
    const char *path;
    Knife::PowerManager *manager;
    u32 bootType;
    u32 result;

    bootType = OS_GetBootType();
    result = 0;
    manager = (Knife::PowerManager *)Knife_GetPowerManager();
    if (bootType == 3) {
        if (slot == 1) {
            path = data_021152d4;
        } else if (slot == 2) {
            path = data_021152f0;
        }
        if (SAVE_LOAD_STATE.loaded != 0 && data_021152d0 == slot) {
            return 0;
        }
        data_021152d0 = slot;
        manager->lockSleep();
        result = Knife_readSaveFile((u8 *)KnifeApp_getInstance() + 0x4b0, path);
        manager->unlockSleep();
    }
    return result;
}
