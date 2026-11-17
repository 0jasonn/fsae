#include "engine/functions.h"
#include "knife/comm/wireless_manager.h"
#include "knife/comm/wireless_manager_methods.h"

// WirelessManager::getFrameFlag (0x020921b0, no original name): the byte at 0x1cdd that update clears each frame.
extern "C" u8 Knife_Comm_WirelessManager_getFrameFlag(void *self);
u8 Knife_Comm_WirelessManager_getFrameFlag(void *self) {
    return ((WirelessManagerWork *)self)->unk_1cdd;
}

int Knife_Comm_WirelessManager_getAID(void *self) {
    WirelessManagerWork *manager;
    s32 state;

    manager = (WirelessManagerWork *)self;
    state = manager->state;
    WmInterruptSection section;
    if (state != 8 && state != 11) {
        return -1;
    }
    return WM_GetAID();
}
