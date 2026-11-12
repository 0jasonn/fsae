#include "engine/functions.h"
#include "global.h"
#include "knife/app/knife_hud_setactiveplayer.h"

// Functions in this file (original names from the debug build):
//   HudManager::setActivePlayer (0x0209e31c)

// Interpolation function with reference parameters (Knife::Interp<VecFx32>::fn)
typedef VecFx32 (*KnifeInterpRefFn)(const VecFx32 &a, const VecFx32 &b, s32 t);

// Knife::Interp<VecFx32>::start (inline in the original): sets the function and both ends, rewinds the time and
// computes the first value
static inline void KnifeHudInterp_start(KnifeHudInterp *interp, KnifeInterpRefFn fn, const VecFx32 &a,
                                        const VecFx32 &b) {
    interp->fn = (void *)fn;
    interp->a = a;
    interp->b = b;
    interp->t = 0;
    if (interp->fn != NULL) {
        interp->value = ((KnifeInterpRefFn)interp->fn)(interp->a, interp->b, interp->t);
    } else if (interp->t >= 0x1000) {
        interp->value = interp->b;
    } else {
        interp->value = interp->a;
    }
}

namespace Knife {
namespace Hud {

// HudManager::setActivePlayer(int) (0x0209e31c): a negative player means none. Moves the two equip icons between
// their idle and active positions, or swings them for the new player, and sends the palette of the unactive icon.
void HudManager::setActivePlayer(int player) {
    KnifeHudVars *v = (KnifeHudVars *)this;
    s32 previous;
    EquipIconPositions idle;
    EquipIconPositions active;

    if (player < 0) {
        player = -1;
    }
    previous = v->activePlayer;
    if (previous == player) {
        return;
    }
    idle = data_020ddd5c;
    active = data_020ddd74;
    v->activePlayer = player;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
        Knife_Hud_HudManager_transferUnactiveEquipIconBasePalette(this, 0);
        return;
    }
    if (v->activePlayer < 0) {
        KnifeHudInterp_start(&v->interp[0], Knife::Interp_VecFx32_Linear, idle.pos[0], active.pos[0]);
        KnifeHudInterp_start(&v->interp[1], Knife::Interp_VecFx32_Linear, idle.pos[1], active.pos[1]);
        v->field6c = 0x400;
        Knife_Hud_HudManager_transferUnactiveEquipIconBasePalette(this, 1);
    } else if (previous < 0 && v->activePlayer >= 0) {
        KnifeHudInterp_start(&v->interp[0], Knife::Interp_VecFx32_Linear, active.pos[0], idle.pos[0]);
        KnifeHudInterp_start(&v->interp[1], Knife::Interp_VecFx32_Linear, active.pos[1], idle.pos[1]);
        v->field6c = 0x400;
        if (v->activePlayer < 2) {
            Knife_Hud_HudManager_transferUnactiveEquipIconBasePalette(this, 1 - v->activePlayer);
        }
    } else {
        KnifeInterpRefFn first;
        KnifeInterpRefFn second;
        if (v->activePlayer == 0) {
            first = (KnifeInterpRefFn)Knife_Hud_HudManager_interp_EquipIcon;
            second = Knife::Interp_VecFx32_None;
        } else {
            first = Knife::Interp_VecFx32_None;
            second = (KnifeInterpRefFn)Knife_Hud_HudManager_interp_EquipIcon;
        }
        KnifeHudInterp_start(&v->interp[0], first, idle.pos[0], idle.pos[0]);
        KnifeHudInterp_start(&v->interp[1], second, idle.pos[1], idle.pos[1]);
        v->field6c = 0x199;
        if (v->activePlayer < 2) {
            Knife_Hud_HudManager_transferUnactiveEquipIconBasePalette(this, 1 - v->activePlayer);
        }
    }
}

}
}
