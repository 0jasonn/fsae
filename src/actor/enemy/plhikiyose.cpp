#include "actor/enemy/em30.h"
#include "actor/enemy/em29.h"
#include "global.h"

// plhikiyose (0x02042044): pulls every player that is allowed to be dragged towards the enemy, then walks the entity
// list: entries of kind 2, 3 (moving) or 5 are nudged towards the enemy, kind 4 entries try to start a segment.
void plhikiyose(Entity *e) {
    Entity *end;
    Entity *node;
    u8 grabbed = 3;

    switch (gameState.playerCount) {
    case 4:
        if (movecheck(playerWork[3].entity)) {
            hikiyoseSet(e, playerWork[3].entity, e->speed);
        }
    case 3:
        if (movecheck(playerWork[2].entity)) {
            hikiyoseSet(e, playerWork[2].entity, e->speed);
        }
    case 2:
        if (movecheck(playerWork[1].entity)) {
            hikiyoseSet(e, playerWork[1].entity, e->speed);
        }
    default:
        if (movecheck(playerWork[0].entity)) {
            hikiyoseSet(e, playerWork[0].entity, e->speed);
        }
    }
    end = (Entity *)&data_0212c6b0[2];
    node = (Entity *)data_0212c6b0[2].next;
    if (node == NULL || end == node) {
        return;
    }
    do {
        switch (node->objId) {
        case 3:
        case 5:
            if (node->speed == 0) {
                break;
            }
        case 2:
            func_020852f8(node, e->speed + 0x80, GetFacingDirection(node, e));
            break;
        case 4:
            if (*(u16 *)&node->unk_64[0] != 0) {
                break;
            }
            if (node->action == 2 && node->subAction < 2) {
                break;
            }
            if (hikiyoseSet(e, node, e->speed + 0x80)) {
                node->subAction = grabbed;
            }
            break;
        }
        node = (Entity *)((EntityNode *)node)->next;
    } while (end != node);
}
