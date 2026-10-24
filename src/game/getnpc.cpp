#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

// GetNPC (0x0204f994) takes a free record of the 8-entry NPC slot table data_02134d30 and binds a new work to it.
// Returns the slot index, or 0xff when none is free.

typedef struct NpcSlot {
    /* 00 */ u8 unk_00[0xc];
    /* 0c */ Entity *entity;
    /* 10 */ u8 unk_10[4];
} NpcSlot;

extern u8 data_02134d30[];

// GetNPC (0x0204f994)
ARM u8 GetNPC(u8 a, u8 b, u8 c) {
    NpcSlot *end;
    NpcSlot *slot;
    Entity *created;
    u8 index;

    slot = (NpcSlot *)data_02134d30;
    end = (NpcSlot *)(data_02134d30 + 0xa0);
    index = 0;
    while (slot < end) {
        if (slot->entity == NULL) {
            created = GetSetWork(a, b, c);
            if (created != NULL) {
                MIi_CpuClear16(0, slot, 0x14);
                slot->entity = created;
                created->linkedEntity = (Entity *)slot;
                return index;
            }
        }
        slot = (NpcSlot *)((u8 *)slot + 0x14);
        index = index + 1;
    }
    return 0xff;
}
