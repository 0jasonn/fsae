#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Knife::Comm::ChildInfo::ChildInfo (0x02092310): sets the vtable and cleans up. Plain function taking self.

extern char data_0211b0b4[]; // ChildInfo vtable (rodata)

extern "C" void Knife_Comm_ChildInfo_cleanup(void *self);

extern "C" void *Knife_Comm_ChildInfo_ChildInfo(void *self);
ARM void *Knife_Comm_ChildInfo_ChildInfo(void *self) {
    *(void **)self = data_0211b0b4;
    Knife_Comm_ChildInfo_cleanup(self);
    return self;
}
