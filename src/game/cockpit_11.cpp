#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/app/knife_hud.h"
#include "game/cockpit_9.h"

extern const u8 data_020ce4d0[];
extern u8 data_0212c4a8[];

// Tile object parameters at data_0212c4a0: two entries with a 32-bit and a 16-bit control word each.
typedef struct HudTileObj {
    u32 unk_00;
    u32 unk_04;
    u32 sizeLo : 8;      // 0x08
    u32 unk_08b : 8;
    u32 sizeHi : 9;
    u32 unk_08c : 5;
    u32 mode : 2;
    u16 tile : 10;       // 0x0c
    u16 unk_0cb : 2;
    u16 palette : 4;
    u32 sizeLo2 : 8;     // 0x10
    u32 unk_10b : 8;
    u32 sizeHi2 : 9;
    u32 unk_10c : 5;
    u32 mode2 : 2;
    u16 tile2 : 10;      // 0x14
    u16 unk_14b : 2;
    u16 palette2 : 4;
} HudTileObj;

extern HudTileObj data_0212c4a0;

// CockpitInit() (0x020264f4): clears the HUD block, activates it, starts the Knife HUD manager and sets up the two tile
// objects (their size, mode, tile number and palette) before the first CockpitUpdate.
void CockpitInit(void) {
    u8 *app;

    OSi_CpuClear32(0, cockpitState, 0x30);
    cockpitState[0] = 1;
    displayState.unk_8 = *(u16 *)(data_020ce4d0 + 0x24);
    cockpitState[3] = 0;
    cockpitState[2] = 1;
    app = (u8 *)KnifeApp_getInstance();
    cockpit_load();
    ((Knife::Hud::HudManager *)(app + 0x1f8))->initialize();
    ((Knife::Hud::HudManager *)(app + 0x1f8))->setStateNone();
    ((Knife::Hud::HudManager *)(app + 0x1f8))->setActivePlayer(0xff);
    MemClearFast(data_0212c4a8, 0x10);
    data_0212c4a0.sizeHi = 0xd4;
    data_0212c4a0.sizeLo = 0xa;
    data_0212c4a0.mode = 1;
    data_0212c4a0.tile = 0x2e8;
    data_0212c4a0.palette = 4;
    data_0212c4a0.sizeHi2 = 0xec;
    data_0212c4a0.sizeLo2 = 0xa;
    data_0212c4a0.mode2 = 1;
    data_0212c4a0.tile2 = 0x2ec;
    data_0212c4a0.palette2 = 4;
    cockpitState[0x2c] = 0xff;
    cockpitState[0xc] = 0xff;
    cockpitState[7] = 0xff;
    CockpitUpdate();
}
