#include "engine/functions.h"
#include "object/coin.h"
#include "global.h"

// Coin actor (module coin). Address -> name:
//   0x02058890 coin (original name)
//   0x020588ac coin_init: not matching yet, see scratch/agentF/nonmatching

ARM void coin(Entity *e) {
    coin_actions[e->action](e);
}
