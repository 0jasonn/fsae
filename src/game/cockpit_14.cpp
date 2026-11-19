#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Cockpit (HUD), fourteenth unit: CockpitOn (0x02026720).

// Turns the cockpit on: loads the background set, updates the screen and copies the page to the bg buffer.
void CockpitOn(void) {
    cockpitState.mode = 1;
    cockpit_obj_set(0);
    func_02027778();
    bg_trans_body();
    cockpitState.transMask = 1 << cockpitState.bufferIndex;
    MIi_CpuCopyFast(data_021361a0 + cockpitState.bufferIndex * 0x800, data_021361a0 + ((cockpitState.bufferIndex ^ 1) * 0x800), 0x140);
    CockpitUpdate();
}
