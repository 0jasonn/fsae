#include "engine/functions.h"
#include "global.h"
#include "engine/vgroup.h"
#include "object/tama11.h"

// VGroup module, continued: 0x02081318 (countVGroupLine) and 0x02081360 (actorDispatch).
//   PutVGroup (0x02081160): releases the object's group: each slot of the group loses one link.
//   VGroupLoadWait (0x020811a8): true while the group's graphics are still loading.
//   GetVgRemain (0x020811c0): longest run of free line slots.
//   setVGroup (0x0208121c): attaches a group to an object and adds one link to each of its slots.
//   createVGroup (0x02081288): makes a group of count slots from first, and queues its request.
//   countVGroupLine (0x02081318): total slots of the request chain for an id.
//   actorDispatch (0x02081360): runs the handler for the action, then the shared update.

extern u8 data_0212c4b8;
extern const EntityFunc actorStateTable[];

// countVGroupLine (0x02081318)
ARM u8 countVGroupLine(u16 id) {
    u32 *record;
    u8 total;

    total = 0;
    record = (u32 *)vgroupRequestTable[id] - 2;
    do {
        record += 2;
        total += (record[1] + 0x1ff) >> 9;
    } while (record[0] & 0x80000000);
    return total;
}

// actorDispatch (0x02081360): an action handler from actorStateTable, then func_020857c8. Same shape as Throw.
ARM void actorDispatch(Entity *e) {
    if (data_0212c4b8 == 0) {
        actorStateTable[e->action](e);
    }
    func_020857c8(e);
}
