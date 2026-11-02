#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit_9.h"

// mapmode_move() (0x02026a34): steps the map screen of the HUD. While the map is allowed it advances the step byte
// (3 and 4 draw the frame and the key counters, 5 puts the map markers), otherwise it closes the map and redraws.
void mapmode_move(void) {
    if (!(data_0212c584[localPlayerIndex] & 0x400) || (u8)(messageRequest[0] & 0x7f) != 0 || frameCounter[0x11] != 0 ||
        data_0212c7c8.unk_6e >= 2 || data_0212c618[HUD_ACTIVE] != 1) {
        data_0212c618[HUD_MAP_STEP] = 0;
        data_0212c618[HUD_CLEAR_MASK] = 1 << (data_0212c618[HUD_BUFFER] ^ 1);
        data_0212c75c.reg66 = 0;
        data_0212c75c.displayFlags &= ~0x4000;
        MIi_CpuClearFast(0, data_021361a0 + (data_0212c618[HUD_BUFFER] << 11) + 0x140, 0x280);
        func_02026774();
    } else {
        switch (data_0212c618[HUD_MAP_STEP]) {
        case 1:
        case 2:
            data_0212c618[HUD_MAP_STEP]++;
            break;
        case 3:
        case 4:
            fill_rect(0xb, 6, 8, 8);
            kakera_disp();
            kinomi_disp();
            func_02026774();
            data_0212c618[HUD_MAP_STEP]++;
            break;
        case 5:
            MapMarkerSet();
            data_0212c618[HUD_MAP_STEP]++;
            break;
        }
        if (data_0212c618[HUD_LAST_VALUE] != data_0212c830[localPlayerIndex]) {
            data_0212c618[HUD_LAST_VALUE] = data_0212c830[localPlayerIndex];
            data_0212c618[HUD_REDRAW] = 1;
        }
    }
}
