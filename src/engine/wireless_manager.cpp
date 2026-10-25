#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/comm_parentinfo.h"
#include "engine/wireless_manager_d.h"

// WirelessManager singleton (0x020909c8) and its initializer with the allocator (0x02090a1c, 0x26c bytes). The object
// lives in bss at data_021770e0, its guard word is at data_021770bc + 4 (bit 0 set once constructed), and its
// destructor (0x020923b4) is registered with Chain_Push.

extern u32 data_021770bc[]; // guard word at +4 (bss)
extern u8 data_021770c4[];  // the handle passed to the exit registration (bss)
extern u8 data_021770e0[];  // the WirelessManager object (bss)

extern "C" void *Knife_Comm_WirelessManager_WirelessManager(void *self);
extern "C" void *Knife_Comm_WirelessManager_dtor_WirelessManager_0923b4(void *self);
extern "C" void Chain_Push(void *object, void *dtor, void *handle);
extern "C" void Knife_Comm_ChildInfo_cleanup(void *self);
extern "C" void MI_CpuFill8(void *dst, u32 value, u32 size);
extern "C" int WM_Init(void *sysWork, u32 dmaNo);

// The allocator the manager is initialized with (WirelessAllocator): slot 0 allocates, slot 1 frees. Pure virtual so
// no vtable is emitted.
class WirelessAllocatorIface {
public:
    virtual void *allocate(u32 size, u32 align) = 0;
    virtual void deallocate(void *block) = 0;
};

// func_020909c8 (0x020909c8, C++ linkage as declared in functions.h): returns the singleton, constructing it on the first
// call. The name is the dsd name for now; the original is a static local of WirelessManager::getInstance.
ARM void *func_020909c8(void) {
    if ((data_021770bc[1] & 1) == 0) {
        Knife_Comm_WirelessManager_WirelessManager(data_021770e0);
        Chain_Push(data_021770e0, Knife_Comm_WirelessManager_dtor_WirelessManager_0923b4, data_021770c4);
        data_021770bc[1] = data_021770bc[1] | 1;
    }
    return data_021770e0;
}

// WirelessManager::init(WirelessAllocator*, unsigned long) (0x02090a1c, no original name): stores the allocator, allocates
// the two buffers (0xf00 and 0x400 bytes, aligned to 0x20), starts the WM library with dmaNo and clears the manager
// state. FALSE on any failure, with the buffers freed.
extern "C" BOOL Knife_Comm_WirelessManager_init(void *self, void *allocatorPtr, u32 dmaNo);
ARM BOOL Knife_Comm_WirelessManager_init(void *self, void *allocatorPtr, u32 dmaNo) {
    WirelessManagerWork *wm;
    WirelessAllocatorIface *allocator;
    u8 *base;
    s32 i;

    wm = (WirelessManagerWork *)self;
    allocator = (WirelessAllocatorIface *)allocatorPtr;
    base = (u8 *)self;
    if (allocator == NULL) {
        return 0;
    }
    if (wm->allocator != NULL) {
        return 0;
    }
    wm->buf1 = allocator->allocate(0xf00, 0x20);
    if (wm->buf1 == NULL) {
        return 0;
    }
    wm->buf2 = allocator->allocate(0x400, 0x20);
    if (wm->buf1 == NULL) {
        allocator->deallocate(wm->buf1);
        wm->buf1 = NULL;
        return 0;
    }
    if (WM_Init(wm->buf1, dmaNo) != 0) {
        allocator->deallocate(wm->buf1);
        allocator->deallocate(wm->buf2);
        wm->buf1 = NULL;
        wm->buf2 = NULL;
        return 0;
    }
    wm->allocator = allocator;
    MI_CpuFill8(base + 0x20, 0, 0x70);
    MI_CpuFill8(base + 0x90, 0, 0x10);
    MI_CpuFill8(base + 0x1a0, 0, 0x40);
    MI_CpuFill8(base + 0x1e0, 0, 0x820);
    MI_CpuFill8(base + 0xa00, 0, 0xc0);
    MI_CpuFill8(base + 0xac0, 0, 0x200);
    MI_CpuFill8(base + 0xa0, 0, 0x100);
    MI_CpuFill8(wm->buf2, 0, 0x400);
    MI_CpuFill8(base + 0xcc0, 0, 0x44);
    MI_CpuFill8(base + 0x1c5c, 0, 0x40);
    base[0x1cb8] = 1;
    base[0x1ccc] = 1;
    *(s32 *)(base + 0x1ca8) = 0;
    *(s32 *)(base + 0x1cac) = 0;
    *(s32 *)(base + 0x1cb0) = 0;
    *(s32 *)(base + 0x1cb4) = 0;
    base[0x1cb9] = 0;
    *(s32 *)(base + 0x1cbc) = 0;
    *(s32 *)(base + 0x1cc4) = 0;
    *(s32 *)(base + 0x1cc8) = 0;
    *(s32 *)(base + 0x1cd4) = 0;
    *(s32 *)(base + 0x1cd8) = 0;
    base[0x1cdc] = 0;
    base[0x1cdd] = 0;
    *(s32 *)(base + 0x1ce4) = 0;
    *(s32 *)(base + 0x1ce8) = 0;
    *(s32 *)(base + 0x1cc0) = 100;
    *(u16 *)(base + 0x1cce) = 0;
    *(u16 *)(base + 0x1cd0) = 0;
    *(u16 *)(base + 0x1cde) = 0;
    *(u16 *)(base + 0x1ce0) = 0;
    for (i = 0; i < 16; i++) {
        ((Knife::Comm::ParentInfo *)(base + 0xd04 + i * 0xd0))->cleanup();
    }
    for (i = 0; i < 15; i++) {
        Knife_Comm_ChildInfo_cleanup(base + 0x1a04 + i * 0x28);
    }
    return 1;
}
