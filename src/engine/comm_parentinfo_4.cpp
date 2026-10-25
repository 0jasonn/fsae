#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/comm_parentinfo.h"

// Knife::Comm::ParentInfo::ParentInfo (0x020922f0): sets the vtable and cleans up. Plain function taking self.

extern char data_0211b0a4[]; // ParentInfo vtable (rodata)

extern "C" void *Knife_Comm_ParentInfo_ParentInfo(void *self);
ARM void *Knife_Comm_ParentInfo_ParentInfo(void *self) {
    Knife::Comm::ParentInfo *info;

    info = (Knife::Comm::ParentInfo *)self;
    info->vtbl = (void *)data_0211b0a4;
    info->cleanup();
    return self;
}
