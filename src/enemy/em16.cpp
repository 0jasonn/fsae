#include "engine/functions.h"
#include "global.h"
#include "enemy/em16.h"
// Actor em16 (module em16), unit 1. Address -> name:
//   0x0203cfcc Em16 (entry, EnemyFunctionHandler on em16_stateTable)
//   0x0203cfe0 em16_normal
// Not matched (best attempts in scratch/agentB/nonmatching): em16_damage 0x0203cffc, em16_getdir 0x0203d1a4,
// em16_move 0x0203d218.

// Entry of the actor: runs the state handler for the current action.
ARM void Em16(Entity *e) {
    EnemyFunctionHandler(e, em16_stateTable);
}

// Runs the handler for the current action.
ARM void em16_normal(Entity *e) {
    em16_actionTable[e->action](e);
}
