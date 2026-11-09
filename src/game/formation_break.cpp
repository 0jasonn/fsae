#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "actor/enemy/decls_b.h"
#include "game/formation_break.h"

// Formation break in single play: when the active player's call state is set, control passes to the other player
// (index ^ 1) unless that one is calling too, in which case it goes to player 0.
void FormationBreak(void) {
    void *app;
    u8 *instance;
    u8 index;
    u8 value;
    int other;

    app = KnifeApp_getInstance();
    if (KnifeApp_isWirelessMode(app) != 0) {
        return;
    }
    instance = Knife_Single_SinglePlay_GetInstance();
    index = *instance;
    value = index;
    if (playerWork[index].callState != 0) {
        other = index ^ 1;
        if (playerWork[other].callState == 0) {
            value = other;
        } else {
            value = 0;
        }
    }
    Knife_Single_SinglePlay_SetContNo(instance, value);
}
