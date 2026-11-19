#include "engine/functions.h"
#include "actor/object/option.h"
#include "global.h"
#include "actor/object/object_handlers.h"

// Option panel (module option): 0x0205c158 open_move (original name) grows the panel window, then hands over to
// the copy actors by leaving action 0.

void open_move(Entity *e) {
    effectState.panelShown = 1;
    if (e->subtimer < 0x28) {
        e->subtimer += 4;
        displayState.win0V = (e->timer << 8) | (e->timer + e->subtimer);
    } else {
        displayState.displayFlags &= 0xdfff;
        effectState.panelState = e->type2;
        e->action = 1;
    }
}
