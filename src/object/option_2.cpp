#include "object/option.h"

// Option panel screen, second unit (module option). Address -> name:
//   0x0205c1c4 panel_copy, 0x0205c1e0 copy_init

ARM void panel_copy(Entity *e) {
    panel_copy_actions[e->action](e);
}

ARM void copy_init(Entity *e) {
    e->action = 1;
    e->spriteSettings.b0 = 2;
    e->spriteSettings.b14 = 3;
}
