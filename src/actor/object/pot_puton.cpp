#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/pot_puton.h"

// Pot actor, being carried (module pot). Address -> name:
//   0x0205f250 pot_puton (original name): keeps the carried pot attached while the holder keeps pressing, drops it otherwise

void pot_puton(Entity *e) {
    Vars_PotPuton *v = VARS(Vars_PotPuton, e);
    u8 playerIndex;

    e->statusFlags = 0;
    if ((v->heldKeys ^ 0xffff) & playerKeys[e->child->type]) {
        e->subtimer++;
        e->timer = 5;
        if (!m4aSongNumIsPlaying(0x229)) {
            EnqueueSFX(0x229);
        }
    }
    switch (e->child->action) {
    case 2:
    case 3:
    case 6:
    case 0x11:
        e->subtimer = pot_putonLimit;
        break;
    }
    if (!(playerWork[e->child->type].statusFlags & 4)) {
        e->subtimer = pot_putonLimit;
    }
    if (playerWork[e->child->type].statusFlags & 0x4c11) {
        e->subtimer = pot_putonLimit;
    }
    if (playerWork[e->child->type].hitFlags & 0x20) {
        e->subtimer = pot_putonLimit;
    }
    playerIndex = localPlayerIndex;
    if (!KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
        playerIndex = *Knife_Single_SinglePlay_GetInstance();
    }
    if (e->subtimer >= pot_putonLimit) {
        if (e->unk_6b != 0) {
            pot_remove(e);
        }
        playerWork[e->child->type].statusFlags &= ~4;
        pot_clash(e, NULL);
        return;
    }
    if (playerIndex == e->child->type) {
        if (((PaletteBitsView *)&playerWork[e->child->type].paletteBits)->low == 0 ||
            (playerWork[e->child->type ^ 1].statusFlags & 4)) {
            pot_ware(e);
            return;
        }
    }
    pot_remove(e);
}
