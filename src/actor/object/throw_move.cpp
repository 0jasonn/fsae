#include "engine/functions.h"
#include "global.h"
#include "actor/object/tama11.h"

// throw_move (0x02080494): while the child keeps the object kind and id that throw_init copied and has reached action 2,
// waits for the player (special state, flag at 0x71 of the player's object clear) and then starts the throw with
// throwinit. If the child changed or is not in action 2, the object is removed.
void throw_move(Entity *e) {
    Entity *child;
    Entity *player;
    u8 type;

    child = e->child;
    type = e->type;
    player = playerWork[type].entity;
    if (VARS(Tama11Vars, e)->copiedKind == child->objKind || VARS(Tama11Vars, e)->copiedId == child->objId) {
        if (child->action != 2) {
            func_02089988(&playerWork[type]);
            PutObjWork(e);
            return;
        }
        if (playerWork[type].specialState != 0 && player->unk_6c[5] == 0) {
            return;
        }
        throwinit(e);
        e->subAction++;
        e->direction = 0xff;
        e->zVelocity = 0;
        return;
    }
    func_02089988(&playerWork[type]);
    PutObjWork(e);
}
