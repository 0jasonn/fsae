#include "object/option.h"

// Option panel screen, first unit (module option). Address -> name:
//   0x0205c03c win_open, 0x0205c070 open_init

ARM void win_open(Entity *e) {
    if (data_021349c0[NP_PANEL_STATE] & 0x80) {
        e->action = 1;
    }
    win_open_actions[e->action](e);
}

ARM void open_init(Entity *e) {
    e->action = 2;
    data_021349c0[NP_PANEL_STATE] = 0xc3;
}
