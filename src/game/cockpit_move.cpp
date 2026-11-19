#include "engine/functions.h"
#include "engine/player.h"
#include "engine/cockpit_state.h"
#include "engine/frame_counter.h"
#include "engine/telop_request.h"
#include "engine/misc.h"
#include "game/cockpitdata.h"
#include "game/cockpit_move.h"

// cockpit_move() (0x02026e4c): per-frame HUD logic. Counts down the rupee gain and loss display timers, updates the
// katti, rupee and heart displays, refreshes the item graphics when the held item (or its flag) of a player changes,
// and counts down the per-player kakera timers that follow a heart pinch.
void cockpit_move(void) {
    s8 i;
    u8 zero;
    PlayerData *second;

    zero = 0;
    cockpitState.redraw = 1;
    if (cockpitState.rupeeLossTimer != 0) {
        if (cockpitState.rupeeLossTimer == 1) {
            cockpitState.rupeeLossTimer = 0;
            cockpitState.rupeeShown = 0;
            cockpitState.rupeeLoss = 0;
            if (cockpitState.rupeeGainTimer != 0) {
                cockpitState.rupeeShown = cockpitState.rupeeGain;
            }
            cockpitState.redraw = 1;
        } else if (frameCounter.pauseRequest == 0) {
            cockpitState.rupeeLossTimer = cockpitState.rupeeLossTimer - 1;
        }
    } else if (cockpitState.rupeeGainTimer != 0) {
        if (cockpitState.rupeeGainTimer == 1) {
            cockpitState.rupeeGainTimer = 0;
            cockpitState.rupeeShown = 0;
            cockpitState.rupeeGain = 0;
            cockpitState.redraw = 1;
        } else if (frameCounter.pauseRequest == 0) {
            cockpitState.rupeeGainTimer = cockpitState.rupeeGainTimer - 1;
        }
    }
    kattiUpdate();
    rupeeUpdate();
    heartUpdate(data_0212c82c[localPlayerIndex]);
    if (cockpitState.item != data_0212c53c->unk_1c) {
        cockpitState.item = data_0212c53c->unk_1c;
        cockpitState.itemState = data_0212c53c->unk_0f & 2;
        make_item_color();
        make_item_char();
        cockpitState.redraw = 1;
    }
    if ((data_0212c53c->unk_0f & 2) != cockpitState.itemState) {
        cockpitState.itemState = data_0212c53c->unk_0f & 2;
        make_item_color();
    }
    if (!KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
        second = &playerWork[1];
        if (cockpitState.item2p != second->unk_1c) {
            cockpitState.item2p = second->unk_1c;
            cockpitState.itemState2p = second->unk_0f & 2;
            make_item_color_2p();
            make_item_char_2p();
            cockpitState.redraw = 1;
        }
        if ((second->unk_0f & 2) != cockpitState.itemState2p) {
            cockpitState.itemState2p = second->unk_0f & 2;
            make_item_color_2p();
        }
    }
    heartAlart();
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
        for (i = 0; i < gameState.playerCount; i++) {
            if (cockpitState.kakeraTimer[i] == 0 && gameState.playerFlag68[i] >= 4) {
                Entity *player = playerWork[i].entity;
                EffectSet(player, 0x15, zero);
                TelopRequest(0x517);
                telopRequest.params[0] = (u16)(player->type + 1);
                telopRequest.params[2] = 500;
            }
            cockpitState.kakeraTimer[i] = cockpitState.kakeraTimer[i] - 1;
        }
    } else {
        if (cockpitState.kakeraTimer[0] == 0 && gameState.playerFlag68[0] >= 4) {
            Entity *player = playerWork[0].entity;
            Entity *player2 = playerWork[1].entity;
            EffectSet(player, 0x15, zero);
            EffectSet(player2, 0x15, zero);
            TelopRequest(0x517);
            telopRequest.params[0] = (u16)(player->type + 1);
            telopRequest.params[2] = 500;
        }
        cockpitState.kakeraTimer[0] = cockpitState.kakeraTimer[0] - 1;
    }
}
