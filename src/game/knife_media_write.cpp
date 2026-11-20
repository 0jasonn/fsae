#include "engine/functions.h"
#include "game/rankingsave.h"
#include "game/savemedia.h"
#include "global.h"
#include "knife/app/knife_manual.h"
#include "knife/app/knife_power.h"

extern const char data_02115310[];
extern const char data_0211532c[];
extern const char data_02115340[];
extern const char data_0211535c[];
extern const char data_02115378[];
s32 Knife_checkFileSpace(s32 fileSize, const char *path);
s32 NAND_CreateDirectory(const char *path);
extern "C" s32 NAND_SaveFile(const char *path, void *buffer, u32 size);

s32 Knife_mediaWrite(void) {
    Knife::PowerManager *manager;
    u32 bootType;
    s32 result;

    manager = (Knife::PowerManager *)Knife_GetPowerManager();
    bootType = OS_GetBootType();
    if (bootType == 3) {
        manager->lockSleep();
        result = Knife_checkFileSpace(0x800, data_02115310);
        if (result != 0) {
            manager->unlockSleep();
            return result;
        }
        NAND_CreateDirectory(data_0211532c);
        result = NAND_SaveFile(data_02115340, (u8 *)KnifeApp_getInstance() + 0x4b0, 0x800);
        if (result != 0) {
            switch (result) {
            case 0xa:
                manager->unlockSleep();
                return 0xa;
            case 0xe:
                manager->unlockSleep();
                return 0xe;
            default:
                break;
            }
        }
        result = Knife_checkFileSpace(0x800, data_0211535c);
        if (result != 0) {
            manager->unlockSleep();
            return result;
        }
        result = NAND_SaveFile(data_02115378, (u8 *)KnifeApp_getInstance() + 0x4b0, 0x800);
        if (result != 0) {
            switch (result) {
            case 0xa:
                manager->unlockSleep();
                return 0xa;
            case 0xe:
                manager->unlockSleep();
                return 0xe;
            default:
                break;
            }
        }
        manager->unlockSleep();
    }
    return 0;
}
