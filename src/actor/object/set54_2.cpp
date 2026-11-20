#include "engine/functions.h"
#include "engine/player.h"
#include "actor/object/rewdoor_knife.h"
#include "actor/object/set54_actions.h"
#include "global.h"

// Set54 door actor (module set54). Address -> name:
//   0x02071b6c set54_open (original name)
//   0x02071bec set54_move (original name)

// Waits out the timer, then rewrites the door cells to the open state and plays the sound.
void set54_open(Entity *e) {
    const u16 *table;

    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->timer = 4;
    e->action = 2;
    if (gameState.unk_01 == 1) {
        table = set54_openTableG1 + ((e->type & 3) * 6 + e->type2);
    } else {
        table = set54_openTableG0 + ((e->type & 3) * 6 + e->type2);
    }
    knife_rewDoor(e, table);
    func_02085f98(e, 0x11);
}

// Waits out the timer, then rewrites the door cells to the closed state and releases the object.
void set54_move(Entity *e) {
    const u16 *table;

    e->timer--;
    if (e->timer != 0) {
        return;
    }
    if (gameState.unk_01 == 1) {
        if (e->type & 4) {
            table = set54_moveTableG1B + ((e->type & 3) * 6 + e->type2);
        } else {
            table = set54_moveTableG1A + ((e->type & 3) * 6 + e->type2);
        }
    } else {
        if (e->type & 4) {
            table = set54_moveTableG0B + ((e->type & 3) * 6 + e->type2);
        } else {
            table = set54_moveTableG0A + ((e->type & 3) * 6 + e->type2);
        }
    }
    knife_rewDoor(e, table);
    PutObjWork(e);
}
