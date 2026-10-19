#include "engine/functions.h"
#include "object/block_neta.h"
#include "global.h"

// Block (neta) actor (module block_neta). Address -> name:
//   0x02059d74 block_neta_typeDispatch (provisional, block_neta_typeActions[e->type](e))

ARM void block_neta_typeDispatch(Entity *e) {
    block_neta_typeActions[e->type](e);
}
