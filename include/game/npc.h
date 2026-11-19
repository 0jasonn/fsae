#ifndef WIP_C_NPC_H
#define WIP_C_NPC_H

#include "engine/entity.h"

#include "engine/scene_slot.h" // struct NPC_WORK_ (the records of the NPC slot table data_02134d30)

typedef s32 (*NpcScriptFunc)(NPC_WORK_ *npc);

// Helpers called by the script opcodes (not named yet)
void ScriptJump(NPC_WORK_ *npc, const void *target);

#endif
