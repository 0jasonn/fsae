#include "engine/functions.h"
#include "global.h"
#include "game/knife_comm_icon.h"

// Knife::Comm::WirelessIcon constructor (0x0209a63c): sets the vtable and clears the state through finalize.
// The bx lr at 0x0209a65c between this and the dtor is not named yet.

extern u8 data_0211c140[];
extern "C" void Knife_Comm_WirelessIcon_finalize(WirelessIcon *self);

// WirelessIcon::WirelessIcon() (0x0209a63c)
extern "C" WirelessIcon *Knife_Comm_WirelessIcon_WirelessIcon(WirelessIcon *self);
ARM WirelessIcon *Knife_Comm_WirelessIcon_WirelessIcon(WirelessIcon *self) {
    *(u8 **)self = data_0211c140;
    Knife_Comm_WirelessIcon_finalize(self);
    return self;
}
