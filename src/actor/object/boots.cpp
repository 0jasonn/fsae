#include "engine/functions.h"
#include "global.h"
#include "actor/object/template.h"
#include "game/hitdecls.h"
#include "engine/player.h"

// Boots actor (module boots). Original names from the debug build:
//   Boots, boots_init, boots_move, plsync (boots_plsync)

extern const EntityFunc data_020ce524[]; // state handlers, indexed by e->action
extern u8 data_0212c4b8; // non-zero while the object update is frozen
extern const s8 data_020ce52c[]; // hitbox offsets, four bytes per pair of animation states
extern const s8 data_020ce51c[]; // (x, y) offsets per animation state, pairs of signed bytes

void boots_move(Entity *e);
void boots_plsync(Entity *e, Entity *tmpl);
void func_02084180(Entity *e);

// Boots main: runs the state handler while the game is not frozen, then the common object update.
void Boots(Entity *e) {
    if (data_0212c4b8 == 0) {
        data_020ce524[e->action](e);
    }
    func_020857c8(e);
}
