#include "engine/functions.h"
#include "sdk/card/card.h"
#include "knife/comm/wireless_manager.h"
#include "knife/comm/wireless_manager_methods.h"

// Updates the recipient mask and packet data while interrupts are disabled.
void Knife_Comm_WirelessManager_setSendPacket(void *self, const void *packet) {
    WmInterruptSection section;
    WirelessManagerWork *manager;
    u16 aids;

    manager = (WirelessManagerWork *)self;
    if (manager->state != 8 && manager->state != 11) {
        return;
    }
    aids = (u16)(WM_GetConnectedAIDs() | 1);
    *(u16 *)((u8 *)self + 0xa0) = aids;
    *(u16 *)((u8 *)self + 0xa2) = 0;
    MI_CpuCopy8(packet, (u8 *)self + 0xa4, (u32)(*(s32 *)((u8 *)self + 0x1cd4) - 4));
}
