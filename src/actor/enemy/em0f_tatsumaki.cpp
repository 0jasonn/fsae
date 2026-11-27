#include "engine/functions.h"
#include "engine/entity.h"
#include "engine/player.h"
#include "engine/map_state.h"
#include "engine/cockpit_state.h"
#include "engine/misc.h"
#include "engine/local_player_index.h"
#include "actor/enemy/em0f_2.h"

// em0f_setTatsumaki(OBJ_WORK_*), 0x0202de80: whirlwind (tatsumaki) phase of em0f. Rebinds the camera target to the
// players when it was moved, spawns three whirlwind children (enemy 0x29) at timer 0x30, 0x18 and 0, then switches to action 5
// and gives the camera and HUD back to the local (wireless) or controlled (single play) player.
void em0f_setTatsumaki(Entity *e) {
    void *app;
    Entity *child;
    Vars_Em0f *vars = VARS(Vars_Em0f, e);

    app = KnifeApp_getInstance();
    if ((KnifeApp_isWirelessMode(app) != 0 && mapState.target != playerWork[localPlayerIndex].entity) ||
        (KnifeApp_isWirelessMode(app) == 0 && mapState.target != playerWork[0].entity &&
         mapState.target != playerWork[1].entity)) {
        BindPlayers();
    }

    e->timer--;
    switch (e->timer) {
    case 0x30:
        child = GetEnemyWork(0x29);
        if (child != NULL) {
            child->type2 = 1;
            ObjPosCopy(e, child);
            child->parent = e;
            e->parent = child;
            e->child = child;
            vars->tatsumakiCount++;
        }
        break;
    case 0x18:
        child = GetEnemyWork(0x29);
        if (child != NULL) {
            child->type = 1;
            ObjPosCopy(e, child);
            child->parent = e;
            e->child->child = child;
            e->child = child;
            vars->tatsumakiCount++;
        }
        break;
    case 0:
        child = GetEnemyWork(0x29);
        if (child != NULL) {
            child->type = 2;
            ObjPosCopy(e, child);
            child->parent = e;
            e->child->child = child;
            vars->tatsumakiCount++;
        }
        e->action = 5;
        e->timer = 0x3c;
        app = KnifeApp_getInstance();
        if ((KnifeApp_isWirelessMode(app) != 0 && mapState.target != playerWork[localPlayerIndex].entity) ||
            (KnifeApp_isWirelessMode(app) == 0 && mapState.target != playerWork[0].entity &&
             mapState.target != playerWork[1].entity)) {
            if (KnifeApp_isWirelessMode(app) != 0) {
                mapState.target = playerWork[localPlayerIndex].entity;
            } else {
                mapState.target = playerWork[*Knife_Single_SinglePlay_GetInstance()].entity;
            }
            cockpitState.mode = 1;
            Scene_ClearFlag5();
            CockpitOn();
            SoundReq(0x19c);
        }
        break;
    }
    UpdateAnimationSingleFrame(e);
}
