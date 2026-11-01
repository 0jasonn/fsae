#ifndef UNKNOWN_WIP_F_SET1A_H
#define UNKNOWN_WIP_F_SET1A_H

#include "engine/entity.h"

// Set1a / parasw actor tables (file-local declarations, not shared).
extern const EntityFunc set1a_actions[];     // set1a_actions, indexed by e->action
extern const EntityFunc set1a_typeActions[]; // set1a_typeActions, indexed by e->type2 (see set1a_typeDispatch)
extern const EntityFunc parasw00_actions[];  // parasw00_actions, indexed by e->action

#endif
