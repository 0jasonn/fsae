#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/objdecls_a.h"

extern EntityFunc set37Table[];        // set37Table, indexed by action
extern const u8 set37Hitbox[];         // set37Hitbox
extern const s8 set37BobTable[];       // set37BobTable, indexed by timer & 7
extern u16 frameCounter;              // frame counter

// Set37, 0x0206b5b8: runs the state function for the current action.
void set37(Entity *e) {
    set37Table[e->action](e);
}

// Set37 actor (module set37), third unit: set37_init (0x0206b5d4), between Set37 and set37_move.

extern const u8 set37Hitbox[]; // set37Hitbox

// Starts the object: next state, sprite flags, hitbox and status, and moves it 4 up (y - 4, z = 0x55 - 0x59).
void set37_init(Entity *e) {
    e->action++;
    e->unk_2e = 1;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b4 = 1;
    e->hitbox = set37Hitbox;
    e->unk_40 = 0x38;
    e->poseId = 0x1f;
    e->statusFlags = 0xd9;
    e->unk_5c = 0x55;
    e->y.HALF.HI -= 4;
    e->z.HALF.HI = 0x55 - 0x59;
}
