#include "engine/functions.h"
#include "engine/entity.h"
#include "engine/scene_slot.h"
#include "global.h"

// GetNPC (0x0204f994) takes a free record of the 8-entry NPC slot table data_02134d30 and binds a new work to it.
// Returns the slot index, or 0xff when none is free.

// GetNPC (0x0204f994)
u8 GetNPC(u8 a, u8 b, u8 c) {
    NPC_WORK_ *end;
    NPC_WORK_ *slot;
    Entity *created;
    u8 index;

    slot = data_02134d30;
    end = data_02134d30 + 8;
    index = 0;
    while (slot < end) {
        if (slot->entity == NULL) {
            created = GetSetWork(a, b, c);
            if (created != NULL) {
                MIi_CpuClear16(0, slot, sizeof(NPC_WORK_));
                slot->entity = created;
                created->linkedEntity = (Entity *)slot;
                return index;
            }
        }
        slot = slot + 1;
        index = index + 1;
    }
    return 0xff;
}
