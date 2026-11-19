#include "engine/functions.h"
#include "engine/player.h"
#include "engine/radar_status.h"
#include "engine/cockpit_state.h"

extern u8 data_0212c82c[]; // per-type maximum hearts (heartKind)

// CockpitUpdate (0x02026628): refreshes the HUD block from the game state: the rupee count, the item state bit of the
// current player (and of the second player outside wireless play), the displayed hearts and the heart kind; then
// requests a redraw. The hearts are 0 when one of the first two players has no health (and it is not a wireless game).
void CockpitUpdate(void) {
    void *app;

    cockpitState.rupees = gameState.score;
    cockpitState.itemState = data_0212c53c->unk_0f & 2;
    app = KnifeApp_getInstance();
    if (KnifeApp_isWirelessMode(app) != 0 || (playerWork[0].entity->health != 0 && playerWork[1].entity->health != 0)) {
        cockpitState.hearts = data_0212c53c->entity->health;
    } else {
        cockpitState.hearts = 0;
    }
    cockpitState.heartKind = data_0212c82c[data_0212c53c->entity->type];
    if (KnifeApp_isWirelessMode(app) == 0) {
        cockpitState.itemState2p = playerWork[1].unk_0f & 2;
    }
    cockpitState.redraw = 1;
}
