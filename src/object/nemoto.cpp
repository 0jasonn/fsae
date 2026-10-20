#include "engine/functions.h"
#include "global.h"
#include "object/set40.h"

// nemoto family (module nemoto), 0x0206c18c .. 0x0206c1c8.
// Address -> name: 0x0206c18c nemoto_init (original nemoto_init)

ARM void nemoto_init(Entity *e) {
    e->action = 1;
    e->spriteSettings.b0 = 1;
    InitAnimationForceUpdate(e, e->type + 4);
    func_0208ae78(e);
}
