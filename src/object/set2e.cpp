#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// Set2e actor (module set2e). Address -> name:
//   0x0205a9f8 Set2e (dispatcher, dsd name Set2e), dispatches through set2e_actions
//   0x0205aa14 set2e_init (original name)

extern const EntityFunc set2e_actions[]; // set2e_actions, indexed by e->action
extern PlayerData *data_0212c53c;        // current player slot pointer (see game/multiplay.h)
void set2e_move(Entity *e);

ARM void Set2e(Entity *e) {
    set2e_actions[e->action](e);
}

ARM void set2e_init(Entity *e) {
    PlayerData *player;

    if (e->type == 0) {
        e->spriteSettings.b0 = 1;
        player = data_0212c53c;
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
            player = &data_0212ceb0[*Knife_Single_SinglePlay_GetInstance()];
        }
        e->spriteSettings.b16 = (player->entity->type + 7) & 0xf;
        e->contactedEntity = player->entity;
    } else {
        e->spriteSettings.b0 = 2;
    }
    e->spriteSettings.b14 = 0;
    e->spriteSettings.b30 = 1;
    e->timer = e->type2;
    e->action++;
    InitAnimationForceUpdate(e, 0);
    set2e_move(e);
}
