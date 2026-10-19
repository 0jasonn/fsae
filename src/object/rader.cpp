#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"

// Rader (radar) parent and child actors (module rader). Address -> name:
//   0x0206305c Set10, 0x020630b0 raderParent (original names)

extern const EntityFunc data_02115a5c[]; // indexed by e->action (parent)
extern Entity *data_0212c838[]; // child entity per type2 (set while the child is active)

void raderChild(Entity *e);
void raderParent(Entity *e);

ARM void Set10(Entity *e) {
    if (e->type == 0) {
        raderParent(e);
        return;
    }
    raderChild(e);
    data_0212c838[e->type2] = (e->spriteSettings.b0 != 0) ? e : NULL;
    e->spriteSettings.b0 = 0;
}

ARM void raderParent(Entity *e) {
    data_02115a5c[e->action](e);
}
