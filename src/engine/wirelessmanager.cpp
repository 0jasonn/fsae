#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_d.h"
#include "engine/stub_noop_a_api.h"
#include "engine/stub_noop_b_api.h"
#include "engine/comm_parentinfo_api.h"
#include "engine/comm_childinfo_api.h"
#include "engine/wirelessmanager.h"

// Knife::Comm::WirelessManager constructor (0x02092334) and destructors (0x020923b4 and the deleting one at 0x020923fc).
// The manager holds 16 ParentInfo entries (0xd0 bytes, from +0xd04) and 15 ChildInfo entries (0x28 bytes, from +0x1a04).
// The constructor stores the vtable pointer at +0 and clears the allocator at +0x1c9c.

void *Knife_Comm_WirelessManager_WirelessManager(void *self) {
    WmDWork *wm;

    wm = (WmDWork *)self;
    *(void **)self = data_0211b0c4;
    Frame_LoopC7b8((u8 *)self + 0xd04, 16, 0xd0, (void *)Knife_Comm_ParentInfo_ParentInfo, (void *)Knife_Comm_WirelessManager_noop_020922ec);
    Frame_LoopC7b8((u8 *)self + 0x1a04, 15, 0x28, (void *)Knife_Comm_ChildInfo_ChildInfo, (void *)Knife_Comm_WirelessManager_noop_02092330);
    wm->allocator = NULL;
    return self;
}

// ~WirelessManager (0x020923b4): destroys the ChildInfo array and then the ParentInfo array. The dtors are empty.
void *Knife_Comm_WirelessManager_dtor_WirelessManager_0923b4(void *self) {
    Frame_LoopC868((u8 *)self + 0x1a04, 15, 0x28, (void *)Knife_Comm_WirelessManager_noop_02092330);
    Frame_LoopC868((u8 *)self + 0xd04, 16, 0xd0, (void *)Knife_Comm_WirelessManager_noop_020922ec);
    return self;
}

// Deleting destructor (0x020923fc): the same arrays, then the block is freed.
void *Knife_Comm_WirelessManager_dtor_WirelessManager_0923fc(void *self) {
    Frame_LoopC868((u8 *)self + 0x1a04, 15, 0x28, (void *)Knife_Comm_WirelessManager_noop_02092330);
    Frame_LoopC868((u8 *)self + 0xd04, 16, 0xd0, (void *)Knife_Comm_WirelessManager_noop_020922ec);
    operator delete(self);
    return self;
}
