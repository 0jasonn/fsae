#include "engine/functions.h"
#include "global.h"
#include "engine/vgroup_slots.h"

// GetVGroup (0x02081088): attaches the object to the slot already holding the id, or reserves a run of free line slots
// for it. Returns 0 on success and 0xff when no run of free slots fits.
u8 GetVGroup(Entity *e, u16 id) {
    VGROUP_ *slot;
    VGROUP_ *line;
    u8 count;
    u8 start;

    slot = vgroupSlots;
    do {
        if ((*(u16 *)&slot->id & 0xff) == id) {
            setVGroup(e, slot);
            return 0;
        }
        slot++;
    } while (slot < (VGROUP_ *)vgroupSlotsEnd);
    count = countVGroupLine(id);
    line = vgroupLines;
    do {
        if (line->link == 0) {
            for (start = 0; start < count; start++) {
                if (line[start].link != 0) {
                    break;
                }
            }
            if (start == count) {
                createVGroup(line, id, count);
                setVGroup(e, line);
                return 0;
            }
        }
        line++;
    } while (line < (VGROUP_ *)vgroupSlotsEnd);
    return 0xff;
}
