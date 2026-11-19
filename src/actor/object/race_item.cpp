#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"
#include "actor/object/race_item_actions.h"

// Race item actor (module race_item). Address -> name:
//   0x02067b60 race_item (original name)

extern const u8 data_02115b14[];  // item id by number of bits collected in the group
extern const u32 data_02115b28[]; // mask of the type bits of each group of four

// Once the race flag of its type is set, records the item as taken, shows the smoke and gives the item whose id
// depends on how many items of its group were taken so far.
void race_item(Entity *e) {
    u8 group;

    e->action = 1;
    if ((em12_typeMasks[0] & (1 << e->type2)) == 0) {
        return;
    }
    em12_typeMasks[4] |= 1 << e->type2;
    KemuriSet(e);
    group = (u32)e->type2 >> 2;
    ItemSet(e, data_02115b14[CountBits(em12_typeMasks[4] & data_02115b28[group])]);
    PutObjWork(e);
}
