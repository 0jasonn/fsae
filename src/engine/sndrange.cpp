#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"
#include "engine/sndlink.h"

// Range tree (provisional). A node has its key at +0, a child list at +0xc (the child list shares its words with the
// bounds, so the bounds are read by offset), the range [lo, hi) at +0x18 and +0x1c and a flags word at +0x20. The root
// list is data_02186000, its flag word data_02185ffc says whether the root has been initialised.
extern "C" {
extern SndList data_02186000;
extern u32 data_02185ffc;
}

// SndRangeTree_Find: returns the deepest node whose range contains value (searching the children of each matching node),
// or 0 when no node in the list contains it.
extern "C" u8 *SndRangeTree_Find(SndList *list, u32 value);
ARM u8 *SndRangeTree_Find(SndList *list, u32 value) {
    u8 *node;
    u8 *found;

    node = func_020c2064(list, 0);
    if (node != 0) {
        do {
            if (*(u32 *)(node + 0x18) <= value && value < *(u32 *)(node + 0x1c)) {
                found = SndRangeTree_Find((SndList *)(node + 0xc), value);
                if (found == 0) {
                    found = node;
                }
                return found;
            }
            node = func_020c2064(list, node);
        } while (node != 0);
    }
    return 0;
}

// SndRangeTree_ParentList: the child list of the node that contains the address of node (or the root list).
extern "C" SndList *SndRangeTree_ParentList(u8 *node);
ARM SndList *SndRangeTree_ParentList(u8 *node) {
    u8 *found;
    SndList *parent;

    found = SndRangeTree_Find(&data_02186000, (u32)node);
    parent = &data_02186000;
    if (found != 0) {
        parent = (SndList *)(found + 0xc);
    }
    return parent;
}

