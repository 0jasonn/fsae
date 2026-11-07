#include "engine/functions.h"
#include "global.h"
#include "engine/k_decls.h"

// Set67 actor (module set67): set67_init (0x020755c0)

// set67_init(e) (0x020755c0): shows the object, starts action 1 and its animation. unk_5e is cleared twice (the original
// wrote it twice; one write gives different code).
void set67_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->action = 1;
    e->unk_5e.b0 = 0;
    e->unk_5e.b0 = 0;
    e->spriteSettings.b14 = 3;
    InitAnimationForceUpdate(e, e->type);
}
