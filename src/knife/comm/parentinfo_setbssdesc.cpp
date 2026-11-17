#include "engine/functions.h"
#include "knife/comm/comm_parentinfo.h"
#include "knife/comm/wm_bssdesc.h"

// Knife::Comm::ParentInfo::setBssDesc(WMBssDesc const*, int) (0x02090868, plain symbol): cleans the entry, copies the
// scanned beacon description into the bss block that follows the vtable, marks the entry as filled and starts its
// time to live (180). The bss block (WMBssDesc, 0xc0 bytes at 0x04) is not a field of ParentInfo yet: proposed.

void Knife_Comm_ParentInfo_setBssDesc(void *self, const WMBssDesc *bssDesc, s32 level) {
    Knife::Comm::ParentInfo *info = (Knife::Comm::ParentInfo *)self;

    info->cleanup();
    *(WMBssDesc *)((u8 *)self + 4) = *bssDesc;
    info->field_c8 = level;
    info->ttl = 0xb4;
    info->emptyFlag = 0;
}
