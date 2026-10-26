#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

// Functions in this file (original names from the debug build):
//   subTask_radar_end (0x020a6f98)

extern "C" void subTask_radar_end(void);

extern u8 data_0212c7c8[];
extern u8 frameCounter[];
extern u8 data_0217a258[];

// subTask_radar_end() (0x020a6f98): frees the four radar slots and the OBJInfo, and starts the fade out when the
// game-state flags are clear
ARM void subTask_radar_end(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        subTask_free_slot(i);
    }
    subTask_free_objinfo((OBJInfo *)data_0217a258);
    if (data_0212c7c8[0x8c] == 0 && frameCounter[0x11] == 0) {
        eff_fade_out_init(0x1000);
    }
}
