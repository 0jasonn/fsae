#include "engine/functions.h"
#include "global.h"
#include "object/tama11.h"

// VGroup module (vgroup), 0x02080e58 onward. A VGroup slot is four bytes; the table holds 0x40 of them.
//   VGroupInit (0x02080e58): clears the slot table and the request queue, then marks slots 0-7 and 0x2b-0x3f free.
//   VGroupManager (0x02080ed4): takes the first queued request whose slot is ready (MdmaCheck), loads its graphics
//     from the Zelda resource into VRAM, then either frees its slot or, when bit 31 of its header is set, requeues it.

typedef struct VGroupSlot {
    u8 state; // 0xff when free; bit 6 is cleared when a request is finished
    u8 link;  // 0xff when free
    u8 unk_2;
    u8 unk_3;
} VGroupSlot;

extern VGroupSlot vgroupSlots[];
extern u32 vgroupQueue[];
extern const u8 vgroupIdTable[];
extern "C" s32 GetResTranslateID(u16 id, const void *table, s32 count);
BOOL MdmaCheck(void);

// VGroupInit (0x02080e58)
ARM void VGroupInit(void) {
    u8 i;

    func_02029a50(vgroupSlots, 0x100);
    func_02029a50(vgroupQueue, 0x100);
    for (i = 0; i < 8; i++) {
        vgroupSlots[i].state = 0xff;
        vgroupSlots[i].link = 0xff;
    }
    for (i = 0x2b; i < 0x40; i++) {
        vgroupSlots[i].state = 0xff;
        vgroupSlots[i].link = 0xff;
    }
}
