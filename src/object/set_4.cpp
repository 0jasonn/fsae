#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Set actor helpers (module set). Address -> name:
//   0x02057ca8 set0a_init (original name)
//   0x02057ccc set0a_wait (original name)
//   0x02057e4c set_runAction (provisional, dispatches e->action through data_02115398)
//   0x02057e68 set00itemSetEntry (provisional, tail call to set00itemSet)
//   0x02057ef4 set0b_wait (original name)
//   0x02057f30 set0b_itemAdd (provisional, tail call to SetItemAdd with e->contactedEntity)
//   0x02057fcc set0b_lift (original name)
//   0x02057fec Set0c (original name)

ARM void set0b_lift(Entity *e) {
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    PutObjWork(e);
}

ARM void Set0c(Entity *e) {
    data_020d8860[e->action](e);
}
