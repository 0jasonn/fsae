#include "engine/functions.h"
#include "global.h"
#include "object/cellcalls.h"

// Set3f actor (module set3f). Address -> name:
//   0x0205dc90 Set3f (original name), 0x0205dcac set3f_init, 0x0205dcec set3f_nop (renamed from set3f_nop),
//   0x0205dcf0 set3f_typeDispatch (renamed from set3f_typeDispatch)

extern const EntityFunc data_020d8c6c[]; // state table indexed by e->action
extern const EntityFunc data_020d8c8c[]; // state table indexed by e->type

ARM void Set3f(Entity *e) {
    data_020d8c6c[e->action](e);
}

ARM void set3f_init(Entity *e) {
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_5e.b0 = 0;
    func_0208ae78(e);
    InitAnimationForceUpdate(e, e->type);
}

ARM void set3f_nop(Entity *e) {
}

ARM void set3f_typeDispatch(Entity *e) {
    data_020d8c8c[e->type](e);
}
