#ifndef WIP_B_VGROUP_H
#define WIP_B_VGROUP_H

// VGroup module (src/wip/B/vgroup.cpp, vgroup_2.cpp): slot table and request queue shared by its functions.
#include "engine/functions.h"

// One VGroup slot (original name VGROUP_). The table starts at vgroupSlots; the line slots are from index 8 on.
typedef struct VGROUP_ {
    u8 state; // low 6 bits: index of the first slot of the group; bit 7 set while the group is in use
    u8 link;  // number of objects that reference this slot
    u8 id;    // group id (low byte of the u16 at offset 2)
    u8 count; // number of slots in the group (high byte of the u16 at offset 2)
} VGROUP_;

extern VGROUP_ vgroupSlots[];
extern u8 vgroupSlotsEnd[];   // end of the slot table (vgroupSlotsEnd)
extern VGROUP_ vgroupLines[]; // line slots, from index 8 (vgroupLines)
extern u32 vgroupQueue[];     // pending requests per slot (vgroupQueue)
extern u32 vgroupRequestTable[]; // request record per group id (vgroupRequestTable)
extern u8 vgroupIdTable[];    // id translation table (vgroupIdTable)

#endif
