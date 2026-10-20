#include "engine/functions.h"
#include "global.h"
#include "engine/vgroup.h"
#include "object/tama11.h"

// VGroup module, continued: 0x02081160 (PutVGroup) to 0x02081360.
//   PutVGroup (0x02081160): releases the object's group: each slot of the group loses one link.
//   VGroupLoadWait (0x020811a8): true while the group's graphics are still loading.
//   GetVgRemain (0x020811c0): longest run of free line slots.
//   setVGroup (0x0208121c): attaches a group to an object and adds one link to each of its slots.
//   createVGroup (0x02081288): makes a group of count slots from first, and queues its request.
//   countVGroupLine (0x02081318): total slots of the request chain for an id.
//   actorDispatch (0x02081360): runs the handler for the action, then the shared update.

extern u8 data_0212c4b8;
extern const EntityFunc actorStateTable[];

// PutVGroup (0x02081160)
ARM void PutVGroup(Entity *e) {
    VGROUP_ *slot;
    u8 id;

    id = e->unk_53;
    if (id == 0) {
        return;
    }
    slot = &vgroupSlots[id];
    if ((slot->state & 0x3f) != id) {
        return;
    }
    do {
        if (slot->link != 0) {
            slot->link--;
        }
        slot++;
    } while ((slot->state & 0x3f) == id);
}

// VGroupLoadWait (0x020811a8)
ARM u32 VGroupLoadWait(Entity *e) {
    return vgroupSlots[e->unk_53].state & 0x40;
}

// GetVgRemain (0x020811c0)
ARM u32 GetVgRemain(void) {
    VGROUP_ *line;
    u32 best;
    u8 run;

    best = 0;
    line = vgroupLines;
    do {
        if (line->link == 0) {
            run = 0;
            do {
                line++;
                run++;
            } while (line->link == 0);
            if (best < run) {
                best = run;
            }
        }
        line++;
    } while (line < (VGROUP_ *)vgroupSlotsEnd);
    return best;
}

