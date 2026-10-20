#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/set58.h"
#include "object/d_decls.h"

// Set59 actor (module set59). Address -> name:
//   0x0207432c Set59 (original name; dispatches on e->action)
//   0x02074348 set59_init (original name)
//   0x020743f0 set59_move (original name)

extern const EntityFunc set59_actions[]; // set59_actions, indexed by e->action
extern const u16 set59_colorTable[];     // set59_colorTable, indexed by rank

ARM void Set59(Entity *e) {
    set59_actions[e->action](e);
}

ARM void set59_init(Entity *e) {
    s32 rank;

    e->spriteSettings.b0 = 1;
    e->action = 1;
    e->unk_5e.b0 = 3;
    e->spriteSettings.b30 = 0;
    e->spriteSettings.b14 = 0;
    rank = RankCheck();
    if (rank == 3) {
        rank = (u8)(rank + data_0212c7c8.unk_1[0]);
    }
    e->spriteSettings.b20 = GetObjColor((u8)set59_colorTable[rank]);
    e->spriteSettings.b16 = e->spriteSettings.b20;
    InitAnimationForceUpdate(e, data_0212c7c8.unk_1[0]);
}

ARM void set59_move(Entity *e) {
    em12_typeMasks |= 0x80;
    if (em12_typeMasks & 0x100) {
        PutObjWork(e);
    }
}
