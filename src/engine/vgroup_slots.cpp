#include "engine/functions.h"
#include "global.h"
#include "engine/vgroup_slots.h"

// VGroup slot functions, 0x0208121c to 0x0208130c. The halfword at offset 2 of a VGROUP_ holds the group id in its
// low byte and the slot count in its high byte (VGROUP_ declares them as two bytes; see the proposal in the report).

// setVGroup (0x0208121c): attaches a group to an object (sprite settings and the group index) and adds one link to each
// of its slots.
void setVGroup(Entity *e, VGROUP_ *group) {
    s32 count;
    u32 kind;

    kind = (group->state & 0x3f) << 4;
    e->unk_20 = kind;
    e->spriteSettings.b6 = kind >> 8;
    e->unk_53 = group->state & 0x3f;
    count = (*(u16 *)&group->id & 0xff00) >> 8;
    while (count-- > 0) {
        group->link++;
        group++;
    }
}

// createVGroup (0x02081288): makes a group of count slots from first, and queues the request of the group id.
void createVGroup(VGROUP_ *first, u16 id, u8 count) {
    u8 index;
    u8 i;
    volatile u32 dispcnt;

    index = ((u32)first - (u32)vgroupSlots) >> 2;
    for (i = 0; i < count; i++) {
        first[i].state = index | 0x80;
        first[i].link = 0;
        *(u16 *)&first[i].id = 0;
    }
    *(u16 *)&first->id = ((count << 8) & 0xff00) | (id & 0xff);
    dispcnt = *(volatile u32 *)0x04000000;
    dispcnt;
    vgroupQueue[index] = vgroupRequestTable[id];
}
