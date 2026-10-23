#include "engine/functions.h"
#include "object/tama02.h"

// tama02 family, address -> name (original names from symbols.txt):
//   0x0207e15c tama02_init, 0x0207e220 tama02_move (Tama02 at 0x0207e0b4 is parked in nonmatching)

// tama02_init, 0x0207e15c. Starts the actor on its partner: sets the timer and the facing, copies the partner's
// hitbox, and gives a player partner the state used while it is carried.
ARM void tama02_init(Entity *e) {
    PlayerData *player;
    e->action = 1;
    e->timer = 0x3c;
    e->type2 = 0;
    e->direction = GetFacingDirection(e, VARS(Vars_Tama02, e)->partner) << 3;
    e->z.WORD = 0;
    e->hitbox = VARS(Vars_Tama02, e)->partner->hitbox;
    VARS(Vars_Tama02, e)->swingTimer = 0x12c;
    VARS(Vars_Tama02, e)->resetTimer = (Random() & 0xf) + 0x18;
    if (VARS(Vars_Tama02, e)->partner->objKind == 1) {
        player = &data_0212ceb0[VARS(Vars_Tama02, e)->partner->type];
        player->state = 0xe;
        player->stateTimer = 0xc1;
        player->unk_39 = 2;
        player->unk_3a[0] = 0xff;
        VARS(Vars_Tama02, e)->partner->animationState = 0;
    } else if (VARS(Vars_Tama02, e)->partner->objKind == 8 && VARS(Vars_Tama02, e)->partner->objId == 4) {
        VARS(Vars_Tama02, e)->partner->unk_1a = (VARS(Vars_Tama02, e)->partner->unk_1a & 0xf0) | 6;
    }
}
