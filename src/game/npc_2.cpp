#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   PutNPC

// Scene slot table: 0x14-byte records (data_02134d30), with the entity pointer of each record in fairySlots
extern u8 data_02134d30[];
extern u8 fairySlots[];

// Releases the entity of scene slot index (if any) and clears the slot record
ARM void PutNPC(u8 index) {
    u32 offset;
    Entity *entity;

    offset = index * 0x14;
    entity = *(Entity **)(fairySlots + offset);
    if (entity != 0) {
        PutObjWork(entity);
    }
    MIi_CpuClear16(0, data_02134d30 + offset, 0x14);
}
