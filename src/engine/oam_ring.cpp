#include "engine/functions.h"
#include "engine/oam_ring.h"

// OamRing_ResetAll (OamRing_ResetAll): hides every OBJ entry of the three banks (attribute 0 becomes 0xc0) and marks all
// OBJ slots and affine groups free (0xffff in the tag tables).
void OamRing_ResetAll(void *oam) {
    MIi_CpuClear16(0xc0, OamRing_attrs0, 0x400);
    MIi_CpuClear16(0xc0, OamRing_attrs1, 0x400);
    MIi_CpuClear16(0xc0, OamRing_attrs2, 0x400);
    MIi_CpuClear16(0xffff, OamRing_banks, 0x100);
    MIi_CpuClear16(0xffff, OamRing_banks1, 0x100);
    MIi_CpuClear16(0xffff, OamRing_banks2, 0x100);
    MIi_CpuClear16(0xffff, OamRing_affineTags0, 0x40);
    MIi_CpuClear16(0xffff, OamRing_affineTags1, 0x40);
    MIi_CpuClear16(0xffff, OamRing_affineTags2, 0x40);
}
