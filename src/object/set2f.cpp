#include "engine/functions.h"
#include "global.h"
#include "object/set2f.h"

// Set2f actor and its lever helper (module set2f). Address -> name:
//   0x0205aed8 Set2f (original name), dispatches through set2f_actions
//   set2f_init at 0x0205af04 is in scratch/agentF/nonmatching/set2f_init.c
//   0x0205afac set2f_move (original name)
//   0x0205b024 rewlever (original name)

extern const EntityFunc set2f_actions[]; // set2f_actions, indexed by e->action
extern const u8 data_020d8a54[];         // hitbox of the lever
extern u32 em12_typeMasks[];
extern const u32 flagBits[];             // flagBits, indexed by e->type
extern Set2fGridOrigin data_0212c648;

void rewlever(Entity *e);

void Set2f(Entity *e) {
    if (e->iframes == 0) {
        VARS(Vars_Set2f, e)->triggered = 0;
    }
    set2f_actions[e->action](e);
}
