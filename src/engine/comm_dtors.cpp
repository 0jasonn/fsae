#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Deleting destructors of Knife::Comm::ChildInfo (0x02093b34) and ParentInfo (0x02093b48): each frees the block.

extern "C" void *Knife_Comm_ChildInfo_dtor_ChildInfo(void *self);
ARM void *Knife_Comm_ChildInfo_dtor_ChildInfo(void *self) {
    operator delete(self);
    return self;
}

extern "C" void *Knife_Comm_ParentInfo_dtor_ParentInfo(void *self);
ARM void *Knife_Comm_ParentInfo_dtor_ParentInfo(void *self) {
    operator delete(self);
    return self;
}
