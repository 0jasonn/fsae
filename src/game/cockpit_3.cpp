#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Functions in this file (module cockpit, original names): CockpitRecovery, cockpit_load

// Redraws the heart or rupee part of the cockpit for a given value (a is the kind, b the amount).
ARM void CockpitRecovery(u8 kind, u8 amount) {
    if (data_0212c618[0] == 0) {
        return;
    }
    if (kind < 4) {
        func_02027778();
        heart_disp();
        func_02026774();
        return;
    }
    if (kind + amount < 0x10) {
        return;
    }
    rupee_disp();
    addrupee_disp();
    func_02026774();
}

// Loads the cockpit graphics: data 1, then the copy of the cockpit block.
ARM void cockpit_load(void) {
    DataLoad(1);
    func_02027778();
    MIi_CpuCopyFast(data_021361a0, data_021369a0, 0x800);
}
