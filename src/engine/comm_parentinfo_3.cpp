#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/comm_parentinfo.h"

// Knife::Comm::ParentInfo::cleanup (0x0209096c) and decrementTTL (0x0209099c): cleanup marks the slot empty and clears
// the bss description block; decrementTTL counts the time to live down and cleans up when it runs out.

extern "C" void MI_CpuFill8(void *dst, u32 value, u32 size); // 0x02015b94, the byte fill of the SDK

namespace Knife {
namespace Comm {

// ParentInfo::cleanup() (0x0209096c)
ARM void ParentInfo::cleanup(void) {
    emptyFlag = 1;
    MI_CpuFill8((u8 *)this + 0x4, 0, 0xc0);
    field_c8 = 0;
    ttl = 0;
}

// ParentInfo::decrementTTL() (0x0209099c): nothing for an empty slot
ARM void ParentInfo::decrementTTL(void) {
    if (emptyFlag != 0) {
        return;
    }
    ttl = ttl - 1;
    if (ttl > 0) {
        return;
    }
    cleanup();
}

}
}
