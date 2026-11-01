#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/comm_dtors_api.h"

// Deleting destructors of Knife::Comm::ChildInfo (0x02093b34) and ParentInfo (0x02093b48): each frees the block.

void *Knife_Comm_ChildInfo_dtor_ChildInfo(void *self) {
    operator delete(self);
    return self;
}

void *Knife_Comm_ParentInfo_dtor_ParentInfo(void *self) {
    operator delete(self);
    return self;
}
