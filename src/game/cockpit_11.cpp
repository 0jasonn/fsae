#include "engine/functions.h"
#include "game/cockpit.h"
#include "global.h"
#include "types.h"
#include "knife/app/knife_hud.h"
#include "game/cockpit_9.h"
#include "engine/hud_tile_obj.h"


// CockpitInit() (0x020264f4): clears the HUD block, activates it, starts the Knife HUD manager and sets up the two tile
// objects (their size, mode, tile number and palette) before the first CockpitUpdate.
void CockpitInit(void) {
    u8 *app;

    OSi_CpuClear32(0, &cockpitState, sizeof(cockpitState));
    cockpitState.mode = 1;
    displayState.bg[0].cnt = *(u16 *)(data_020ce4d0 + 0x24);
    cockpitState.bufferIndex = 0;
    cockpitState.redraw = 1;
    app = (u8 *)KnifeApp_getInstance();
    cockpit_load();
    ((Knife::Hud::HudManager *)(app + 0x1f8))->initialize();
    ((Knife::Hud::HudManager *)(app + 0x1f8))->setStateNone();
    ((Knife::Hud::HudManager *)(app + 0x1f8))->setActivePlayer(0xff);
    MemClearFast(data_0212c4a0.entries, sizeof(data_0212c4a0.entries));
    data_0212c4a0.entries[0].sizeHi = 0xd4;
    data_0212c4a0.entries[0].sizeLo = 0xa;
    data_0212c4a0.entries[0].mode = 1;
    data_0212c4a0.entries[0].tile = 0x2e8;
    data_0212c4a0.entries[0].palette = 4;
    data_0212c4a0.entries[1].sizeHi = 0xec;
    data_0212c4a0.entries[1].sizeLo = 0xa;
    data_0212c4a0.entries[1].mode = 1;
    data_0212c4a0.entries[1].tile = 0x2ec;
    data_0212c4a0.entries[1].palette = 4;
    cockpitState.item2p = 0xff;
    cockpitState.item = 0xff;
    cockpitState.kattiKind = 0xff;
    CockpitUpdate();
}
