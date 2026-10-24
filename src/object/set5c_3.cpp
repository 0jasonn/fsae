#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Set5c actor, per-frame update and helpers (module set5c). Address -> name:
//   0x0205fb38 set5c_update (per-frame update: event check, state table, zelda_disp)
//   0x0205fb68 set5c_event_check (name from symbols.txt)
//   (zelda_disp at 0x0205fb9c is parked in scratch/agentC/nonmatching)
//   (set5d_init at 0x0205fbd4 is in the next unit)

ARM void set5c_update(Entity *e) {
    set5c_event_check(e);
    data_020d9028[e->action](e);
    zelda_disp(e);
}

ARM void set5c_event_check(Entity *e) {
    Entity *linked = e->linkedEntity;

    if (e->action == 0 || linked->unk_00[4] == 0) {
        return;
    }
    e->action = linked->unk_00[4];
    e->subAction = 0;
    linked->unk_00[4] = 0;
    linked->unk_00[2] = 1;
}
