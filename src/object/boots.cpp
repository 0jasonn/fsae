#include "engine/functions.h"
#include "global.h"
#include "object/template.h"
#include "game/hitdecls.h"

// Boots actor (module boots). Original names from the debug build:
//   Boots, boots_init, boots_move, plsync (boots_plsync)

extern const EntityFunc data_020ce524[]; // state handlers, indexed by e->action
extern u8 data_0212c4b8; // non-zero while the object update is frozen
extern u8 data_0212cece[]; // one flag byte per template entry (0x94 apart): non-zero while the boots are worn
extern u8 data_0212ceb0[]; // one byte per template entry (0x94 apart), read at offset 0x3e
extern u8 data_0212cedc[]; // second pointer of each template entry: the boots object currently in use for this type
extern const s8 data_020ce52c[]; // hitbox offsets, four bytes per pair of animation states
extern const s8 data_020ce51c[]; // (x, y) offsets per animation state, pairs of signed bytes

void boots_move(Entity *e);
void boots_plsync(Entity *e, Entity *tmpl);
void func_02084180(Entity *e);

// Boots main: runs the state handler while the game is not frozen, then the common object update.
ARM void Boots(Entity *e) {
    if (data_0212c4b8 == 0) {
        data_020ce524[e->action](e);
    }
    func_020857c8(e);
}
